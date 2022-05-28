#pragma once

#include "util.h"

C_BEGIN
void timerBegin();
void timerStop();
uint64_t timerMicros();
uint64_t timerMillis();
C_END
