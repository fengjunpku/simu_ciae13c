#include "myCellSD.hh"

myCellSD::myCellSD(G4String csdName,int numX,int numY,G4double *arrHou)
{
	Nx=numX;
	Ny=numY;
	cname=csdName;
	sizeCell=3.1*mm;
	for(int i=0;i<Nx*Ny;++i)
	{
		G4Box*                pSolid;
		G4LogicalVolume*      pLogic;
		G4VPhysicalVolume*    pPhysi;
		vpSolidSSD.push_back(pSolid);
		vpLogicSSD.push_back(pLogic);
		vpPhysiSSD.push_back(pPhysi);
		fHouCell.push_back(arrHou[i]);
	}
}

myCellSD::~myCellSD()
{
	//---------
	for(vector<G4Box*>::iterator it=vpSolidSSD.begin();it!=vpSolidSSD.end();++it)
	{
		if (NULL != *it) 
		{delete *it;*it = NULL;}
	}
	//---------
	for(vector<G4LogicalVolume*>::iterator it=vpLogicSSD.begin();it!=vpLogicSSD.end();++it)
	{
		if (NULL != *it) 
		{delete *it;*it = NULL;}
	}
	//---------
	for(vector<G4VPhysicalVolume*>::iterator it=vpPhysiSSD.begin();it!=vpPhysiSSD.end();++it)
	{
		if (NULL != *it) 
		{delete *it;*it = NULL;}
	}
	//-------------
	vpLogicSSD.clear();
	vpSolidSSD.clear();
	vpPhysiSSD.clear();
}

void myCellSD::place(G4RotationMatrix* pRot, const G4ThreeVector &tlate, G4Material* pMaterial,G4LogicalVolume* pCurrentLogical)
{
	G4ThreeVector tran,rotran;
	//tran00[0]=tlate[0]-(Nx-1.)/2.*sizeCell;
	//tran00[1]=tlate[1]-(Ny-1.)/2.*sizeCell;
	//tran00[2]=tlate[2];
	for(int j=0;j<Ny;++j)
	{
		for(int i=0;i<Nx;++i)
		{
			tran[0]=tlate[0]-(Nx-1.)/2.*sizeCell+i*sizeCell;
			tran[1]=tlate[1]-(Ny-1.)/2.*sizeCell+j*sizeCell;
			tran[2]=tlate[2];
			rotran=tlate+pRot->inverse()*(tran-tlate);//rotate the tran
			G4String name[3];
			name[0]=cname+"_solid_";
			name[0]+=(48+i);name[0]+=(48+j);
			name[1]=cname+"_logic_";
			name[1]+=(48+i);name[1]+=(48+j);
			name[2]=cname+"_physi_";
			name[2]+=(48+i);name[2]+=(48+j);
			vpSolidSSD[i+Ny*j] = new G4Box(name[0],0.5*sizeCell,0.5*sizeCell,0.5*fHouCell[i+Ny*j]);
			vpLogicSSD[i+Ny*j] = new G4LogicalVolume(vpSolidSSD[i+Ny*j],pMaterial,name[1],0,0,0,true);
			vpPhysiSSD[i+Ny*j] = new G4PVPlacement(pRot,rotran,vpLogicSSD[i+Ny*j],name[2],pCurrentLogical,false,0);
		}
	}
}
