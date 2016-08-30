
#include "AIAction.h"
class AIActionMove :
	public AIAction
{
public:
	int EvalCount;
	int EvalTime;
	Vector OldPosition;
	Vector Position;
	AIActionMove(EntityWolf * owner,Vector pos);
	~AIActionMove();
	void Execute() override;
	AIAction * CopySelf(EntityWolf * newowner) override;
	void Mutate(float Factor) override;
	std::string Description() override;
};
