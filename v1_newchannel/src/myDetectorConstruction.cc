#include "myDetectorConstruction.hh"

myDetectorConstruction::myDetectorConstruction()
{
	//get parameters
	jParManager = JunParMan::Instance();
	dssdNames = jParManager->GetAllDSSDName();
	dssdNums = dssdNames.size();
	//World_para
	fSizeWorld[0]=0.5*70.*cm;
	fSizeWorld[1]=0.5*70.*cm;
	fSizeWorld[2]=0.5*70.*cm;
}

myDetectorConstruction::~myDetectorConstruction()
{;}

void myDetectorConstruction::DefineMaterials()
{
		G4NistManager* man = G4NistManager::Instance();
		G4Element *N =  man->FindOrBuildElement("N");
		G4Element *O =  man->FindOrBuildElement("O");
		G4Element *Si = man->FindOrBuildElement("Si");
		G4Element *Be = man->FindOrBuildElement("Be");

		pVacuum = new G4Material("Vacuum",1.29e-10*mg/cm3,2,kStateGas);//kStateSolid,kStateLiquid
		pSilicon = new G4Material("Silicon",2.321*g/cm3,1,kStateSolid);
		pBerylium = new G4Material("Berylium",1.848*g/cm3,1,kStateSolid);

		pVacuum->AddElement(N, 70.*perCent);
		pVacuum->AddElement(O, 30.*perCent);
		pSilicon->AddElement(Si,100.*perCent);
		pBerylium->AddElement(Be,100.*perCent);
}

G4VPhysicalVolume* myDetectorConstruction::DefineVoumes()
{
		//------------------world
		pSolidWorld = new G4Box("solidWorld",fSizeWorld[0],fSizeWorld[1],fSizeWorld[2]);
		pLogicWorld = new G4LogicalVolume(pSolidWorld,pVacuum, "logicWorld",0,0,0);
		pPhysiWorld = new G4PVPlacement(0,G4ThreeVector(0,0,0),pLogicWorld,"physiWorld",0,false,0);
		//-------------target
		G4RotationMatrix *rot = new G4RotationMatrix();
		rot->rotateX(0*deg);//rotation
		G4ThreeVector tran(0.,0.,0.);//translation
		pSolidTarget = new G4Tubs("solidTarget",0.*cm,1.5*cm,0.05*um,0.*deg,360.*deg);
		pLogicTarget = new G4LogicalVolume(pSolidTarget,pBerylium,"logicTarget",0,0,0,true);
		pPhysiTarget = new G4PVPlacement(rot,tran,pLogicTarget,"physiTarget",pLogicWorld,false,0);
		//-------------dssd-----------
		pSolidDetecotr = new G4Box*[dssdNums];
		pLogicDetecotr = new G4LogicalVolume*[dssdNums];
		pPhysiDetecotr = new G4VPhysicalVolume*[dssdNums];
		for(int i=0;i<dssdNums;++i)
		{
			string _dssdName=dssdNames[i];
			Par_DSSD *_dssdPar = jParManager->GetDSSDPar(_dssdName);
			G4float halfHeigh = 0.5*(_dssdPar->heigh)*mm;
			G4float halfWidth = 0.5*(_dssdPar->width)*mm;
			G4float halfThick = 0.5*(_dssdPar->thick)*mm;
			string solidName = _dssdName+"_solid";
			pSolidDetecotr[i] = new G4Box(solidName,halfHeigh,halfWidth,halfThick);
			string logicName = _dssdName+"_logic";
			pLogicDetecotr[i] = new G4LogicalVolume(pSolidDetecotr[i],pSilicon,logicName,0,0,0,true);
			string physiName = _dssdName+"_physi";
			G4RotationMatrix *_dRot = new G4RotationMatrix();
			G4double _dAngle = (_dssdPar->angle)*deg;
			_dRot->rotateY(_dAngle);
			G4ThreeVector _dPos(0.,0.,0.);
			G4double _dDistance = (_dssdPar->distance)*mm;
			_dPos[0] = _dDistance*sin(-1*_dAngle);
			_dPos[2] = _dDistance*cos(_dAngle);
			pPhysiDetecotr[i] = new G4PVPlacement(_dRot,_dPos,pLogicDetecotr[i],physiName,pLogicWorld,false,0);
		}
		//----------------VIS-----------------
		//pLogicWorld->SetVisAttributes(G4VisAttributes::Invisible);
		G4VisAttributes *pTarVisAtt = new G4VisAttributes(G4Colour::Yellow());
		pLogicTarget->SetVisAttributes(pTarVisAtt);
		G4VisAttributes *pLeftVisAtt = new G4VisAttributes(G4Colour::Red());
		pLogicDetecotr[0]->SetVisAttributes(pLeftVisAtt);
	//------------------end-----------------
		return pPhysiWorld;
}

G4VPhysicalVolume* myDetectorConstruction::Construct()
{
		//
		DefineMaterials();
		return DefineVoumes();
}

void myDetectorConstruction::ConstructSDandField()
{
	G4SDManager *SDmanager = G4SDManager::GetSDMpointer();
	//-------------------------------------------
	for(int i=0;i<dssdNums;++i)
	{
		Par_DSSD *_dssdPar = jParManager->GetDSSDPar(dssdNames[i]);
		G4int _dVStrips = _dssdPar->vstrips;
		G4int _dHStrips = _dssdPar->hstrips;
		G4double _dWidth = (_dssdPar->width)*mm;
		G4double _dHeigh = (_dssdPar->heigh)*mm;
		string _dSDname=dssdNames[i]+"_SD";
		mySSD* pSensiDetector = new mySSD(_dSDname,_dVStrips,_dHStrips,_dWidth,_dHeigh);
		SDmanager->AddNewDetector(pSensiDetector);
		pLogicDetecotr[i]->SetSensitiveDetector(pSensiDetector);
	}
	//-------------------------------------------
	// G4String fname[4]={"t1l_","t1r_","t2l_","t2r_"};
	// G4String sdname=fname[lr];
	// sdname+=(49+i);
	// mySSD* pSensiSSDx = new mySSD(sdname);
	// SDman->AddNewDetector(pSensiSSDx);
	// T1[lr]->pLogicSD[i]->SetSensitiveDetector(pSensiSSDx);
}
