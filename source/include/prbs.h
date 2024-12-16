
#pragma once

#include <stdint.h>

void prbs7_period(uint8_t start);
void prbs8_period(uint8_t start);
void prbs15_period(uint16_t start);
void prbs16_period(uint16_t start);
void prbs24_period(uint16_t start);
void prbs32_period(uint32_t start);

uint32_t prbs_next(const uint32_t bits, const uint32_t seed);
void prbs_fill(uint32_t* addr, uint32_t bits, uint32_t num, uint32_t seed);
bool prbs_check(uint32_t* addr, uint32_t bits, uint32_t num, uint32_t seed);
void prbs8_writeFile(char* filename, uint32_t num, uint8_t seed);
void prbs32_writeFile(char* filename, uint32_t num, uint32_t seed);

