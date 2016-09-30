#include "GameInstance.h"



GameInstance::GameInstance()
{
}


GameInstance::~GameInstance()
{
}
//Private
float GameInstance::CalculateDamage(PokemonBase * Attacker, PokemonBase * Defender, int Move)
{

}
float GameInstance::ResolveMoves(PokemonBase * PokemonA, PokemonBase * PokemonB, GameInstance::MovePairs Moves)
{

}
GameInstance::MovePairs GameInstance::GetPlayerMoves()
{
	MovePairs Moves = MovePairs();
	Moves.A = Players[0].GetMove();
	Moves.B = Players[1].GetMove();
	return Moves;
}
//Public
void GameInstance::Update()
{
	GameInstance::MovePairs Moves = GetPlayerMoves();
	ResolveMoves();
}