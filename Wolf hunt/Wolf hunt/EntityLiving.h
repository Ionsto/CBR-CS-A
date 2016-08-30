#pragma once
#include <SFML/Graphics.hpp>
#include "ItemRayCaster.h"
class EntityLiving :
	public Entity
{
public:
	sf::RectangleShape RenderCanvas;
	ItemRayCaster RayCaster;
	float MoveForce;
	EntityLiving(World * world, Vector pos = Vector());
	~EntityLiving();
	void Render(GameManager * gm);
	void SetSize(float size);
	void Update() override;
};

