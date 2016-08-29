#include <stdlib.h>
#include "GameManager.h"
int main(int args, char ** argc)
{
	GameManager * gm = new GameManager();
	gm->Init();
	gm->MainLoop();
	gm->Delete();
	return 0;
}