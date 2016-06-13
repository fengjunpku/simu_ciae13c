#include "JunDSSDAngle.hh"

JunDSSDAngle* JunDSSDAngle::thisAngle=NULL;

JunDSSDAngle::JunDSSDAngle()
{
  JunParMan *jParMan = JunParMan::Instance();
  vector<string> dssdNames = jParMan->GetAllDSSDName();
  for(auto name = dssdNames.begin();name != dssdNames.end();++name)
  {
    Par_DSSD *dssdPar = jParMan->GetDSSDPar(*name);
    double perX = dssdPar->width/dssdPar->vstrips;
    double perY = dssdPar->heigh/dssdPar->hstrips;
    int ni = dssdPar->vstrips;
    int nj = dssdPar->hstrips;
    for(int i=0;i<ni;++i)
    {
      for(int j=0;j<nj;++j)
      {
        char buff[48];
        sprintf(buff,"%s_%02d_%02d",(*name).c_str(),i,j);
        string varName=string(buff);
        TVector3 position(0,0,0);
        position[0]=((ni-1)/2.-i)*perX;
        position[1]=((nj-1)/2.-j)*perY;
        position[2]=dssdPar->distance;
        position.RotateY(dssdPar->angle/180*TMath::Pi());
        mapOfTheta[varName]=position.Theta();
        mapOfPhi[varName]=position.Phi();
      }
    }
  }
}

double JunDSSDAngle::GetTheta(string dssdname,int i,int j)
{
  char buff[48];
  sprintf(buff,"%s_%02d_%02d",dssdname.c_str(),i,j);
  string varName=string(buff);
  if(!mapOfTheta.count(varName))
  {
    cout<<"Miao! Error: Key: "<<varName<<" is not in theta Map!"<<endl;
    exit(0);
  }
    return mapOfTheta[varName];
}

double JunDSSDAngle::GetPhi(string dssdname,int i,int j)
{
  char buff[48];
  sprintf(buff,"%s_%02d_%02d",dssdname.c_str(),i,j);
  string varName=string(buff);
  if(!mapOfPhi.count(varName))
  {
    cout<<"Miao! Error: Key: "<<varName<<" is not in phi Map!"<<endl;
    exit(0);
  }
    return mapOfPhi[varName];
}

JunDSSDAngle::~JunDSSDAngle()
{
  cout<<"End of Angle Manager!"<<endl;
}

JunDSSDAngle* JunDSSDAngle::Instance()
{
  if(thisAngle==NULL)
    thisAngle = new JunDSSDAngle();
  return thisAngle;
}