#include "myPhysicsList.hh"

myPhysicsList::myPhysicsList()
{
	defaultCutValue=0.1*mm;//threshold of secondary particle
	G4int ver=0;//verbose level
	SetVerboseLevel(ver);
	SetCutsWithDefault();

	//Decays
	RegisterPhysics(new G4DecayPhysics("Decay"));
	//RadioactiveDecayPhysics
	RegisterPhysics(new G4RadioactiveDecayPhysics());
	//EM Physics
	RegisterPhysics(new G4EmStandardPhysics(ver,"EM"));
	//Synchroton Radiation & GammaNuclear Physics
	G4String fState="on";
	G4EmExtraPhysics *pEmPhy=new G4EmExtraPhysics(ver);
	pEmPhy->Synch(fState);
	pEmPhy->GammaNuclear(fState);
	pEmPhy->MuonNuclear(fState);
	RegisterPhysics(pEmPhy);
}
myPhysicsList::~myPhysicsList()
{;}
