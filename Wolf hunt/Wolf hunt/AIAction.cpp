#include "AIAction.h"



AIAction::AIAction(EntityWolf * owner)
{
	this->Owner = owner;
}


AIAction::~AIAction()
{
}

void AIAction::Execute()
{

}
void AIAction::RemoveSelf()
{
	Owner->AIStack.pop();
	delete this;
}
AIAction * AIAction::CopySelf(EntityWolf * newowner)
{
	AIAction * NewVer = new AIAction(newowner);
	return NewVer;
}
void AIAction::Mutate(float Factor)
{

}
std::string AIAction::Description()
{
	return "Null action";
}