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
//== Módulo     : Uart.c                                                          ==
//== Descrição  : Módulo de acesso à UART1, UART2, UART3 e UART4                  ==
//==                                                                              ==
//==------------------------------------------------------------------------------==
//==------------------------------------------------------------------------------==
//==------------------------------------------------------------------------------==
//== UART1 = MODEM GSM                                                            ==
//== UART2 = GPS                                                                  ==
//== UART3 = RS-232                                                               ==
//== UART4 = RS-485                                                               ==
//==------------------------------------------------------------------------------==
//==------------------------------------------------------------------------------==
//==------------------------------------------------------------------------------==
//==                                                                              ==
//== Autor      : Nilton Gomes Valente - VAGON Engenharia LTDA                    ==
//== Email      : nilton@vagon.com.br                                             ==
//==                                                                              ==
//==================================================================================

//==================================================================================
//== INCLUDES                                                                     ==
//==================================================================================
#include "Uart.h"
#include "Main.h"
#include "Interrupt.h"

//==================================================================================
//== INSTÂNCIA DAS VARIÁVEIS GLOBAIS DECLARADAS NESTE MÓDULO                      ==
//==================================================================================
ST_UART stUART1;
ST_UART stUART2;
ST_UART stUART3;
ST_UART stUART4;

unsigned char byBufferUART1Tx[TAM_BUFF_TX_UART1];
unsigned char byBufferUART1Rx[TAM_BUFF_RX_UART1];
unsigned char byBufferUART2Tx[TAM_BUFF_TX_UART2];
unsigned char byBufferUART2Rx[TAM_BUFF_RX_UART2];

unsigned char byQtdCrLfIntermediarios;
unsigned char* pbyBufferRxUART1;
//==================================================================================
//== FUNÇÕES                                                                      ==
//==================================================================================
//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    : UART_UART1Init()                                                 --
//-- Descricao :                                                                  --
//-- Entrada   : Nenhuma                                                          --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void UART_UART1Init(void) {
    //LAT_RF6_UART1_DIR = RS485_RX;

    U1MODEbits.UARTEN = 1; //-- Habilita UART1
    U1MODEbits.USIDL = 1; //-- Não opera em IDLE
    U1MODEbits.IREN = 0; //-- Encoder IrDA desabilitado
    U1MODEbits.RTSMD = 0; //-- U1RTS no modo flow
    U1MODEbits.UEN = 0; //-- Não usa CTS e RTS
    U1MODEbits.WAKE = 0; //-- Não acorda no start bit
    U1MODEbits.LPBACK = 0; //-- Desabilita loopback
    U1MODEbits.ABAUD = 0; //-- Sem autobaud
    U1MODEbits.RXINV = 0; //-- U1RX qdo em IDLE é "1"
    U1MODEbits.PDSEL = 0; //-- 8 bits, sem paridade
    U1MODEbits.STSEL = 0; //-- 1 stop bit

    U1STAbits.UTXISEL1 = 0; //-- Interrupção quando o buffer de transmissão estiver vazio
    U1STAbits.UTXISEL0 = 0; //-- Interrupção quando o buffer de transmissão estiver vazio
    U1STAbits.UTXINV = 0; //-- U1TX qdo em IDLE é "1"
    U1STAbits.UTXBRK = 0; //-- Sync Break é desarmado
    U1STAbits.UTXEN = 1; //-- U1TX controlado pela UART1
    U1STAbits.URXISEL = 0; //-- Interrupção a cada caractere recebido
    U1STAbits.ADDEN = 0; //-- Detecção de endereço desabilitada
    U1STAbits.OERR = 0; //-- Error (buffer de recepção cheio)

    //U1MODEbits.BRGH		= 0;    //-- Standard speed mode
    U1MODEbits.BRGH = 1; //-- High speed mode
    U1BRG = 103; //-- Fclock = 8MHz (Fcy = FOSC/2  = 4MHz) - Baud Rate = 9600
    //-- UxBRG = (FCY / ((4 ^ (2 - BRGH)) * BaudRate)) - 1

    IFS0bits.U1TXIF = 0; //-- Limpa o Flag de Interrupção
    IEC0bits.U1TXIE = 0; //-- Interrupção desabilitada
    IPC3bits.U1TXIP = 5; //-- Valor Default no RESET do PIC24

    IFS0bits.U1RXIF = 0; //-- Limpa o Flag de Interrupção
    IEC0bits.U1RXIE = 1; //-- Interrupção habilitada
    IPC2bits.U1RXIP = 5; //-- Valor Default no RESET do PIC24

    IFS4bits.U1ERIF = 0; //-- Limpa o Flag de Interrupção
    IEC4bits.U1ERIE = 0; //-- Interrupção desabilitada
    IPC16bits.U1ERIP = 5; //-- Valor Default no RESET do PIC24

}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    : UART1_ProcessaByteRecebido()                                     --
//-- Descricao : Processa os dados recebidos do MODEM                             --
//-- Entrada   : Dado recebido pela Rotina de Interrupção da UART1                --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void UART_UART1ProcessaByteRecebido(unsigned char byDadoRx1) {
    //  unsigned char           byXInt;

    Nop();
    Nop();
    Nop();

    //  //------------------------------------------------------------------------
    //  //-- Tempo máximo para recebimento do próximo byte.                     --
    //  //-- Se ficar 200ms sem receber o proximo byte, entao recomeça processo --
    //  //------------------------------------------------------------------------
    //  //if (stUART1.byTimeOut == TRUE) {
    //  //  //--------------------
    //  //  //-- Houve Time Out --
    //  //  //--------------------
    //  //  UART1_Inicializa();                           //-- Inicializa UART1 - MODEM
    //  //}
    //  //else 
    //  //{
    //  //  stUART1.wTimeOut = K_TEMPO_500_ms;
    //  //  stUART1.byTimeOut = FALSE;
    //  //  if ((RCSTA1bits.OERR == 1) || (RCSTA1bits.FERR == 1))
    //  //  {
    //  //    UART1_Inicializa();                           //-- Inicializa UART1 - MODEM
    //  //  }
    //  //  else
    //  //  {
    //      if (stUART1.byBufferOk == FALSE)
    //      {
    //        switch (stUART1.byEstadoAtual)
    //        {
    //          case MODEM_Aguardando_CR_Inicial:
    //          {
    //            if (byDadoRx1 == ASCII_CR)
    //            {
    //              stUART1.wIndexBuffer = 0;
    //              stUART1.byEstadoAtual = MODEM_Aguardando_LF_Inicial;
    //            }
    //            break;
    //          }
    //
    //
    //          case MODEM_Aguardando_LF_Inicial:
    //          {
    //            if (byDadoRx1 == ASCII_LF)
    //            {
    //              stUART1.byEstadoAtual = MODEM_Aguardando_LF_Intermediario_ou_O;
    //            }
    //            break;
    //          }
    //
    //
    //          case MODEM_Aguardando_LF_Intermediario_ou_O:
    //          {
    //            *(byBufferUART1Rx + stUART1.wIndexBuffer) = byDadoRx1;
    //            stUART1.wIndexBuffer++;
    //            if (((byDadoRx1 == '@') || (byDadoRx1 == '>')) && (stModem.byAguardandoArrobaOuMaior == 0xFF))
    //            {
    //              *(byBufferUART1Rx + stUART1.wIndexBuffer) = 0x00;
    //              stUART1.byBufferOk = TRUE;
    //              stUART1.wIndexBuffer = 0;
    //              stUART1.byEstadoAtual = MODEM_Aguardando_CR_Inicial;
    //            }
    //            else
    //            {
    //              if (byDadoRx1 == ASCII_LF)
    //              {
    //                if ((byBufferUART1Rx[0] == 'E') &&
    //                    (byBufferUART1Rx[1] == 'R') &&
    //                    (byBufferUART1Rx[2] == 'R') &&
    //                    (byBufferUART1Rx[3] == 'O') &&
    //                    (byBufferUART1Rx[4] == 'R'))
    //                {
    //                  stUART1.byEstadoAtual = MODEM_Aguardando_LF_Final;
    //                }
    //                else
    //                {
    //                  if ((byBufferUART1Rx[0] == '+') &&
    //                      (byBufferUART1Rx[1] == 'U') &&
    //                      (byBufferUART1Rx[2] == 'U'))
    //                  {
    //                    if ((byBufferUART1Rx[3] == 'L') &&
    //                        (byBufferUART1Rx[4] == 'O') &&
    //                        (byBufferUART1Rx[5] == 'C'))
    //                    {
    //    
    ////                      byDataHoraGSM[0] = byBufferUART1Rx[8];
    ////                      byDataHoraGSM[1] = byBufferUART1Rx[9];
    ////                      byDataHoraGSM[2] = byBufferUART1Rx[11];
    ////                      byDataHoraGSM[3] = byBufferUART1Rx[12];
    ////                      byDataHoraGSM[4] = byBufferUART1Rx[16];
    ////                      byDataHoraGSM[5] = byBufferUART1Rx[17];
    ////                      byDataHoraGSM[6] = byBufferUART1Rx[19];
    ////                      byDataHoraGSM[7] = byBufferUART1Rx[20];
    ////                      byDataHoraGSM[8] = byBufferUART1Rx[22];
    ////                      byDataHoraGSM[9] = byBufferUART1Rx[23];
    ////                      byDataHoraGSM[10] = byBufferUART1Rx[25];
    ////                      byDataHoraGSM[11] = byBufferUART1Rx[26];
    //
    //                      for (byXInt = 0; byXInt < 13; byXInt++)
    //                      {
    //                        byLat_LBS[byXInt] = 0x00;
    //                        byLong_LBS[byXInt] = 0x00;
    //                        if (byXInt < 11)
    //                        {
    //                          byMaxErr_LBS[byXInt] = 0x00;
    //                        }
    //                      }                      
    //                      ptrBufferAuxRxUART1 = &byBufferUART1Rx[0];
    //                      while (*(ptrBufferAuxRxUART1) != ',')
    //                      {
    //                        ptrBufferAuxRxUART1++;
    //                      }
    //                      ptrBufferAuxRxUART1++;
    //                      while (*(ptrBufferAuxRxUART1) != ',')
    //                      {
    //                        ptrBufferAuxRxUART1++;
    //                      }
    //                      ptrBufferAuxRxUART1++;
    //                      byXInt = 0;
    //                      while (*(ptrBufferAuxRxUART1) != ',')
    //                      {
    //                        byLat_LBS[byXInt++] = *(ptrBufferAuxRxUART1);
    //                        ptrBufferAuxRxUART1++;
    //                      }
    //                      ptrBufferAuxRxUART1++;
    //                      byXInt = 0;
    //                      while (*(ptrBufferAuxRxUART1) != ',')
    //                      {
    //                        byLong_LBS[byXInt++] = *(ptrBufferAuxRxUART1);
    //                        ptrBufferAuxRxUART1++;
    //                      }
    //                      ptrBufferAuxRxUART1++;
    //                      while (*(ptrBufferAuxRxUART1) != ',')
    //                      {
    //                        ptrBufferAuxRxUART1++;
    //                      }
    //                      ptrBufferAuxRxUART1++;
    //                      byXInt = 0;
    //                      while (*(ptrBufferAuxRxUART1) != ',')
    //                      {
    //                        byMaxErr_LBS[byXInt++] = *(ptrBufferAuxRxUART1);
    //                        ptrBufferAuxRxUART1++;
    //                      }
    //    
    //                      byRecebeuUULOC = TRUE;
    //                      stUART1.byBufferOk = TRUE;
    //                      stUART1.wIndexBuffer = 0;
    ////                      stUART1.byEstadoAtual = MODEM_Aguardando_CR_Inicial;
    //                    }
    //                    stUART1.byEstadoAtual = MODEM_Aguardando_CR_Inicial;
    ////                    else
    ////                    {
    ////                      stUART1.byEstadoAtual = MODEM_Aguardando_LF_Final;
    ////                    }
    //
    //                  }
    //                  else
    //                  {
    //                    stUART1.byEstadoAtual = MODEM_Aguardando_O;
    //                  }
    //                }
    //              }
    //              else
    //              {
    //                if (byDadoRx1 == 'O')
    //                {
    //                  stUART1.byEstadoAtual = MODEM_Aguardando_K;
    //                }
    //              }
    //            }
    //            break;
    //          }
    //
    //
    //          case MODEM_Aguardando_O:
    //          {
    //            *(byBufferUART1Rx + stUART1.wIndexBuffer) = byDadoRx1;
    //            stUART1.wIndexBuffer++;
    //            if (byDadoRx1 == 'O')
    //            {
    //              stUART1.byEstadoAtual = MODEM_Aguardando_K;
    //            }
    //            else
    //            {
    //              stUART1.byEstadoAtual = MODEM_Aguardando_LF_Intermediario_ou_O;
    //            }
    //            break;
    //          }
    //
    //
    //          case MODEM_Aguardando_K:
    //          {
    //            *(byBufferUART1Rx + stUART1.wIndexBuffer) = byDadoRx1;
    //            stUART1.wIndexBuffer++;
    //            if (byDadoRx1 == 'K')
    //            {
    //              stUART1.byEstadoAtual = MODEM_Aguardando_CR_Final;
    //            }
    //            else
    //            {
    //              stUART1.byEstadoAtual = MODEM_Aguardando_LF_Intermediario_ou_O;
    //            }
    //            break;
    //          }
    //
    //
    //          case MODEM_Aguardando_CR_Final:
    //          {
    //            *(byBufferUART1Rx + stUART1.wIndexBuffer) = byDadoRx1;
    //            stUART1.wIndexBuffer++;
    //            if (byDadoRx1 == ASCII_CR)
    //            {
    //              stUART1.byEstadoAtual = MODEM_Aguardando_LF_Final;
    //            }
    //            else
    //            {
    //              stUART1.wIndexBuffer = 0;
    //              stUART1.byEstadoAtual = MODEM_Aguardando_CR_Inicial;  
    //            }
    //            break;
    //          }
    //
    //
    //          case MODEM_Aguardando_LF_Final:
    //          {
    //            *(byBufferUART1Rx + stUART1.wIndexBuffer) = byDadoRx1;
    //            stUART1.wIndexBuffer++;
    //            if (byDadoRx1 == ASCII_LF)
    //            {
    //              *(byBufferUART1Rx + stUART1.wIndexBuffer) = 0x00;
    //              stUART1.byBufferOk = TRUE;
    //            }
    //            stUART1.wIndexBuffer = 0;
    //            stUART1.byEstadoAtual = MODEM_Aguardando_CR_Inicial;
    //            break;
    //          }
    //        }
    //
    //
    //        if (stUART1.wIndexBuffer >= TAM_BUFF_RX_UART1)
    //        {
    //          stUART1.wIndexBuffer = 0;
    //          stUART1.byEstadoAtual = MODEM_Aguardando_LF_Inicial;
    //          stUART1.byBufferOk = FALSE;
    //        }
    //      }

    //  }
    //}
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    : UART1_EnviaTxBuffer()                                            --
//-- Descricao :                                                                  --
//-- Entrada   : Buffer dos dados a Transmitir e respectiva Quantidade de Bytes   --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void UART_UART1EnviaTxBuffer(unsigned int wQtdBytesTx) {
    unsigned int wI;

    MAIN_Delay_5ms();
    MAIN_Delay_5ms();
    MAIN_Delay_5ms();

    for (wI = 0; wI < wQtdBytesTx; wI++) {
        U1TXREG = byBufferUART1Tx[wI];
        while (U1STAbits.TRMT);
        MAIN_Delay_5ms();
    }
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    : UART_UART1EnviaBufferASCII()                                     --
//-- Descricao :                                                                  --
//-- Entrada   : Buffer dos dados a Transmitir terminado em 0x00                  --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void UART_UART1EnviaTxBufferASCII(unsigned char *byBufferTxASCII) {
    unsigned int wITxBufferASCII;

    for (wITxBufferASCII = 0; *(byBufferTxASCII + wITxBufferASCII) != 0x00; wITxBufferASCII++) {
        U1TXREG = *(byBufferTxASCII + wITxBufferASCII);
        while (U1STAbits.TRMT);
        MAIN_Delay_5ms();
    }
    Nop();
    Nop();
    Nop();
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    : UART2_InicializaUART()                                           --
//-- Descricao :                                                                  --
//-- Entrada   : Nenhuma                                                          --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void UART_UART2Init(void) {
    U2MODEbits.UARTEN = 1; //-- Habilita UART2
    U2MODEbits.USIDL = 1; //-- Não opera em IDLE
    U2MODEbits.IREN = 0; //-- Encoder IrDA desabilitado
    U2MODEbits.RTSMD = 0; //-- U2RTS no modo flow
    U2MODEbits.UEN = 0; //-- Não usa CTS e RTS
    U2MODEbits.WAKE = 0; //-- Não acorda no start bit
    U2MODEbits.LPBACK = 0; //-- Desabilita loopback
    U2MODEbits.ABAUD = 0; //-- Sem autobaud
    U2MODEbits.RXINV = 0; //-- U2RX qdo em IDLE é "1"
    U2MODEbits.PDSEL = 0; //-- 8 bits, sem paridade
    U2MODEbits.STSEL = 0; //-- 1 stop bit

    U2STAbits.UTXISEL1 = 0; //-- Interrupção quando o buffer de transmissão estiver vazio
    U2STAbits.UTXISEL0 = 0; //-- Interrupção quando o buffer de transmissão estiver vazio
    U2STAbits.UTXINV = 0; //-- U2TX qdo em IDLE é "1"
    U2STAbits.UTXBRK = 0; //-- Sync Break é desarmado
    U2STAbits.UTXEN = 1; //-- U2TX controlado pela UART2
    U2STAbits.URXISEL = 0; //-- Interrupção a cada caractere recebido
    U2STAbits.ADDEN = 0; //-- Detecção de endereço desabilitada
    U2STAbits.OERR = 0; //-- Error (buffer de recepção cheio)

    //U2MODEbits.BRGH		= 0;    //-- Standard speed mode
    U2MODEbits.BRGH = 1; //-- High speed mode
    U2BRG = 16; //-- Fclock = 8MHz (Fcy = FOSC/2  = 4MHz) - Baud Rate = 57600
    //-- UxBRG = (FCY / ((4 ^ (2 - BRGH)) * BaudRate)) - 1

    IFS1bits.U2TXIF = 0; //-- Limpa o Flag de Interrupção
    IEC1bits.U2TXIE = 0; //-- Interrupção desabilitada
    IPC7bits.U2TXIP = 5; //-- Valor Default no RESET do PIC24

    IFS1bits.U2RXIF = 0; //-- Limpa o Flag de Interrupção
    IEC1bits.U2RXIE = 1; //-- Interrupção habilitada
    IPC7bits.U2RXIP = 5; //-- Valor Default no RESET do PIC24

    IFS4bits.U2ERIF = 0; //-- Limpa o Flag de Interrupção
    IEC4bits.U2ERIE = 0; //-- Interrupção desabilitada
    IPC16bits.U2ERIP = 5; //-- Valor Default no RESET do PIC24
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    : UART2_ProcessaByteRecebido()                                     --
//-- Descricao : Processa os dados recebidos do GPS                               --
//-- Entrada   : Dado recebido pela Rotina de Interrupção da UART2                --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void UART_UART2ProcessaByteRecebido(unsigned char byDadoRx2) {
    Nop();
    Nop();
    Nop();

    if ((U2STAbits.OERR == 1) || (U2STAbits.FERR == 1)) {
        UART_UART2Init(); //-- Inicializa UART2 - GPS
    } else {
        if (stUART2.byBufferOk == FALSE) {

            //Novo dado recebido, ja chegou ao fim?
            if (byDadoRx2 == ASCII_LF) {
                *(byBufferUART2Rx + stUART2.wIndexBuffer++) = byDadoRx2;
                stUART2.byBufferOk = TRUE;
            }
            else {
                *(byBufferUART2Rx + stUART2.wIndexBuffer++) = byDadoRx2;
            }

            //Se o buffer ficar maior que o limite, parar
            if (stUART2.wIndexBuffer >= TAM_BUFF_RX_UART2) {
                stUART2.wIndexBuffer = 0;
                stUART2.byBufferOk = FALSE;
            }
        }
    }
    //  }
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    : UART2_EnviaBuffer()                                              --
//-- Descricao :                                                                  --
//-- Entrada   : Buffer dos dados a Transmitir e respectiva Quantidade de Bytes   --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void UART_UART2EnviaTxBuffer(unsigned int wQtdBytesTx) {
    unsigned int wI;

    for (wI = 0; wI < wQtdBytesTx; wI++) {
        U2TXREG = byBufferUART2Tx[wI];
        while (U2STAbits.TRMT);
        MAIN_Delay_5ms();
    }
}

//----------------------------------------------------------------------------------
//--                                                                              --
//-- Funcao    : UART_UART2EnviaBufferASCII()                                     --
//-- Descricao :                                                                  --
//-- Entrada   : Buffer dos dados a Transmitir terminado em 0x00                  --
//-- Saida     : Nenhuma                                                          --
//--                                                                              --
//----------------------------------------------------------------------------------

void UART_UART2EnviaTxBufferASCII(unsigned char *byBufferTxASCII) {
    unsigned int wITxBufferASCII;
    unsigned char byByteToTx;

    for (wITxBufferASCII = 0; *(byBufferTxASCII + wITxBufferASCII) != 0x00; wITxBufferASCII++) {
        byByteToTx = *(byBufferTxASCII + wITxBufferASCII);
        U2TXREG = byByteToTx;
        while (U2STAbits.TRMT);
        MAIN_Delay_5ms();
    }
    Nop();
    Nop();
    Nop();
    byBufferTxASCII = 0x00;
}

//==================================================================================
//== Fim do arquivo Uart.c                                                        ==
//==================================================================================
