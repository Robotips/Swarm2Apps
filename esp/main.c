#include "esp8266.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <board.h>

#include "driver/uart.h"
#include "sys/buffer.h"

// data receive from esp
uint8_t esp8266_socket = 0;
uint16_t esp8266_sizePacket = 0;
uint16_t esp8266_idPacket = 0;
uint8_t esp8266_flagPacket = 0;
char /*__attribute__((far))*/ esp8266_dataPacket[2049];

// station IP
char esp8266_ip[16] = "";
uint8_t esp8266_ipid = 0;
char esp8266_mac[18] = "";
uint8_t esp8266_macid = 0;


typedef enum
{
    FSM_UNKNOW = 0,
    FSM_WAITING_VALIDATE,
    FSM_START,

    FSM_ready_r,
    FSM_ready_e,
    FSM_ready_a,
    FSM_ready_d,
    FSM_ready_y,

    FSM_OK_O,
    FSM_OK_K,

    FSM_SENDOK_S,
    FSM_SENDOK_E,
    FSM_SENDOK_N,
    FSM_SENDOK_D,
    FSM_SENDOK_Sp,
    FSM_SENDOK_O,
    FSM_SENDOK_K,

    FSM_ERROR_E,
    FSM_ERROR_R1,
    FSM_ERROR_R2,
    FSM_ERROR_O,
    FSM_ERROR_R3,

    FSM_FAIL_F,
    FSM_FAIL_A,
    FSM_FAIL_I,
    FSM_FAIL_L,

    FSM_PLUS,

    FSM_IP_C,
    FSM_IP_I,
    FSM_IP_F,
    FSM_IP_S,
    FSM_IP_R,
    FSM_IP_dP,
    FSM_IP_S2,
    FSM_IP_T,
    FSM_IP_A,
    FSM_IP_WIP,
    FSM_IP_IP,
    FSM_IP_WMAC,
    FSM_IP_MAC,

    FSM_IPD_I,
    FSM_IPD_P,
    FSM_IPD_D,
    FSM_IPD_COMMA_1,
    FSM_IPD_SOCKET_DIGIT,
    FSM_IPD_COMMA_2,
    FSM_IPD_SIZE_DIGITS,
    FSM_PACKET_RX,
    FSM_RX_COMPLETE

} ESP8266_FSMSTATE;
volatile ESP8266_FSMSTATE esp8266_fsmState = FSM_START;

typedef enum
{
    ESP8266_STATE_NONE = 0,
    ESP8266_STATE_READY,
    ESP8266_STATE_OK,
    ESP8266_STATE_ERROR,
    ESP8266_STATE_FAIL,
    ESP8266_STATE_RECEIVE_DATA,
    ESP8266_STATE_SEND_DATA,
    ESP8266_STATE_SEND_OK
} ESP8266_STATE;
volatile ESP8266_STATE esp8266_pendingState = ESP8266_STATE_NONE;
volatile ESP8266_STATE esp8266_state = ESP8266_STATE_NONE;

typedef enum
{
    ESP8266_CMD_NONE = 0,
    ESP8266_CMD_CUSTOM,
    ESP8266_CMD_OPENTCP,
    ESP8266_CMD_OPENUDP,
    ESP8266_CMD_SETMODE,
    ESP8266_CMD_APCONFIG,
    ESP8266_CMD_CONNECTAP,
    ESP8266_CMD_DISCONNECTAP,
    ESP8266_CMD_CLOSESOCKET,
    ESP8266_CMD_WRITESOCK_REQ,
    ESP8266_CMD_WRITESOCK_DATA,
    ESP8266_CMD_SERVERCREATE,
    ESP8266_CMD_SERVERDESTROY
} ESP8266_CMD;
volatile ESP8266_CMD esp8266_currentCmd = ESP8266_CMD_NONE;

uint8_t esp8266_config = 0;

void esp8266_parse(char rec);

rt_dev_t esp8266_uart;

STATIC_BUFFER(esp8266_txBuff, 100);


int main(void)
{
	esp8266_init();
	esp8266_task();

}