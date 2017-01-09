#include <vector>
struct CBRCaseDistance{
  float Distance;
  CBRCase * Case;  
}
class CBRCaseBase{
public:
  CBRCaseBase();
  ~CBRCaseBase();
  std::vector<CBRCaseDistance> GetKNN(int K,float threshold);
};
