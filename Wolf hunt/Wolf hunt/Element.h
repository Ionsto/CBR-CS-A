#pragma once
#include "Vector.h"
#include <SFML\Graphics.hpp>
class GameManager;
class Element
{
public:
	//This is a unified effect on an element e.g. grey out
	sf::Color Tint;
	bool ShouldRender;
	bool Centered;
	//0-1
	Vector Position;
	//0-1
	Vector Size;
	Element(Vector Pos = Vector(), Vector Size = Vector());
	~Element();
	virtual void Update(GameManager * gm);
	virtual void Render(GameManager * gm);
	virtual void SetTint(sf::Color newtint);
	bool PointInsideElement(Vector point);
	virtual void SetCentered(bool Center);
};

