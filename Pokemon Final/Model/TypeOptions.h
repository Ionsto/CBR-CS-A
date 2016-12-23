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
	const float Effective = 2;
	const float Normal = 1;
	const float Ineffective = 0.5;
	switch (AttackerType)
	{
	Normal:
		switch (DefenseType)
		{
		Normal:
			return Normal;
		Ground:
			return Normal;
		Water:
			return Normal;
		Electric:
			return Normal;
		Grass:
			return Normal;
		}
	Ground:
		switch (DefenseType)
		{
		Normal:
			return Normal;
		Ground:
			return Normal;
		Water:
			return Normal;
		Electric:
			return Effective;
		Grass:
			return Ineffective;
		}
	Water:
		switch (DefenseType)
		{
		Normal:
			return Normal;
		Ground:
			return Normal;
		Water:
			return Normal;
		Electric:
			return Normal;
		Grass:
			return Normal;
		}
	Electric:
		switch (DefenseType)
		{
		Normal:
			return Normal;
		Ground:
			return Normal;
		Water:
			return Normal;
		Electric:
			return Normal;
		Grass:
			return Normal;
		}
	Grass:
		switch (DefenseType)
		{
		Normal:
			return Normal;
		Ground:
			return Normal;
		Water:
			return Normal;
		Electric:
			return Normal;
		Grass:
			return Normal;
		}
	}
}