#pragma once
#include "PokemonBase.h"
#include "Player.h"
#include <memory>
#include "MoveOptions.h"
#include <functional>
class GameInstance
{
private:
	//Datastructures
	struct MovePairs {
		int A, B;
	};
	//This is an overwritable function, this allows other programs to effectivly intergrate.
	std::function<void(GameInstance)> DisplayCallback;
	//PTR is needed for polymorphism
	std::unique_ptr<Player> Players[2];
	//Calculates damage for a single attack
	float CalculateDamage(PokemonBase * Attacker, PokemonBase * Defender, int Move);
	//Resolves a pair of moves (this means it works out execution order, calculates damage, and ends.
	void ResolveMoves(GameInstance::MovePairs Moves);
	MovePairs GetPlayerMoves();
public:
	bool Finished;
	GameInstance(std::unique_ptr<Player> A, std::unique_ptr<Player> B);
	~GameInstance();
	void Update();
};

