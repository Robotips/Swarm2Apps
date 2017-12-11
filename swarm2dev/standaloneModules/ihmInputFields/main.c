//My extra header files
#include "inputField.h"
#include "utilities.h"

int main(void)
{
	archi_init();
	sysclock_setClockDiv(SYSCLOCK_CLOCK_TIMER, 16);
    sysclock_setClockDiv(SYSCLOCK_CLOCK_UART, 16);

    board_init();
	
	//We initialize the screen
	ihm_init();
	
	char title[] = "MyInput", textToGet[100] = "";
	
	input_field wifi_input_field;
	
	input_field_set_title(&wifi_input_field,title);
	input_field_set_type(&wifi_input_field,ip_adress);
	
	show_input_field(&wifi_input_field,textToGet);
	//Main loop
	while(1)
	{
		input_update(&wifi_input_field);
	}
	
	return 0;
}