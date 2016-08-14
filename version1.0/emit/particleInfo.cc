// ************************************************************************* 
//  > File Name: particleInfo.cc
//  > Author: Feng Jun
//  > Mail: test@test
//  > Created Time: Wed 27 Apr 2016 07:03:50 PM CST
// ************************************************************************* 
#include <iostream>
#include <string>
#include "stdio.h"
#include "stdlib.h"

#include <TString.h>
#include <TRandom3.h>
#include <vector>

#include "JunParticle.hh"
#include "JunDataWriter.hh"
#include "JunTreeReader.hh"
using namespace std;

int main(int argc,char** argv)
{
  const double Mass_C13 = 12109.5;//*MeV
  const double Mass_Be9 = 8392.75;//*MeV
  const double Mass_He4 = 3727.38;//*MeV
  TRandom3 r(0);
  //-----------------
  TString inputfile = "../build/etree.root";
  JunTreeReader *reader = new JunTreeReader(inputfile);
  Long64_t numOfEntries = reader->GetEntries();
  
  TString outputfile = "otree.root";
  JunDataWriter::Instance()->OpenFile(outputfile);
  
  Int_t fileSize = 0;
  for(Long64_t i=0;i<numOfEntries;++i)
  {
    fileSize+=reader->GetEntry(i);
    for(int n=0;n<3;++n)
    {
      JunParticle thisParticle;
      thisParticle.SetParticle((*reader->name)[n],
                               reader->energy[n],
                               reader->px[n],
                               reader->py[n],
                               reader->pz[n]);
      //cout<<" "<<thisParticle.name<<endl;
      JunDataWriter::Instance()->vParticle.push_back(thisParticle);
      //cout<<JunDataWriter::Instance()->vParticle[n].name<<endl;
    }
    JunParticle C13;
    Double_t e_C13 = reader->energy[0]+reader->energy[1];
    Double_t x_C13 = 4*reader->px[0]+9*reader->px[1];
    Double_t y_C13 = 4*reader->py[0]+9*reader->py[1];
    Double_t z_C13 = 4*reader->pz[0]+9*reader->pz[1];
    C13.SetParticle("13C",e_C13,x_C13,y_C13,z_C13);
    JunDataWriter::Instance()->vParticle.push_back(C13);
    //---------
    JunParticle im;
    Double_t im_e1 = reader->energy[0]+0.1;
    Double_t im_e2 = reader->energy[1]+0.5;
    TVector3 im_dir1(reader->px[0],reader->py[0],reader->pz[0]);
    im_dir1 = TMath::Sqrt(2*Mass_He4*im_e1)*im_dir1.Unit();
    TVector3 im_dir2(reader->px[1],reader->py[1],reader->pz[1]);
    im_dir2 = TMath::Sqrt(2*Mass_Be9*im_e2)*im_dir2.Unit();
    TVector3 dir_recon = im_dir1+im_dir2;
    double energy_recon = im_e1+im_e2-dir_recon*dir_recon/Mass_C13/2.+r.Gaus(0,0.1);
    im.SetParticle("im",energy_recon,dir_recon.X(),dir_recon.Y(),dir_recon.Z());
    JunDataWriter::Instance()->vParticle.push_back(im);
    //-------------mix
    JunParticle mix;
    Double_t mix_e1 = reader->energy[0]+0.1;
    Double_t mix_e2 = reader->energy[2]+0.5;
    TVector3 mix_dir1(reader->px[0],reader->py[0],reader->pz[0]);
    mix_dir1 = TMath::Sqrt(2*Mass_He4*mix_e1)*mix_dir1.Unit();
    TVector3 mix_dir2(reader->px[2],reader->py[2],reader->pz[2]);
    mix_dir2 = TMath::Sqrt(2*Mass_Be9*mix_e2)*mix_dir2.Unit();
    TVector3 dir_recon_mix = mix_dir1+mix_dir2;
    double energy_recon_mix = mix_e1+mix_e2-dir_recon_mix*dir_recon_mix/Mass_C13/2.+r.Gaus(0,0.1);
    mix.SetParticle("mix",energy_recon_mix,dir_recon_mix.X(),dir_recon_mix.Y(),dir_recon_mix.Z());
    JunDataWriter::Instance()->vParticle.push_back(mix);
    //---------------
    JunDataWriter::Instance()->Fill();
  }
  JunDataWriter::Instance()->Record();
  cout<<"Read the size : "<<fileSize<<endl;
  delete reader;
  delete JunDataWriter::Instance();
}
