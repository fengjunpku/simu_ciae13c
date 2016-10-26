//===================C++==================//
#include <ctime>// initialize random seed
#include <string>
#include <stdlib.h>
//=================GEANT4=================//
#include "Randomize.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
//================ROOT=================//
#include "TStopwatch.h"
//==================User==================//necessary
#include "JunPrimaryGeneratorAction.hh"
#include "myDetectorConstruction.hh"
#include "myPhysicsList.hh"
//===================optional
//#include "SteppingAction.hh"
//#include "TrackingAction.hh"
#include "myEventAction.hh"
#include "myRunAction.hh"
#include "JunParMan.hh"

int main(int argc,char** argv)
{
	TStopwatch watch;
	watch.Start();
  //================read config file ==========================================//
  JunParMan *parman = JunParMan::Instance();
  parman->ReadParFile("fj13c_setup.par");
  //===========================Set the Seed of Random===========================//
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
  CLHEP::HepRandom::setTheSeed(time(NULL));
  //================================Main Codes==================================//
  //runmanger
  G4RunManager* runManager = new G4RunManager();
  //Detector
  myDetectorConstruction* detectors = new myDetectorConstruction();
  runManager->SetUserInitialization(detectors);
  //PhysicsList
  myPhysicsList* physics= new myPhysicsList();
  runManager->SetUserInitialization(physics);
  //Action: PrimaryGenerator
  JunPrimaryGeneratorAction* gen_action = new JunPrimaryGeneratorAction();
  runManager->SetUserAction(gen_action);
  //============================Initialize G4 kernel============================//
  runManager->Initialize();
  //for different parameters
  if(argc==2&&string(argv[1])=="vis")
  {
    //-----------------vis mode---
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/run/verbose 0");
    UImanager->ApplyCommand("/event/verbose 0");
    UImanager->ApplyCommand("/tracking/verbose 0");
    G4UIExecutive *ui=new G4UIExecutive(argc,argv);
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
    ui=NULL;
    delete visManager;
    visManager=NULL;
  }
  else
  {
    //-------------Exec Mode-------------
    //G4UserSteppingAction* stepping_action =new SteppingAction;
    //runManager->SetUserAction(stepping_action);
    //G4UserTrackingAction* tracking_action =new TrackingAction;
    //runManager->SetUserAction(tracking_action);
    G4UserEventAction* event_action = new myEventAction();
    runManager->SetUserAction(event_action);
    G4UserRunAction* run_action = new myRunAction();
    runManager->SetUserAction(run_action);
    if(argc==1)
    {
      int defaultNumberOfEvent=1;
      runManager->BeamOn(defaultNumberOfEvent);
    }
    if(argc==2)
    {
      int numberOfEvent=atoi(argv[1]);
      runManager->BeamOn(numberOfEvent);
    }
  }

  delete runManager;
  runManager=NULL;
  G4cout<<"End of Main!"<<G4endl;
	G4cout<<"== CPU Time : "<<watch.CpuTime()<<G4endl;
	G4cout<<"== RealTime : "<<watch.RealTime()<<G4endl;
  return 0;
}
