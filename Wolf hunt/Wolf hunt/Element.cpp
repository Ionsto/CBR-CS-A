#include "Element.h"
#include "GameManager.h"


Element::Element(Vector pos,Vector size)
{
	ShouldRender = true;
	Centered = false;
	Position = pos;
	Size = size;
	Tint = sf::Color::White;
}


Element::~Element()
{
}

void Element::Update(GameManager * gm)
{
}
void Element::Render(GameManager * gm)
{
}
void Element::SetTint(sf::Color newtint)
{
	Tint = newtint;
}
bool Element::PointInsideElement(Vector point)
{
	Vector EffectiveLesserLoc = Position;
	Vector EffectiveGreaterLoc = Position + Size;
	if (Centered)
	{
		EffectiveLesserLoc -= Size / 2;
		EffectiveGreaterLoc -= Size / 2;
	}
	if (point.X > EffectiveLesserLoc.X && point.X < EffectiveGreaterLoc.X &&
		point.Y > EffectiveLesserLoc.Y && point.Y < EffectiveGreaterLoc.Y)
	{
		return true;
	}
	return false;
}
void Element::SetCentered(bool cet)
{
	Centered = cet;
}