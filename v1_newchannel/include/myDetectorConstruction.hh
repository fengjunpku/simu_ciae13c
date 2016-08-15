#ifndef myDetectorConstruction_H
#define myDetectorConstruction_H 1

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4NistManager.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh" 
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"//for sensitive detector
#include "mySSD.hh"//my Sesitive Detector define class
//#include "myTele.hh"
#include "JunParMan.hh"
#include <string>
#include <vector>
using namespace std;

class myDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	myDetectorConstruction();
	virtual ~myDetectorConstruction();

	virtual G4VPhysicalVolume* Construct();
	virtual void ConstructSDandField();

private:
	void DefineMaterials();
	G4VPhysicalVolume* DefineVoumes();
	//world_para
	G4double fSizeWorld[3];//for tube: rmin,rmax,height,startAngle,spanningAngle
	//Material
	G4Material*           pVacuum;
	G4Material*           pSilicon;
	G4Material*           pBerylium;
	//world
	G4Box*                pSolidWorld;
	G4LogicalVolume*      pLogicWorld;
	G4VPhysicalVolume*    pPhysiWorld;
	//target
	G4Tubs*               pSolidTarget;
	G4LogicalVolume*      pLogicTarget;
	G4VPhysicalVolume*    pPhysiTarget;
	//dssd defined by par_dssd
	JunParMan *jParManager;
	vector<string>  dssdNames;
	G4int           dssdNums;
	G4Box**             pSolidDetecotr;
	G4LogicalVolume**   pLogicDetecotr;
	G4VPhysicalVolume** pPhysiDetecotr;
};

#endif
