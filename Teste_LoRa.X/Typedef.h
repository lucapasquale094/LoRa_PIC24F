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
//== Módulo     : Typedef.h                                                       ==
//== Descrição  : Novas definições de variáveis, structs, unions, etc             ==
//==                                                                              ==
//==------------------------------------------------------------------------------==
//==                                                                              ==
//== Autor      : Nilton Gomes Valente - VAGON Engenharia LTDA                    ==
//== Email      : nilton@vagon.com.br                                             ==
//==                                                                              ==
//==================================================================================

//==================================================================================
//== DEFINIÇÕES DE TIPOS DE VARIÁVEIS (TYPEDEF)                                   ==
//==================================================================================
//----------------------------------------------------------------------------------
//-- Estrutura para conversão Char para Bits                                      --
//----------------------------------------------------------------------------------
typedef union{
  unsigned char byByte;
  struct  {
    unsigned bFlag00:1;       //-- bit 0 --//
    unsigned bFlag01:1;       //-- bit 1 --//
    unsigned bFlag02:1;       //-- bit 2 --//
    unsigned bFlag03:1;       //-- bit 3 --//
    unsigned bFlag04:1;       //-- bit 4 --//
    unsigned bFlag05:1;       //-- bit 5 --//
    unsigned bFlag06:1;       //-- bit 6 --//
    unsigned bFlag07:1;       //-- bit 7 --//
  } stFlagsByte;
} UN_BYTE_TO_BITS;

//----------------------------------------------------------------------------------
//-- Estrutura para conversão Int para Char                                       --
//----------------------------------------------------------------------------------
typedef union {
  struct {
    unsigned  char  byB0;
    unsigned  char  byB1;
  } stByte;
  unsigned int  wWord;
} UN_INT_TO_CHAR;
extern UN_INT_TO_CHAR unAccelEixoX;
extern UN_INT_TO_CHAR unAccelEixoY;
extern UN_INT_TO_CHAR unAccelEixoZ;

//----------------------------------------------------------------------------------
//-- Estrutura para conversão Long para Int para Char                             --
//----------------------------------------------------------------------------------
typedef union {
  struct {
    unsigned  char  byB0;
    unsigned  char  byB1;
    unsigned  char  byB2;
    unsigned  char  byB3;
  } stByte;
  struct {
    unsigned int wWord0;
    unsigned int wWord1;
  } stWord;
  unsigned long dwLong;
  float         flFloat;
} UN_LONG_TO_INT_TO_CHAR;

//----------------------------------------------------------------------------------
//-- Estrutura para definições de FLAGS em um BYTE (8 bits)                       --
//----------------------------------------------------------------------------------
//typedef struct  {
//  unsigned bFlag00:1;       //-- bit 2 --//
//  unsigned bFlag01:1;       //-- bit 2 --//
//  unsigned bFlag02:1;       //-- bit 2 --//
//  unsigned bFlag03:1;       //-- bit 3 --//
//  unsigned bFlag04:1;       //-- bit 4 --//
//  unsigned bFlag05:1;       //-- bit 5 --//
//  unsigned bFlag06:1;       //-- bit 6 --//
//  unsigned bFlag07:1;       //-- bit 7 --//
//} ST_FLAGS_BYTE;

//----------------------------------------------------------------------------------
//-- Estrutura para definições de FLAGS em uma WORD (16 bits)                     --
//----------------------------------------------------------------------------------
//typedef struct  {
//  unsigned bFlag00:1;       //-- bit 0 --//
//  unsigned bFlag01:1;       //-- bit 1 --//
//  unsigned bFlag02:1;       //-- bit 2 --//
//  unsigned bFlag03:1;       //-- bit 3 --//
//  unsigned bFlag04:1;       //-- bit 4 --//
//  unsigned bFlag05:1;       //-- bit 5 --//
//  unsigned bFlag06:1;       //-- bit 6 --//
//  unsigned bFlag07:1;       //-- bit 7 --//
//  unsigned bFlag08:1;       //-- bit 0 --//
//  unsigned bFlag09:1;       //-- bit 1 --//
//  unsigned bFlag10:1;       //-- bit 2 --//
//  unsigned bFlag11:1;       //-- bit 3 --//
//  unsigned bFlag12:1;       //-- bit 4 --//
//  unsigned bFlag13:1;       //-- bit 5 --//
//  unsigned bFlag14:1;       //-- bit 6 --//
//  unsigned bFlag15:1;       //-- bit 7 --//
//} ST_FLAGS_WORD;

//----------------------------------------------------------------------------------
//-- Estrutura de dados da RS232 (UART do PIC)                                    --
//----------------------------------------------------------------------------------
typedef struct {
  unsigned char byEstadoAtual;        // Estado do tratamento do Buffer entre STX e ETX
  unsigned char byBufferOk;
  unsigned char byTimeOut;            
  unsigned int  wTimeOut;             // Contador de tempo (Time-out)
  unsigned int  wIndexBuffer;         // Indice do Buffer Rx/Tx
} ST_UART;
extern ST_UART  stUART1;
extern ST_UART  stUART2;
extern ST_UART  stUART3;
extern ST_UART  stUART4;
//----------------------------------------------------------------------------------
//-- Estrutura de controle de temporização do sistema                             --
//----------------------------------------------------------------------------------
typedef struct  {
  unsigned      bFlag1s             :1; //-- bit 00 --//
  unsigned      bFlagEDP0           :1; //-- bit 01 --//
  unsigned      bFlagEDP1           :1; //-- bit 02 --//
  unsigned      bFlagEDP2           :1; //-- bit 03 --//
  unsigned      bFlagEDN            :1; //-- bit 04 --//
  unsigned      bFlagVBAT           :1; //-- bit 05 --//
  unsigned      bFlagVBAT_BKP       :1; //-- bit 06 --//
  unsigned      bFlagACCEL          :1; //-- bit 09 --//
  unsigned      bFlagDebounceACCEL  :1; //-- bit 09 --//
  unsigned      bFlagTxPrimVez      :1; //-- bit 07 --//
  unsigned      bFlag_T_Tx          :1; //-- bit 08 --//
  unsigned      bFlag11             :1; //-- bit 11 --//
  unsigned      bFlag12             :1; //-- bit 12 --//
  unsigned      bFlag13             :1; //-- bit 13 --//
  unsigned      bFlag14             :1; //-- bit 14 --//
  unsigned      bFlag15             :1; //-- bit 15 --//
  unsigned int  wContadorTempo1s;
  unsigned int  wContadorTempoEDP0;
  unsigned int  wContadorTempoEDP1;
  unsigned int  wContadorTempoEDP2;
  unsigned int  wContadorTempoEDN;
  unsigned int  wContadorTempoVBAT;
  unsigned int  wContadorTempoVBAT_BKP;
  unsigned int  wContadorTempoACCEL;
  unsigned int  wContadorTempoDebounceACCEL;
  unsigned int  wT_Log;
  unsigned int  wT_Tx;
  unsigned int  wT_Sleep1;
  unsigned int  wT_Sleep2;
  unsigned int  wT_KeepAlive;
  unsigned int  wT_TimeoutMaqModem;
  unsigned int  wT_TempoRF;
} ST_TEMPORIZACAO;
extern ST_TEMPORIZACAO  stTemporizacao;

//==================================================================================
//== Fim do arquivo Typedef.h                                                     ==
//==================================================================================
