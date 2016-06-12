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
#include "TApplication.h"
using namespace std;


const double Mass_C13 = 12109.5;//*MeV
const double Mass_Be9 = 8392.75;//*MeV
const double Mass_He4 = 3727.38;//*MeV
const double Energy_in = 70,0;//*MeV

int main(int argc,char *argv[])
{
  void C2L(double &x,double &y);
  double MaxAngle();
  double maxangle=MaxAngle();
  string filename="El13c9be.data";
  if(argc==1) 
  {
    cout<<"Please give a data file"<<endl;
    cout<<"./fort2hist filename"<<endl;
    return 0;
  }
  if(argc==2) filename=argv[1];
  // TApplication *theApp = new TApplication("app",&argc,argv);
  // TCanvas *can = new TCanvas("c1","hist of CrossSection");
  // TGraph *g = new TGraph();
  TFile *f = new TFile("cs.root","RECREATE");
  if(!f||!f->IsOpen()){cout<<"Error! Failed to Open file!"<<endl;return 0;}
  TH1D *h1 = new TH1D("h1","hist of CrossSection",30,0,30);
  TH1D *h0 = new TH1D("h0","hist of CrossSection",30,0,30);
  //int n=0;
  fstream input(filename.c_str(),ios::in);
  if(!input||!input.is_open()) {cerr<<"Error : file "<<filename<<" not exist!"<<endl;exit(0);}
  string line;
  double x,y;
  while(getline(input,line))
  {
    int i=0;
    char headl=line[i];
    while(isspace(headl)) headl=line[++i];
    if(isdigit(headl)) 
    {
      istringstream linestream(line);
      linestream>>x>>y;
      if(x>=0&&x<20)
      {
        C2L(x,y);
        h1->Fill(x,y);
        h0->Fill(x,y);
      }
      if(x>=20&&x<=maxangle)
      {
        C2L(x,y);
        h1->Fill(x,y);
        h0->Fill(x,y);
      }
      // if(x>=0&&x<maxangle)
      // {
      	// C2L(x,y);
      	// g->SetPoint(n,x,y);
      	// ++n;
      // }
    }
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
void C2L(double &x,double &y)
{
  double pie=TMath::Pi();
  //double c=13.0/9.0;// elastic
  double c=13.0/9.0*sqrt(30./15.);//inelastic
  double xrad=x/180.0*pie;
  double term1=sqrt(1+c*c+2*c*cos(xrad));
  x=acos((c+cos(xrad))/term1)/pie*180.0;
  y=pow(term1,3)/TMath::Abs(1+c*cos(xrad))*y;
}

double MaxAngle(double ex)
{
  double pie=TMath::Pi();
  //double c=13.0/9.0;
  //double c=13.0/9.0*sqrt(30./15.);
  double cosE = Energy_in*Mass_Be9/(Mass_Be9+Mass_C13);
  double c=Mass_C13/Mass_Be9*sqrt(cosE/(cosE-ex));
  return TMath::ACos(-1./c)/pie*180;
}

