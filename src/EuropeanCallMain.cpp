#include<vector>
#include<ctime>
#include<cstdlib>
#include<iostream>
#include"EuropeanCallOption.h"
#include"getOneGaussianByBoxMueller.h"
#include <Rcpp.h>

using namespace Rcpp;

// [[Rcpp::export]]
double europeanCallOption(int n, 
                          double strike, 
                          double spot,
                          double vol, 
                          double r,
                          double exp,
                          double barrier,
                          int nReps){

  srand(time(NULL));

  EuropeanCallOption option(n, strike, spot, vol, r, exp, barrier);
  double price = option.getEuropeanCallPrice(nReps);
  std::cout << "The price of the option is: " << price;

  return price;
}
