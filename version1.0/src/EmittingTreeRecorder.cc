#include "EmittingTreeRecorder.hh"

EmittingTreeRecorder* EmittingTreeRecorder::theRecorder=NULL;

EmittingTreeRecorder::EmittingTreeRecorder()
{
  //----------------------
  //ptree->Branch("deltaE",&deltaE,"deltaE/D");
}

EmittingTreeRecorder::~EmittingTreeRecorder()
{
  //delete ptree;
  cout<<"End of EmittingTreeRecorder!"<<endl;
}

////////////////////////////////////
void EmittingTreeRecorder::OpenFile(const TString filename)
{
  pfile = new TFile(filename,"RECREATE");
  //ptree = new TTree("tree","tree");
  ptree = new TTree("etree","etree");
  ptree->Branch("type",type,"type[3]/I");
  ptree->Branch("name",&name,32000,1);
  //ptree->Branch("vec",&vec,32000,1);
  ptree->Branch("energy",energy,"energy[3]/D");
  ptree->Branch("px",px,"px[3]/D");
  ptree->Branch("py",py,"py[3]/D");
  ptree->Branch("pz",pz,"pz[3]/D");
}
//////////////////////////
EmittingTreeRecorder* EmittingTreeRecorder::Instance()
{
  if(theRecorder==NULL)
    theRecorder = new EmittingTreeRecorder();
  return theRecorder;
}
/////////////////////////
void EmittingTreeRecorder::Fill()
{
  pfile->cd();
  ptree->Fill();
  name.clear();
  vector<string>().swap(name);
}
//
void EmittingTreeRecorder::Record()
{
  pfile->cd();
  ptree->Write();
  pfile->Close();
}
