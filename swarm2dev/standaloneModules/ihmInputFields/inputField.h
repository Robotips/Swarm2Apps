#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"
#include "fonts.h"

void ihm_init();

typedef enum
{
    ip_adress,
    number,
    alpha_numeric

} input_type;

//input field struct
typedef struct
{
    char *title;
    char *textTyped;
    input_type field_type;
    int8_t is_frozen;
} input_field;

typedef enum
{
    false,true
} bool;

void input_field_set_title(input_field *input ,char *inputField_title);

void input_field_set_type(input_field *input, input_type type);

void show_input_field(input_field *input, char *buffer);

void input_update(input_field *input);

void button_flipFlop(uint8_t button, int8_t *fl, int8_t *var, bool inc);