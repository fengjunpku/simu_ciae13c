#ifndef myTele_H
#define myTele_H 1

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh" 
#include "myCellSD.hh"//SSD divided to many cells
class myTele
{
public:
		myTele();
		virtual ~myTele();
		myCellSD*           pCellSD[2];
		G4Box*              pSolidSD[3];
		G4LogicalVolume*    pLogicSD[3];
		G4VPhysicalVolume*  pPhysiSD[3];
};
#endif
