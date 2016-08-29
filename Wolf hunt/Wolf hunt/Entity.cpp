#include "Entity.h"
#include "GameManager.h"
Entity::Entity(World * world,Vector pos)
{
	Alive = true;
	Pos = pos;
	PosOld = pos;
	Acc = Vector();
	Mass = 100;
	Rotation = 0;
	Elasticity = 0;
	Rot = 0;
	RotOld = 0;
	Friction = 0.98;
	FrictionRot = 0.5;
	Health = 100;
	Id = -1;
	SetSize(8);
	worldObj = world;
	Type = EntityType::TypeEntity;
}
Entity::~Entity()
{

}
void Entity::Update()
{
	if (Health <= 0)
	{
		Kill();
	}
}
void Entity::Intergrate()
{
	Vector NewPos = this->Pos;
	Pos += ((Pos - PosOld) * Friction) + (Acc * worldObj->DeltaTimeSqrd);
	PosOld = NewPos;
	if ((Pos - PosOld).Dot((Pos - PosOld)) < 0.0000001)
	{
		Pos = PosOld;
	}
	NormaliseRots();
	float tempRot = Rot;
	Rot += AngleDifference(Rot,RotOld) * FrictionRot;
	RotOld = tempRot;
	NormaliseRots();
	//Rotation = NormaliseAngle(Rot);
	Acc = Vector();
	if (abs((Pos - PosOld).X) < 0.0001) { PosOld.X = Pos.X; }
	if (abs((Pos - PosOld).Y) < 0.0001) { PosOld.Y = Pos.Y; }
}
void Entity::ApplyForce(Vector V)
{
	//F = MA
	Acc += (V / Mass);
}
void Entity::NormaliseRots()
{
	Rot = NormaliseAngle(Rot);
	RotOld = NormaliseAngle(RotOld);
}
float Entity::NormaliseAngle(float x)
{
	while (abs(x) > 180)
	{
		x += copysignf(360, -x);
	}
	return x;
}
float Entity::AngleDifference(float a, float b)
{
	float x = NormaliseAngle(a - b);
	//extra level
	//if (x >= 180) { x -= 180; }
	//if (x <= -180) { x += 180; }
	return x;
}
void Entity::Kill()
{
	//Entity will actually get killed by world later
	Alive = false;
}
void Entity::SetPosition(Vector pos)
{
	Pos = pos;
	PosOld = pos;
}
void Entity::DoDamage(int hp)
{
	Health -= hp;
}
void Entity::Render(GameManager * gm)
{

}
void Entity::SetSize(float size)
{
	Size = size;
}