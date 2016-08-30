#pragma once
class CBRWeight
{
public:
	float Position;
	float Distance;
	float Type;
};
class CBRWeightValue : public CBRWeight
{
public:
	CBRWeightValue()
	{
		Position = 0;
		Distance = 5;
		Type = 0;
	};
};
class CBRWeightDistance : public CBRWeight
{
public:
	CBRWeightDistance()
	{
		Position = 1;
		Distance = 1;
		Type = 4;
	};
};