#pragma once
class CBRWeight
{
public:
	float Position;
	float Distance;
	float Type;
	float ExecutionTime;
};
class CBRWeightValue : public CBRWeight
{
public:
	CBRWeightValue()
	{
		Position = 0;
		Distance = 10;
		Type = 0;
		ExecutionTime = 0;
	};
};
class CBRWeightDistance : public CBRWeight
{
public:
	CBRWeightDistance()
	{
		Position = 1;
		Distance = 0;
		Type = 0;
		ExecutionTime = 0;
	};
};