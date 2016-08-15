{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Wed Apr 20 20:31:48 2016 by ROOT version5.34/34)
//   from TTree jtree/jtree
//   found on file: jtree.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../build/jtree.root");
   if (!f) {
      f = new TFile("../../build/jtree.root");
   }
    f->GetObject("jtree",jtree);

//Declaration of leaves types
   Double_t        t1l1e[3];
   Double_t        t1l1t[3];
   Double_t        t1l1x[3];
   Double_t        t1l1y[3];
   Double_t        t1l1i[3];
   Double_t        t1l1j[3];
   Double_t        t1l1n[3];
   Double_t        t1l2e[3];
   Double_t        t1l2t[3];
   Double_t        t1l2x[3];
   Double_t        t1l2y[3];
   Double_t        t1l2i[3];
   Double_t        t1l2j[3];
   Double_t        t1l2n[3];
   Double_t        t2l1e[3];
   Double_t        t2l1t[3];
   Double_t        t2l1x[3];
   Double_t        t2l1y[3];
   Double_t        t2l1i[3];
   Double_t        t2l1j[3];
   Double_t        t2l1n[3];
   Double_t        t2l2e[3];
   Double_t        t2l2t[3];
   Double_t        t2l2x[3];
   Double_t        t2l2y[3];
   Double_t        t2l2i[3];
   Double_t        t2l2j[3];
   Double_t        t2l2n[3];
   Double_t        t1r1e[3];
   Double_t        t1r1t[3];
   Double_t        t1r1x[3];
   Double_t        t1r1y[3];
   Double_t        t1r1i[3];
   Double_t        t1r1j[3];
   Double_t        t1r1n[3];
   Double_t        t1r2e[3];
   Double_t        t1r2t[3];
   Double_t        t1r2x[3];
   Double_t        t1r2y[3];
   Double_t        t1r2i[3];
   Double_t        t1r2j[3];
   Double_t        t1r2n[3];
   Double_t        t2r1e[3];
   Double_t        t2r1t[3];
   Double_t        t2r1x[3];
   Double_t        t2r1y[3];
   Double_t        t2r1i[3];
   Double_t        t2r1j[3];
   Double_t        t2r1n[3];
   Double_t        t2r2e[3];
   Double_t        t2r2t[3];
   Double_t        t2r2x[3];
   Double_t        t2r2y[3];
   Double_t        t2r2i[3];
   Double_t        t2r2j[3];
   Double_t        t2r2n[3];

   // Set branch addresses.
   jtree->SetBranchAddress("t1l1e",t1l1e);
   jtree->SetBranchAddress("t1l1t",t1l1t);
   jtree->SetBranchAddress("t1l1x",t1l1x);
   jtree->SetBranchAddress("t1l1y",t1l1y);
   jtree->SetBranchAddress("t1l1i",t1l1i);
   jtree->SetBranchAddress("t1l1j",t1l1j);
   jtree->SetBranchAddress("t1l1n",t1l1n);
   jtree->SetBranchAddress("t1l2e",t1l2e);
   jtree->SetBranchAddress("t1l2t",t1l2t);
   jtree->SetBranchAddress("t1l2x",t1l2x);
   jtree->SetBranchAddress("t1l2y",t1l2y);
   jtree->SetBranchAddress("t1l2i",t1l2i);
   jtree->SetBranchAddress("t1l2j",t1l2j);
   jtree->SetBranchAddress("t1l2n",t1l2n);
   jtree->SetBranchAddress("t2l1e",t2l1e);
   jtree->SetBranchAddress("t2l1t",t2l1t);
   jtree->SetBranchAddress("t2l1x",t2l1x);
   jtree->SetBranchAddress("t2l1y",t2l1y);
   jtree->SetBranchAddress("t2l1i",t2l1i);
   jtree->SetBranchAddress("t2l1j",t2l1j);
   jtree->SetBranchAddress("t2l1n",t2l1n);
   jtree->SetBranchAddress("t2l2e",t2l2e);
   jtree->SetBranchAddress("t2l2t",t2l2t);
   jtree->SetBranchAddress("t2l2x",t2l2x);
   jtree->SetBranchAddress("t2l2y",t2l2y);
   jtree->SetBranchAddress("t2l2i",t2l2i);
   jtree->SetBranchAddress("t2l2j",t2l2j);
   jtree->SetBranchAddress("t2l2n",t2l2n);
   jtree->SetBranchAddress("t1r1e",t1r1e);
   jtree->SetBranchAddress("t1r1t",t1r1t);
   jtree->SetBranchAddress("t1r1x",t1r1x);
   jtree->SetBranchAddress("t1r1y",t1r1y);
   jtree->SetBranchAddress("t1r1i",t1r1i);
   jtree->SetBranchAddress("t1r1j",t1r1j);
   jtree->SetBranchAddress("t1r1n",t1r1n);
   jtree->SetBranchAddress("t1r2e",t1r2e);
   jtree->SetBranchAddress("t1r2t",t1r2t);
   jtree->SetBranchAddress("t1r2x",t1r2x);
   jtree->SetBranchAddress("t1r2y",t1r2y);
   jtree->SetBranchAddress("t1r2i",t1r2i);
   jtree->SetBranchAddress("t1r2j",t1r2j);
   jtree->SetBranchAddress("t1r2n",t1r2n);
   jtree->SetBranchAddress("t2r1e",t2r1e);
   jtree->SetBranchAddress("t2r1t",t2r1t);
   jtree->SetBranchAddress("t2r1x",t2r1x);
   jtree->SetBranchAddress("t2r1y",t2r1y);
   jtree->SetBranchAddress("t2r1i",t2r1i);
   jtree->SetBranchAddress("t2r1j",t2r1j);
   jtree->SetBranchAddress("t2r1n",t2r1n);
   jtree->SetBranchAddress("t2r2e",t2r2e);
   jtree->SetBranchAddress("t2r2t",t2r2t);
   jtree->SetBranchAddress("t2r2x",t2r2x);
   jtree->SetBranchAddress("t2r2y",t2r2y);
   jtree->SetBranchAddress("t2r2i",t2r2i);
   jtree->SetBranchAddress("t2r2j",t2r2j);
   jtree->SetBranchAddress("t2r2n",t2r2n);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// jtree->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   TH2F *h = new TH2F("h1","h1",500,0,50,200,0,20);
   Long64_t nentries = jtree->GetEntries();

   Long64_t nbytes = 0;
   for (Long64_t i=0; i<nentries;i++) 
   { 
			nbytes += jtree->GetEntry(i);
      h->Fill(t1l2e[0],t1l1e[0]);
   }
   h->Draw();
}
