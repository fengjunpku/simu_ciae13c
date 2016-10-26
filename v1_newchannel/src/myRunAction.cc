#include "myRunAction.hh"

myRunAction::myRunAction():G4UserRunAction()
{
  //G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
  //anaMan->SetVerboseLevel(1);
  //anaMan->SetFirstHistoId(1);
  //anaMan->CreateH1("1","Edep in SSD",100,0.,10*MeV);
  /////////////////////////////////////
  myTTreeRecorder *rec = myTTreeRecorder::Instance();
  EmittingTreeRecorder *emitRec = EmittingTreeRecorder::Instance();
}

myRunAction::~myRunAction()
{
  //delete G4AnalysisManager::Instance();
  delete JunParMan::Instance();
  delete myTTreeRecorder::Instance();
  delete EmittingTreeRecorder::Instance();
  G4cout<<"End of the run!"<<G4endl;
}

void myRunAction::BeginOfRunAction(const G4Run* aRun)
{
  fRunID = aRun->GetRunID();
  //G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
  //anaMan->OpenFile("myData");
  ///////////////////////////
  myTTreeRecorder *rec = myTTreeRecorder::Instance();
  string outfile="jtree.root";
  rec->OpenFile(outfile);
  G4cout<<"\033[35;1m # Miao \033[0m : Open the output \033[33m\'"<<outfile<<"\033[0m\' !"<<G4endl;
  //---------
  EmittingTreeRecorder *emitRec = EmittingTreeRecorder::Instance();
  outfile="etree.root";
  emitRec->OpenFile(outfile);
  G4cout<<"\033[35;1m # Miao \033[0m : Open the output \033[33m\'"<<outfile<<"\033[0m\' !"<<G4endl;
}

void myRunAction::EndOfRunAction(const G4Run* aRun)
{
  //G4AnalysisManager* anaMan = G4AnalysisManager::Instance();
  //anaMan->Write();
  //anaMan->CloseFile();
  /////////////////
  myTTreeRecorder *rec = myTTreeRecorder::Instance();
  G4cout<<"\033[35;1m # Miao \033[0m : Try to Record to th file !"<<G4endl;
  rec->Record();
  G4cout<<"\033[35;1m # Miao \033[0m : Record the output file !"<<G4endl;
  //--------
  EmittingTreeRecorder *emitRec = EmittingTreeRecorder::Instance();
  emitRec->Record();
  G4cout<<"\033[35;1m # Miao \033[0m : Record the output file2 !"<<G4endl;
}
