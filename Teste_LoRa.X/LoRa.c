/*
 * File:   LoRa.c
 * Author: lucap
 *
 * Created on 21 de Outubro de 2016, 16:34
 */
#include <stdio.h>
#include "Uart.h"
#include "LoRa.h"
#include "Main.h"

void InitLoRa(void) {
    //Reseta o módulo LoRa
    SendCommand("sys reset\r\n");
    //SendCommand("mac get deveui\r\n");

    //Seta os parâmentros da rede para conectar na Orbiwise
    SendCommand("mac set devaddr 020155B1\r\n");
    SendCommand("mac set appskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");
    SendCommand("mac set nwkskey 2B7E151628AED2A6ABF7158809CF4F3C\r\n");
    SendCommand("mac set adr on\r\n");

    //Tenta se conectar na rede
    SendCommand("mac join abp\r\n");

    //Salva os parâmetros configurados
    SendCommand("mac save\r\n");
    //SendCommand("sys set pindig GPIO6 1\r\n");
}

void SendCommand(char * string) {

    //Limpa buffer RX
    int i;
    for (i = 0; i < sizeof (byBufferUART2Rx); i++)
        byBufferUART2Rx[i] = '\0';

    //Escreve no buffer de TX e envia pela UART
    sprintf((char *) byBufferUART2Tx, string);
    stUART2.wIndexBuffer = 0;
    stUART2.byBufferOk = 0;
    UART_UART2EnviaTxBufferASCII(byBufferUART2Tx);

    //Espera resposta do módulo no RX
    while (stUART2.byBufferOk != TRUE) {
        Nop();
    }
}
