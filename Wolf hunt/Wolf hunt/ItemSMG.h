#pragma once
#include "Item.h"
class ItemSMG :
	public Item
{
public:
	ItemSMG();
	~ItemSMG();
	float InnSpeed(float Speed) override;
};

