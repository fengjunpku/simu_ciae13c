void readDAT()
{
  TH1F *hcs = new TH1F("hcs","hcs",1800,-0.05,179.95);
  ifstream infile;
  infile.open("cross.dat",ios::in);
  if(!infile) return;
  string line;
  double x,w;
  while(getline(infile,line))
  {
    int i=0;
    char headOfLine = line[i];
    while(isspace(line[i])) headOfLine = line[++i];
    //cout<<i<<endl;
    if(isdigit(headOfLine))
    {
      stringstream lineStream;
      lineStream.str(line);
      lineStream>>x>>w;
      if(x>0.05) hcs->Fill(x,w);
      //cout<<x<<" "<<w<<endl;
    }
  }
  hcs->SaveAs("hcs.root");
}
