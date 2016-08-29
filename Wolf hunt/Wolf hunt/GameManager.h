#pragma once
#include <stdlib.h>
#include <iostream>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "World.h"
#include "ResourceManager.h"
#include "RenderFlashBang.h"
#include "MainMenu.h"
class GameManager
{
public:
	enum GameStateEnum
	{
		StateMainMenu, StateGame
	} GameState = StateMainMenu;
	bool Running;
	sf::RenderWindow Window;
	ResourceManager * ResManager;
	RenderFlashBang * FlashBangRenderer;
	World * WorldObj;
	MainMenu * Mainmenu;
	Vector WindowSize;
	struct MouseData{
		Vector MousePosition = Vector();
		//0 = Not active, 1 = Active, 2 = Released this frame 
		int LeftMouseState = 0;
		//0 = Not active, 1 = Active, 2 = Released this frame 
		int RightMouseState = 0;
	} MouseState;
	bool KeyState[255];
	GameManager();
	~GameManager();
	void MainLoop();
	void Update();
	void PollInput();
	void Init();
	void InitGraphics();
	void InitWorld();
	void Render();
	void Delete();
};

