#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cctype>
#include <sstream>
#include "TROOT.h"
#include "TGraph.h"
#include "TMath.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TApplication.h"
using namespace std;


const double Mass_C13 = 12109.5;//*MeV
const double Mass_Be9 = 8392.75;//*MeV
const double Mass_He4 = 3727.38;//*MeV
const double Energy_in = 70.0;//*MeV
const double pie=TMath::Pi();

int main(int argc,char *argv[])
{
  void C2L(double &x,double &y,double ex);
  double MaxAngle(double ex);
  double maxangle_lab,tmp;
  double exEnergy;
  TRandom3 r(0);
  //-----------------
  if(argc==1) exEnergy=0;
  if(argc==2) exEnergy=atof(argv[1]);
  char rootfile[36];
  sprintf(rootfile,"cs_%.2f.root",exEnergy);
  TFile *f = new TFile(rootfile,"RECREATE");
  if(!f||!f->IsOpen()){cout<<"Error! Failed to Open file!"<<endl;return 0;}
  //-----------
  maxangle_lab = MaxAngle(exEnergy);
  tmp = 1;
  C2L(maxangle_lab,tmp,exEnergy);
  int bins = (int)maxangle_lab+1;
  TH1D *h1 = new TH1D("h1","hist of CrossSection",bins*10,0-0.5,bins+0.5);
  for(int i=0;i<1000000;i++)
  {
    
    h1->Fill(r.Uniform(0,maxangle_lab));
  }
  f->cd();
  h1->Write();
  f->Close();
  // can->cd();
  // gPad->SetLogy();
  // gPad->SetGrid();
  // gPad->SetTicks();
  // g->Draw();
  // h0->SetLineColor(2);
  // h0->Draw();
  // h1->Draw("Same");
  // theApp->Run();
  return 0;
}
void C2L(double &x,double &y,double ex)
{
  double cosE = Energy_in*Mass_Be9/(Mass_Be9+Mass_C13);
  double c=Mass_C13/Mass_Be9*sqrt(cosE/(cosE-ex));
  double xrad=x/180.0*pie;
  double term1=sqrt(1+c*c+2*c*cos(xrad));
  x=acos((c+cos(xrad))/term1)/pie*180.0;
  y=pow(term1,3)/TMath::Abs(1+c*cos(xrad))*y;
}

double MaxAngle(double ex)
{
  double cosE = Energy_in*Mass_Be9/(Mass_Be9+Mass_C13);
  double c=Mass_C13/Mass_Be9*sqrt(cosE/(cosE-ex));
  return TMath::ACos(-1./c)/pie*180;
}

