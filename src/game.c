#include "game.h"

NAKED void _gameUpdate(uint16_t dt) { 
	asm volatile ("jmp gameUpdate");
}
NAKED void _gameSetup() { 
	asm volatile ("jmp gameSetup");
}
