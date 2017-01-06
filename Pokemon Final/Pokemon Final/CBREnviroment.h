struct PokmonCase {
	float Health;	
};

class CBREnviroment{
	PokmonCase Owned;
	PokmonCase Opponent;
	CBREnviroment();
	~CBREnviroment();
};
