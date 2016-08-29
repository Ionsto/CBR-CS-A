#pragma once
#include "Entity.h"
#include <SFML\Graphics.hpp>
class EntitySwordEffect : public Entity
{
public:
	sf::RectangleShape line;
	EntitySwordEffect(World * world, Vector pos, Vector end);
	~EntitySwordEffect();
	void Update();
	void Render(GameManager * gm);
};

