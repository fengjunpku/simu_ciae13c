#include "JunDataWriter.hh"

JunDataWriter* JunDataWriter::theWriter = NULL;

JunDataWriter::JunDataWriter()
{}

JunDataWriter::~JunDataWriter()
{
  delete ofile;
  //delete otree;//may cause problem
  printf("End of class JunDataWriter\n");
}

////////////////////////////////////
void JunDataWriter::OpenFile(const TString filename)
{
  ofile = new TFile(filename,"RECREATE");
  otree = new TTree("ptree","ptree");
  //otree->Branch("particle",&vParticle,32000,3);
  otree->Branch("pNum",&pNum,"pNum/I");
  otree->Branch("aNum",&aNum,"aNum/I");
  otree->Branch("alpha",&alpha,32000,3);
  otree->Branch("breakup",&breakup,32000,3);
  otree->Branch("recoil",&recoil,32000,3);
  otree->Branch("im",&im,32000,3);
  otree->Branch("mm",&mm,32000,3);
  otree->Branch("mix",&mix,32000,3);
}
//////////////////////////
JunDataWriter* JunDataWriter::Instance()
{
  if(theWriter==NULL)
    theWriter = new JunDataWriter();
  return theWriter;
}
/////////////////////////
void JunDataWriter::Record()
{
  ofile->cd();
  otree->Write();
  ofile->Close();
}

void JunDataWriter::Fill()
{
  ofile->cd();
  otree->Fill();
  // vParticle.clear();
  // vector<JunParticle>().swap(vParticle);
}