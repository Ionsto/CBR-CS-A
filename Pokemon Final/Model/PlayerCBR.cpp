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
	AIInstance.reset();
}
void PlayerCBR::PopulateEnviroment(CBREnviroment * env, Player * enemy)
{
	env->Owned.Health = GetActivePokemon()->Health;
	env->Owned.Type = GetActivePokemon()->PokemonType;
	env->Owned.Attack = GetActivePokemon()->Health;
	env->Owned.Defence = GetActivePokemon()->PokemonType;
	for (int i = 0;i < 4;++i) 
	{
		env->Owned.Moves[i].AttackSpeed = GetActivePokemon()->MoveSet[i]->AttackSpeed;
		env->Owned.Moves[i].AttackType = GetActivePokemon()->MoveSet[i]->AttackType;
		env->Owned.Moves[i].BaseDamage = GetActivePokemon()->MoveSet[i]->BaseDamage;
		env->Owned.Moves[i].DefenseBuff = GetActivePokemon()->MoveSet[i]->DefenseBuff;
		env->Owned.Moves[i].UsesLeft =  (GetActivePokemon()->MoveSet[i]->CurrentUses < GetActivePokemon()->MoveSet[i]->MaxUses) ? 1 : 0;
	}
	env->Opponent.Health = enemy->GetActivePokemon()->Health;
	env->Opponent.Type = enemy->GetActivePokemon()->PokemonType;
	env->Opponent.Attack = GetActivePokemon()->Attack;
	env->Opponent.Defence = GetActivePokemon()->Defense;
	for (int i = 0;i < 4;++i)
	{
		env->Opponent.Moves[i].AttackSpeed = 0;//enemy->GetActivePokemon()->MoveSet[i]->AttackSpeed;
		env->Opponent.Moves[i].AttackType = 0;//enemy->GetActivePokemon()->MoveSet[i]->AttackType;
		env->Opponent.Moves[i].BaseDamage = 0;//enemy->GetActivePokemon()->MoveSet[i]->BaseDamage;
		env->Opponent.Moves[i].DefenseBuff = 0;//enemy->GetActivePokemon()->MoveSet[i]->DefenseBuff;
		env->Opponent.Moves[i].UsesLeft = (enemy->GetActivePokemon()->MoveSet[i]->CurrentUses < enemy->GetActivePokemon()->MoveSet[i]->MaxUses) ? 1 : 0;
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
	if (Alive)
	{
		std::unique_ptr<CBREnviroment> env = std::make_unique<CBREnviroment>();
		PopulateEnviroment(env.get(), enemy);
		AIInstance->ResolveAnswer(std::move(env));
	}
}