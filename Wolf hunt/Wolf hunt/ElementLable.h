#pragma once
#include "Element.h"
class ElementLable : public Element
{
public:
	sf::Font font;
	std::string ActualText;
	sf::Text Text;
	ElementLable(Vector Pos = Vector(), Vector Size = Vector(), std::string Data = "");
	~ElementLable();
	void ChangeText(std::string newdata);
	void Render(GameManager * gm);
	virtual void SetTint(sf::Color newtint);
};

