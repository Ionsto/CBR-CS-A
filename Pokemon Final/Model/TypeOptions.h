#pragma once
//Slightly odd name, but keeps consistancy with MoveOptions
enum TypeTypes
{
	Normal,
	Water,
	Electric
};
/*
Explination on types
Some types beat others, this gives large bonus modifiers to the damage calculations
150% effective
100% normal
50% ineffective
----Normal----
Normal:All 
----Water----

----Electric----
Effective:Water
Normal:Electric
Ineffective:Ground
*/
//Hacky solution to a lookup table that is static
static float GetMultiplier(int AttackerType,int DefenseType)
{
	const float MultEffective = 2;
	const float MultNormal = 1;
	const float MultIneffective = 0.5;
	const float AttackerDefenderValues[][3] = {{MultNormal,MultNormal,MultNormal},{MultNormal,MultNormal,MultIneffective},{MultNormal,MultEffective,MultNormal}};
	return AttackerDefenderValues[AttackerType][DefenseType];
}
