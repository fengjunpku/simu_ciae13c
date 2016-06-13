#ifndef JunDataWriter_HH
#define JunDataWriter_HH

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <iomanip>
#include <vector>
#include "stdio.h"

#include "JunParticle.hh"

using namespace std;
//instance->openfile->gettree->recorde
class JunDataWriter
{
private:
  JunDataWriter();
public:
  virtual ~JunDataWriter();
  static JunDataWriter* Instance();
  void Fill();
  void Record();
  void OpenFile(const TString filename);
  
private:
  TTree *otree;
  TFile *ofile;
  static JunDataWriter* theWriter;
public:
  //vector<JunParticle> vParticle;
  int pNum;
  JunParticle alpha;
  JunParticle breakup;
  JunParticle recoil;
  JunParticle im;
  JunParticle mm;
};
#endif