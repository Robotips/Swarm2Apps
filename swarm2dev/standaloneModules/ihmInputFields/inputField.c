#include "inputField.h"

char b[4];
int8_t i = 0, flipFlop[3] = {true}, letter = 65;

void ihm_init()
{
	rt_dev_t i2c_ihm = i2c(OLED_I2C_BUS);
    i2c_open(i2c_ihm);
    i2c_setBaudSpeed(i2c_ihm, I2C_BAUD_400K);
    i2c_enable(i2c_ihm);
    gui_init(i2c_ihm);
	gui_setFont(&Lucida_Console10);
    gui_setBrushColor(0);
    gui_setPenColor(1);
}

void input_field_set_title(input_field *input , char *inputField_title)
{
	input->title = inputField_title;
}

void input_field_set_type(input_field *input, input_type type)
{
	input->field_type = type;
}

void show_input_field(input_field *input, char *buffer)
{
	input->textTyped = buffer;
	
	gui_drawTextRect(0, 0, gui_screenWidth(), 15, input->title, GUI_FONT_ALIGN_VMIDDLE);
	
	gui_ctrl_update();
}

void button_flipFlop(uint8_t button, int8_t *fl, int8_t *var, bool inc)
{
	if(*fl && board_getButton(button))
	{	if(inc)
			(*var)++;
		else
			(*var)--;
			
		*fl = false;
	}
	
	if(!*fl && !board_getButton(button))
	{
		*fl = true;
	}
}

void input_update(input_field *input)
{
	button_flipFlop(0, &flipFlop[0], &i, true);
	button_flipFlop(1, &flipFlop[1], &letter, false);
	button_flipFlop(2, &flipFlop[2], &letter, true);
	
	switch(input->field_type)
	{
		case ip_adress:
			break;
		case number:
			break;
		case alpha_numeric:
			if(board_getButton(0))
			{
				letter = 97;
			}
			if(letter == 123)letter = 45;
			
			if(letter == 58)letter = 65;
			
			if(letter == 91)letter = 97;
			
			/*if(letter == 123)letter = 45;
			
			if(letter == 58)letter = 65;
			
			if(letter == 91)letter = 97;*/
			
			break;
	}
	
	(input->textTyped)[i] = letter;
	
	gui_drawTextRect(0, 20, gui_screenWidth(), 15, input->textTyped,GUI_FONT_ALIGN_HMIDDLE);
	
	gui_ctrl_update();
	
}
