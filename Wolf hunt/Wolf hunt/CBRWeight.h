#pragma once
class CBRWeight
{
public:
	float Health;
	float FlashTime;
	float Rotation;
	float Position;
	float Type;
};
class CBRWeightValue : public CBRWeight
{
public:
	CBRWeightValue()
	{
		Health = 1;
		FlashTime = 1;
		Rotation = 1;
		Position = 1;
		Type = 4;
	};
};
class CBRWeightDistance : public CBRWeight
{
public:
	CBRWeightDistance()
	{
		Health = 0.2;
		FlashTime = 1;
		Rotation = 1;
		Position = 1;
		Type = 4;
	};
};