#define JunTreeReader_cxx
#include "JunTreeReader.hh"

JunTreeReader::JunTreeReader(TString filename)
{
  inputFile = TFile::Open(filename);
  if(!inputFile||!inputFile->IsOpen())
  {
    cout<<"\033[35;1m # Miao \033[0m : Can not open \033[33m\'"<<filename<<"\033[0m\' !"<<endl;
    exit(0);
  }
  inputFile->GetObject("etree",ptree);
  Init();
}

JunTreeReader::~JunTreeReader()
{
  inputFile->Close();
  delete inputFile;
  printf("End of class JunTreeReader\n");
}

Int_t JunTreeReader::GetEntry(Long64_t entry)
{
  inputFile->cd();
  if (!ptree) return 0;
  return ptree->GetEntry(entry);
}

Long64_t JunTreeReader::GetEntries()
{
   inputFile->cd();
   if (!ptree) return 0;
   return ptree->GetEntriesFast();
}

void JunTreeReader::Init()
{
   // Set object pointer
   name = 0;
   // Set branch addresses and branch pointers
   if (!ptree) return;
   // set make class status
   ptree->SetMakeClass(1);

   ptree->SetBranchAddress("type", type, &b_type);
   ptree->SetBranchAddress("name", &name, &b_name);
   ptree->SetBranchAddress("energy", energy, &b_energy);
   ptree->SetBranchAddress("px", px, &b_px);
   ptree->SetBranchAddress("py", py, &b_py);
   ptree->SetBranchAddress("pz", pz, &b_pz);
}