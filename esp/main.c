#include "esp8266.h"

int main(void)
{
    board_init();
	esp8266_init();
	esp8266_task();
}