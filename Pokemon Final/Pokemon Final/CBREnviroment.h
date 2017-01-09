struct MoveCase {
	int AttackSpeed; 
 	int BaseDamage; 
 	int MaxUses; 
 	int CurrentUses; 
 	int AttackType; 
}
struct PokmonCase {
	float Health;
	int Type;
	int Atttack;
	int Defence;
	MoveCase Moves[4];
};

class CBREnviroment{
	PokmonCase Owned;
	PokmonCase Opponent;
	CBREnviroment();
	~CBREnviroment();
};
