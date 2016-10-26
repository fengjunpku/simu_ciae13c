#ifndef EmittingTreeRecorder_h
#define EmittingTreeRecorder_h 1

#include "globals.hh"
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TVector3.h>
#include "G4ios.hh"
#include <iomanip>
#include <vector>
#include "stdio.h"

using namespace std;
//instance->openfile->gettree->recorde
class EmittingTreeRecorder
{
private:
  EmittingTreeRecorder();
public:
  virtual ~EmittingTreeRecorder();
  static EmittingTreeRecorder* Instance();
  void Record();
  void OpenFile(const TString filename);
  void Fill();
  
private:
  TTree *ptree;
  TFile *pfile;
  static EmittingTreeRecorder* theRecorder;
public:
  int type[5];
  vector<string> name;
  double energy[5];
  double px[5];
  double py[5];
  double pz[5];
  double th[5];
  double ph[5];
};
#endif
