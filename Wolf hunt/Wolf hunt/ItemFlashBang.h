#pragma once
#include "Item.h"
class ItemFlashBang :
	public Item
{
public:
	ItemFlashBang();
	~ItemFlashBang();
	bool FireFrom(World * world, Vector pos, float Rot);
};

