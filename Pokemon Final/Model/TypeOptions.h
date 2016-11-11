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