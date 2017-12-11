#include "inputField.h"

char b[4];
bool come_from_zero;
int8_t i = 0, flipFlop[3] = {true},letter = '0';
uint32_t timestamp = 0;

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
	
	switch(input->field_type)
	{
		case alpha_numeric:
			//On commence par un A
			letter = 'A';
			break;
		case ip_adress:
			letter = '0';
			break;
		default:
			break;
	}
	
	gui_drawTextRect(0, 0, gui_screenWidth(), 15, input->title, GUI_FONT_ALIGN_VMIDDLE);
	
	gui_ctrl_update();
}

void button_flipFlop(uint8_t button, int8_t *fl, int8_t *var, bool inc)
{
	if(*fl && board_getButton(button))
	{	
		gui_setPenColor(0);
		gui_drawLine(0, 35, gui_screenWidth(), 35);
		gui_setPenColor(1);
		
		if(inc)
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
	timestamp++; 
	
	switch(input->field_type)
	{
		case ip_adress:
			if(letter == '0')come_from_zero = true;
			if(letter == '.')come_from_zero = false;
			
			if(letter == 59)letter = 46;
			
			if(letter == 47 && !come_from_zero)letter = 48;
			else if(letter == 47 && come_from_zero) letter = 46;
			
			if(letter == 45)letter = 58;
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
			//----------------------------------
			if(letter == 96)letter = 90;
			
			if(letter == 64)letter = 57;
			
			if(letter == 44)letter = 122;
			
			break;
	}
	
	(input->textTyped)[i] = letter;
	uint8_t l =  gui_getFontTextWidth(input->textTyped);
	if(timestamp < 10)
	{
		gui_drawTextRect(0, 20, gui_screenWidth(), 15, input->textTyped,GUI_FONT_ALIGN_HMIDDLE|GUI_FONT_ALIGN_VLEFT);
		gui_setPenColor(0);
		gui_drawLine(0, 35, gui_screenWidth(), 35);
		gui_setPenColor(1);
	}
	else if(timestamp >= 10 && timestamp <= 20)
	{
		gui_drawTextRect(0, 20, gui_screenWidth(), 15, input->textTyped,GUI_FONT_ALIGN_HMIDDLE|GUI_FONT_ALIGN_VLEFT);
		gui_drawLine(l-7, 35, l-2, 35);
	}
	else
		timestamp = 0;
	
	gui_ctrl_update();
}
