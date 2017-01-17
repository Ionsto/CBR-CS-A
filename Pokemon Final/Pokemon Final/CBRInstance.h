/*
This is an instance of an AI, each AI will have different trained learned patterns or enviroment weights.
*/
class CBRInstance{
public:
	float ExplorationConstant;
	float IdenticalThreshold;
	CBRInstance();
	~CBRInstance();
	void CBRInstance::GetMove(std::unique_ptr<CBREnviroment> startenv);
	void CBRInstance::ResolveAnswer(std::unique_ptr<CBREnviroment> finalenv);
};			
