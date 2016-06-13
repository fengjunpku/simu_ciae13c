// ************************************************************************* 
//	> File Name: Analysis.cc
//	> Author: Feng Jun
//	> Mail: test@test
//	> Created Time: Sat 23 Apr 2016 08:30:20 PM CST
// ************************************************************************* 
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"

#include <TString.h>
#include <vector>
#include <TApplication.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TMath.h>

using namespace std;


int main(int argc,char** argv)
{
  TApplication *theApp = new TApplication("app",&argc,argv);
  TCanvas *c = new TCanvas("c","distribution of angle",800,600);
  //TH2D *h = new TH2D("h","distribution of angle",160,0,80,720,-180,180);
  gROOT->SetMacroPath("/home/fengjun/share/analysis/testCut/");
  gROOT->ProcessLine(".x 9Be_t1l.cc");
  TFile *_file0 = TFile::Open("jtree_sample.root");
  gROOT->ProcessLine("jtree->Draw(\"t1l1e:t1l2e\",\"Be9_t1l\",\"colz\")");
  c->cd();
  //h->Draw("colz");
  theApp->Run();
  return 0;
}
