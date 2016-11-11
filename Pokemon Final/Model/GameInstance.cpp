#include "GameInstance.h"
#include <memory>


GameInstance::GameInstance(std::unique_ptr<Player> A, std::unique_ptr<Player> B)
{
	Players[0] = std::move(A);
	Players[1] = std::move(B);
	Finished = false;
}


GameInstance::~GameInstance()
{
	//Clear up memory
	for (int i = 0; i < 2; ++i)
	{
		Players[i].release();
	}
	//Players does not need to be deleted as it is stack allocated
}
//Private
float GameInstance::CalculateDamage(PokemonBase * Attacker, PokemonBase * Defender, int Move)
{
	return 0;
}
void GameInstance::ResolveMoves(GameInstance::MovePairs Moves)
{
	
	int MoveSpeed[2];
	MoveSpeed[0] = -1;
	MoveSpeed[1] = -1;
	if (Moves.A && MoveTypesMoveSelector == MoveTypes::ChoosePokemon)
	{
		MoveSpeed[0] = 0;
		Players[0]->ActivePokemon = Moves.A && MoveTypesOptionSelector;
	}
	if (Moves.B && MoveTypesMoveSelector == MoveTypes::ChoosePokemon)
	{
		MoveSpeed[0] = 0;
		Players[1]->ActivePokemon = Moves.B && MoveTypesOptionSelector;
	}
	if ((Moves.A && MoveTypesMoveSelector == MoveTypes::ChoosePokemon) && (Moves.B && MoveTypesMoveSelector == MoveTypes::ChoosePokemon))
	{
		//Both players swapped in pokemon symultaiusly.
		return;
	}
	//Edgecase, the other player has swapped in a pokemon -> Hit them straight away
	if (MoveSpeed[0] == 0)
	{
		//Resolve 0
		return;
	}
	if (MoveSpeed[0] == 0)
	{
		//Resolve 1
		return;
	}
	//At this point in execution we know both players are going for attack moves, and we need to resolve order of operation
	//MoveSpeed[0] = Players[0]->GetActivePokemon()->
}
GameInstance::MovePairs GameInstance::GetPlayerMoves()
{
	MovePairs Moves = MovePairs();
	Moves.A = Players[0]->GetMove();
	Moves.B = Players[1]->GetMove();
	return Moves;
}
//Public
void GameInstance::Update()
{
	GameInstance::MovePairs Moves = GetPlayerMoves();
	ResolveMoves(Moves);
	for (int i = 0; i < 2; ++i)
	{
		Players[i]->Update();
	}
	if (Players[0]->Alive == false || Players[1]->Alive == false)
	{
		Finished = true;
	}
}