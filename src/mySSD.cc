#include "mySSD.hh"

mySSD::mySSD(G4String detName,G4int numVStrips,G4int numHStrips,G4double width,G4double heigh) : G4VSensitiveDetector(detName), hitsCollection(0), collectionID(-1)
{
	G4String name_col = detName+"_collection";
	collectionName.insert(name_col);
	_numVS = numVStrips;
	_numHS = numHStrips;
	_width = width;
	_heigh = heigh;
}

mySSD::~mySSD()
{
}

void mySSD::Initialize(G4HCofThisEvent* HCE)
{
	if(collectionID<0) collectionID=GetCollectionID(0);
	hitsCollection = new myHitsCollection(SensitiveDetectorName,collectionName[0]);
	HCE->AddHitsCollection(collectionID,hitsCollection);
}

G4bool mySSD::ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist)
{
	myHit* aHit = new myHit();
	//some set methods
	G4double stepE = aStep->GetTotalEnergyDeposit();
	G4double stepT = aStep->GetPostStepPoint()->GetGlobalTime();
	G4TouchableHandle touchHandle = aStep->GetPreStepPoint()->GetTouchableHandle();
	G4ThreeVector worldPos = aStep->GetPreStepPoint()->GetPosition();
	G4ThreeVector localPos= touchHandle->GetHistory()->GetTopTransform().TransformPoint(worldPos);
	G4double stepX = localPos.getX();
	G4double stepY = localPos.getY();
	//G4cout<<"  "<<stepT / ns<<" *ns"<<endl;
	G4int stepVS = (G4int)((stepX/_width+0.5)*_numVS);
	G4int stepHS = (G4int)((stepY/_heigh+0.5)*_numHS);
///////////////
	aHit->SetDeltaE(stepE);
	aHit->SetHitT(stepT);
	aHit->SetXY(stepX,stepY);
	aHit->SetStrip(stepVS,stepHS);
	/////
	hitsCollection->insert(aHit);
	return true;
}

void mySSD::EndOfEvent(G4HCofThisEvent* HCE)
{;}
