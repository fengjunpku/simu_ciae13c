#include "myEventAction.hh"

myEventAction::myEventAction()
{
  JunParMan *jParManager = JunParMan::Instance();
  G4int maxParticles = jParManager->GetPar("Max_Num_Particle");
  energy = new double[maxParticles+1];
  time = new double[maxParticles+1];
  px = new double[maxParticles+1];
  py = new double[maxParticles+1];
  iStrip = new int[maxParticles+1];
  jStrip = new int[maxParticles+1];
}

myEventAction::~myEventAction()
{
  G4cout<<"End of myEventAction.(0)"<<G4endl;
  delete[] energy;
  delete[] time;
  delete[] px;
  delete[] py;
  delete[] iStrip;
  delete[] jStrip;
  G4cout<<"End of myEventAction.(1)"<<G4endl;
}

void myEventAction::BeginOfEventAction(const G4Event* evt)
{
  G4int id = evt->GetEventID();
  if(!(id%10000)) G4cout<<"      EventID : "<<id<<G4endl;
}

void myEventAction::EndOfEventAction(const G4Event* evt)
{
  G4HCofThisEvent* _eHC = evt->GetHCofThisEvent();
  //---------------------------------------------------
  JunParMan *jParManager = JunParMan::Instance();
  vector<string> dssdNames = jParManager->GetAllDSSDName();
  G4int dssdNums = dssdNames.size();
  G4int maxParticles = jParManager->GetPar("Max_Num_Particle");
  G4int sizeArray = maxParticles+1;
  //G4cout<<" # "<<maxParticles<<G4endl;
  myTTreeRecorder *rec = myTTreeRecorder::Instance();
  //-----------------------------
  for(int i=0;i<dssdNums;++i)
  {
    TRandom3 Trndm(0);
    string _dCollectionName = dssdNames[i]+"_SD_collection";
    G4int _dCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(_dCollectionName);
    myHitsCollection* _dHC = 0;
    if(_eHC) _dHC = (myHitsCollection*)(_eHC->GetHC(_dCollectionID));
    if(_dHC)
    {
      for(int ij=0;ij<maxParticles+1;++ij)
      {
        energy[ij] = 0;
        time[ij] = 1.*ms;
        px[ij] = -6.*cm;
        py[ij] = -6.*cm;
        iStrip[ij] = -1;
        jStrip[ij] = -1;
      }
      nhit=0;
      //------------------
      G4int _dNumSteps = _dHC->entries();
      for(int k=0;k<_dNumSteps;++k)
      {
        int vTmp = (*_dHC)[k]->GetVStrip();
        int hTmp = (*_dHC)[k]->GetHStrip();
        if( iStrip[nhit%sizeArray]!=vTmp || jStrip[nhit%sizeArray]!=hTmp)
        {
          nhit++;
          time[nhit%sizeArray] = (*_dHC)[k]->GetHitT();
          px[nhit%sizeArray] = (*_dHC)[k]->GetX();
          py[nhit%sizeArray] = (*_dHC)[k]->GetY();
          iStrip[nhit%sizeArray] = vTmp;
          jStrip[nhit%sizeArray] = hTmp;
        }
        energy[nhit%sizeArray]+=(*_dHC)[k]->GetDeltaE();
      }
      ////////////////
      //G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
      //anaMan->FillH1(1,energy[0]);
      ///////////////
      
      for(int mp=0;mp<maxParticles;++mp)
      {
        if(energy[mp+1]>0)
          energy[mp+1] += Trndm.Gaus(0,0.1);
        rec->var[7*i+0][mp] = energy[mp+1];//+Trndm.Gaus(0,0.1);
        rec->var[7*i+1][mp] = time[mp+1];
        rec->var[7*i+2][mp] = px[mp+1];
        rec->var[7*i+3][mp] = py[mp+1];
        rec->var[7*i+4][mp] = iStrip[mp+1];
        rec->var[7*i+5][mp] = jStrip[mp+1];
        rec->var[7*i+6][mp] = nhit;
      }
    }
  }
  double totalE=0;
  for(int i=0;i<dssdNums;++i)
  {
    for(int mp=0;mp<maxParticles;++mp)
    {
      totalE+=rec->var[7*i+0][mp];
    }
  }
  if(totalE>0) rec->Fill();
}
