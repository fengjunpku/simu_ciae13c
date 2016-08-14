#include "JunParticle.hh"

JunParticle::JunParticle()
{
  name="null";
  direction.SetXYZ(0,0,-1);
  energy=-1;
}

JunParticle::~JunParticle()
{;}

void JunParticle::SetParticle(string pName,Double_t pEnergy,TVector3 pDirection)
{
  name=pName;
  direction=pDirection.Unit();
  energy=pEnergy;
  theta=direction.Theta()/TMath::Pi()*180;
  phi=direction.Phi()/TMath::Pi()*180;
  //momentum=CalMomentum();
}

// TVector3 JunParticle::CalMomentum()
// {
	// Double_t pMass=1;;
	// if(name=="9Be")
		// pMass=9;
	// else if(name=="4He")
		// pMass=4;
	// else if(name=="13C")
		// pMass=13;
	// else
		// pMass=-1;
	// return (energy/pMass)*direction;
// }