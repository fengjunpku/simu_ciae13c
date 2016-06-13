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
  inputFile->GetObject("jtree",ptree);//"name of tree,pointer of tree"
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
   // Set branch addresses and branch pointers
   if (!ptree) return;
   // set make class status
   ptree->SetMakeClass(1);

  ptree->SetBranchAddress("t1l1e", t1l1e, &b_t1l1e);
  ptree->SetBranchAddress("t1l1t", t1l1t, &b_t1l1t);
  ptree->SetBranchAddress("t1l1x", t1l1x, &b_t1l1x);
  ptree->SetBranchAddress("t1l1y", t1l1y, &b_t1l1y);
  ptree->SetBranchAddress("t1l1i", t1l1i, &b_t1l1i);
  ptree->SetBranchAddress("t1l1j", t1l1j, &b_t1l1j);
  ptree->SetBranchAddress("t1l1n", t1l1n, &b_t1l1n);
  ptree->SetBranchAddress("t1l2e", t1l2e, &b_t1l2e);
  ptree->SetBranchAddress("t1l2t", t1l2t, &b_t1l2t);
  ptree->SetBranchAddress("t1l2x", t1l2x, &b_t1l2x);
  ptree->SetBranchAddress("t1l2y", t1l2y, &b_t1l2y);
  ptree->SetBranchAddress("t1l2i", t1l2i, &b_t1l2i);
  ptree->SetBranchAddress("t1l2j", t1l2j, &b_t1l2j);
  ptree->SetBranchAddress("t1l2n", t1l2n, &b_t1l2n);
  ptree->SetBranchAddress("t2l1e", t2l1e, &b_t2l1e);
  ptree->SetBranchAddress("t2l1t", t2l1t, &b_t2l1t);
  ptree->SetBranchAddress("t2l1x", t2l1x, &b_t2l1x);
  ptree->SetBranchAddress("t2l1y", t2l1y, &b_t2l1y);
  ptree->SetBranchAddress("t2l1i", t2l1i, &b_t2l1i);
  ptree->SetBranchAddress("t2l1j", t2l1j, &b_t2l1j);
  ptree->SetBranchAddress("t2l1n", t2l1n, &b_t2l1n);
  ptree->SetBranchAddress("t2l2e", t2l2e, &b_t2l2e);
  ptree->SetBranchAddress("t2l2t", t2l2t, &b_t2l2t);
  ptree->SetBranchAddress("t2l2x", t2l2x, &b_t2l2x);
  ptree->SetBranchAddress("t2l2y", t2l2y, &b_t2l2y);
  ptree->SetBranchAddress("t2l2i", t2l2i, &b_t2l2i);
  ptree->SetBranchAddress("t2l2j", t2l2j, &b_t2l2j);
  ptree->SetBranchAddress("t2l2n", t2l2n, &b_t2l2n);
  ptree->SetBranchAddress("t1r1e", t1r1e, &b_t1r1e);
  ptree->SetBranchAddress("t1r1t", t1r1t, &b_t1r1t);
  ptree->SetBranchAddress("t1r1x", t1r1x, &b_t1r1x);
  ptree->SetBranchAddress("t1r1y", t1r1y, &b_t1r1y);
  ptree->SetBranchAddress("t1r1i", t1r1i, &b_t1r1i);
  ptree->SetBranchAddress("t1r1j", t1r1j, &b_t1r1j);
  ptree->SetBranchAddress("t1r1n", t1r1n, &b_t1r1n);
  ptree->SetBranchAddress("t1r2e", t1r2e, &b_t1r2e);
  ptree->SetBranchAddress("t1r2t", t1r2t, &b_t1r2t);
  ptree->SetBranchAddress("t1r2x", t1r2x, &b_t1r2x);
  ptree->SetBranchAddress("t1r2y", t1r2y, &b_t1r2y);
  ptree->SetBranchAddress("t1r2i", t1r2i, &b_t1r2i);
  ptree->SetBranchAddress("t1r2j", t1r2j, &b_t1r2j);
  ptree->SetBranchAddress("t1r2n", t1r2n, &b_t1r2n);
  ptree->SetBranchAddress("t2r1e", t2r1e, &b_t2r1e);
  ptree->SetBranchAddress("t2r1t", t2r1t, &b_t2r1t);
  ptree->SetBranchAddress("t2r1x", t2r1x, &b_t2r1x);
  ptree->SetBranchAddress("t2r1y", t2r1y, &b_t2r1y);
  ptree->SetBranchAddress("t2r1i", t2r1i, &b_t2r1i);
  ptree->SetBranchAddress("t2r1j", t2r1j, &b_t2r1j);
  ptree->SetBranchAddress("t2r1n", t2r1n, &b_t2r1n);
  ptree->SetBranchAddress("t2r2e", t2r2e, &b_t2r2e);
  ptree->SetBranchAddress("t2r2t", t2r2t, &b_t2r2t);
  ptree->SetBranchAddress("t2r2x", t2r2x, &b_t2r2x);
  ptree->SetBranchAddress("t2r2y", t2r2y, &b_t2r2y);
  ptree->SetBranchAddress("t2r2i", t2r2i, &b_t2r2i);
  ptree->SetBranchAddress("t2r2j", t2r2j, &b_t2r2j);
  ptree->SetBranchAddress("t2r2n", t2r2n, &b_t2r2n);
}