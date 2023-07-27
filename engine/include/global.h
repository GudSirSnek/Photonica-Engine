#pragma once
#include "input.h"
#include "config.h"

typedef struct global {
	Config_State config;
	Input_State input;
	//Time_State time;
} Global;

extern Global global;