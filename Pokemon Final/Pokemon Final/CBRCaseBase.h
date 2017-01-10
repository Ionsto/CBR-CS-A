#include <vector>
struct CBRCaseDistance{
  float Distance;
  CBRCase * Case;  
}
class CBRCaseBase{
public:
  //Weights for the distance
  CBRCaseBase();
  ~CBRCaseBase();
  std::vector<CBRCaseDistance> GetKNN(int K,float threshold);
  //returns weighted eucliden distance between two Cases
  float GetDistance(CBRCase * a, CBRCase * b);
};
