#include "ElementTexture.h"
#include "GameManager.h"


ElementTexture::ElementTexture(Vector pos, Vector size, std::string TextureLoc) : Element(pos, size)
{
	RenderTexture = sf::Texture();
	RenderTexture.loadFromFile(TextureLoc);
	RenderFrame = sf::RectangleShape(sf::Vector2f(size.X, size.Y));
	RenderFrame.setPosition(sf::Vector2f(pos.X, pos.Y));	
	RenderFrame.setTexture(&RenderTexture);
}

ElementTexture::~ElementTexture()
{
}

void ElementTexture::Render(GameManager * gm)
{
	RenderFrame.setFillColor(Tint);
	gm->Window.draw(RenderFrame);
}
void ElementTexture::SetTint(sf::Color newtint)
{
	RenderFrame.setFillColor(newtint);
	Tint = newtint;
}
void ElementTexture::SetCentered(bool center)
{
	Centered = center;
	if (Centered)
	{
		RenderFrame.setOrigin(sf::Vector2f(Size.X / 2, Size.Y / 2));
	}
	else
	{
		RenderFrame.setOrigin(sf::Vector2f(0,0));
	}
}