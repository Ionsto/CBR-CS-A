#include "World.h"
#include "GameManager.h"
#include <SFML\Graphics.hpp>
#include "EntityLiving.h"
World::World(GameManager * gm)
{
	ResManager = gm->ResManager;
	FlashManager = gm->FlashBangRenderer;
	DeltaTime = 0.1F;
	DeltaTimeSqrd = DeltaTime*DeltaTime;
	this->rectangle = sf::RectangleShape(sf::Vector2f(10,10));
	rectangle.setFillColor(sf::Color(100, 250, 50));
	rectangle.setOrigin(sf::Vector2f(5, 5));
	DeleteCounter = 0;
	DeleteCountMax = 10;
	EntityCount = 200;
	CameraLoc = Vector();
	EntityList = new Entity*[EntityCount];
	WorldCollision = std::vector<Vector*>();
	Floor = sf::RectangleShape(sf::Vector2f(ResManager->FloorTexture.getSize()));
	Floor.setTexture(&ResManager->FloorTexture);
	Floor.setPosition(sf::Vector2f(0, 0));
	for (int i = 0; i < EntityCount; ++i)
	{
		EntityList[i] = NULL;
 	}
	Player = NULL;
	AIInstance = new CBRInstance();
	AIInstance->Load("./Data/AI/Guard.txt");
}


World::~World()
{

	for (int i = 0; i < EntityCount; ++i)
	{
		if (EntityList[i] != NULL)
		{
			delete EntityList[i];
		}
	}
	delete EntityList;
	for (int i = 0; i < WorldCollision.size(); ++i)
	{
		delete WorldCollision.at(i);
	}
	WorldCollision.clear();
	delete AIInstance;
}

void World::Update(GameManager * GM)
{
	Collide();
	for (int i = 0; i < EntityCount; ++i)
	{
		if (EntityList[i] != NULL)
		{
			if (EntityList[i]->Alive)
			{
				EntityList[i]->Update();
				EntityList[i]->Intergrate();
			}
		}
	}
	PhysicsUpdate();
	if (DeleteCounter++ >= DeleteCountMax)
	{
		DeleteEntities();
		DeleteCounter = 0;
	}
}
void World::DeleteEntities()
{
	//This finds the bodies and deletes them, this is called less frames as the deleting takes ages
	for (int i = 0; i < EntityCount; ++i)
	{
		if (EntityList[i] != NULL)
		{
			if (!EntityList[i]->Alive)
			{
				delete EntityList[i];
				EntityList[i] = NULL;
			}
		}
	}
}
void World::PhysicsUpdate()
{

}
void World::CollideEntity(int id)
{
	if (EntityList[id]->Size != 0) {
		for (int j = id + 1; j < EntityCount; ++j)
		{
			if (EntityList[j] != NULL)
			{
				if (EntityList[j]->Alive)
				{
					if (EntityList[j]->Size != 0) {
						Vector Distance = EntityList[id]->Pos - EntityList[j]->Pos;
						float DistanceDot = Distance.Dot(Distance);
						float MinDist = EntityList[id]->Size + EntityList[j]->Size;
						//do collisions
						//Resolve both I and J
						if (DistanceDot <= (MinDist*MinDist))
						{
							float RealDistance = sqrtf(DistanceDot);
							const float ResFactor = 0.005 * RealDistance / MinDist;
							EntityList[id]->PosOld -= Distance * ResFactor * (EntityList[id]->Mass / (EntityList[id]->Mass + EntityList[j]->Mass));
							EntityList[j]->PosOld += Distance * ResFactor * (EntityList[j]->Mass / (EntityList[id]->Mass + EntityList[j]->Mass));
							//
						}
					}
				}
			}
		}
	}
}
void World::CollideWorld(int id)
{
	Entity * myEnt = EntityList[id];
	for (int i = 0; i < WorldCollision.size(); ++i)
	{
		Vector LesserPos = WorldCollision.at(i)[0] - Vector(myEnt->Size, myEnt->Size);
		Vector GreaterPos = WorldCollision.at(i)[0] + WorldCollision.at(i)[1] + Vector(myEnt->Size, myEnt->Size);
		if (myEnt->Pos.X > LesserPos.X &&
			myEnt->Pos.X < GreaterPos.X &&
			myEnt->Pos.Y > LesserPos.Y &&
			myEnt->Pos.Y < GreaterPos.Y)
		{
			//Resolve
			float ResXLess = myEnt->Pos.X - LesserPos.X;
			float ResYLess = myEnt->Pos.Y - LesserPos.Y;
			float ResXGreat = GreaterPos.X - myEnt->Pos.X;
			float ResYGreat = GreaterPos.Y - myEnt->Pos.Y;
			//Left wall
			if (ResXLess < ResYLess && ResXLess < ResXGreat && ResXLess < ResYGreat)
			{
				myEnt->Pos.X -= ResXLess;
				myEnt->PosOld.X -= ResXLess;
				myEnt->PosOld.X += (myEnt->Pos.X - myEnt->PosOld.X) * myEnt->Elasticity * 2;
			}
			//Right wall?
			if (ResXGreat < ResXLess && ResXGreat < ResYLess && ResXGreat < ResYGreat)
			{
				myEnt->Pos.X += ResXGreat;
				myEnt->PosOld.X += ResXGreat;
				myEnt->PosOld.X += (myEnt->Pos.X - myEnt->PosOld.X) * myEnt->Elasticity * 2;
			}
			//Bottom wall
			if (ResYLess < ResXLess && ResYLess < ResXGreat && ResYLess < ResYGreat)
			{
				myEnt->Pos.Y -= ResYLess;
				myEnt->PosOld.Y -= ResYLess;
				myEnt->PosOld.Y += (myEnt->Pos.Y - myEnt->PosOld.Y) * myEnt->Elasticity * 2;
			}
			//Top wall
			if (ResYGreat < ResXLess && ResYGreat < ResYLess && ResYGreat < ResXGreat)
			{
				myEnt->Pos.Y += ResYGreat;
				myEnt->PosOld.Y += ResYGreat;
				myEnt->PosOld.Y += (myEnt->Pos.Y - myEnt->PosOld.Y) * myEnt->Elasticity * 2;
			}
		}
	}
}
void World::Collide()
{
	for (int i = 0; i < EntityCount - 1; ++i)
	{
		if (EntityList[i] != NULL)
		{
			if (EntityList[i]->Alive)
			{
				CollideEntity(i);
				CollideWorld(i);
			}
		}
	}
}
void World::Render(GameManager * gm)
{
	Floor.setPosition(CameraLoc.X, CameraLoc.Y);
	gm->Window.draw(Floor);
	for (int i = 0; i < EntityCount; ++i)
	{
		if (EntityList[i] != NULL)
		{

			if (EntityList[i]->Alive)
			{
				EntityList[i]->Render(gm);
			}
			//rectangle.setTexture();
			/*
			rectangle.setSize(sf::Vector2f(EntityList[i]->Size * 2, EntityList[i]->Size * 2));

			rectangle.setOrigin(sf::Vector2f(EntityList[i]->Size, EntityList[i]->Size));
			rectangle.setPosition(sf::Vector2f(EntityList[i]->Pos.X + CameraLoc.X, EntityList[i]->Pos.Y  + CameraLoc.Y));
			rectangle.setRotation(EntityList[i]->Rot);
			gm->Window.draw(rectangle);*/
		}
	}
	rectangle.setPosition(sf::Vector2f(gm->MouseState.MousePosition.X,gm->MouseState.MousePosition.Y));
	rectangle.setRotation(0);
	gm->Window.draw(rectangle);
	//if()
}
int World::AddEntity(Entity * entity, bool todelete)
{
	for (int i = 0; i < EntityCount; ++i)
	{
		if (EntityList[i] == NULL)
		{
			entity->Id = i;
			EntityList[i] = entity;
			return i;
		}
	}
	if(todelete)
	{
		delete entity;
	}
	return -1;
}
void World::AddWorldCollision(Vector pos, Vector size)
{
	if (size.X < 0) {
		pos.X += size.X;
		size.X = -size.X;
	}
	if (size.Y < 0) {
		pos.Y += size.Y;
		size.Y = -size.Y;
	}
	this->WorldCollision.push_back(new Vector[2]{ pos,size });
}