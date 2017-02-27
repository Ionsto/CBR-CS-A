#include "PlayerCBR.h"
#include <Pokemon Final\CBREnviroment.h>
#include "PokemonPikachu.h"
PlayerCBR::PlayerCBR(std::unique_ptr<CBRInstance> inst) : Player()
{
	if (inst == NULL)
	{
		AIInstance = std::make_unique<CBRInstance>();
	}
	else
	{
		AIInstance = std::move(inst);
	}
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
	env->Owned.Type = GetActivePokemon()->PokemonType;
	for (int i = 0;i < 4;++i) 
	{
		env->Owned.Moves[i].AttackSpeed = GetActivePokemon()->MoveSet[i]->AttackSpeed;
		env->Owned.Moves[i].AttackType = GetActivePokemon()->MoveSet[i]->AttackType;
		env->Owned.Moves[i].BaseDamage = GetActivePokemon()->MoveSet[i]->BaseDamage;
		env->Owned.Moves[i].DefenseBuff = GetActivePokemon()->MoveSet[i]->DefenseBuff;
		env->Owned.Moves[i].CurrentUses = GetActivePokemon()->MoveSet[i]->CurrentUses;
		env->Owned.Moves[i].MaxUses = GetActivePokemon()->MoveSet[i]->MaxUses;
	}
	env->Opponent.Health = enemy->GetActivePokemon()->Health;
	env->Opponent.Type = enemy->GetActivePokemon()->PokemonType;
	for (int i = 0;i < 4;++i)
	{
		env->Opponent.Moves[i].AttackSpeed = enemy->GetActivePokemon()->MoveSet[i]->AttackSpeed;
		env->Opponent.Moves[i].AttackType = enemy->GetActivePokemon()->MoveSet[i]->AttackType;
		env->Opponent.Moves[i].BaseDamage = enemy->GetActivePokemon()->MoveSet[i]->BaseDamage;
		env->Opponent.Moves[i].DefenseBuff = enemy->GetActivePokemon()->MoveSet[i]->DefenseBuff;
		env->Opponent.Moves[i].CurrentUses = enemy->GetActivePokemon()->MoveSet[i]->CurrentUses;
		env->Opponent.Moves[i].MaxUses = enemy->GetActivePokemon()->MoveSet[i]->MaxUses;
	}
}
int PlayerCBR::GetMove(Player * enemy)
{
	std::unique_ptr<CBREnviroment> env = std::make_unique<CBREnviroment>();
	PopulateEnviroment(env.get(), enemy);
	return AIInstance->GetMove(std::move(env));
}

void PlayerCBR::Update(Player * enemy)
{
	Player::Update(enemy);
	std::unique_ptr<CBREnviroment> env = std::make_unique<CBREnviroment>();
	PopulateEnviroment(env.get(), enemy);
	AIInstance->ResolveAnswer(std::move(env));
}