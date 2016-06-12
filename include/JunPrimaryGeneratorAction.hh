#ifndef JunPrimaryGeneratorAction_h
#define JunPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4NucleiProperties.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TVector3.h"
#include "TF1.h"
#include "TH1D.h"
#include "TFile.h"
#include "Math/SpecFuncMathMore.h"
#include "Math/SpecFuncMathCore.h"

#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include "EmittingTreeRecorder.hh"

using namespace std;

class JunPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  JunPrimaryGeneratorAction();
  ~JunPrimaryGeneratorAction();
  void GeneratePrimaries(G4Event* anEvent);
private:
  void JunSetExParticle(G4int zValue,G4int aValue,string particleID);
  void JunExBeamOn(G4double beamEnergy,G4double excitedEnergy);
  G4double JunExScattered(G4double initialEnergy,G4double exEnergy,G4double scatteredTheta);
  G4double JunDisOfPiece(int l_jun,int m_jun);
  G4double GetMaxLabTheta(G4double initialEnergy,G4double exEnergy);
  void LoadCrossSection(string csfile);
  G4double GetAngleByCS(G4double beamEnergy,G4double exEnergy);
private:
  G4ParticleGun* JunParticleGun;

  G4double energyLightPiece,energyHeavyPiece,energyRecoiPiece,breakupThreshold;
  G4ThreeVector velocityLightPiece,velocityHeavyPiece,mometumRecoiPiece;//velocity;mometum

  G4double Mass_a;//beam a
  G4double Mass_A;//target A
  G4double Mass_b;//outgoing b
  G4double Mass_B;//recoil B
  G4double massLightPiece,massHeavyPiece;//pieces
  G4double* exStates;
  int numStates;
  TH1D *hist_cs;
};

#endif