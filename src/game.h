#pragma once
#include "util.h"

#define GCODE __attribute__((section(".game")))

extern void NOINLINE GCODE gameSetup();
extern void NOINLINE GCODE gameUpdate(uint16_t dt);

void NOINLINE SECTION(.gamesetup) _gameSetup();
void NOINLINE SECTION(.gameupdate) _gameUpdate(uint16_t dt);
