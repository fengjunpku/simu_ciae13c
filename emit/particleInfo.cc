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
#include <vector>

#include "JunParticle.hh"
#include "JunDataWriter.hh"
#include "JunTreeReader.hh"
using namespace std;

int main(int argc,char** argv)
{
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
    JunDataWriter::Instance()->Fill();
  }
  JunDataWriter::Instance()->Record();
  cout<<"Read the size : "<<fileSize<<endl;
  delete reader;
  delete JunDataWriter::Instance();
}
