#ifndef mySSD_h
#define mySSD_h 1

#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "myHit.hh"//my....

using namespace std;

class mySSD : public G4VSensitiveDetector
{
public:
	mySSD(G4String detName,G4int numVStrips=1,G4int numHStrips=1,G4double width=50.*mm,G4double heigh=50.*mm);
	virtual ~mySSD();
	virtual void Initialize(G4HCofThisEvent* HCE);
	virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
	virtual void EndOfEvent(G4HCofThisEvent* HCE);

private:
	myHitsCollection* hitsCollection;
	G4int collectionID;
	G4int _numVS;
	G4int _numHS;
	G4double _width;
	G4double _heigh;
};

#endif
