// ************************************************************************* 
//	> File Name: Analysis.cc
//	> Author: Feng Jun
//	> Mail: test@test
//	> Created Time: Sat 23 Apr 2016 08:30:20 PM CST
// ************************************************************************* 
#include <iostream>
#include <string>
#include <vector>
#include "stdio.h"
#include "stdlib.h"

#include <TApplication.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TMath.h>
#include <TCutG.h>

#include "JunParticle.hh"
#include "JunDataWriter.hh"
#include "JunTreeReader.hh"
#include "JunDSSDAngle.hh"
#include "JunParMan.hh"
#include "JunLossCorrection.hh"
using namespace std;

//const double epsA = 2./180.*TMath::Pi();

int main(int argc,char** argv)
{
  JunLossCorrection *correction = new JunLossCorrection();
  correction->addDataFile("He_in_Si.txt","HeInSi");
  correction->addDataFile("He_in_Be.txt","HeInBe");
  correction->addDataFile("Be_in_Si.txt","BeInSi");
  correction->addDataFile("Be_in_Be.txt","BeInBe");
  //cout<<elc.correctEnergy(1,20,"HeInSi")<<endl;
  //----------------------------------------
  const double Mass_C13 = 12109.5;//*MeV
  const double Mass_Be9 = 8392.75;//*MeV
  const double Mass_He4 = 3727.38;//*MeV
  //--------------------
  // TApplication *theApp = new TApplication("app",&argc,argv);
  // TCanvas *c = new TCanvas("c","distribution",800,600);
  // TH2D *h = new TH2D("h","distribution",500,0,50,500,0,50);
  //Load the setup & parameter of detectors
  JunParMan::Instance()->ReadParFile("../fj13c_setup.par");
  string teleNameBack[4]={"t1l2","t1r2","t2l2","t2r2"};
  //------------------angle info of dssd------------------
  JunDSSDAngle *jAngle = JunDSSDAngle::Instance();
  //cout<<jAngle->GetTheta("t1l1",1,1)/TMath::Pi()*180<<endl;
  //---------------------load cut---------------------
  TCutG *t1l_Be9,*t1l_alpha,*t2l_Be9,*t2l_alpha,*all_recoil;
  TFile *cf = TFile::Open("cutfile/big_recoil.root");
  cf->GetObject("CUTG",all_recoil);
  cf = TFile::Open("cutfile/l0_he4.root");
  cf->GetObject("CUTG",t1l_alpha);
  cf = TFile::Open("cutfile/l1_be9.root");
  cf->GetObject("CUTG",t2l_Be9);
  cf = TFile::Open("cutfile/l1_he4.root");
  cf->GetObject("CUTG",t2l_alpha);
  cf = TFile::Open("cutfile/l0_be9.root");
  cf->GetObject("CUTG",t1l_Be9);
  //-----------------------in--------------------
  //TString inputfile = "jtree_sample.root";
  //TString inputfile = "../beta/build/jtree.root";
  TString inputfile = "../build/jtree.root";
  JunTreeReader *reader = new JunTreeReader(inputfile);
  Long64_t numOfEntries = reader->GetEntries();
  //------------------------out-------------------------
  TString outputfile = "ptree.root";
  JunDataWriter::Instance()->OpenFile(outputfile);
  //-------------------------------------------------
  cout<<numOfEntries<<endl;
  Int_t fileSize = 0;
  for(Long64_t i=0;i<numOfEntries;++i)
  {
    int numOfEventParticle = 0;
    bool flag_alpha = 0;
    bool flag_breakup = 0;
    bool flag_recoil = 0;
    int num_alpha = 0;
    fileSize+=reader->GetEntry(i);
    for(int it=0;it<4;++it)//for 4 telescope
    {
      int hitNumFront[2],hitNumBack[2];
      int iStripFront[2],iStripBack[2];
      int jStripFront[2],jStripBack[2];
      double energyFront[2],energyBack[2];
      double timeOfFront[2],timeOfBack[2];
      double xBack[2],yBack[2];
      TCutG *He4,*Be9;
      switch(it)
      {
        case 0://t1l
        {
          hitNumFront[0]=reader->t1l1n[0];hitNumBack[0]=reader->t1l2n[0];
          hitNumFront[1]=reader->t1l1n[1];hitNumBack[1]=reader->t1l2n[1];
          iStripFront[0]=reader->t1l1i[0];iStripBack[0]=reader->t1l2i[0];
          iStripFront[1]=reader->t1l1i[1];iStripBack[1]=reader->t1l2i[1];
          jStripFront[0]=reader->t1l1j[0];jStripBack[0]=reader->t1l2j[0];
          jStripFront[1]=reader->t1l1j[1];jStripBack[1]=reader->t1l2j[1];
          energyFront[0]=reader->t1l1e[0];energyBack[0]=reader->t1l2e[0];
          energyFront[1]=reader->t1l1e[1];energyBack[1]=reader->t1l2e[1];
          timeOfFront[0]=reader->t1l1t[0];timeOfBack[0]=reader->t1l2t[0];
          timeOfFront[1]=reader->t1l1t[1];timeOfBack[1]=reader->t1l2t[1];
          He4 = t1l_alpha;
          Be9 = t1l_Be9;
          xBack[0] = reader->t1l2x[0];
          xBack[1] = reader->t1l2x[1];
          yBack[0] = reader->t1l2y[0];
          yBack[1] = reader->t1l2y[1];
          break;
        }
        case 1://t1r
        {
          hitNumFront[0]=reader->t1r1n[0];hitNumBack[0]=reader->t1r2n[0];
          hitNumFront[1]=reader->t1r1n[1];hitNumBack[1]=reader->t1r2n[1];
          iStripFront[0]=reader->t1r1i[0];iStripBack[0]=reader->t1r2i[0];
          iStripFront[1]=reader->t1r1i[1];iStripBack[1]=reader->t1r2i[1];
          jStripFront[0]=reader->t1r1j[0];jStripBack[0]=reader->t1r2j[0];
          jStripFront[1]=reader->t1r1j[1];jStripBack[1]=reader->t1r2j[1];
          energyFront[0]=reader->t1r1e[0];energyBack[0]=reader->t1r2e[0];
          energyFront[1]=reader->t1r1e[1];energyBack[1]=reader->t1r2e[1];
          timeOfFront[0]=reader->t1r1t[0];timeOfBack[0]=reader->t1r2t[0];
          timeOfFront[1]=reader->t1r1t[1];timeOfBack[1]=reader->t1r2t[1];
          He4 = t1l_alpha;
          Be9 = t1l_Be9;
          xBack[0] = reader->t1r2x[0];
          xBack[1] = reader->t1r2x[1];
          yBack[0] = reader->t1r2y[0];
          yBack[1] = reader->t1r2y[1];
          break;
        }
        case 2://t2l
        {
          hitNumFront[0]=reader->t2l1n[0];hitNumBack[0]=reader->t2l2n[0];
          hitNumFront[1]=reader->t2l1n[1];hitNumBack[1]=reader->t2l2n[1];
          iStripFront[0]=reader->t2l1i[0];iStripBack[0]=reader->t2l2i[0];
          iStripFront[1]=reader->t2l1i[1];iStripBack[1]=reader->t2l2i[1];
          jStripFront[0]=reader->t2l1j[0];jStripBack[0]=reader->t2l2j[0];
          jStripFront[1]=reader->t2l1j[1];jStripBack[1]=reader->t2l2j[1];
          energyFront[0]=reader->t2l1e[0];energyBack[0]=reader->t2l2e[0];
          energyFront[1]=reader->t2l1e[1];energyBack[1]=reader->t2l2e[1];
          timeOfFront[0]=reader->t2l1t[0];timeOfBack[0]=reader->t2l2t[0];
          timeOfFront[1]=reader->t2l1t[1];timeOfBack[1]=reader->t2l2t[1];
          He4 = t2l_alpha;
          Be9 = t2l_Be9;
          xBack[0] = reader->t2l2x[0];
          xBack[1] = reader->t2l2x[1];
          yBack[0] = reader->t2l2y[0];
          yBack[1] = reader->t2l2y[1];
          break;
        }
        case 3://t2r
        {
          hitNumFront[0]=reader->t2r1n[0];hitNumBack[0]=reader->t2r2n[0];
          hitNumFront[1]=reader->t2r1n[1];hitNumBack[1]=reader->t2r2n[1];
          iStripFront[0]=reader->t2r1i[0];iStripBack[0]=reader->t2r2i[0];
          iStripFront[1]=reader->t2r1i[1];iStripBack[1]=reader->t2r2i[1];
          jStripFront[0]=reader->t2r1j[0];jStripBack[0]=reader->t2r2j[0];
          jStripFront[1]=reader->t2r1j[1];jStripBack[1]=reader->t2r2j[1];
          energyFront[0]=reader->t2r1e[0];energyBack[0]=reader->t2r2e[0];
          energyFront[1]=reader->t2r1e[1];energyBack[1]=reader->t2r2e[1];
          timeOfFront[0]=reader->t2r1t[0];timeOfBack[0]=reader->t2r2t[0];
          timeOfFront[1]=reader->t2r1t[1];timeOfBack[1]=reader->t2r2t[1];
          He4 = t2l_alpha;
          Be9 = t2l_Be9;
          xBack[0] = reader->t2r2x[0];
          xBack[1] = reader->t2r2x[1];
          yBack[0] = reader->t2r2y[0];
          yBack[1] = reader->t2r2y[1];
          break;
        }
      }
      if(hitNumFront[0]==hitNumBack[0]&&hitNumFront[0]>0)
      {
        for(int hitn=0;hitn<4;hitn++)//2 hits 
        {
          //if(it!=0&&it!=3) break;
          if(hitn==0&&hitNumFront[0]>2) break;
          if(hitn>0&&hitNumFront[0]<2) break;
          if(iStripBack[hitn]<2*iStripFront[hitn]-1) break;
          if(iStripBack[hitn]>2*iStripFront[hitn]+1) break;
          if(jStripBack[hitn]<2*jStripFront[hitn]-1&&it<2) break;
          if(jStripBack[hitn]>2*jStripFront[hitn]+1&&it<2) break;
          double _energy = energyBack[hitn]+energyFront[hitn];
          double _nsTime=timeOfBack[hitn]-timeOfFront[hitn];
          TVector3 _dir(0,0,1);
          _dir.SetTheta(jAngle->GetTheta(teleNameBack[it],iStripBack[hitn],jStripBack[hitn]));
          _dir.SetPhi(jAngle->GetPhi(teleNameBack[it],iStripBack[hitn],jStripBack[hitn]));
          // _dir.SetTheta(jAngle->RealTheta(teleNameBack[it],xBack[hitn],yBack[hitn]));
          // _dir.SetPhi(jAngle->RealPhi(teleNameBack[it],xBack[hitn],yBack[hitn]));
          //cout<<jAngle->Check(teleNameBack[it],iStripBack[hitn],jStripBack[hitn],xBack[hitn],yBack[hitn])<<endl;
          JunParticle thisParticle;
          if(He4->IsInside(energyBack[hitn],energyFront[hitn]))
          {
            _energy = correction->correctEnergy(1,energyBack[hitn],"HeInSi");
            _energy = correction->correctEnergy(1,_energy+energyFront[hitn],"HeInSi");
            double angle0 = TVector3(0,0,1).Angle(_dir);
            double rangeInTarget = 1./TMath::Cos(angle0);
            _energy = correction->correctEnergy(rangeInTarget,_energy,"HeInBe");
            //cout<<_energy-energyBack[hitn]-energyFront[hitn]<<endl;
            thisParticle.SetParticle("alpha",_energy,_dir);
            numOfEventParticle++;
            flag_alpha=1;
            num_alpha++;
            JunDataWriter::Instance()->alpha = thisParticle;
          }
          if(Be9->IsInside(energyBack[hitn],energyFront[hitn]))
          {
            _energy = correction->correctEnergy(1,energyBack[hitn],"BeInSi");
            _energy = correction->correctEnergy(1,_energy+energyFront[hitn],"BeInSi");
            double angle0 = TVector3(0,0,1).Angle(_dir);
            double rangeInTarget = 1./TMath::Cos(angle0);
            _energy = correction->correctEnergy(rangeInTarget,_energy,"BeInBe");
            //cout<<_energy-energyBack[hitn]-energyFront[hitn]<<endl;
            if(all_recoil->IsInside(_dir.Theta()/TMath::Pi()*180,_energy))
            {
              thisParticle.SetParticle("recoil",_energy,_dir);
              numOfEventParticle++;
              flag_recoil=1;
              JunDataWriter::Instance()->recoil = thisParticle;
              //cout<<"1"<<endl;
            }
            else
            {
              thisParticle.SetParticle("breakup",_energy,_dir);
              numOfEventParticle++;
              flag_breakup=1;
              JunDataWriter::Instance()->breakup = thisParticle;
            }
          }
          //JunDataWriter::Instance()->vParticle.push_back(thisParticle);
        }
      }
    }
    //============================================================
    JunDataWriter::Instance()->pNum = numOfEventParticle;
    JunDataWriter::Instance()->aNum = num_alpha;
    //-------------------------------------------
    if(flag_alpha&&flag_breakup)
    {
      JunParticle InMa;
      double energy1 = JunDataWriter::Instance()->alpha.energy;
      double energy2 = JunDataWriter::Instance()->breakup.energy;
      TVector3 dir1  = TMath::Sqrt(2*Mass_He4*energy1)*JunDataWriter::Instance()->alpha.direction;
      TVector3 dir2  = TMath::Sqrt(2*Mass_Be9*energy2)*JunDataWriter::Instance()->breakup.direction;
      TVector3 dir_recon = dir1+dir2;
      double energy_recon = energy1+energy2-dir_recon*dir_recon/Mass_C13/2.;
      InMa.SetParticle("im",energy_recon,dir_recon);
      JunDataWriter::Instance()->im = InMa;
    }
    //--------------------------------------------
    if(flag_recoil)
    {
      JunParticle MiMa;
			double beamEnergy = 69.54;//*MeV;or 69.54 0r 70
      double energyR = JunDataWriter::Instance()->recoil.energy;
      TVector3 dirR = TMath::Sqrt(2*Mass_Be9*energyR)*JunDataWriter::Instance()->recoil.direction;
      TVector3 dir0(0,0,1);
      dir0 = TMath::Sqrt(2*Mass_C13*beamEnergy)*dir0;
      TVector3 dir_recon = dir0-dirR;
      double energy_recon = beamEnergy-energyR-dir_recon*dir_recon/Mass_C13/2.;
      MiMa.SetParticle("mm",energy_recon,dir_recon);
      JunDataWriter::Instance()->mm = MiMa;
    }
    //--------------mix----
    if(flag_alpha&&flag_recoil)
    {
      JunParticle Mix;
      double energy1 = JunDataWriter::Instance()->alpha.energy;
      double energy2 = JunDataWriter::Instance()->recoil.energy;
      TVector3 dir1  = TMath::Sqrt(2*Mass_He4*energy1)*JunDataWriter::Instance()->alpha.direction;
      TVector3 dir2  = TMath::Sqrt(2*Mass_Be9*energy2)*JunDataWriter::Instance()->recoil.direction;
      TVector3 dir_recon = dir1+dir2;
      double energy_recon = energy1+energy2-dir_recon*dir_recon/Mass_C13/2.;
      Mix.SetParticle("mix",energy_recon,dir_recon);
      JunDataWriter::Instance()->mix = Mix;
    }
    //---------------------------------
    if(numOfEventParticle>0) JunDataWriter::Instance()->Fill();
  }
  JunDataWriter::Instance()->Record();
  cout<<"Read the size : "<<fileSize<<endl;

  // for(int i=0;i<32;i++)
    // for(int j=0;j<32;j++)
      // h->Fill(jAngle->GetTheta("t1r2",i,j)/TMath::Pi()*180,jAngle->GetPhi("t1r2",i,j)/TMath::Pi()*180);
  // c->cd();
  // h->Draw("colz");
  // theApp->Run();
  return 0;
}
