#pragma once
#include "PokemonBase.h"
#include "Player.h"
#include <functional>
class GameInstance
{
private:
	//Datastructures
	struct MovePairs {
		int A, B;
	};
	std::function<void(GameInstance)> DisplayCallback;
	Player Players[2];
	float CalculateDamage(PokemonBase * Attacker, PokemonBase * Defender, int Move);
	float ResolveMoves(PokemonBase * PokemonA, PokemonBase * PokemonB, GameInstance::MovePairs Moves);
	MovePairs GetPlayerMoves();
public:
	struct  {
		int A, B;
	};
	GameInstance();
	~GameInstance();
	void Update();
};

