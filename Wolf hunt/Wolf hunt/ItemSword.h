#pragma once
#include "Item.h"
class ItemSword :
	public Item
{
public:
	ItemSword();
	~ItemSword();
	bool FireFrom(World * world, Vector pos, float rot) override;
};

