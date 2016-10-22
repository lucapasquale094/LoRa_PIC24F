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
//== M�dulo     : Interrupt.c                                                     ==
//== Descri��o  : M�dulo de Inicializa��o e Tratamento das Interrup��es           ==
//==                                                                              ==
//==------------------------------------------------------------------------------==
//==                                                                              ==
//== Autor      : Nilton Gomes Valente - VAGON Engenharia LTDA                    ==
//== Email      : nilton@vagon.com.br                                             ==
//==                                                                              ==
//==================================================================================

//==================================================================================
//== FUN��ES DECLARADAS NESTE M�DULO                                              ==
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
//== INST�NCIA DAS VARI�VEIS GLOBAIS DECLARADAS NESTE M�DULO                      ==
//==================================================================================
ST_TEMPORIZACAO stTemporizacao;

unsigned int wTimer1ContadorTempo_ms;
unsigned char byFlagTempo_ms;

unsigned int wTimer1ContadorTempo1s;

unsigned int wContadorTempo_s;
unsigned char byFlagTempo_s;

//==================================================================================
//== FUN��ES                                                                      ==
//==================================================================================
//----------------------------------------------------------------------------------
//--                                                                              --
//-- Fun��o    : void INTERRUPT_TIMER1Init(void)                                  --
//--                                                                              --
//-- Descri��o : Inicializa o TIMER1                                              --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void INTERRUPT_TIMER1Init(void) {
    T1CONbits.TON = 0; // Timer1 desligado
    IEC0bits.T1IE = 0; // Interrup��o desabilitada
    TMR1 = 0; // Zera o timer para in�cio de contagem

    PR1 = 6000; // Configura o registrador de per�odo [Tempo = 250us == PR1 = 1000]
    // PR1 = [ ( (FOSC / 2) * Tempo) / PS ]
    // OBS.: PR1 = 999 devido ao ajuste da Lat�ncia do Tratamento da Interrup��o

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
//-- Fun��o    : void INTERRUPT_TIMER1On(void)                                    --
//--                                                                              --
//-- Descri��o : Liga o TIMER1                                                    --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void INTERRUPT_TIMER1On(void) {
    IFS0bits.T1IF = 0; // Limpa flag de interrup��o
    IEC0bits.T1IE = 1; // Habilita interrup��o do Timer1
    T1CONbits.TON = 1; // Timer1 ligado  
}


//----------------------------------------------------------------------------------
//--                                                                              --
//-- Fun��o    : void __attribute__((interrupt,auto_psv)) _ISR _T1Interrupt(void) --
//--                                                                              --
//-- Descri��o : Tratamento da Interrup��o do TIMER1                              --
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

    IFS0bits.T1IF = 0; // Limpa flag de interrup��o
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Fun��o    : void __attribute__((interrupt,auto_psv)) _ISR _INT0Interrupt(void) --
//--                                                                                --
//-- Descri��o : Tratamento da INT0                                                 --
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

    byAccelINT = TRUE; // Sinaliza interrup��o do aceler�metro

    byPIN_ACCEL = PIN_ON;

    IFS1bits.INT1IF = 0; // Limpa flag de interrup��o
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Fun��o    : void __attribute__((interrupt,auto_psv)) _ISR _U1RXInterrupt(void) --
//--                                                                                --
//-- Descri��o : Tratamento da Interrup��o de Dado Recebido pela UART1              --
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

    IFS0bits.U1RXIF = 0; //-- Limpa o Flag de Interrup��o
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Fun��o    : void __attribute__((interrupt,auto_psv)) _ISR _U1TXInterrupt(void) --
//--                                                                                --
//-- Descri��o : Tratamento da Interrup��o de Dado Enviado pela UART1               --
//--                                                                                --
//-- Entrada   : Nenhuma                                                            --
//--                                                                                --
//-- Saida     : Nenhuma                                                            --
//--                                                                                --
//------------------------------------------------------------------------------------

void __attribute__((interrupt, auto_psv)) _ISR _U1TXInterrupt(void) {

    IFS0bits.U1TXIF = 0; //-- Limpa o Flag de Interrup��o
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Fun��o    : void __attribute__((interrupt,auto_psv)) _ISR _U1ErrInterrupt(void)--
//--                                                                                --
//-- Descri��o : Tratamento da Interrup��o de Erro na UART1                         --
//--                                                                                --
//-- Entrada   : Nenhuma                                                            --
//--                                                                                --
//-- Saida     : Nenhuma                                                            --
//--                                                                                --
//------------------------------------------------------------------------------------

void __attribute__((interrupt, auto_psv)) _ISR _U1ErrInterrupt(void) {
    IFS4bits.U1ERIF = 0; //-- Limpa o Flag de Interrup��o
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Fun��o    : void __attribute__((interrupt,auto_psv)) _ISR _U2RXInterrupt(void) --
//--                                                                                --
//-- Descri��o : Tratamento da Interrup��o de Dado Recebido pela UART2              --
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

    IFS1bits.U2RXIF = 0; //-- Limpa o Flag de Interrup��o
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Fun��o    : void __attribute__((interrupt,auto_psv)) _ISR _U2TXInterrupt(void) --
//--                                                                                --
//-- Descri��o : Tratamento da Interrup��o de Dado Enviado pela UART2               --
//--                                                                                --
//-- Entrada   : Nenhuma                                                            --
//--                                                                                --
//-- Saida     : Nenhuma                                                            --
//--                                                                                --
//------------------------------------------------------------------------------------

void __attribute__((interrupt, auto_psv)) _ISR _U2TXInterrupt(void) {
    IFS1bits.U2TXIF = 0; //-- Limpa o Flag de Interrup��o
}

//------------------------------------------------------------------------------------
//--                                                                                --
//-- Fun��o    : void __attribute__((interrupt,auto_psv)) _ISR _U2ErrInterrupt(void)--
//--                                                                                --
//-- Descri��o : Tratamento da Interrup��o de Erro na UART2                         --
//--                                                                                --
//-- Entrada   : Nenhuma                                                            --
//--                                                                                --
//-- Saida     : Nenhuma                                                            --
//--                                                                                --
//------------------------------------------------------------------------------------

void __attribute__((interrupt, auto_psv)) _ISR _U2ErrInterrupt(void) {
    IFS4bits.U2ERIF = 0; //-- Limpa o Flag de Interrup��o
}

//==================================================================================
//== FIM DO ARQUIVO Interrupt.c                                                   ==
//==================================================================================

