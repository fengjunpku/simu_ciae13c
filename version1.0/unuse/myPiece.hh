#ifndef myPiece_H
#define myPiece_H 1

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TF1.h"
#include "Math/SpecFuncMathMore.h"
#include "Math/SpecFuncMathCore.h"
#include "G4NucleiProperties.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
class myPiece
{
public:
	myPiece();
	virtual ~myPiece();
	void beamOn(G4double beamEnergy,G4double exEnergy);
	inline G4ThreeVector GetLightV(){return vl;}//Velocity of light piece
	inline G4ThreeVector GetHeavyV(){return vh;}
	inline G4ThreeVector GetRecoilP(){return pr;}
	inline G4double GetLightE(){return el;}//energy if light piece
	inline G4double GetHeavyE(){return eh;}
	inline G4double GetRecoilE(){return er;}
	inline G4ParticleDefinition* GetLightPiece(){return plight;}
	inline G4ParticleDefinition* GetHeavyPiece(){return pheavy;}
	inline G4ParticleDefinition* GetRecoilPiece(){return precoil;}
private:
	G4ParticleDefinition *plight;
	G4ParticleDefinition *pheavy;
	G4ParticleDefinition *precoil;
	G4double Eb,Ex;
	G4double el,eh,er;//light,heavy,recoil
	G4ThreeVector vl,vh,pr;//velocity;mometum
	///
	G4NucleiProperties *pro;
	G4double M_a;//beam
	G4double M_A;//target
	G4double M_b;//outgoing
	G4double M_B;//recoil
	G4double ml,mh;//pieces
	///
	G4double scattered(G4double Ein,G4double theta,G4double ExE);//energy after scattering
public:
	G4double disOfP(int l,int m);
};
#endif
