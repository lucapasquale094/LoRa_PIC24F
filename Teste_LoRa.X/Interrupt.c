//==================================================================================
//==                                                                              ==
//==                               VAGON ENGENHARIA                               ==
//==                                                                              ==
//==------------------------------------------------------------------------------==
//==              ==================================================              ==
//==                               == BB-LoRa-24 ==                               ==
//==              ==================================================              ==
//==------------------------------------------------------------------------------==

//==                                                                              ==
//== Módulo     : Interrupt.c                                                     ==
//== Descrição  : Módulo de Inicialização e Tratamento das Interrupções           ==
//==                                                                              ==
//==------------------------------------------------------------------------------==
//==                                                                              ==
//== Autor      : Nilton Gomes Valente - VAGON Engenharia LTDA                    ==
//== Email      : nilton@vagon.com.br                                             ==
//==                                                                              ==
//==================================================================================

//==================================================================================
//== FUNÇÕES DECLARADAS NESTE MÓDULO                                              ==
//==================================================================================
//----------------------------------------------------------------------------------
//--                                                                              --
//--                                                                              --
//--                                                                              --
//----------------------------------------------------------------------------------

//==================================================================================
//== INCLUDES                                                                     ==
//==================================================================================
#include "Interrupt.h"
#include "Main.h"
#include "Accel.h"
#include "Uart.h"

//==================================================================================
//== INSTÂNCIA DAS VARIÁVEIS GLOBAIS DECLARADAS NESTE MÓDULO                      ==
//==================================================================================
ST_TEMPORIZACAO stTemporizacao;

unsigned int wTimer1ContadorTempo_ms;
unsigned char byFlagTempo_ms;

unsigned int wTimer1ContadorTempo1s;

unsigned int wContadorTempo_s;
unsigned char byFlagTempo_s;

//==================================================================================
//== FUNÇÕES                                                                      ==
//==================================================================================
//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : void INTERRUPT_TIMER1Init(void)                                  --
//--                                                                              --
//-- Descrição : Inicializa o TIMER1                                              --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void INTERRUPT_TIMER1Init(void) {
    T1CONbits.TON = 0; // Timer1 desligado
    IEC0bits.T1IE = 0; // Interrupção desabilitada
    TMR1 = 0; // Zera o timer para início de contagem

    PR1 = 6000; // Configura o registrador de período [Tempo = 250us == PR1 = 1000]
    // PR1 = [ ( (FOSC / 2) * Tempo) / PS ]
    // OBS.: PR1 = 999 devido ao ajuste da Latência do Tratamento da Interrupção

    T1CONbits.TSIDL = 1; // Timer desligado em modo Idle    
    T1CONbits.T1ECS = 0; // Timer1 Extended Clock
    T1CONbits.TGATE = 0; // Gated Time Accumulation disabled 
    T1CONbits.TCKPS = 0; // Configura prescaler 1:1
    T1CONbits.TSYNC = 0; // Timer1 External Clock Sincronization
    T1CONbits.TCS = 0; // Modo timer (clock interno - FOSC/2)

    IPC0bits.T1IP = 7; // Prioridade = 7 (Mais Alta)
    IFS0bits.T1IF = 0; // Limpa flag
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : void INTERRUPT_TIMER1On(void)                                    --
//--                                                                              --
//-- Descrição : Liga o TIMER1                                                    --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void INTERRUPT_TIMER1On(void) {
    IFS0bits.T1IF = 0; // Limpa flag de interrupção
    IEC0bits.T1IE = 1; // Habilita interrupção do Timer1
    T1CONbits.TON = 1; // Timer1 ligado  
}


//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : void __attribute__((interrupt,auto_psv)) _ISR _T1Interrupt(void) --
//--                                                                              --
//-- Descrição : Tratamento da Interrupção do TIMER1                              --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void __attribute__((interrupt, auto_psv)) _ISR _T1Interrupt(void) {
    if (byFlagTempo_ms == FALSE) {
        wTimer1ContadorTempo_ms--;
        if (!wTimer1ContadorTempo_ms) {
            byFlagTempo_ms = TRUE;
        }
    }

    wTimer1ContadorTempo1s--;
    if (!wTimer1ContadorTempo1s) {
        wTimer1ContadorTempo1s = K_TEMPO_1_s;
        stTemporizacao.bFlag1s = TRUE;
        wContadorTempo_s--;
        if (!wContadorTempo_s) {
            byFlagTempo_s = TRUE;
        }
    }

    IFS0bits.T1IF = 0; // Limpa flag de interrupção
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Função    : void __attribute__((interrupt,auto_psv)) _ISR _INT0Interrupt(void) --
//--                                                                                --
//-- Descrição : Tratamento da INT0                                                 --
//--                                                                                --
//-- Entrada   : Nenhuma                                                            --
//--                                                                                --
//-- Saida     : Nenhuma                                                            --
//--                                                                                --
//------------------------------------------------------------------------------------
//void __attribute__((interrupt, auto_psv)) _ISR _INT1Interrupt(void)

void __attribute__((interrupt, auto_psv)) _ISR _INT1Interrupt(void) {
    Nop();
    Nop();
    Nop();

    byAccelINT = TRUE; // Sinaliza interrupção do acelerômetro

    byPIN_ACCEL = PIN_ON;

    IFS1bits.INT1IF = 0; // Limpa flag de interrupção
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Função    : void __attribute__((interrupt,auto_psv)) _ISR _U1RXInterrupt(void) --
//--                                                                                --
//-- Descrição : Tratamento da Interrupção de Dado Recebido pela UART1              --
//--                                                                                --
//-- Entrada   : Nenhuma                                                            --
//--                                                                                --
//-- Saida     : Nenhuma                                                            --
//--                                                                                --
//------------------------------------------------------------------------------------

void __attribute__((interrupt, auto_psv)) _ISR _U1RXInterrupt(void) {
    unsigned char byDadoRec1;

    byDadoRec1 = U1RXREG; // Leitura
    UART_UART1ProcessaByteRecebido(byDadoRec1);

    IFS0bits.U1RXIF = 0; //-- Limpa o Flag de Interrupção
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Função    : void __attribute__((interrupt,auto_psv)) _ISR _U1TXInterrupt(void) --
//--                                                                                --
//-- Descrição : Tratamento da Interrupção de Dado Enviado pela UART1               --
//--                                                                                --
//-- Entrada   : Nenhuma                                                            --
//--                                                                                --
//-- Saida     : Nenhuma                                                            --
//--                                                                                --
//------------------------------------------------------------------------------------

void __attribute__((interrupt, auto_psv)) _ISR _U1TXInterrupt(void) {

    IFS0bits.U1TXIF = 0; //-- Limpa o Flag de Interrupção
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Função    : void __attribute__((interrupt,auto_psv)) _ISR _U1ErrInterrupt(void)--
//--                                                                                --
//-- Descrição : Tratamento da Interrupção de Erro na UART1                         --
//--                                                                                --
//-- Entrada   : Nenhuma                                                            --
//--                                                                                --
//-- Saida     : Nenhuma                                                            --
//--                                                                                --
//------------------------------------------------------------------------------------

void __attribute__((interrupt, auto_psv)) _ISR _U1ErrInterrupt(void) {
    IFS4bits.U1ERIF = 0; //-- Limpa o Flag de Interrupção
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Função    : void __attribute__((interrupt,auto_psv)) _ISR _U2RXInterrupt(void) --
//--                                                                                --
//-- Descrição : Tratamento da Interrupção de Dado Recebido pela UART2              --
//--                                                                                --
//-- Entrada   : Nenhuma                                                            --
//--                                                                                --
//-- Saida     : Nenhuma                                                            --
//--                                                                                --
//------------------------------------------------------------------------------------

void __attribute__((interrupt, auto_psv)) _ISR _U2RXInterrupt(void) {
    unsigned char byDadoRec2;

    byDadoRec2 = U2RXREG; // Leitura
    UART_UART2ProcessaByteRecebido(byDadoRec2);

    IFS1bits.U2RXIF = 0; //-- Limpa o Flag de Interrupção
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Função    : void __attribute__((interrupt,auto_psv)) _ISR _U2TXInterrupt(void) --
//--                                                                                --
//-- Descrição : Tratamento da Interrupção de Dado Enviado pela UART2               --
//--                                                                                --
//-- Entrada   : Nenhuma                                                            --
//--                                                                                --
//-- Saida     : Nenhuma                                                            --
//--                                                                                --
//------------------------------------------------------------------------------------

void __attribute__((interrupt, auto_psv)) _ISR _U2TXInterrupt(void) {
    IFS1bits.U2TXIF = 0; //-- Limpa o Flag de Interrupção
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Função    : void __attribute__((interrupt,auto_psv)) _ISR _U2ErrInterrupt(void)--
//--                                                                                --
//-- Descrição : Tratamento da Interrupção de Erro na UART2                         --
//--                                                                                --
//-- Entrada   : Nenhuma                                                            --
//--                                                                                --
//-- Saida     : Nenhuma                                                            --
//--                                                                                --
//------------------------------------------------------------------------------------

void __attribute__((interrupt, auto_psv)) _ISR _U2ErrInterrupt(void) {
    IFS4bits.U2ERIF = 0; //-- Limpa o Flag de Interrupção
}

//==================================================================================
//== FIM DO ARQUIVO Interrupt.c                                                   ==
//==================================================================================

