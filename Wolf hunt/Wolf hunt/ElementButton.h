#pragma once
#include "ElementTexture.h"
#include "ElementLable.h"
class ElementButton : public ElementTexture
{
public:
	bool Enabled;
	int State;
	ElementLable * Text;
	ElementButton(Vector pos = Vector(),Vector Size = Vector(),std::string Text = "");
	~ElementButton();
	virtual void SetTint(sf::Color newtint);
	virtual void Update(GameManager * gm);
	virtual void Render(GameManager * gm);
};

