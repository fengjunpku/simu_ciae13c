#include "myTTreeRecorder.hh"

myTTreeRecorder* myTTreeRecorder::theRecorder=NULL;

myTTreeRecorder::myTTreeRecorder()
{
	//----------------------
	//ptree->Branch("deltaE",&deltaE,"deltaE/D");
}

myTTreeRecorder::~myTTreeRecorder()
{
  delete[] var;
  //delete ptree;
  cout<<"End of myTTreeRecord!"<<endl;
}
//////////////////
void myTTreeRecorder::Fill()
{
  pfile->cd();
  ptree->Fill();
}
////////////////////////////////////
void myTTreeRecorder::OpenFile(const G4String filename)
{
  pfile = new TFile(filename,"RECREATE");
  //ptree = new TTree("tree","tree");
  JunParMan *jParManager = JunParMan::Instance();
  vector<string> dssdNames = jParManager->GetAllDSSDName();
  G4int dssdNums = dssdNames.size();
  G4int maxParticles = jParManager->GetPar("Max_Num_Particle");
  var = new double*[dssdNums*7];//7 vars: E T x y vs(i) hs(j) n
  for(int line=0;line<dssdNums*7;++line)
    var[line] = new double[maxParticles];
  //------------------------
  ptree = new TTree("jtree","jtree");
  TString datatype[7]={"e","t","x","y","i","j","n"};
  for(int i=0;i<dssdNums;++i)
  {
    for(int j=0;j<7;++j)
    {
      TString branchname = dssdNames[i]+datatype[j];
      char _rbuff[20];
      sprintf(_rbuff,"[%d]/D",maxParticles);
      TString leaf=branchname+_rbuff;
      ptree->Branch(branchname,var[7*i+j],leaf);
    }
  }
}
//////////////////////////
myTTreeRecorder* myTTreeRecorder::Instance()
{
	if(theRecorder==NULL)
		theRecorder = new myTTreeRecorder();
	return theRecorder;
}
/////////////////////////
void myTTreeRecorder::Record()
{
	pfile->cd();
	ptree->Write();
	pfile->Close();
}
