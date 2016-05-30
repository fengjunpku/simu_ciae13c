#include "myPiece.hh"

myPiece::myPiece()
{
	plight = G4ParticleTable::GetParticleTable()->FindParticle("alpha");
	pheavy = G4IonTable::GetIonTable()->GetIon(4,9,0);//Z,A,Ex
	//G4cout<<"***Find  aaaaaaa   "<<pheavy<<G4endl;
	//pheavy = G4IonTable::GetIonTable()->FindIon(4,9,0);//Z,A,Ex
	//G4cout<<"Get  aaaaaaa   "<<pheavy<<G4endl;
	precoil = pheavy;
	pro = new G4NucleiProperties();
	M_a=pro->GetNuclearMass(13,6);//beam MeV
	M_A=pro->GetNuclearMass(9,4);//target
	M_b=pro->GetNuclearMass(13,6);//outgoing
	M_B=pro->GetNuclearMass(9,4);//recoil
	ml=pro->GetNuclearMass(4,2);//alpha
	mh=pro->GetNuclearMass(9,4);
}

myPiece::~myPiece()
{
	delete pro;
}

G4double myPiece::scattered(G4double Ein,G4double theta,G4double ExE)
{
	G4double Qvalue=0.-ExE;
	G4double part1,part2,part3;
	part1=TMath::Sqrt(M_a*M_b*Ein)*TMath::Cos(theta)/(M_B+M_b);
	part2=Ein*(M_B-M_a)/(M_B+M_b)+TMath::Power(part1,2);
	part3=M_B*Qvalue/(M_B+M_b);
	if((part2+part3)>0)
		return TMath::Power((part1+TMath::Sqrt(part2+part3)),2);
	else 
		return -1;
}

void myPiece::beamOn(G4double beamEnergy,G4double exEnergy)
{
	Eb=beamEnergy;
	Ex=exEnergy;
	G4double theta0=CLHEP::RandFlat::shoot(0.,40)*deg;
	G4double phi0=CLHEP::RandFlat::shoot(0.,360.)*deg;
	G4double ek0=scattered(Eb,theta0,Ex);
	G4ThreeVector pin,p0,vpcms;//beam,13C,in cms,recoil
	pin.set(0,0,TMath::Sqrt((Eb+2*M_a)*Eb));
	if(ek0!=-1)
	{
		G4double p0mag=TMath::Sqrt((ek0+2*M_b)*ek0);
		p0.setRThetaPhi(p0mag,theta0,phi0);
		pr=pin-p0;
		er=TMath::Sqrt(pr*pr+M_B*M_B)-M_B;
		G4double pcms=TMath::Sqrt(2*(Ex-10.7)*ml*mh/M_b);
		G4double thetacms=TMath::ACos(disOfP(0,0));//!!!
		G4double phicms=CLHEP::RandFlat::shoot(0.,360.)*deg;
		vpcms.setRThetaPhi(pcms,thetacms,phicms);
		vl=p0/M_b+vpcms/ml;
		el=0.5*ml*(vl*vl);
		vh=p0/M_b-vpcms/mh;
		eh=0.5*mh*(vh*vh);
	}
	else
	{
		el=-1;eh=-1;
		vl={0,0,-1};
		vh={0,0,-1};
	}
}

G4double legendre2(double *x,double *p)
{
	return TMath::Power(ROOT::Math::assoc_legendre(p[0],p[1],x[0]),2);
}

G4double myPiece::disOfP(int l,int m)
{
	TF1 *flen2 = new TF1("len",legendre2,-1,1,2);
	flen2->SetParameters(l,m);
	return flen2->GetRandom();
}
