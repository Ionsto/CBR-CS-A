#pragma once
#include "Item.h"
//This item fires a ray at an angle and blinds them if they are looking
class ItemBlinder :
	public Item
{
public:
	ItemBlinder();
	~ItemBlinder();
	HitStructure * RayCasting(World * world, Vector pos, float rot);
	virtual bool FireFrom(World * world, Vector pos, float rot);
};

