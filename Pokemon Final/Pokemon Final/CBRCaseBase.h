/*
CBRCasebase is a delegaded system for storing retrieving and removeing cases.
The CBRCasebase will have two versions, a linear list (slow but for testing) and a kd-tree (a kind of binary tree)
*/
#include <vector>
struct CBRCaseDistance{
  float Distance;
  CBRCase * Case;  
}
struct MoveWeight { 
 	int AttackSpeed;  
 	int BaseDamage;  
 	int MaxUses;  
 	int CurrentUses;  
 	int AttackType;  
}
struct PokmonWeight { 
  float Health; 
  int Type; 
	int Atttack; 
 	int Defence; 
  MoveWeight Moves[4];
}
struct CaseWeights{
  PokemonWeight PlayerPokemon;
  PokemonWeight EnemyPokemon;
}
class CBRCaseBase{
public:
  //Weights for the distance
  CaseWeights DistanceWeight;
  CBRCaseBase();
  ~CBRCaseBase();
  virtual std::vector<CBRCaseDistance> GetKNN(int K,float threshold);
  //returns weighted eucliden distance between two Cases
  virtual float GetDistance(CBRCase * a, CBRCase * b);
};
