#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"
#include "fonts.h"

//Height = 64
//Width = 128

char led=0;
void tt()
{
    board_setLed(1, led++);
}

void clearScreen()
{
	gui_fillScreen(0);
	//gui_drawFillRect(0, 15, 127, 0);
}

int main(void)
{
    uint16_t i, j, h;
    rt_dev_t uartDbg;
    uint16_t value;
    char buffer[100];

    archi_init();
    //sysclock_setClock(200000000);
    sysclock_setClockDiv(SYSCLOCK_CLOCK_TIMER, 16);
    sysclock_setClockDiv(SYSCLOCK_CLOCK_UART, 16);

    board_init();

    //board_setLed(1, 1);

    gui_init(0);

    // uart debug init
    uartDbg = uart(2);
    uart_open(uartDbg);
    uart_setBaudSpeed(uartDbg, 250000);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);
    uart_write(uartDbg, "OK", 2);

    // init timer
    rt_dev_t timer;
    timer = timer_getFreeDevice();
    timer_setPeriodMs(timer, 1000);
    timer_setHandler(timer, tt);
    timer_enable(timer);

    // console init
    cmdline_init();
    cmdline_setDevice(uartDbg, uartDbg);

#ifdef OLED_I2C_BUS
    rt_dev_t i2c_ihm = i2c(OLED_I2C_BUS);
    i2c_open(i2c_ihm);
    i2c_setBaudSpeed(i2c_ihm, I2C_BAUD_400K);
    i2c_enable(i2c_ihm);
    gui_init(i2c_ihm);
    gui_setFont(&Lucida_Console10);
    gui_setBrushColor(0);
    gui_setPenColor(1);

    //gui_drawLine(0, 15, 127, 15);
    //gui_setBrushColor(1);
    //gui_drawFillRect(12, 12, 26, 12);

    //Test function to write on the screen
    for(h=0; h<=50; h++)
    {
		sprintf(buffer,"Indice : %d", h);
		for(j=0; j<5; j++) for(i=0; i<65000; i++);
    	clearScreen();
	    gui_drawText(0,10,buffer);
	    gui_ctrl_update();
	}
	clearScreen();
	gui_drawText(15,21,"Terminer !");
	gui_ctrl_update();
    
#endif

    while(1)
    {
        cmdline_task();

        board_setLed(2, 1);
        for(j=0; j<5; j++) for(i=0; i<65000; i++);
        board_setLed(2, 0);
        for(j=0; j<5; j++) for(i=0; i<65000; i++);
    }

    return 0;
}