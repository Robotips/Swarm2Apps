#include "esp8266.h"
#include "board.h"

int main(void)
{
    board_init();
	esp8266_init();
	esp8266_task();
    return 0;
}