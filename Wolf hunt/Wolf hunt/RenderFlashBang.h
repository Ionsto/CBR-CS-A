#pragma once
#include <vector>
#include "Vector.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
class World;
class EntityLiving;
struct FlashIncident {
	Vector Position;
	float Time;
	float MaxTime;
	FlashIncident() { Position = Vector(); Time = -1; MaxTime = 5; };
	sf::Vector3f SFFormat(World * world, Vector ScreenSize);
};
class GameManager;
class RenderFlashBang
{
public:
	static const int MaxFlashes = 3;
	float MaxFlashTime;
	sf::RectangleShape FlashBang;
	FlashIncident PlayerFlashedList[MaxFlashes];
	sf::Vector3f UniformEvents[MaxFlashes];
	Vector ScreenSize;
	RenderFlashBang(GameManager * gm);
	~RenderFlashBang();
	void Update(GameManager * gm);
	void Render(GameManager * gm);
	void AddFlashBangEvent(EntityLiving * eng,Vector Position);
};

