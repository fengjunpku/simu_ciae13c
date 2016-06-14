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
  otree = new TTree("otree","otree");
  otree->Branch("particle",&vParticle,32000,3);
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
  vParticle.clear();
  vector<JunParticle>().swap(vParticle);
}