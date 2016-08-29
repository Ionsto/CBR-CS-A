#pragma once
#include "Entity.h"
#include <SFML\Graphics.hpp>
class EntityTracerEffect : public Entity
{
public:
	sf::RectangleShape line;
	EntityTracerEffect(World * world, Vector pos,Vector end);
	~EntityTracerEffect();
	void Update();
	void Render(GameManager * gm);
};

