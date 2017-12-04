#include "utilities.h"

void delay(uint16_t a, uint16_t d)
{
	uint16_t i, j;
	for(j=0; j<a; j++) for(i=0; i<d; i++);
}