void range()
{
  gSystem->Load("libTMVA");
  TCanvas *c = new TCanvas("c");
  ifstream fin;
  fin.open("He_in_Si.txt",ios::in);
  string buff;
  TGraph *g = new TGraph();
  int n=0;
  while(getline(fin,buff))
  {
    stringstream buffstream;
    buffstream.str(buff);
    if(buff[0]=='#') continue;
    double energy,tmp1,tmp2,range;
    string unit1,unit2;
    buffstream>>energy>>unit1>>tmp1>>tmp2>>range>>unit2;
    if(unit1=="keV") energy=energy/1000.;//keV->MeV
    if(unit2=="A") range = range/10000.;//A->um
    if(unit2=="mm") range = range*1000.;//mm->mm
    g->SetPoint(n,energy,range);
    n++;
    //printf("%10.3f %10.3f\n",energy,range);
  }
  g->SetTitle("Range vs Energy;#it{Energy}/MeV;#it{Range}/#mum");
  //g->GetXaxis()->SetTitle("#it{Energy}/MeV");
  //g->GetYaxis()->SetTitle("#it{Range}/#mum");
  g->SetMarkerStyle(kCircle);
  g->DrawClone("APE");
  TMVA::TSpline2 *sp = new TMVA::TSpline2("sp",g);
  TGraph *g2 = new TGraph();
  n=0;
  for(double x=0.5;x<102;x=x+1)
  {
    g2->SetPoint(n,x,sp->Eval(x));
    n++;
  }
  g2->SetLineColor(kRed);
  g2->DrawClone("Same");
  TLegend leg(.2,.55,.55,.85,"");
  leg.SetFillColor(19);
  g2->SetFillColor(19);
  g->SetFillColor(19);
  leg.AddEntry(g,"Data from SRIM");
  leg.AddEntry(g2,"Line by TMVA::TSpline2");
  leg.DrawClone("Same");
}
