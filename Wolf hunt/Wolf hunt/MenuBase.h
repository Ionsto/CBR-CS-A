#pragma once
#include "Vector.h"
#include <vector>
#include "Element.h"
#include <SFML\Graphics.hpp>
class GameManager;
class MenuBase
{
public:
	std::vector<Element*> ElementList;
	MenuBase();
	~MenuBase();
	void Update(GameManager * gm);
	void Render(GameManager * gm);
};

