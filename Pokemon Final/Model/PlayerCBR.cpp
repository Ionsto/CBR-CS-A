#include "PlayerCBR.h"
#include <Pokemon Final\CBREnviroment.h>
#include "PokemonPikachu.h"
PlayerCBR::PlayerCBR() : Player()
{
	AIInstance = std::make_unique<CBRInstance>();
	MyPokemon[0] = std::make_unique<PokemonPikachu>();
	ActivePokemon = 0;
}

PlayerCBR::~PlayerCBR()
{
	AIInstance.release();
}
void PlayerCBR::PopulateEnviroment(CBREnviroment * env, Player * enemy)
{
	env->Owned.Health = GetActivePokemon()->Health;
	env->Opponent.Health = enemy->GetActivePokemon()->Health;
}
int PlayerCBR::GetMove(Player * enemy)
{
	std::unique_ptr<CBREnviroment> env = std::make_unique<CBREnviroment>();
	PopulateEnviroment(env.get(), enemy);
	return AIInstance->GetMove(std::move(env));
}

void PlayerCBR::Update(Player * enemy)
{
	std::unique_ptr<CBREnviroment> env = std::make_unique<CBREnviroment>();
	PopulateEnviroment(env.get(), enemy);
	AIInstance->ResolveAnswer(std::move(env));
}