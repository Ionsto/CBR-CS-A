#pragma once

//Format
//MoveType|Option
const int MoveTypesMoveSelector = 0xFC;
const int MoveTypesOptionSelector = 0x04;
//This format allows scalibility in the model, like adding "run away" to the moveset
enum MoveTypes
{
	//Selectors
	Option0,Option1,Option2,Option3,
	ChoosePokemon,
	UseAttack,
};