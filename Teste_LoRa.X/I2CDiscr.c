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
//== Módulo     : I2CDiscr.c                                                      ==
//== Descrição  : Módulo de tratamento da I2C de forma discreta (sem o HW do PIC) ==
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
#include "I2CDiscr.h"
#include "Main.h"

//==================================================================================
//== INSTÂNCIA DAS VARIÁVEIS GLOBAIS DECLARADAS NESTE MÓDULO                      ==
//==================================================================================
unsigned char byI2cWriteByteReturn;
unsigned char byACKLido;

//==================================================================================
//== FUNÇÕES                                                                      ==
//==================================================================================

//------------------
//-- Acelerômetro --
//------------------

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : void I2CDISCR_Accel_InicializaBarramentoI2C(void)                --
//--                                                                              --
//-- Descrição : Inicializa (RESET) o barramento I2C                              --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------
void I2CDISCR_Accel_InicializaBarramentoI2C(void)
{
  LAT_SDA_ACCEL = 0;
  LAT_SCL_ACCEL = 0;
  TRIS_SDA_ACCEL = TRIS_SAIDA;
  TRIS_SCL_ACCEL = TRIS_SAIDA;

  MAIN_Delay_10us();

  TRIS_SDA_ACCEL = TRIS_ENTRADA;
  Nop();
  Nop();
  Nop();
  TRIS_SCL_ACCEL = TRIS_ENTRADA;  
  Nop();
  Nop();
  Nop();
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : void I2CDISCR_Accel_GeraStartBit(void)                           --
//--                                                                              --
//-- Descrição : Gera o START BIT do Protocolo I2C                                --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------
void I2CDISCR_Accel_GeraStartBit(void)
{
  TRIS_SCL_ACCEL = TRIS_ENTRADA;
  TRIS_SDA_ACCEL = TRIS_ENTRADA;
  MAIN_Delay_1us();
  LAT_SDA_ACCEL = 0;
  TRIS_SDA_ACCEL = TRIS_SAIDA;
  MAIN_Delay_10us();
  LAT_SCL_ACCEL = 0;
  TRIS_SCL_ACCEL = TRIS_SAIDA;
  MAIN_Delay_10us(); 
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : void I2CDISCR_Accel_GeraStopBit(void)                            --
//--                                                                              --
//-- Descrição : Gera o STOP BIT do Protocolo I2C                                 --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------
void I2CDISCR_Accel_GeraStopBit(void)
{
  LAT_SCL_ACCEL = 0;
  TRIS_SCL_ACCEL = TRIS_SAIDA;
  LAT_SDA_ACCEL = 0;
  TRIS_SDA_ACCEL = TRIS_SAIDA;
  MAIN_Delay_1us();
  TRIS_SCL_ACCEL = TRIS_ENTRADA;
  MAIN_Delay_10us();
  TRIS_SDA_ACCEL = TRIS_ENTRADA;
  MAIN_Delay_10us(); 
}

//
//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : void I2CDISCR_Accel_WriteByte(unsigned char byI2CDadoWr)         --
//--                                                                              --
//-- Descrição : Escreve um byte no barramento I2C                                --
//--                                                                              --
//-- Entrada   : byI2CDadoWr - Dado a escrever no barramento I2C                  --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------
void I2CDISCR_Accel_WriteByte(unsigned char byI2CDadoWr)
{
  unsigned char byIWrByteI2C;
  unsigned char byBitSDA;

  for (byIWrByteI2C = 0; byIWrByteI2C < 8; byIWrByteI2C++)
  {
    byBitSDA = (byI2CDadoWr >> (7 - byIWrByteI2C)) & 0x01;
    if (byBitSDA == 0)
    {
      LAT_SDA_ACCEL = 0;
      TRIS_SDA_ACCEL = TRIS_SAIDA;
    }
    else
    {
      TRIS_SDA_ACCEL = TRIS_ENTRADA;
    }
    MAIN_Delay_1us();
    TRIS_SCL_ACCEL = TRIS_ENTRADA;
    MAIN_Delay_10us();
    LAT_SCL_ACCEL = 0;
    TRIS_SCL_ACCEL = TRIS_SAIDA;
    MAIN_Delay_1us();
  }
  TRIS_SDA_ACCEL = TRIS_ENTRADA;
  MAIN_Delay_1us();
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : unsigned char I2CDISCR_Accel_ReadByte(void)                      --
//--                                                                              --
//-- Descrição : Leu um byte do barramento I2C                                    --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : Dado lido do barramento I2C                                      --
//--                                                                              --
//----------------------------------------------------------------------------------
unsigned char I2CDISCR_Accel_ReadByte(void)
{
  unsigned char byI2CDadoRd;
  unsigned char byBitLidoI2C;
  unsigned char byIRdByteI2C;

  byI2CDadoRd = 0;
  
  TRIS_SDA_ACCEL = TRIS_ENTRADA;
  for (byIRdByteI2C = 0; byIRdByteI2C < 8; byIRdByteI2C++)
  {
    TRIS_SCL_ACCEL = TRIS_ENTRADA;
    MAIN_Delay_10us();
    byBitLidoI2C = PIN_SDA_ACCEL;
    byI2CDadoRd = (byI2CDadoRd << 1) | byBitLidoI2C;
    MAIN_Delay_1us();
    LAT_SCL_ACCEL = 0;
    TRIS_SCL_ACCEL = TRIS_SAIDA;
    MAIN_Delay_1us();
  }

  return (byI2CDadoRd); 
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : void I2CDISCR_Accel_LeACK(void)                                  --
//--                                                                              --
//-- Descrição : Le o ACK gerado pelo SLAVE                                       --
//--                                                                              --
//-- Entrada   : Nenhuma                                                          --
//--                                                                              --
//-- Saida     : ACK Lido                                                         --
//--                                                                              --
//----------------------------------------------------------------------------------
unsigned char I2CDISCR_Accel_LeACK(void)
{
  unsigned char byACKLidoI2C;

  TRIS_SCL_ACCEL = TRIS_ENTRADA;
  MAIN_Delay_1us();
  byACKLidoI2C = PIN_SDA_ACCEL;
  MAIN_Delay_10us();
  LAT_SCL_ACCEL = 0;
  TRIS_SCL_ACCEL = TRIS_SAIDA;
  MAIN_Delay_10us();
  MAIN_Delay_10us();

  return (byACKLidoI2C);
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    : void I2CDISCR_Accel_GeraACK_NAK(void)                            --
//--                                                                              --
//-- Descrição : Gera ACK ou NAK para o SLAVE                                     --
//--                                                                              --
//-- Entrada   : byACK_NAK - Dado a escrever como ACK ("0") ou NAK ("1")          --
//--                                                                              --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------
void I2CDISCR_Accel_GeraACK_NAK(unsigned char byACK_NAK)
{
  if (byACK_NAK == 0)
  {
    //-- ACK --
    LAT_SDA_ACCEL = 0;
    TRIS_SDA_ACCEL = TRIS_SAIDA;
  }
  else
  {
    //-- NAK --
    TRIS_SDA_ACCEL = TRIS_ENTRADA;
  }
  MAIN_Delay_1us();
  TRIS_SCL_ACCEL = TRIS_ENTRADA;
  MAIN_Delay_10us();
  LAT_SCL_ACCEL = 0;
  TRIS_SCL_ACCEL = TRIS_SAIDA;
  TRIS_SDA_ACCEL = TRIS_ENTRADA;
  MAIN_Delay_10us();
  MAIN_Delay_10us();
}

//==================================================================================
//== FIM DO ARQUIVO I2CDiscr.c                                                    ==
//==================================================================================
