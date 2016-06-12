// ************************************************************************* 
//	> File Name: test.cc
//	> Author: Feng Jun
//	> Mail: test@test
//	> Created Time: Sat 30 Apr 2016 01:21:09 PM CST
// *************************************************************************
const double Mass_C13 = 12109.5;//*MeV
const double Mass_Be9 = 8392.75;//*MeV
const double Mass_He4 = 3727.38;//*MeV
const double Energy_in = 70,0;//*MeV

void test()
{
  TCanvas *c = new TCanvas();
  gPad->SetLogy();
  TFile *in_file = TFile::Open("cs.root");
  TH1D *h = (TH1D*)in_file->GetObjectChecked("h1","TH1D");
  TH1D *ha = new TH1D("ha","random",120,0,30);
  TH1D *hb = new TH1D("hb","random",120,0,30);
  double critical = MaxAngle();
  Double_t angle=0;
  for(int i=0;i<10000000;i++)
  {
    angle=h->GetRandom();
    ha->Fill(angle);
    //if(angle<critical) ha->Fill(angle);
    //else hb->Fill(angle);
  }
  ha->Draw();
  //hb->SetLineColor(2);
  //hb->Draw("Same");
}

double C2L(double angle)
{
  double pie=TMath::Pi();
  //double c=13.0/9.0;// elastic
  double c=13.0/9.0*sqrt(30./15.);//inelastic
  double xrad=angle/180.0*pie;
  double term1=sqrt(1+c*c+2*c*cos(xrad));
  return acos((c+cos(xrad))/term1)/pie*180.0;
}

double MaxAngle()
{
  double pie=TMath::Pi();
  double cosE = Energy_in*Mass_Be9/(Mass_Be9+Mass_C13);
  double c=Mass_C13/Mass_Be9*sqrt(cosE/(cosE-ex));
  return TMath::ACos(-1./c)/pie*180;
}
