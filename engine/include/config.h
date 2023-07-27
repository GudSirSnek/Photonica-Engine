#pragma once

#include "input.h"
#include <stdint.h>


typedef struct config{
    uint8_t keybinds[5];
    
}Config_State;

void config_init(void);

void config_key_bind(Input_Key key, const char *key_name);