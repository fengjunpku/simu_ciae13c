#ifndef myTTreeRecorder_h
#define myTTreeRecorder_h 1

#include "globals.hh"
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include "G4ios.hh"
#include <iomanip>
#include "JunParMan.hh"
#include "stdio.h"
using namespace std;
//instance->openfile->gettree->recorde
class myTTreeRecorder
{
private:
	myTTreeRecorder();
public:
	virtual ~myTTreeRecorder();
	static myTTreeRecorder* Instance();
	void Record();
	void OpenFile(const G4String filename);
  void Fill();
	
private:
	TTree *ptree;
	TFile *pfile;
	static myTTreeRecorder* theRecorder;
public:
	double **var;
};
#endif
