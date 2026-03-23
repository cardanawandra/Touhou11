#pragma once
#include <stdint.h>

struct EclInstruction
{
	int32_t time;            // 0x0
	int16_t opcode;          // 0x4
	uint16_t offsetToNext;   // 0x6
	uint16_t paramMask;      // 0x8
	uint8_t difficultyMask;  // 0xA
	uint8_t paramCount;      // 0xB
	uint32_t dummy;          // 0xC
	unsigned char args[];    // 0x10
};