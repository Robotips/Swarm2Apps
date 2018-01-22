#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"
#include "fonts.h"
#include "driver/i2c.h"
#include "../rtprog/support/module/sensor/driver/lsm6ds3/lsm6ds3.h"
#include "../rtprog/support/module/sensor/driver/lsm6ds3/lsm6ds3_registers.h"

char led=0;

void tt()
{
    board_setLed(1,led++);
}

void clearScreen()
{
	gui_fillScreen(0);
}

int main(void)
{
    uint16_t i;
    char buffer[100];
    char bufferB[100];
    char bufferT[100];
    rt_dev_t uartDbg;
    rt_dev_t i2c_bus;
    int16_t acc[3];

    board_init();
    //sysclock_setClock(200000000);
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
    gui_setFont(&Lucida_Console8);
    gui_setBrushColor(0);
    gui_setPenColor(1);

#endif

    //init accelerometer and gyroscope
    i2c_bus = i2c(4);
	i2c_open(i2c_bus);
	i2c_setBaudSpeed(i2c_bus, I2C_BAUD_400K);
	i2c_setAddressWidth(i2c_bus, 7);
	i2c_enable(i2c_bus);
    i2c_writereg(i2c_bus, 0xD6, LSM6DS3_CTRL1_XL, 0b00100000, 0); //Accel

    while(1)
    {
        #ifdef SIMULATOR
            usleep(1000);
        #endif
        
        cmdline_task();

        board_toggleLed(2);
        for(i=0; i<65000; i++);

	    i2c_readregs(i2c_bus, 0xD6, LSM6DS3_OUTX_L_XL, (uint8_t*)acc, 6, 0); //Accel

		//write the value of the acc/gyro in buffer's variables
		sprintf(buffer, "X : %d", acc[0]);  //Axe x
		sprintf(bufferB, "Y : %d", acc[1]); //Axe y
		sprintf(bufferT, "Z : %d", acc[2]); //Axe z

		//write on the screen the values
		gui_drawTextRect(0, 10, 120, 20, buffer, 0);
		gui_drawTextRect(0, 25, 120, 20, bufferB, 0);
		gui_drawTextRect(0, 40, 120, 20, bufferT, 0);

		gui_ctrl_update();
    }

    return 0;
}
