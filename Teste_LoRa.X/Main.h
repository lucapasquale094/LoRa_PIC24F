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
//== Módulo     : Main.h                                                          ==
//== Descrição  : Módulo principal do programa                                    ==
//==                                                                              ==
//==------------------------------------------------------------------------------==
//==                                                                              ==
//== Autor      : Nilton Gomes Valente - VAGON Engenharia LTDA                    ==
//== Email      : nilton@vagon.com.br                                             ==
//==                                                                              ==
//==================================================================================

//==================================================================================
//== INCLUDES                                                                     ==
//==================================================================================
#include <p24F16KL402.h>
#include <xc.h>
#include "Typedef.h"

//==================================================================================
//== DECLARAÇÃO DOS PROTÓTIPOS DAS FUNÇÕES                                        ==
//==================================================================================
extern void MAIN_Delay_1ms(void);
extern void MAIN_Delay_5ms(void);
extern void MAIN_Delay_100us(void);
extern void MAIN_Delay_50us(void);
extern void MAIN_Delay_10us(void);
extern void MAIN_Delay_1us(void);

//==================================================================================
//== DEFINIÇÕES                                                                   ==
//==================================================================================
//------------------------------------------
//-- Versão.Revisão-Protótipo do Hardware --
//------------------------------------------
#define HW_Ver_1      '0'
#define HW_Ver_0      '1'

#define HW_Rev_1      '0'
#define HW_Rev_0      '0'

#define HW_Prot_1     '0'
#define HW_Prot_0     '0'

//------------------------------------------
//-- Versão.Revisão-Protótipo do Firmware --
//------------------------------------------
#define FW_Ver_1      '0'
#define FW_Ver_0      '1'

#define FW_Rev_1      '0'
#define FW_Rev_0      '0'

#define FW_Prot_1     '0'
#define FW_Prot_0     '0'

//-------------------------------------------
//-- CONFIGURAÇÃO DOS PINOS DO PROCESSADOR --
//-------------------------------------------
//------------
//-- PORT A --
//------------
#define TRIS_SDA_ACCEL            TRISAbits.TRISA0  //
#define PIN_SDA_ACCEL             PORTAbits.RA0
#define LAT_SDA_ACCEL             LATAbits.LATA0

#define TRIS_MTOUCH_C             TRISAbits.TRISA1  //
#define PIN_MTOUCH_C              PORTAbits.RA1
#define LAT_MTOUCH_C              LATAbits.LATA1

#define TRIS_RST_C                TRISAbits.TRISA2  //
#define PIN_RST_C                 PORTAbits.RA2
#define LAT_RST_C                 LATAbits.LATA2

#define TRIS_LORA_RST             TRISAbits.TRISA3  // 
#define PIN_LORA_RST              PORTAbits.RA3
#define LAT_LORA_RST              LATAbits.LATA3

#define TRIS_SW_TACT_C            TRISAbits.TRISA4  //
#define PIN_SW_TACT_C             PORTAbits.RA4
#define LAT_SW_TACT_C             LATAbits.LATA4

//#define TRIS_MCLR                 TRISAbits.TRISA5  //
#define PIN_MCLR                  PORTAbits.RA5
//#define LAT_MCLR                  LATAbits.LATA5

#define TRIS_PWM_C                TRISAbits.TRISA6  //
#define PIN_PWM_C                 PORTAbits.RA6
#define LAT_PWM_C                 LATAbits.LATA6

#define TRIS_MISO_C               TRISAbits.TRISA7  //
#define PIN_MISO_C                PORTAbits.RA7
#define LAT_MISO_C                LATAbits.LATA7

//------------
//-- PORT B --
//------------
#define TRIS_LORA_RXD             TRISBbits.TRISB0  //
#define PIN_LORA_RXD              PORTBbits.RB0
#define LAT_LORA_RXD              LATBbits.LATB0

#define TRIS_LORA_TXD             TRISBbits.TRISB1  //
#define PIN_LORA_TXD              PORTBbits.RB1
#define LAT_LORA_TXD              LATBbits.LATB1

#define TRIS_UART1_RXD            TRISBbits.TRISB2  //
#define PIN_UART1_RXD             PORTBbits.RB2
#define LAT_UART1_RXD             LATBbits.LATB2

#define TRIS_SCL_ACCEL            TRISBbits.TRISB3  //
#define PIN_SCL_ACCEL             PORTBbits.RB3
#define LAT_SCL_ACCEL             LATBbits.LATB3

#define TRIS_RA5_C                TRISBbits.TRISB4  // 
#define PIN_RA5_C                 PORTBbits.RB4
#define LAT_RA5_C                 LATBbits.LATB4

#define TRIS_SCK_C                TRISBbits.TRISB5  //
#define PIN_SCK_C                 PORTBbits.RB5
#define LAT_SCK_C                 LATBbits.LATB5

#define TRIS_MOSI_C               TRISBbits.TRISB6  //
#define PIN_MOSI_C                PORTBbits.RB6
#define LAT_MOSI_C                LATBbits.LATB6

#define TRIS_UART1_TDX            TRISBbits.TRISB7  //
#define PIN_UART1_TDX             PORTBbits.RB7
#define LAT_UART1_TDX             LATBbits.LATB7

#define TRIS_SCL_C                TRISBbits.TRISB8  //
#define PIN_SCL_C                 PORTBbits.RB8
#define LAT_SCL_C                 LATBbits.LATB8

#define TRIS_SDA_C                TRISBbits.TRISB9  //
#define PIN_SDA_C                 PORTBbits.RB9
#define LAT_SDA_C                 LATBbits.LATB9

#define TRIS_ICSP_PGED            TRISBbits.TRISB10 //
#define PIN_ICSP_PGED             PORTBbits.RB10
#define LAT_ICSP_PGED             LATBbits.LATB10

#define TRIS_ICSP_PGEC            TRISBbits.TRISB11 //
#define PIN_ICSP_PGEC             PORTBbits.RB11
#define LAT_ICSP_PGEC             LATBbits.LATB11

#define TRIS_CS_C                 TRISBbits.TRISB12 //
#define PIN_CS_C                  PORTBbits.RB12
#define LAT_CS_C                  LATBbits.LATB12

#define TRIS_RC0_C                TRISBbits.TRISB13 //
#define PIN_RC0_C                 PORTBbits.RB13
#define LAT_RC0_C                 LATBbits.LATB13

#define TRIS_INT_1                TRISBbits.TRISB14 // 
#define PIN_INT_1                 PORTBbits.RB14
#define LAT_INT_1                 LATBbits.LATB14

#define TRIS_AN_C                 TRISBbits.TRISB15 //  
#define PIN_AN_C                  PORTBbits.RB15
#define LAT_AN_C                  LATBbits.LATB15

//------------------------------------------------------------------
//-- Constantes para definição de direcionamento dos pinos do PIC --
//------------------------------------------------------------------
#define TRIS_SAIDA    0
#define TRIS_ENTRADA  1

//-----------------------
//-- Definições Gerais --
//-----------------------
#define PIN_INPUT     1
#define PIN_OUTPUT    0

#define PIN_OFF       0
#define PIN_ON        1

#define FALSE         0
#define TRUE          1

//-----------------------
//-- DEFINIÇÕES GERAIS --
//-----------------------

//------------------------------------
//-- Estados da Maqquina de Bloueio --
//------------------------------------
#define BL_AGUARDANDO_PINO_BLOUEIO        0
#define BL_AGUARDANDO_30_SEGUNDOS         1
#define BL_EXEUTANDO_BLOQUEIO_PROGRESSIVO 2
#define BL_EXEUTANDO_CICLO                3
#define BL_AGUARDANDO_DESBLOUEIO          4
#define BL_AGUARDANDO_5_SEGUNDOS          5

//------------------------------------
//-- Definições para Testes e Debug --
//------------------------------------
//--------------------------
//-- Teste sem o Hardware --
//-- 0 = Desabilita       --
//-- 1 = Habilita         --
//--------------------------
#define EN_TESTE_SEM_HW                   0

//==================================================================================
//== DECLARAÇÃO DAS VARIÁVEIS GLOBAIS DESTE MÓDULO                                ==
//==================================================================================
extern unsigned char byEstadoAtualBloqueio;
extern unsigned int  wIndiceDoCicloDeBloqueio;
extern unsigned int  wContadosDeCilosPorIndice;
extern unsigned int  wAuxI;
extern unsigned int  wTOn;
extern unsigned int  wTOff;

//==================================================================================
//== Fim do arquivo Main.h                                                        ==
//==================================================================================
