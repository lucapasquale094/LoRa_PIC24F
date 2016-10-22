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
//== Módulo     : Accel.h                                                         ==
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
#include <p24F16KL402.h>

//==================================================================================
//== DECLARAÇÃO DOS PROTÓTIPOS DAS FUNÇÕES                                        ==
//==================================================================================
extern void ACCEL_InicializaLIS3DSH(void);
extern void ACCEL_InicializaStateMachine1LIS3DSH(void);
extern void ACCEL_WriteByte(unsigned char, unsigned char);
extern unsigned char ACCEL_ReadByte(unsigned char );
extern void GPIO_TrataAcelerometro(void);

//==================================================================================
//== DEFINIÇÕES                                                                   ==
//==================================================================================
#define LIS3DSH_TEMPERATURE      0x0C
#define LIS3DSH_INFO1            0x0D
#define LIS3DSH_INFO2            0x0E
#define LIS3DSH_WHO_AM_I         0x0F
#define LIS3DSH_INTERRUPT_SYNC   0x18
#define LIS3DSH_CTRL_REG4        0x20
#define LIS3DSH_CTRL_REG1        0x21
#define LIS3DSH_CTRL_REG2        0x22
#define LIS3DSH_CTRL_REG3        0x23
#define LIS3DSH_CTRL_REG5        0x24
#define LIS3DSH_CTRL_REG6        0x25
#define LIS3DSH_STATUS_REG       0x27
#define LIS3DSH_OUT_X_L          0x28
#define LIS3DSH_OUT_X_H          0x29
#define LIS3DSH_OUT_Y_L          0x2A
#define LIS3DSH_OUT_Y_H          0x2B
#define LIS3DSH_OUT_Z_L          0x2C
#define LIS3DSH_OUT_Z_H          0x2D
#define LIS3DSH_FIFO_CTRL_REG    0x2E
#define LIS3DSH_FIFO_SRC_REG     0x2F

#define LIS3DSH_ST1_01           0x40
#define LIS3DSH_ST1_02           0x41
#define LIS3DSH_ST1_03           0x42
#define LIS3DSH_ST1_04           0x43
#define LIS3DSH_ST1_05           0x44
#define LIS3DSH_ST1_06           0x45
#define LIS3DSH_ST1_07           0x46
#define LIS3DSH_ST1_08           0x47
#define LIS3DSH_ST1_09           0x48
#define LIS3DSH_ST1_10           0x49
#define LIS3DSH_ST1_11           0x4A
#define LIS3DSH_ST1_12           0x4B
#define LIS3DSH_ST1_13           0x4C
#define LIS3DSH_ST1_14           0x4D
#define LIS3DSH_ST1_15           0x4E
#define LIS3DSH_ST1_16           0x4F
#define LIS3DSH_TIM3_1           0x51
#define LIS3DSH_THRS1_1          0x57
#define LIS3DSH_MASK1_B          0x59
#define LIS3DSH_MASK1_A          0x5A
#define LIS3DSH_SETT1            0x5B
#define LIS3DSH_OUTS1            0x5F


#define LIS3DSH_CONTROL_BYTE_WR  0b00111100  //0x3C
#define LIS3DSH_CONTROL_BYTE_RD  0b00111101  //0x3D

//==================================================================================
//== DECLARAÇÃO DAS VARIÁVEIS GLOBAIS DESTE MÓDULO                                ==
//==================================================================================
extern unsigned char  byAccelINT;
extern unsigned char  byPIN_ACCEL;

//==================================================================================
//== Fim do arquivo Accel.h                                                       ==
//==================================================================================
