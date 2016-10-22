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
//== Módulo     : Accel.c                                                         ==
//== Descrição  : Módulo de tratamento do Acelerômetro (LIS3DSH)                  ==
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
#include "Accel.h"
#include "I2CDiscr.h"
#include "Main.h"
#include "Interrupt.h"

//==================================================================================
//== INSTÂNCIA DAS VARIÁVEIS GLOBAIS DECLARADAS NESTE MÓDULO                      ==
//==================================================================================
UN_INT_TO_CHAR unAccelEixoX;
UN_INT_TO_CHAR unAccelEixoY;
UN_INT_TO_CHAR unAccelEixoZ;
unsigned char  byAccelINT;
unsigned char  byPIN_ACCEL;

//==================================================================================
//== FUNÇÕES                                                                      ==
//==================================================================================
//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    :                                                                  --
//--                                                                              --
//-- Descrição :                                                                  --
//--                                                                              --
//-- Entrada   :                                                                  --
//--                                                                              --
//-- Saida     :                                                                  --
//--                                                                              --
//----------------------------------------------------------------------------------
void ACCEL_InicializaLIS3DSH(void)
{
  Nop();
  Nop();
  Nop();
  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG1,0b00000000);
  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG2,0b00000000);
  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG3,0b00000000);
  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG4,0b01101111);
  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG5,0b00000000);
  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG6,0b00010000);
  ACCEL_WriteByte((unsigned char)LIS3DSH_FIFO_CTRL_REG,0b00000000);
  Nop();
  Nop();
  Nop();
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    :                                                                  --
//--                                                                              --
//-- Descrição :                                                                  --
//--                                                                              --
//-- Entrada   :                                                                  --
//--                                                                              --
//-- Saida     :                                                                  --
//--                                                                              --
//----------------------------------------------------------------------------------
void ACCEL_InicializaStateMachine1LIS3DSH(void)
{
  Nop();
  Nop();
  Nop();

  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG6,0x10);
  ACCEL_WriteByte((unsigned char)LIS3DSH_FIFO_CTRL_REG,0x00);
  ACCEL_WriteByte((unsigned char)LIS3DSH_FIFO_SRC_REG,0x20);

  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG1,0x01);
  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG2,0x00);
  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG3,0x48);
  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG4,0x67);
  ACCEL_WriteByte((unsigned char)LIS3DSH_CTRL_REG5,0x00);
  ACCEL_WriteByte((unsigned char)LIS3DSH_THRS1_1,0x4F);
  ACCEL_WriteByte((unsigned char)LIS3DSH_ST1_01,0x05);
  ACCEL_WriteByte((unsigned char)LIS3DSH_ST1_02,0x11);
  ACCEL_WriteByte((unsigned char)LIS3DSH_MASK1_B,0xFC);
  ACCEL_WriteByte((unsigned char)LIS3DSH_MASK1_A,0xFC);
  ACCEL_WriteByte((unsigned char)LIS3DSH_SETT1,0x01);

  Nop();
  Nop();
  Nop();
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    :                                                                  --
//--                                                                              --
//-- Descrição :                                                                  --
//--                                                                              --
//-- Entrada   :                                                                  --
//--                                                                              --
//-- Saida     :                                                                  --
//--                                                                              --
//----------------------------------------------------------------------------------
void ACCEL_WriteByte(unsigned char byAccelWrAddress, unsigned char byAccelWrByte)
{
  unsigned char  byACKLido;
  
  Nop();
  Nop();
  Nop();

  I2CDISCR_Accel_GeraStartBit();
  I2CDISCR_Accel_WriteByte(LIS3DSH_CONTROL_BYTE_WR);   //-- Control Byte
  byACKLido = I2CDISCR_Accel_LeACK();
  Nop();
  Nop();
  Nop();
  I2CDISCR_Accel_WriteByte(byAccelWrAddress);         //-- Address High Byte
  byACKLido = I2CDISCR_Accel_LeACK();
  I2CDISCR_Accel_WriteByte(byAccelWrByte);            //-- Data Byte (Write)
  byACKLido = I2CDISCR_Accel_LeACK();
  I2CDISCR_Accel_GeraStopBit();

  MAIN_Delay_10us();
  Nop();
  Nop();
  Nop();
  MAIN_Delay_5ms();
  MAIN_Delay_5ms();
  MAIN_Delay_5ms();
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Função    :                                                                  --
//--                                                                              --
//-- Descrição :                                                                  --
//--                                                                              --
//-- Entrada   :                                                                  --
//--                                                                              --
//-- Saida     :                                                                  --
//--                                                                              --
//----------------------------------------------------------------------------------
unsigned char ACCEL_ReadByte(unsigned char byAccelRdAddress)
{
  unsigned char  byAccelRdByte;
  unsigned char  byACKLido;
  
  Nop();
  Nop();
  Nop();
  I2CDISCR_Accel_GeraStartBit();
  I2CDISCR_Accel_WriteByte(LIS3DSH_CONTROL_BYTE_WR);   //-- Control Byte
  byACKLido = I2CDISCR_Accel_LeACK();
  I2CDISCR_Accel_WriteByte(byAccelRdAddress);          //-- Sub Address (Register Address))
  byACKLido = I2CDISCR_Accel_LeACK();
  MAIN_Delay_10us();
  MAIN_Delay_10us();
  I2CDISCR_Accel_GeraStartBit();
  I2CDISCR_Accel_WriteByte(LIS3DSH_CONTROL_BYTE_RD);   //-- Control Byte
  byACKLido = I2CDISCR_Accel_LeACK();
  byAccelRdByte = I2CDISCR_Accel_ReadByte();           //-- Data Byte (Read))
  I2CDISCR_Accel_GeraACK_NAK(I2C_NAK);
  I2CDISCR_Accel_GeraStopBit();

  MAIN_Delay_10us();

  Nop();
  Nop();
  Nop();
  
  return (byAccelRdByte);
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    :                                                                  --
//-- Descricao :                                                                  --
//--                                                                              --
//--                                                                              --
//--                                                                              --
//-- Entrada   :                                                                  --
//-- Saida     :                                                                  --
//--                                                                              --
//----------------------------------------------------------------------------------
void GPIO_TrataAcelerometro(void)
{
  unsigned char byTrataAccelRetFunc;
  
  if (byAccelINT == TRUE)
  {
    byAccelINT = FALSE;
    byTrataAccelRetFunc = ACCEL_ReadByte(LIS3DSH_OUTS1);
  }

}

//==================================================================================
//== FIM DO ARQUIVO Accel.c                                                       ==
//==================================================================================
