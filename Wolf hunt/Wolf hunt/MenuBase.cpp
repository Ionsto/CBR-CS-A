#include "MenuBase.h"
#include "GameManager.h"


MenuBase::MenuBase()
{
}


MenuBase::~MenuBase()
{
}

void MenuBase::Update(GameManager * gm)
{
	//Look for updates on flags
	for (int i = 0; i < ElementList.size(); ++i)
	{
		if (ElementList.at(i)->ShouldRender)
		{
			ElementList.at(i)->Update(gm);
		}
	}
}

void MenuBase::Render(GameManager * gm)
{
	//gm->Window.draw(RenderFrame);
	for (int i = 0; i < ElementList.size(); ++i)
	{
		if (ElementList.at(i)->ShouldRender)
		{
			ElementList.at(i)->Render(gm);
		}
	}
}