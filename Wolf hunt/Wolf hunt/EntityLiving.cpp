#include "EntityLiving.h"
#include "GameManager.h"


EntityLiving::EntityLiving(World * world,Vector pos) : Entity (world,pos)
{
	for (int i = 0; i < 4; ++i) {
		ItemList[i] = NULL;
	}
	Health = 100;
	MoveForce = 8;
	this->RenderCanvas = sf::RectangleShape(sf::Vector2f(10, 10));
	RenderCanvas.setFillColor(sf::Color(100, 250, 50));
	SetSize(8);
	Type = EntityType::TypeLiving;
}


EntityLiving::~EntityLiving()
{
	for (int i = 0; i < 4; ++i) {
		if (ItemList[i] != NULL) {
			delete ItemList[i];
		}
	}
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
bool EntityLiving::UseItemCurrent()
{
	if (ItemCurrent != NULL)
	{
		float GunSize = Size * 2;
		Vector FireFrom = Pos + Vector(GunSize * cosf(Rot / 180 * 3.14), GunSize * sinf(Rot / 180 * 3.14));
		return ItemCurrent->FireFrom(worldObj, FireFrom, Rot);
	}
	return false;
}
void EntityLiving::Flash(Vector position)
{
	Vector dist = position - Pos;
	float Angle = 180 / 3.14 * atan2f(dist.Y, dist.X);
	FlashTime = worldObj->FlashManager->MaxFlashTime * (1 - (abs(AngleDifference(Rot, Angle)) / 90));
}
void EntityLiving::Update()
{
	if (FlashTime > 0) {
		FlashTime -= worldObj->DeltaTime * 0.05;
	}
	else if (FlashTime < 0)
	{
		FlashTime = 0;
	}
}
void EntityLiving::ChangeWeapon(int wep)
{
	if (wep >= 0 && wep < 4)
	{
		if (ItemList[wep] != NULL)
		{
			ItemCurrent = ItemList[wep];
		}
	}
}