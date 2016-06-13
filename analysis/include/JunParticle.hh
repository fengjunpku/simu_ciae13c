#ifndef JunParticle_HH
#define JunParticle_HH
#include <iostream>
#include <string>
#include "TVector3.h"
#include "TMath.h"
using namespace std;
class JunParticle
{
public:
  JunParticle();
  virtual ~JunParticle();
  void SetParticle(string pName,Double_t pEnergy,TVector3 pDirection);
  string name;
  TVector3 direction;
  Double_t energy;
  Double_t theta;
  Double_t phi;
  //TVector3 momentum;
private:
  //TVector3 CalMomentum();
};
#endif