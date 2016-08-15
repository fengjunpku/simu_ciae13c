#include "myPrimaryGeneratorAction.hh"
#include <iomanip>
#include <iostream>
using namespace std;
myPrimaryGeneratorAction::myPrimaryGeneratorAction()
{
	//particle number
	G4int n_particle = 1;
	particleGun = new G4ParticleGun(n_particle);
	particleTable = G4ParticleTable::GetParticleTable();
	ionTable = G4IonTable::GetIonTable();
}

myPrimaryGeneratorAction::~myPrimaryGeneratorAction()
{
	delete particleGun;
}

void myPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	//方法一
	//G4ParticleTable* pparticleTable=G4ParticleTable::GetParticleTable();
	//G4ParticleDefinition* particle=pparticleTable->FindParticle("alpha");  //"e-","e+","gamma","neutron","proton"
	//方法二
	//G4IonTable *particleTable=G4IonTable::GetIonTable();
	//particleTable->GetIon(2,4,0.0); //alpha
	//方法三
	//particleGun->SetParticleDefinition(particle);
	//particleGun->SetParticleCharge(0.);//EM 物理过程自动修正
	//particleGun->SetParticleEnergy(10.*MeV);
	//particleGun->SetParticleTime(0.);
	//particleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
	//particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,1.));
	//particleGun->GeneratePrimaryVertex(anEvent);
	//
	//particleGun->SetParticleMomentum(G4ParticleMomentum);
	//particleGun->SetParticlePolarization(G4ThreeVector);

	myPiece *mypieces = new myPiece();
	G4double lightE = -1;
	G4double heavyE = -1;
	G4double recoilE = -1;
	G4ThreeVector lightV,heavyV,recoilV;
	while(lightE<0 || heavyE<0 || recoilE<0)
	{
		mypieces->beamOn(70,15);
		lightE = mypieces->GetLightE();
		heavyE = mypieces->GetHeavyE();
		recoilE = mypieces->GetRecoilE();
		lightV = mypieces->GetLightV();
		heavyV = mypieces->GetHeavyV();
		recoilV = mypieces->GetRecoilP();
	}
	G4double total = lightE+heavyE+recoilE+10.7;
	if(total>75)
		cout<<setw(10)<<total<<setw(2)<<" : "<<setw(10)<<lightE<<" "<<setw(10)<<heavyE<<" "<<setw(10)<<recoilE<<endl;
	//particle_1
	particleGun->SetParticleDefinition(mypieces->GetLightPiece());
	particleGun->SetParticleCharge(0.);
	particleGun->SetParticleEnergy(lightE);
	particleGun->SetParticleTime(0.);
	particleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
	particleGun->SetParticleMomentumDirection(lightV);
	particleGun->GeneratePrimaryVertex(anEvent);
	//particle_2
	particleGun->SetParticleDefinition(mypieces->GetHeavyPiece());
	particleGun->SetParticleCharge(0.);
	particleGun->SetParticleEnergy(heavyE);
	particleGun->SetParticleTime(0.);
	particleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
	particleGun->SetParticleMomentumDirection(heavyV);
	particleGun->GeneratePrimaryVertex(anEvent);
	//particle_3
	particleGun->SetParticleDefinition(mypieces->GetRecoilPiece());
	particleGun->SetParticleCharge(0.);
	particleGun->SetParticleEnergy(recoilE);
	particleGun->SetParticleTime(0.);
	particleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
	particleGun->SetParticleMomentumDirection(recoilV);
	particleGun->GeneratePrimaryVertex(anEvent);
	delete mypieces;
	mypieces=NULL;
}
//////////////////////////



