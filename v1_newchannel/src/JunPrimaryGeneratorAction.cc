#include "JunPrimaryGeneratorAction.hh"

JunPrimaryGeneratorAction::JunPrimaryGeneratorAction()
{

  //particle number per shoot 
  G4int numParticle = 1;
  JunParticleGun = new G4ParticleGun(numParticle);
  //---basic parameters for elastic breakup
  G4double states_list[] = {13.2*MeV,14.2*MeV,15.*MeV,16.*MeV};
  //string files_list[] = {"genCS/cs_"}
  numStates = sizeof(states_list)/sizeof(states_list[0]);
  exStates = new G4double[numStates];
  for(int i=0;i<numStates;++i)
    exStates[i] = states_list[i];
  //-----------
  JunSetExParticle(4,9,"target");//9Be
  JunSetExParticle(6,13,"beam");//13C
  JunSetExParticle(2,4,"light");//alpha
  JunSetExParticle(4,9,"heavy");//9Be
  Mass_b = Mass_a;
  Mass_B = Mass_A;
  breakupThreshold = 10.65*MeV;
  //cout<<GetMaxLabTheta(70,15)<<endl;
  //cout<<"Mass of 13C : "<<Mass_a<<endl;
  //cout<<"Mass of 9Be : "<<Mass_A<<endl;
  //cout<<"Mass of 4He : "<<massLightPiece<<endl;
  //--
  //LoadCrossSection("../genCS/cs_16.00.root");//cross-section in lab
  //------------------------
  G4NucleiProperties* JunNucleiProperties = new G4NucleiProperties();
  excitedC13 = {13,6,0,JunNucleiProperties->GetNuclearMass(13,6),G4ThreeVector(0,0,1),0,NULL};
  jbMode[0].threshold = 10.65*MeV;
  jbMode[0].numbreak = 2;
  jbMode[0].piece["recoilBe9"] = {9,4,0,JunNucleiProperties->GetNuclearMass(9,4),G4ThreeVector(0,0,1),0,NULL};
  jbMode[0].piece["breakupBe9"] = {9,4,1,JunNucleiProperties->GetNuclearMass(9,4),G4ThreeVector(0,0,1),0,NULL};
  jbMode[0].piece["breakupHe4"] = {4,2,1,JunNucleiProperties->GetNuclearMass(4,2),G4ThreeVector(0,0,1),0,NULL};
  jbMode[1].threshold = 12.3*MeV;
  jbMode[1].numbreak = 4;
  jbMode[1].piece["recoilBe9"] = {9,4,0,JunNucleiProperties->GetNuclearMass(9,4),G4ThreeVector(0,0,1),0,NULL};
  jbMode[1].piece["breakHe4a"] = {4,2,1,JunNucleiProperties->GetNuclearMass(4,2),G4ThreeVector(0,0,1),0,NULL};
  jbMode[1].piece["breakHe4b"] = {4,2,1,JunNucleiProperties->GetNuclearMass(4,2),G4ThreeVector(0,0,1),0,NULL};
  jbMode[1].piece["breakHe4c"] = {4,2,1,JunNucleiProperties->GetNuclearMass(4,2),G4ThreeVector(0,0,1),0,NULL};
}

JunPrimaryGeneratorAction::~JunPrimaryGeneratorAction()
{
  delete JunParticleGun;
}

void JunPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //G4ParticleDefinition* G4IonTable::GetIon(G4int Z, G4int A, G4double E, G4int J=0)
  //..................................GetIon(G4int Z, G4int A, G4int lvl=0)
  // G4ParticleDefinition *lightPiece = G4IonTable::GetIonTable()->GetIon(2,4);
  // G4ParticleDefinition *heavyPiece = G4IonTable::GetIonTable()->GetIon(4,9);
  // G4ParticleDefinition *recoiPiece = G4IonTable::GetIonTable()->GetIon(4,9);
  //----------------------------
  energyLightPiece=-1;
  energyHeavyPiece=-1;
  energyRecoiPiece=-1;
  G4double beamEnergyOfEvent = 70.*MeV;
  G4double excitedEnergyOfEvent = 15.*MeV;
  //----------------------------------
  excitedEnergyOfEvent = *(exStates+(int)CLHEP::RandFlat::shoot(0.,numStates));
  //==========================
  JunPreparePieces(jbMode[1],beamEnergyOfEvent,excitedEnergyOfEvent,anEvent);
  //cout<<"************************************ "<<excitedEnergyOfEvent<<endl;
  //------------------------------------
  // while(energyLightPiece<0||energyHeavyPiece<0||energyRecoiPiece<0)
  // {
  //   JunExBeamOn(beamEnergyOfEvent,excitedEnergyOfEvent);
  // }
  //---------------
  // EmittingTreeRecorder *emitRec = EmittingTreeRecorder::Instance();
  // emitRec->type[0]=0;//aplha
  // emitRec->name.push_back("alpha");
  // emitRec->energy[0]=energyLightPiece;
  // emitRec->px[0]=velocityLightPiece[0];
  // emitRec->py[0]=velocityLightPiece[1];
  // emitRec->pz[0]=velocityLightPiece[2];
  
  // emitRec->type[1]=1;//breaking 9Be
  // emitRec->name.push_back("9Be");
  // emitRec->energy[1]=energyHeavyPiece;
  // emitRec->px[1]=velocityHeavyPiece[0];
  // emitRec->py[1]=velocityHeavyPiece[1];
  // emitRec->pz[1]=velocityHeavyPiece[2];
  
  // emitRec->type[2]=2;//recoil 9Be
  // emitRec->name.push_back("recoil");
  // emitRec->energy[2]=energyRecoiPiece;
  // emitRec->px[2]=mometumRecoiPiece[0];
  // emitRec->py[2]=mometumRecoiPiece[1];
  // emitRec->pz[2]=mometumRecoiPiece[2];
  // emitRec->Fill();
  //particle_1
  // JunParticleGun->SetParticleDefinition(lightPiece);
  // JunParticleGun->SetParticleCharge(0.);
  // JunParticleGun->SetParticleEnergy(energyLightPiece);
  // JunParticleGun->SetParticleTime(0.);
  // JunParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  // JunParticleGun->SetParticleMomentumDirection(velocityLightPiece);
  // JunParticleGun->GeneratePrimaryVertex(anEvent);
  //G4cout<<"\033[35;1m # Miao ****"<<heavyPiece<<"****** \033[0m"<<G4endl;
  //particle_2
  // JunParticleGun->SetParticleDefinition(heavyPiece);
  // JunParticleGun->SetParticleCharge(0.);
  // JunParticleGun->SetParticleEnergy(energyHeavyPiece);
  // JunParticleGun->SetParticleTime(0.);
  // JunParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  // JunParticleGun->SetParticleMomentumDirection(velocityHeavyPiece);
  // JunParticleGun->GeneratePrimaryVertex(anEvent);
  //particle_3
  // JunParticleGun->SetParticleDefinition(recoiPiece);
  // JunParticleGun->SetParticleCharge(0.);
  // JunParticleGun->SetParticleEnergy(energyRecoiPiece);
  // JunParticleGun->SetParticleTime(0.);
  // JunParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  // JunParticleGun->SetParticleMomentumDirection(mometumRecoiPiece);
  // JunParticleGun->GeneratePrimaryVertex(anEvent);
  //
}

void JunPrimaryGeneratorAction::JunSetExParticle(G4int zValue,G4int aValue,string particleID)
{
  //static G4double G4NucleiProperties::GetNuclearMass (const G4int A, const G4int Z)
  G4NucleiProperties* JunNucleiProperties = new G4NucleiProperties();
  //----------
  if(particleID=="target")
    Mass_A = JunNucleiProperties->GetNuclearMass(aValue,zValue);
  else if(particleID=="beam")
    Mass_a = JunNucleiProperties->GetNuclearMass(aValue,zValue);
  else if(particleID=="light")
    massLightPiece = JunNucleiProperties->GetNuclearMass(aValue,zValue);
  else if(particleID=="heavy")
    massHeavyPiece = JunNucleiProperties->GetNuclearMass(aValue,zValue);
  else
  {
    G4cout<<"\033[35;1m # Miao \033[0m : Wrong label of particle setting !"<<G4endl;
    exit(0);
  }
  delete JunNucleiProperties;
  JunNucleiProperties = NULL;
}

void JunPrimaryGeneratorAction::JunExBeamOn(G4double beamEnergy,G4double excitedEnergy)
{
  G4double Eb=beamEnergy;
  G4double Ex=excitedEnergy;
  //G4double maxLabTheta = GetMaxLabTheta(Eb,Ex);
  //G4double theta0=CLHEP::RandFlat::shoot(0.,maxLabTheta)*deg;
  G4double theta0=GetAngleByCS(Eb,Ex);
  G4double phi0=CLHEP::RandFlat::shoot(0.,360.)*deg;
  //cout<<" # "<<setw(10)<<theta0/deg<<setw(10)<<phi0/deg<<endl;
  G4double ek0=JunExScattered(Eb,Ex,theta0);
  G4ThreeVector pin,p0,vpcms;//beam,13C,in cms,recoil
  pin.set(0,0,TMath::Sqrt((Eb+2*Mass_a)*Eb));
  if(ek0!=-1)
  {
    G4double p0mag=TMath::Sqrt((ek0+2*Mass_b)*ek0);
    p0.setRThetaPhi(p0mag,theta0,phi0);
    mometumRecoiPiece=pin-p0;
    energyRecoiPiece=TMath::Sqrt(mometumRecoiPiece*mometumRecoiPiece+Mass_B*Mass_B)-Mass_B;
    G4double pcms=TMath::Sqrt(2*(Ex-breakupThreshold)*massLightPiece*massHeavyPiece/Mass_b);
    G4double thetacms=TMath::ACos(JunDisOfPiece(0,0));//!!!
    G4double phicms=CLHEP::RandFlat::shoot(0.,360.)*deg;
    vpcms.setRThetaPhi(pcms,thetacms,phicms);
    velocityLightPiece=p0/Mass_b+vpcms/massLightPiece;
    energyLightPiece=0.5*massLightPiece*(velocityLightPiece*velocityLightPiece);
    velocityHeavyPiece=p0/Mass_b-vpcms/massHeavyPiece;
    energyHeavyPiece=0.5*massHeavyPiece*(velocityHeavyPiece*velocityHeavyPiece);
  }
  else
  {
    energyLightPiece=-1;
    energyHeavyPiece=-1;
    energyRecoiPiece=-1;
    velocityLightPiece={0,0,-1};
    velocityHeavyPiece={0,0,-1};
    mometumRecoiPiece={0,0,-1};
  }
}

G4double JunPrimaryGeneratorAction::GetMaxLabTheta(G4double initialEnergy,G4double exEnergy)
{
  G4double ans2 = (Mass_B+Mass_b)*(exEnergy*Mass_B-initialEnergy*Mass_B+initialEnergy*Mass_a)/Mass_a/Mass_b/initialEnergy;
  if(ans2<0) return 180;
  else if(ans2>1) return 0;
  else return TMath::ACos(TMath::Sqrt(ans2))/deg;
}

G4double JunPrimaryGeneratorAction::JunExScattered(G4double initialEnergy,G4double exEnergy,G4double scatteredTheta)
{
  G4double Qvalue = 0.-exEnergy;
  G4double part1,part2,part3;
  part1=TMath::Sqrt(Mass_a*Mass_b*initialEnergy)*TMath::Cos(scatteredTheta)/(Mass_B+Mass_b);
  part2=initialEnergy*(Mass_B-Mass_a)/(Mass_B+Mass_b)+TMath::Power(part1,2);
  part3=Mass_B*Qvalue/(Mass_B+Mass_b);
  if((part2+part3)>0)
  {
    // if(CLHEP::RandFlat::shoot(0.,1.)<=0.01)
      // return TMath::Power((part1-TMath::Sqrt(part2+part3)),2);
    // else 
      // 
    return TMath::Power((part1+TMath::Sqrt(part2+part3)),2);
  }
  else 
  {
    return -1;
  }
}

G4double legendre2(double *x,double *p)
{
  return TMath::Power(ROOT::Math::assoc_legendre(p[0],p[1],x[0]),2);
}

G4double JunPrimaryGeneratorAction::JunDisOfPiece(int l_jun,int m_jun)
{
  TF1 flen2("len",legendre2,-1,1,2);
  flen2.SetParameters(l_jun,m_jun);
  return flen2.GetRandom();
  //return CLHEP::RandFlat::shoot(0.01,0.99);
}

void JunPrimaryGeneratorAction::LoadCrossSection(string csfile)
{
  TFile *in_file = TFile::Open(csfile.c_str());
  hist_cs = (TH1D*)in_file->GetObjectChecked("h1","TH1D");
}

G4double JunPrimaryGeneratorAction::GetAngleByCS(G4double beamEnergy,G4double exEnergy)
{
  double cosE = beamEnergy*Mass_A/(Mass_A+Mass_a);
  double c=Mass_a/Mass_A*sqrt(cosE/(cosE-exEnergy));
  double xrad=acos(-1./c);
  double term1=sqrt(1+c*c+2*c*cos(xrad));
  double angle=acos((c+cos(xrad))/term1);
  return CLHEP::RandFlat::shoot(0.,angle);
  //return hist_cs->GetRandom()*deg;
}
//======================
 G4double JunPrimaryGeneratorAction::JunPreSca(G4double initialEnergy,G4double exEnergy,G4double scatteredTheta)
 {
  G4double Qvalue = 0.-exEnergy;
  G4double part1,part2,part3;
  G4double flag = -1;
  while(flag<0)
  {
    part1=TMath::Sqrt(Mass_a*Mass_b*initialEnergy)*TMath::Cos(scatteredTheta)/(Mass_B+Mass_b);
    part2=initialEnergy*(Mass_B-Mass_a)/(Mass_B+Mass_b)+TMath::Power(part1,2);
    part3=Mass_B*Qvalue/(Mass_B+Mass_b);
    flag = part2+part3;
  }
  return TMath::Power((part1+TMath::Sqrt(part2+part3)),2);
 }

void JunPrimaryGeneratorAction::JunPreparePieces(JunBreakupMode mode,G4double beamEnergy,G4double excitedEnergy,G4Event* anEvent)
{
  G4double Eb = beamEnergy;
  G4double Ex = excitedEnergy;
  G4double th = mode.threshold;
  //the beam
  G4ThreeVector pin;
  pin.set(0,0,TMath::Sqrt((Eb+2*Mass_a)*Eb));//the beam
  // the excited one
  G4double theta0=GetAngleByCS(Eb,Ex);//exC13
  G4double phi0=CLHEP::RandFlat::shoot(0.,360.)*deg;//exC13
  G4double ek0=JunPreSca(Eb,Ex,theta0);//exC13
  G4ThreeVector p0;//mometum of 13C
  G4double m0 = excitedC13.mass;//mass of excitedC13
  G4double p0mag=TMath::Sqrt((ek0+2*m0)*ek0);
  p0.setRThetaPhi(p0mag,theta0,phi0);//excited 13C
  //the recoil one
  G4ThreeVector Pr = pin-p0; //mometum
  G4double Mr = mode.piece["recoilBe9"].mass;//restmass
  G4double Er = TMath::Sqrt(Pr*Pr+Mr*Mr)-Mr;//energy
  mode.piece["recoilBe9"].direction = Pr;
  mode.piece["recoilBe9"].energy = Er;
  //two modes
  if(mode.numbreak == 2)
  {
    G4double ml = mode.piece["breakupHe4"].mass;
    G4double mh = mode.piece["breakupBe9"].mass;
    G4double pcms = TMath::Sqrt(2*(Ex-th)*ml*mh/(ml+mh));//相对论的解太复杂了
    G4double thetacms = TMath::ACos(JunDisOfPiece(0,0));//!!!
    G4double phicms = CLHEP::RandFlat::shoot(0.,360.)*deg;
    G4ThreeVector vpcms;//vector of mometum in cms
    vpcms.setRThetaPhi(pcms,thetacms,phicms);
    G4ThreeVector vl = p0/m0+vpcms/ml;
    G4ThreeVector vh = p0/m0-vpcms/mh;
    G4double El = 0.5*ml*vl*vl;
    G4double Eh = 0.5*mh*vh*vh;
    mode.piece["breakupHe4"].direction = vl;
    mode.piece["breakupBe9"].direction = vh;
    mode.piece["breakupHe4"].energy = El;
    mode.piece["breakupBe9"].energy = Eh;
  }
  else if(mode.numbreak > 2)
  {
    G4double Eres = Ex-th;
    for(auto it=mode.piece.begin();it!=mode.piece.end();++it)
    {
      if(it->second.isBreak)
      {
        G4double ranTheta = TMath::ACos(JunDisOfPiece(0,0));
        G4double ranPhi = CLHEP::RandFlat::shoot(0.,360.)*deg;
        G4double ranE = CLHEP::RandFlat::shoot(0.,Eres);
        G4double mass = it->second.mass;
        G4double pcms = TMath::Sqrt((ranE+2*mass)*ranE);
        G4ThreeVector vpcms;
        vpcms.setRThetaPhi(pcms,ranTheta,ranPhi);
        G4ThreeVector v = p0/m0+vpcms/mass;//velocity
        it->second.direction = v;
        it->second.energy = 0.5*mass*v*v;
        Eres = Eres-ranE;
      }
    }
  }
  else
  {
    cout<<"Error num of breakups"<<endl;
    exit(0);
  }
  //set particle gun
  for(auto it=mode.piece.begin();it!=mode.piece.end();++it)
  {
    //it->second.g4pd = G4IonTable::GetIonTable()->GetIon(it->second.Z,it->second.A);
    G4ParticleDefinition *g4pd = G4IonTable::GetIonTable()->GetIon(it->second.Z,it->second.A);
    JunParticleGun->SetParticleDefinition(g4pd);
    JunParticleGun->SetParticleCharge(0.);
    JunParticleGun->SetParticleEnergy(it->second.energy);
    JunParticleGun->SetParticleTime(0.);
    JunParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
    JunParticleGun->SetParticleMomentumDirection(it->second.direction);
    JunParticleGun->GeneratePrimaryVertex(anEvent);
    //cout<<it->second.energy<<endl;
  }
}