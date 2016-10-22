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
//== Módulo     : Main.c                                                          ==
//== Descrição  : Módulo principal do programa                                    ==
//==                                                                              ==
//==------------------------------------------------------------------------------==
//==                                                                              ==
//== Autor      : Nilton Gomes Valente - VAGON Engenharia LTDA                    ==
//== Email      : nilton@vagon.com.br                                             ==
//==                                                                              ==
//==================================================================================

//==================================================================================
//== CONTROLE DE VERSÕES                                                          ==
//==================================================================================
//----------------------------------------------------------------------------------
//--                                                                              --
//-- Versão     : 1.00                                                            --
//-- Processador: PIC24F16KL402                                                   --
//-- Compilador : MPLAB XC16 V1.26 (MPLABX IDE V3.35)                             --
//-- Início     : __/__/20__                                                      --
//-- Liberada em: __/__/____                                                      --
//-- Descrição  : Primeira versão                                                 --
//--                                                                              --
//----------------------------------------------------------------------------------
//--                                                                              --
//-- Versão     : _.__                                                            --
//-- Processador:                                                                 --
//-- Compilador : MPLAB XC16 V1.26 (MPLABX IDE V3.35)                             --
//-- Início     : __/__/____                                                      --
//-- Liberada em: __/__/____                                                      --
//-- Descrição  :                                                                 --
//--                                                                              --
//----------------------------------------------------------------------------------

//==================================================================================
//== INCLUDES                                                                     ==
//==================================================================================
#include <stdio.h>
#include <string.h>
//#include <rtcc.h>
#include "Main.h"
#include "Interrupt.h"
#include "I2CDiscr.h"
#include "Accel.h"
#include "Uart.h"
#include "LoRa.h"

//==================================================================================
//== CONFIGURAÇÃO DO HARDWARE DO MICROCONTROLADOR                                 ==
//==================================================================================
/* -------------------------------------------------------- */
/* Macros for setting device configuration registers        */
/* -------------------------------------------------------- */
// PIC24F16KL402 Configuration Bit Settings
// 'C' source line config statements

// FBS
#pragma config BWRP = OFF               // Boot Segment Write Protect (Disabled)
#pragma config BSS = OFF                // Boot segment Protect (No boot flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Flash Write Protect (General segment may be written)
#pragma config GSS0 = OFF               // General Segment Code Protect (No Protection)

// FOSCSEL
#pragma config FNOSC = FRCDIV           // Oscillator Select (8MHz FRC with Postscaler (FRCDIV))
#pragma config SOSCSRC = DIG            // SOSC Source Type (Digital Mode for use with external clock on SCLKI)
#pragma config LPRCSEL = HP             // LPRC Power and Accuracy (High Power/High Accuracy)
#pragma config IESO = OFF               // Internal External Switch Over bit (Internal External Switchover mode disabled (Two-speed Start-up disabled))

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode (Primary oscillator disabled)
#pragma config OSCIOFNC = ON            // CLKO Pin I/O Function (Port I/O enabled (CLKO disabled))
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range (Primary Oscillator/External Clock frequency >8MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switching and Fail-safe Clock Monitor Disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32768)
#pragma config FWPSA = PR128            // WDT Prescaler bit (WDT prescaler ratio of 1:128)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bits (WDT disabled in hardware; SWDTEN bit disabled)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected (windowed WDT disabled))

// FPOR
#pragma config BOREN = BOR0             // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware; SBOREN bit disabled)
#pragma config PWRTEN = ON              // Power-up Timer Enable (PWRT enabled)
#pragma config I2C1SEL = PRI            // Alternate I2C1 Pin Mapping bit (Default SCL1/SDA1 Pins for I2C1)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset at 1.8V)
#pragma config MCLRE = ON               // MCLR Pin Enable bit (RA5 input disabled; MCLR enabled)

// FICD
#pragma config ICS = PGx2               // ICD Pin Placement Select (EMUC/EMUD share PGC2/PGD2)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


//==================================================================================
//== ALOCAÇÃO DOS BUFFERS NA FLASH E RAM DO PROCESSADOR                           ==
//==================================================================================
//const unsigned int  wNumeroDeSerieConst __attribute__ ((section("program"), address(0x1000))) = 1;
//unsigned int        wNumeroDeSerie;
//unsigned char       byNumeroDeSerieASCII[9];
//unsigned char       byNumeroRelatorioASCII[9];


//==================================================================================
//== INSTÂNCIA DAS VARIÁVEIS GLOBAIS DECLARADAS NESTE MÓDULO                      ==
//==================================================================================
unsigned char byEstadoAtualBloqueio;
unsigned int wIndiceDoCicloDeBloqueio;
unsigned int wContadosDeCilosPorIndice;
unsigned int wAux;
unsigned int wTOn;
unsigned int wTOff;
unsigned int wAuxIgnicao;
unsigned int wAuxBloqueio;

//==================================================================================
//== FUNÇÕES                                                                      ==
//==================================================================================
//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : MAIN_InicializaPorts                                             --
//--                                                                              --
//-- Descrição : Esta função é responsável pela inicialização de todos  os  pinos --
//--             do processador como entrada ou saída e definindo seu estado ini- --
//--             cial quando configurado como saída                               --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void MAIN_InicializaPorts(void) {
    //--------------------------
    //-- I/O PORT Definitions --
    //--------------------------

    ANSA = 0x0000;
    ANSB = 0x0000;

    //------------
    //-- PORT A --
    //------------
    TRIS_SDA_ACCEL = TRIS_ENTRADA;
    //LAT_SDA_ACCEL

    TRIS_MTOUCH_C = TRIS_ENTRADA;
    //LAT_MTOUCH_C

    TRIS_RST_C = TRIS_ENTRADA;
    //LAT_RST_C

    TRIS_LORA_RST = TRIS_ENTRADA;
    //LAT_LORA_RST

    TRIS_SW_TACT_C = TRIS_ENTRADA;

    TRIS_PWM_C = TRIS_SAIDA;
    LAT_PWM_C = 0;

    TRIS_MISO_C = TRIS_ENTRADA;
    //LAT_MISO_C

    //------------
    //-- PORT B --
    //------------
    TRIS_LORA_RXD = TRIS_ENTRADA;
    //LAT_LORA_RXD

    TRIS_LORA_TXD = TRIS_ENTRADA;
    //LAT_LORA_TXD

    TRIS_UART1_RXD = TRIS_ENTRADA;
    //LAT_UART1_RXD

    TRIS_SCL_ACCEL = TRIS_ENTRADA;
    //LAT_SCL_ACCEL

    TRIS_RA5_C = TRIS_SAIDA;
    LAT_RA5_C = 0;

    TRIS_SCK_C = TRIS_ENTRADA;
    //LAT_SCK_C

    TRIS_MOSI_C = TRIS_ENTRADA;
    //LAT_MOSI_C

    TRIS_UART1_TDX = TRIS_ENTRADA;
    //LAT_UART1_TDX

    TRIS_SCL_C = TRIS_ENTRADA;
    //LAT_SCL_C

    TRIS_SDA_C = TRIS_ENTRADA;
    //LAT_SDA_C

    TRIS_ICSP_PGED = TRIS_ENTRADA;
    //LAT_ICSP_PGED

    TRIS_ICSP_PGEC = TRIS_ENTRADA;
    //LAT_ICSP_PGEC

    TRIS_CS_C = TRIS_ENTRADA;
    //LAT_CS_C

    TRIS_RC0_C = TRIS_ENTRADA;
    //LAT_RC0_C

    TRIS_INT_1 = TRIS_ENTRADA;
    //LAT_INT_1

    TRIS_AN_C = TRIS_ENTRADA;
    //LAT_AN_C  
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : MAIN_InicializaOscilador()                                       --
//--                                                                              --
//-- Descrição : Esta função é responsável pela inicialização do Controle do Os-  --
//--             cilador do Processador                                           --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void MAIN_InicializaOscilador(void) {
    Nop();

    OSCCONbits.COSC = 0;
    OSCCONbits.NOSC = 0;
    OSCCONbits.CLKLOCK = 0;
    OSCCONbits.LOCK = 0;
    OSCCONbits.SOSCDRV = 0;
    OSCCONbits.SOSCEN = 0;
    OSCCONbits.OSWEN = 0;

    CLKDIVbits.ROI = 0;
    CLKDIVbits.DOZE = 0;
    CLKDIVbits.DOZEN = 0;
    CLKDIVbits.RCDIV = 0;

    OSCTUNbits.TUN = 0;
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : MAIN_InicializaVariaveisGlobais()                                --
//--                                                                              --
//-- Descrição : Esta função é responsável pela inicialização de todas as variá-  --
//--             veis Globais do Programa para permitir o fuincionamento correto  --
//--             em cada ocorrência de um RESET.                                  --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void MAIN_InicializaVariaveisGlobais(void) {
    wTimer1ContadorTempo1s = K_TEMPO_1_s;
    stTemporizacao.bFlag1s = FALSE;
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    :                                                                  --
//--                                                                              --
//-- Descricao :                                                                  --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void MAIN_Delay_5ms(void) {
    unsigned int byI;

    for (byI = 0; byI < 3350; byI++) {
        Nop();
    }
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    :                                                                  --
//--                                                                              --
//-- Descricao :                                                                  --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void MAIN_Delay_1ms(void) {
    unsigned int byI;

    for (byI = 0; byI < 670; byI++) {
        Nop();
    }
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    :                                                                  --
//--                                                                              --
//-- Descricao :                                                                  --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void MAIN_Delay_100us(void) {
    unsigned int byI;

    for (byI = 0; byI < 65; byI++) //-- Confirmar o valor
    {
        Nop();
    }
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    :                                                                  --
//--                                                                              --
//-- Descricao :                                                                  --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void MAIN_Delay_50us(void) {
    unsigned int byI;

    for (byI = 0; byI < 32; byI++) {
        Nop();
    }
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    :                                                                  --
//--                                                                              --
//-- Descricao :                                                                  --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void MAIN_Delay_10us(void) {
    unsigned int byI;

    for (byI = 0; byI < 5; byI++) {
        Nop();
    }
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    :                                                                  --
//--                                                                              --
//-- Descricao :                                                                  --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void MAIN_Delay_1us() {
    Nop();
    Nop();
    Nop();
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : void main(void)                                                  --
//--                                                                              --
//-- Descrição : Função de Início do Programa                                     --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

int main(void) {
    int i, j;
    MAIN_InicializaPorts(); //-- Inicializa os PORTS do PIC
    MAIN_InicializaOscilador(); //-- Inicializa o Oscilador do PIC
    MAIN_InicializaVariaveisGlobais(); //-- Inicializa as Variáveis Globais
    I2CDISCR_Accel_InicializaBarramentoI2C(); //-- Inicializa oBarramento I2C do Acelerômetro
    //ACCEL_InicializaLIS3DSH();                      //-- Inicializa o Acelerômetro
    //ACCEL_InicializaStateMachine1LIS3DSH();         //-- Iniciaiza o WakeUp do Acelerômetro
    INTERRUPT_TIMER1Init(); //-- Inicializa o TIMER1 - Base de Tempo do Sistema (1ms)
    INTERRUPT_TIMER1On(); //-- Liga o TIMER1

    UART_UART2Init();
    InitLoRa();

    //---------------------------------
    //-- Loop Principal do Programa  --
    //---------------------------------
    while (1) {
        //Tenta enviar dado
        SendCommand("mac tx uncnf 1 123ABC\r\n");


        SendCommand("sys set pindig GPIO6 1\r\n");
        for (i = 0; i < 250; i++) {
            MAIN_Delay_5ms();
        }
        SendCommand("sys set pindig GPIO6 0\r\n");


        for (i = 0; i < 60; i++) {
            for (j = 0; j < 200; j++) {
                MAIN_Delay_5ms();
            }
        }
    } //-- Fim do while(1)
} //-- Fim do Main()

//==================================================================================
//== FIM DO ARQUIVO Main.c                                                        ==
//==================================================================================
