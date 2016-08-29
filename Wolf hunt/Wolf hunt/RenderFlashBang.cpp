#include "RenderFlashBang.h"
#include "GameManager.h"
#include "World.h"
#include "EntityLiving.h"


sf::Vector3f FlashIncident::SFFormat(World * world, Vector ScreenSize)
{
	Vector screenpos = ((Position - world->Player->Pos) * Vector(1, -1)) + (ScreenSize / 2);
	return sf::Vector3f(screenpos.X, screenpos.Y, Time);
}
RenderFlashBang::RenderFlashBang(GameManager * gm)
{
	FlashBang = sf::RectangleShape(sf::Vector2f(gm->WindowSize.X, gm->WindowSize.Y));
	FlashBang.setPosition(0, 0);
	FlashBang.setFillColor(sf::Color::White);
	ScreenSize = gm->WindowSize;
	MaxFlashTime = 12;
	for (int i = 0; i < MaxFlashes;++i)
	{
		PlayerFlashedList[i] = FlashIncident();
		UniformEvents[i] = sf::Vector3f(0,0,-1);// PlayerFlashedList[i].SFFormat(gm->WorldObj, ScreenSize);
	}
}


RenderFlashBang::~RenderFlashBang()
{
}

void RenderFlashBang::Update(GameManager * gm)
{
	int UniformCount = 0;
	for (int i = 0; i < MaxFlashes;++i)
	{
		if (PlayerFlashedList[i].Time != -1) {
			/*if (PlayerFlashedList[i].MaxTime <= 2)
			{
				PlayerFlashedList[i].Time += gm->WorldObj->DeltaTime * 0.03 * (MaxFlashTime);
			}
			else
			{*/
			PlayerFlashedList[i].Time += gm->WorldObj->DeltaTime * 0.05 * (MaxFlashTime / PlayerFlashedList[i].MaxTime);
			//}
			if (PlayerFlashedList[i].Time > MaxFlashTime)
			{
				PlayerFlashedList[i].Time = -1;
			}
		}
		UniformEvents[i] = PlayerFlashedList[i].SFFormat(gm->WorldObj,ScreenSize);
	}
	gm->ResManager->FlashBangShaderFrag.setParameter("FlashEventA", UniformEvents[0]);
	gm->ResManager->FlashBangShaderFrag.setParameter("FlashEventB", UniformEvents[1]);
	gm->ResManager->FlashBangShaderFrag.setParameter("FlashEventC", UniformEvents[2]);
}
void RenderFlashBang::Render(GameManager * gm)
{
	gm->Window.draw(this->FlashBang , &gm->ResManager->FlashBangShaderFrag);
}
void RenderFlashBang::AddFlashBangEvent(EntityLiving * ent,Vector Position)
{
	for (int i = 0; i < MaxFlashes; ++i)
	{
		if (PlayerFlashedList[i].Time == -1)
		{
			PlayerFlashedList[i].Time = 0;
			PlayerFlashedList[i].MaxTime = ent->FlashTime;
			PlayerFlashedList[i].Position = Position;
			return;
		}
	}
}