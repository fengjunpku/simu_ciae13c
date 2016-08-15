#ifndef myEventAction_h
#define myEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4VHitsCollection.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "myHit.hh"
//#include "myAnalysis.hh"
#include "myTTreeRecorder.hh"
#include <TRandom3.h>
#include "JunParMan.hh"
#include <vector>
#include <string>
class myEventAction : public G4UserEventAction
{
public:
  myEventAction();
  virtual ~myEventAction();
  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);
private:
  double* energy;
  double* time;
  double* px;
  double* py;
  int* iStrip;
  int* jStrip;
  int nhit;
};



#endif
