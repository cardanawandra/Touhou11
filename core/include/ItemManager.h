#pragma once
#include "Chireiden.h"
#include "Chain.h"
#include "Item.h"
#include "Macros.h"

class ItemManager
{
public:
	uint32_t flags;
	uint32_t idk1;
	ChainElem* onTick;
	ChainElem* onDraw;
	uint32_t idk2;
	Item normalItems[150];
	Item cancelItems[2048];
	int numItemsAlive;
	int nextCancelItemIndex;
	int numCancelledItemsSpawnedThisFrame;

	void spawnItem(ItemManager* This, D3DXVECTOR3* spawnLocation, int someMode, D3DCOLOR param_3, float angle, float scale);
};
ASSERT_SIZE(ItemManager, 0x265e70);