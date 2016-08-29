#include "EntitySwordEffect.h"
#include "World.h"
#include "GameManager.h"


EntitySwordEffect::EntitySwordEffect(World * world, Vector pos, Vector end) : Entity(world, pos)
{
	Mass = 0;
	SetSize(0);
	Vector LookVec = (end - pos);
	float Length = LookVec.Dot(LookVec);
	line = sf::RectangleShape();
	/*line.setSize(sf::Vector2f(sqrtf(Length), 20));
	line.setOrigin(0, -10);*/
	line.setSize(sf::Vector2f(50,50));
	line.setOrigin(10, 0);
	Rot = (180 / 3.14 * atan2f(LookVec.Y, LookVec.X)) - 100;
	RotOld = Rot;
	line.setRotation(Rot);
	world->ResManager->SwordTexture.setRepeated(true);
	line.setTexture(&world->ResManager->SwordTexture);
}


EntitySwordEffect::~EntitySwordEffect()
{
}
void EntitySwordEffect::Update()
{
	Entity::Update();
	if (!Alive) { return; }
	Health -= 0.5;
}

void EntitySwordEffect::Render(GameManager * gm)
{
	//line.setPosition(sf::Vector2f(worldObj->CameraLoc.X,worldObj->CameraLoc.Y));
	line.setPosition(sf::Vector2f(Pos.X + worldObj->CameraLoc.X, Pos.Y + worldObj->CameraLoc.Y));
	line.setFillColor(sf::Color(255, 255, 255, 255 * (Health / 100)));
	gm->Window.draw(line);
}