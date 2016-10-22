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
//== Módulo     : Uart.h                                                          ==
//== Descrição  : Módulo de acesso à UART1, UART2, UART3 e UART4                  ==
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

//==================================================================================
//== DECLARAÇÃO DOS PROTÓTIPOS DAS FUNÇÕES                                        ==
//==================================================================================
extern void UART_UART1Init(void);
extern void UART_UART1ProcessaByteRecebido(unsigned char);
extern void UART_UART1EnviaTxBuffer(unsigned int);
extern void UART_UART1EnviaTxBufferASCII(unsigned char *);
extern void UART_UART2Init(void);
extern void UART_UART2ProcessaByteRecebido(unsigned char);
extern void UART_UART2EnviaTxBuffer(unsigned int);
extern void UART_UART2EnviaTxBufferASCII(unsigned char *);
extern void UART_UART3Init(void);
extern void UART_UART3ProcessaByteRecebido(unsigned char);
extern void UART_UART3EnviaTxBuffer(unsigned int);
extern void UART_UART3EnviaTxBufferASCII(unsigned char *);
extern void UART_UART4Init(void);
extern void UART_UART4ProcessaByteRecebido(unsigned char);
extern void UART_UART4EnviaTxBuffer(unsigned int);
extern void UART_UART4EnviaTxBufferASCII(unsigned char *);

//==================================================================================
//== DEFINIÇÕES                                                                   ==
//==================================================================================
//------------------------------------------------
//-- SPBRG:                                     --
//--         SYNC = 0, BGR16 = 0, BRGH = 0      --
//------------------------------------------------
//#define UART_SPBRG_57600  (unsigned char)(((FOSC / (float)115200) / 64) - 1) + 0.5

//------------------------------------------------
//-- SPBRG:                                     --
//--         SYNC = 0, BGR16 = 0, BRGH = 1      --
//--         ou
//--         SYNC = 0, BGR16 = 1, BRGH = 0      --
//------------------------------------------------
//#define UART_SPBRG_115200 (unsigned char)(((FOSC / (float)115200) / 16) - 1) + 0.5
//#define UART_SPBRG_57600  (unsigned char)(((FOSC / (float) 57600) / 16) - 1) + 0.5
//#define UART_SPBRG_19200  (unsigned char)(((FOSC / (float) 19200) / 16) - 1) + 0.5
//#define UART_SPBRG_9600   (unsigned char)(((FOSC / (float)  9600) / 16) - 1) + 0.5
//#define UART_SPBRG_4800   (unsigned char)(((FOSC / (float)  4800) / 16) - 1) + 0.5
//#define UART_SPBRG_2400   (unsigned char)(((FOSC / (float)  2400) / 16) - 1) + 0.5
//#define UART_SPBRG_1200   (unsigned char)(((FOSC / (float)  1200) / 16) - 1) + 0.5

//------------------------------------------------
//-- SPBRG:                                     --
//--         SYNC = 0, BGR16 = 1, BRGH = 1      --
//--         ou
//--         SYNC = 1, BGR16 = 1, BRGH = X      --
//------------------------------------------------
//#define UART_SPBRG_115200 (unsigned char)(((FOSC / (float)115200) / 4) - 1) + 0.5
//#define UART_SPBRG_57600  (unsigned char)(((FOSC / (float) 57600) / 4) - 1) + 0.5
//#define UART_SPBRG_19200  (unsigned char)(((FOSC / (float) 19200) / 4) - 1) + 0.5
//#define UART_SPBRG_9600   (unsigned char)(((FOSC / (float)  9600) / 4) - 1) + 0.5
//#define UART_SPBRG_4800   (unsigned char)(((FOSC / (float)  4800) / 4) - 1) + 0.5
//#define UART_SPBRG_2400   (unsigned char)(((FOSC / (float)  2400) / 4) - 1) + 0.5
//#define UART_SPBRG_1200   (unsigned char)(((FOSC / (float)  1200) / 4) - 1) + 0.5

//------------------------------------
//-- Caracteres de Controle (ASCII) --
//------------------------------------
#define ASCII_NULL            0x00   //Null
#define ASCII_SOH             0x01   //Start of Heading
#define ASCII_STX             0x02   //Start of Text
#define ASCII_ETX             0x03   //End of Text
#define ASCII_EOT             0x04   //End of Transmission
#define ASCII_ENQ             0x05   //Enquiry
#define ASCII_ACK             0x06   //Acknowledge
#define ASCII_BEL             0x07   //Bell
#define ASCII_BS              0x08   //Backspace
#define ASCII_TAB             0x09   //Horizontal Tab
#define ASCII_LF              0x0A   //Line Feed (New Line)
#define ASCII_VT              0x0B   //Vertical Tab
#define ASCII_FF              0x0C   //Form Feed (New Page)
#define ASCII_CR              0x0D   //Carriage Return
#define ASCII_SO              0x0E   //Shift Out
#define ASCII_SI              0x0F   //Shift In
#define ASCII_DLE             0x10  //Data Link Escape
#define ASCII_DC1             0x11  //Device Control 1
#define ASCII_DC2             0x12  //Device Control 2
#define ASCII_DC3             0x13  //Device Control 3
#define ASCII_DC4             0x14  //Device Control 4
#define ASCII_NAK             0x15  //Negative Acknowledge
#define ASCII_SYN             0x16  //Sunchronous Idle
#define ASCII_ETB             0x17  //End of Transmission Block
#define ASCII_CAN             0x18  //Cancel
#define ASCII_EM              0x19  //End of Medium
#define ASCII_SUB             0x1A  //Substitute
#define ASCII_ESC             0x1B  //Escape
#define ASCII_FS              0x1C  //File Separator
#define ASCII_GS              0x1D  //Group Separator
#define ASCII_RS              0x1E  //Recor Separator
#define ASCII_US              0x1F  //Unit Separator

//-----------------------------------------------------------------------------
//-- Estados do Protocolo de Tratamento dos Dados da UART2 (GPS)             --
//-----------------------------------------------------------------------------
#define GPS_Aguardando_CIFRAO                 0x00
#define GPS_Aguardando_CR                     0x01
#define GPS_Aguardando_LF                     0x02

//#define GPS_Aguardando_CIFRAO                 0x00
//#define GPS_Aguardando_G                      0x01
//#define GPS_Aguardando_P                      0x02
//#define GPS_Aguardando_ASTERISCO              0x03
//#define GPS_Aguardando_CS1                    0x04
//#define GPS_Aguardando_CS0                    0x05
//#define GPS_Aguardando_CR                     0x06
//#define GPS_Aguardando_LF                     0x07

//-----------------------------------------------------------------------------
//-- Estados do Protocolo de Tratamento dos Dados da UART3 (RS232)           --
//-----------------------------------------------------------------------------
#define UART1_Aguardando_STX                  0x00
#define UART1_Aguardando_ETX                  0x01

//-----------------------------------------------------------------------------
//-- Estados do Protocolo de Tratamento dos Dados da UART4 (RS-485)          --
//-----------------------------------------------------------------------------
#define UART4_Aguardando_STX                  0x00
#define UART4_Aguardando_ETX                  0x01

#define RS485_RX      0
#define RS485_TX      1

#define TAM_BUFF_TX_UART1   128
#define TAM_BUFF_RX_UART1   128
#define TAM_BUFF_TX_UART2   64
#define TAM_BUFF_RX_UART2   64

//==================================================================================
//== VARIÁVEIS GLOBAIS                                                            ==
//==================================================================================
extern unsigned char  byBufferUART1Tx[TAM_BUFF_TX_UART1];
extern unsigned char  byBufferUART1Rx[TAM_BUFF_RX_UART1];
extern unsigned char  byBufferUART2Tx[TAM_BUFF_TX_UART2];
extern unsigned char  byBufferUART2Rx[TAM_BUFF_RX_UART2];

extern unsigned char  byQtdCrLfIntermediarios;
extern unsigned char* pbyBufferRxUART1;

//==================================================================================
//== Fim do arquivo Uart.h                                                        ==
//==================================================================================
