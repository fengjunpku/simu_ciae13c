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
  int type[3];
  vector<string> name;
  double energy[3];
  double px[3];
  double py[3];
  double pz[3];
};
#endif
