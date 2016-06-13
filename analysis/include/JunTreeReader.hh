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
  Double_t        t1l1e[3];
  Double_t        t1l1t[3];
  Double_t        t1l1x[3];
  Double_t        t1l1y[3];
  Double_t        t1l1i[3];
  Double_t        t1l1j[3];
  Double_t        t1l1n[3];
  Double_t        t1l2e[3];
  Double_t        t1l2t[3];
  Double_t        t1l2x[3];
  Double_t        t1l2y[3];
  Double_t        t1l2i[3];
  Double_t        t1l2j[3];
  Double_t        t1l2n[3];
  Double_t        t2l1e[3];
  Double_t        t2l1t[3];
  Double_t        t2l1x[3];
  Double_t        t2l1y[3];
  Double_t        t2l1i[3];
  Double_t        t2l1j[3];
  Double_t        t2l1n[3];
  Double_t        t2l2e[3];
  Double_t        t2l2t[3];
  Double_t        t2l2x[3];
  Double_t        t2l2y[3];
  Double_t        t2l2i[3];
  Double_t        t2l2j[3];
  Double_t        t2l2n[3];
  Double_t        t1r1e[3];
  Double_t        t1r1t[3];
  Double_t        t1r1x[3];
  Double_t        t1r1y[3];
  Double_t        t1r1i[3];
  Double_t        t1r1j[3];
  Double_t        t1r1n[3];
  Double_t        t1r2e[3];
  Double_t        t1r2t[3];
  Double_t        t1r2x[3];
  Double_t        t1r2y[3];
  Double_t        t1r2i[3];
  Double_t        t1r2j[3];
  Double_t        t1r2n[3];
  Double_t        t2r1e[3];
  Double_t        t2r1t[3];
  Double_t        t2r1x[3];
  Double_t        t2r1y[3];
  Double_t        t2r1i[3];
  Double_t        t2r1j[3];
  Double_t        t2r1n[3];
  Double_t        t2r2e[3];
  Double_t        t2r2t[3];
  Double_t        t2r2x[3];
  Double_t        t2r2y[3];
  Double_t        t2r2i[3];
  Double_t        t2r2j[3];
  Double_t        t2r2n[3];
  
  // List of branches
  TBranch        *b_t1l1e;   //!
  TBranch        *b_t1l1t;   //!
  TBranch        *b_t1l1x;   //!
  TBranch        *b_t1l1y;   //!
  TBranch        *b_t1l1i;   //!
  TBranch        *b_t1l1j;   //!
  TBranch        *b_t1l1n;   //!
  TBranch        *b_t1l2e;   //!
  TBranch        *b_t1l2t;   //!
  TBranch        *b_t1l2x;   //!
  TBranch        *b_t1l2y;   //!
  TBranch        *b_t1l2i;   //!
  TBranch        *b_t1l2j;   //!
  TBranch        *b_t1l2n;   //!
  TBranch        *b_t2l1e;   //!
  TBranch        *b_t2l1t;   //!
  TBranch        *b_t2l1x;   //!
  TBranch        *b_t2l1y;   //!
  TBranch        *b_t2l1i;   //!
  TBranch        *b_t2l1j;   //!
  TBranch        *b_t2l1n;   //!
  TBranch        *b_t2l2e;   //!
  TBranch        *b_t2l2t;   //!
  TBranch        *b_t2l2x;   //!
  TBranch        *b_t2l2y;   //!
  TBranch        *b_t2l2i;   //!
  TBranch        *b_t2l2j;   //!
  TBranch        *b_t2l2n;   //!
  TBranch        *b_t1r1e;   //!
  TBranch        *b_t1r1t;   //!
  TBranch        *b_t1r1x;   //!
  TBranch        *b_t1r1y;   //!
  TBranch        *b_t1r1i;   //!
  TBranch        *b_t1r1j;   //!
  TBranch        *b_t1r1n;   //!
  TBranch        *b_t1r2e;   //!
  TBranch        *b_t1r2t;   //!
  TBranch        *b_t1r2x;   //!
  TBranch        *b_t1r2y;   //!
  TBranch        *b_t1r2i;   //!
  TBranch        *b_t1r2j;   //!
  TBranch        *b_t1r2n;   //!
  TBranch        *b_t2r1e;   //!
  TBranch        *b_t2r1t;   //!
  TBranch        *b_t2r1x;   //!
  TBranch        *b_t2r1y;   //!
  TBranch        *b_t2r1i;   //!
  TBranch        *b_t2r1j;   //!
  TBranch        *b_t2r1n;   //!
  TBranch        *b_t2r2e;   //!
  TBranch        *b_t2r2t;   //!
  TBranch        *b_t2r2x;   //!
  TBranch        *b_t2r2y;   //!
  TBranch        *b_t2r2i;   //!
  TBranch        *b_t2r2j;   //!
  TBranch        *b_t2r2n;   //!

  JunTreeReader(TString filename);
  virtual ~JunTreeReader();
  Long64_t  GetEntries();
  Int_t     GetEntry(Long64_t entry);
  void      Init();
  
private:
  TFile          *inputFile;
};

#endif