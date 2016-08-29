#include "MainMenu.h"
#include "GameManager.h"
#include "ElementTexture.h"
#include "ElementLable.h"
#include "ElementButton.h"
MainMenu::MainMenu()
{
	ElementList = std::vector<Element*>();
	ElementList.push_back(new ElementTexture(Vector(), Vector(800, 800), "./UI/MainMenu.png"));
	ElementList.push_back(new ElementButton(Vector(400, 250), Vector(100, 50), "./UI/Enter.png"));
	ElementList.push_back(new ElementButton(Vector(400, 350), Vector(100, 50), "./UI/Quit.png"));
}
MainMenu::~MainMenu()
{
	for (int i = 0; i < ElementList.size(); ++i)
	{
		delete ElementList.at(i);
	}
}
void MainMenu::Update(GameManager * gm)
{
	this->MenuBase::Update(gm);
	//Fetch info exec it etc
	if (((ElementButton*)ElementList.at(1))->Enabled)
	{
		gm->GameState = GameManager::GameStateEnum::StateGame;
	}
	if (((ElementButton*)ElementList.at(2))->Enabled)
	{
		gm->Running = false;
	}
}
void MainMenu::Render(GameManager * gm)
{
	this->MenuBase::Render(gm);
}