#include<vector>

class EuropeanCallOption{
public:

  //constructor
  EuropeanCallOption(
    int nInt_,
    double strike_,
    double spot_,
    double vol_,
    double r_,
    double expiry_,
    double barier_
  );

  //destructor
  ~EuropeanCallOption(){};

  //methods
  void generatePath();
  void printPath();
  double getEuropeanCallPrice(int nReps);
  double getLastPrice();

  //members
  std::vector<double> thisPath;
  int nInt;
  double strike;
  double spot;
  double vol;
  double r;
  double expiry;
  double barier;
};
