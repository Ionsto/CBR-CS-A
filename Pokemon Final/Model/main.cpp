#include "GameInstance.h"
#include "PlayerConsole.h"
int main(int argc, char **args)
{
	//Example program
	GameInstance * Game = new GameInstance(std::make_unique<PlayerConsole>(), std::make_unique<PlayerConsole>());
	while (!Game->Finished) {
		Game->Update();
	}
	return 0;
}