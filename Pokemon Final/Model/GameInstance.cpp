#include "GameInstance.h"
#include <memory>


GameInstance::GameInstance(std::unique_ptr<Player> A, std::unique_ptr<Player> B)
{
	Players[0] = std::move(A);
	Players[1] = std::move(B);
	DisplayCallback = NULL;
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
	//TODO FIX
	float RandomFactor = 0.8 + ((rand() % 3)/10.0);
	if (Attacker->MoveSet[Move]->CurrentUses++ >= Attacker->MoveSet[Move]->MaxUses)
	{
		RandomFactor = 0;
	}
	return ((Attacker->Attack/Defender->Defense) * Attacker->MoveSet[Move]->BaseDamage + 2.0) * RandomFactor;
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
	else
	{
		MoveSpeed[0] = Players[0]->GetActivePokemon()->MoveSet[Moves.A && MoveTypesOptionSelector]->AttackSpeed;
	}
	if (Moves.B && MoveTypesMoveSelector == MoveTypes::ChoosePokemon)
	{
		MoveSpeed[0] = 0;
		Players[1]->ActivePokemon = Moves.B && MoveTypesOptionSelector;
	}
	else
	{
		MoveSpeed[1] = Players[1]->GetActivePokemon()->MoveSet[Moves.B && MoveTypesOptionSelector]->AttackSpeed;
	}
	if ((Moves.A && MoveTypesMoveSelector == MoveTypes::ChoosePokemon) && (Moves.B && MoveTypesMoveSelector == MoveTypes::ChoosePokemon))
	{
		//Both players swapped in pokemon symultaiusly.
		//Nothing else happens
		return;
	}
	//Edgecase, the other player has swapped in a pokemon -> Hit them straight away
	if (MoveSpeed[0] == 0)
	{
		//Resolve 0
		Players[0]->GetActivePokemon()->Health = fmaxf(0, Players[0]->GetActivePokemon()->Health - CalculateDamage(Players[1]->GetActivePokemon(), Players[0]->GetActivePokemon(), Moves.B && MoveTypesOptionSelector));
		return;
	}
	if (MoveSpeed[1] == 0)
	{
		//Resolve 1
		Players[1]->GetActivePokemon()->Health = fmaxf(0, Players[1]->GetActivePokemon()->Health - CalculateDamage(Players[0]->GetActivePokemon(), Players[1]->GetActivePokemon(), Moves.A && MoveTypesOptionSelector));
		return;
	}
	//At this point in execution we know both players are going for attack moves, and we need to resolve order of operation
	if (MoveSpeed[0] < MoveSpeed[1])
	{
		Players[1]->GetActivePokemon()->Health = fmaxf(0, Players[1]->GetActivePokemon()->Health - CalculateDamage(Players[0]->GetActivePokemon(), Players[1]->GetActivePokemon(), Moves.A && MoveTypesOptionSelector));
		if (Players[1]->GetActivePokemon()->Health != 0)
		{
			Players[0]->GetActivePokemon()->Health = fmaxf(0, Players[0]->GetActivePokemon()->Health - CalculateDamage(Players[1]->GetActivePokemon(), Players[0]->GetActivePokemon(), Moves.B && MoveTypesOptionSelector));
		}
	}
	else if(MoveSpeed[0] > MoveSpeed[1])
	{
		Players[0]->GetActivePokemon()->Health = fmaxf(0, Players[0]->GetActivePokemon()->Health - CalculateDamage(Players[1]->GetActivePokemon(), Players[0]->GetActivePokemon(), Moves.B && MoveTypesOptionSelector));
		if (Players[0]->GetActivePokemon()->Health != 0)
		{
			Players[1]->GetActivePokemon()->Health = fmaxf(0, Players[1]->GetActivePokemon()->Health - CalculateDamage(Players[0]->GetActivePokemon(), Players[1]->GetActivePokemon(), Moves.A && MoveTypesOptionSelector));
		}
	}
	else
	{
		//Randomise
		if (rand() % 2 == 0)
		{
			Players[0]->GetActivePokemon()->Health = fmaxf(0, Players[0]->GetActivePokemon()->Health - CalculateDamage(Players[1]->GetActivePokemon(), Players[0]->GetActivePokemon(), Moves.B && MoveTypesOptionSelector));
			if (Players[0]->GetActivePokemon()->Health != 0)
			{
				Players[1]->GetActivePokemon()->Health = fmaxf(0, Players[1]->GetActivePokemon()->Health - CalculateDamage(Players[0]->GetActivePokemon(), Players[1]->GetActivePokemon(), Moves.A && MoveTypesOptionSelector));
			}
		}
		else
		{
			Players[1]->GetActivePokemon()->Health = fmaxf(0, Players[1]->GetActivePokemon()->Health - CalculateDamage(Players[0]->GetActivePokemon(), Players[1]->GetActivePokemon(), Moves.A && MoveTypesOptionSelector));
			if (Players[1]->GetActivePokemon()->Health != 0)
			{
				Players[0]->GetActivePokemon()->Health = fmaxf(0, Players[0]->GetActivePokemon()->Health - CalculateDamage(Players[1]->GetActivePokemon(), Players[0]->GetActivePokemon(), Moves.B && MoveTypesOptionSelector));
			}
		}
	}
}
Player* GameInstance::GetPlayer(int i)
{
	return Players[i].get();
}
GameInstance::MovePairs GameInstance::GetPlayerMoves()
{
	MovePairs Moves = MovePairs();
	Moves.A = Players[0]->GetMove(Players[1].get());
	Moves.B = Players[1]->GetMove(Players[0].get());
	return Moves;
}
//Public
void GameInstance::Update()
{
	GameInstance::MovePairs Moves = GetPlayerMoves();
	ResolveMoves(Moves);
	Players[0]->Update(Players[1].get());
	Players[1]->Update(Players[0].get());
	if (Players[0]->Alive == false || Players[1]->Alive == false)
	{
		Finished = true;
	}
	if (DisplayCallback != NULL) {
		DisplayCallback(this, Players,Moves);
	}
}