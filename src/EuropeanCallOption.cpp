#include<iostream>
#include<cmath>
#include"getOneGaussianByBoxMueller.h"
#include"EuropeanCallOption.h"

//definition of constructor
EuropeanCallOption::EuropeanCallOption(
  int nInt_,
  double strike_,
  double spot_,
  double vol_,
  double r_,
  double expiry_,
  double barier_){
  nInt = nInt_;
  strike = strike_;
  spot = spot_;
  vol = vol_;
  r = r_;
  expiry = expiry_;
  barier = barier_;
  generatePath();
}


void EuropeanCallOption::generatePath(){
  double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
  double cumShocks = 0;
  thisPath.clear();

  for(int i = 0; i < nInt; i++){
    cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());
    thisPath.push_back(spot * exp(cumShocks));
  }
}


//method definition
void EuropeanCallOption::printPath(){

  for(int i = 0;  i < nInt; i++){

    std::cout << thisPath[i] << "\n";

  }

}

double EuropeanCallOption::getLastPrice(){

  return thisPath[nInt-1];

}

//method definition
double EuropeanCallOption::getEuropeanCallPrice(int nReps){

  double rollingSum = 0.0;
  double lastPrice = 0.0;

  for(int i = 0; i < nReps; i++){
    lastPrice=getLastPrice();

    if(*std::max_element(thisPath.begin(), thisPath.end()) <= barier){
      rollingSum += ( lastPrice > strike) ? (lastPrice -strike) : 0;
    }
    generatePath();
  }

  return exp(-r*expiry)*rollingSum/double(nReps);

}
