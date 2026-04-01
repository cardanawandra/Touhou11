#pragma once
#include "Chireiden.h"
#include "AnmManager.h"
#include "Timer.h"
#include "Macros.h"
#include "Vectors.h"

struct Item
{
	AnmVm vm;
	Float3 vec3;
	Float2 vec2;
	int someInt_0x448;
	int someInt_0x44c;
	Timer timer;
	int someInt_0x464;
	int someInt_0x468;
	int someInt_0x46c;
	int shotFileRelated;
	int someInt_0x474;
};
ASSERT_SIZE(Item, 0x478);