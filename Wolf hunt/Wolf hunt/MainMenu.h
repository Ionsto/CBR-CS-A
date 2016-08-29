#pragma once
#include "MenuBase.h"
class MainMenu : public MenuBase{
public:
	MainMenu();
	~MainMenu();
	void Update(GameManager * gm);
	void Render(GameManager * gm);
};