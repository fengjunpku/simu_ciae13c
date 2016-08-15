//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr 28 16:26:28 2016 by ROOT version 5.34/34
// from TTree etree/etree
// found on file: etree.root
//////////////////////////////////////////////////////////
// function :
//   JunTreeReader *reader = new JunTreeReader("test.root");
//   reader->GetEntries();
//      reader->GetEntry(int entry);
//
#ifndef JunTreeReader_hh
#define JunTreeReader_hh

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <iostream>
using namespace std;
// Fixed size dimensions of array or collections stored in the TTree if any.

class JunTreeReader {
public :
  TTree          *ptree;   //!pointer to the analyzed TTree or TChain

  // Declaration of leaf types
  Int_t           type[3];
  vector<string>  *name;
  Double_t        energy[3];
  Double_t        px[3];
  Double_t        py[3];
  Double_t        pz[3];

  // List of branches
  TBranch        *b_type;   //!
  TBranch        *b_name;   //!
  TBranch        *b_energy;   //!
  TBranch        *b_px;   //!
  TBranch        *b_py;   //!
  TBranch        *b_pz;   //!

  JunTreeReader(TString filename);
  virtual ~JunTreeReader();
  Long64_t  GetEntries();
  Int_t     GetEntry(Long64_t entry);
  void      Init();
  
private:
  TFile          *inputFile;
};

#endif