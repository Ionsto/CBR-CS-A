#include "EntityLiving.h"
#include "GameManager.h"


EntityLiving::EntityLiving(World * world,Vector pos) : Entity (world,pos)
{
	Health = 100;
	MoveForce = 8;
	this->RenderCanvas = sf::RectangleShape(sf::Vector2f(10, 10));
	RenderCanvas.setFillColor(sf::Color(100, 250, 50));
	SetSize(8);
	Type = EntityType::TypeLiving;
	RayCaster = ItemRayCaster();
}


EntityLiving::~EntityLiving()
{
}
void EntityLiving::Render(GameManager * gm)
{
	RenderCanvas.setPosition(sf::Vector2f(Pos.X + worldObj->CameraLoc.X, Pos.Y + worldObj->CameraLoc.Y));
	RenderCanvas.setRotation(Rot + 90);
	gm->Window.draw(RenderCanvas);
}
void EntityLiving::SetSize(float size)
{
	RenderCanvas.setSize(sf::Vector2f(Size * 2, Size * 2));
	RenderCanvas.setOrigin(sf::Vector2f(Size, Size));
}
void EntityLiving::Update()
{
	Entity::Update();
}