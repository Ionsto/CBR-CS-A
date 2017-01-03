#pragma once
//Slightly odd name, but keeps consistancy with MoveOptions
enum TypeTypes
{
	Normal,
	Ground,
	Water,
	Electric,
	Grass
};
/*
Explination on types
Some types beat others, this gives large bonus modifiers to the damage calculations
150% effective
100% normal
50% ineffective
----Normal----
Normal:All 
----Ground----
Effective:Electric
Normal:Ground
Ineffective:Grass
----Water----

----Electric----
Effective:Water
Normal:Electric
Ineffective:Ground,Grass
----Grass:----
Effective:

*/
//Hacky solution to a lookup table that is static
static float GetMultiplier(int AttackerType,int DefenseType)
{
	const float MultEffective = 2;
	const float MultNormal = 1;
	const float MultIneffective = 0.5;
	switch (AttackerType)
	{
	(int)(TypeTypes::Normal):
		switch (DefenseType)
		{
		TypeTypes::Normal:
			return MultNormal;
		Ground:
			return MultNormal;
		Water:
			return MultNormal;
		Electric:
			return MultNormal;
		Grass:
			return MultNormal;
		}
	Ground:
		switch (DefenseType)
		{
		Normal:
			return MultNormal;
		Ground:
			return MultNormal;
		Water:
			return MultNormal;
		Electric:
			return MultEffective;
		Grass:
			return Ineffective;
		}
	Water:
		switch (DefenseType)
		{
		Normal:
			return MultNormal;
		Ground:
			return MultNormal;
		Water:
			return MultNormal;
		Electric:
			return MultIneffective;
		Grass:
			return MultIneffective;
		}
	Electric:
		switch (DefenseType)
		{
		Normal:
			return MultNormal;
		Ground:
			return MultIneffective;
		Water:
			return MultEffective;
		Electric:
			return MultIneffective;
		Grass:
			return MultNormal;
		}
	Grass:
		switch (DefenseType)
		{
		Normal:
			return MultNormal;
		Ground:
			return MultNormal;
		Water:
			return MultNormal;
		Electric:
			return MultNormal;
		Grass:
			return MultEffective;
		}
	}
}