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
//== Módulo     : I2CDiscr.h                                                      ==
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
#include <p24F16KL402.h>

//==================================================================================
//== DECLARAÇÃO DOS PROTÓTIPOS DAS FUNÇÕES                                        ==
//==================================================================================
extern void I2CDISCR_Accel_InicializaBarramentoI2C(void);
extern void I2CDISCR_Accel_GeraStartBit(void);
extern void I2CDISCR_Accel_GeraStopBit(void);
extern void I2CDISCR_Accel_WriteByte(unsigned char);
extern unsigned char I2CDISCR_Accel_ReadByte(void);
extern unsigned char I2CDISCR_Accel_LeACK(void);
extern void I2CDISCR_Accel_GeraACK_NAK(unsigned char);

extern void I2CDISCR_EEProm_InicializaBarramentoI2C(void);
extern void I2CDISCR_EEProm_GeraStartBit(void);
extern void I2CDISCR_EEProm_GeraStopBit(void);
extern void I2CDISCR_EEProm_WriteByte(unsigned char);
extern unsigned char I2CDISCR_EEProm_ReadByte(void);
extern unsigned char I2CDISCR_EEProm_LeACK(void);
extern void I2CDISCR_EEProm_GeraACK_NAK(unsigned char);
//==================================================================================
//== DEFINIÇÕES                                                                   ==
//==================================================================================
#define I2C_ACK 0
#define I2C_NAK 1

//==================================================================================
//== DECLARAÇÃO DAS VARIÁVEIS GLOBAIS DESTE MÓDULO                                ==
//==================================================================================
extern unsigned char byI2cWriteByteReturn;
extern unsigned char byACKLido;

//==================================================================================
//== Fim do arquivo I2CDiscr.h                                                    ==
//==================================================================================
