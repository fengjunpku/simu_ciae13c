#ifndef myCellSD_H
#define myCellSD_H 1

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include <vector>
using std::vector;
class myCellSD
{
public:
		//name,xnum,ynum,arrary of houdu
		myCellSD(G4String csdName,int numX,int numY,G4double *arrHou);
		virtual ~myCellSD();
		void place(G4RotationMatrix* pRot, const G4ThreeVector &tlate, G4Material* pMaterial,G4LogicalVolume* pCurrentLogical);
		

private:
		G4String cname;
		vector<G4Box*>              vpSolidSSD;
		vector<G4LogicalVolume*>    vpLogicSSD;
		vector<G4VPhysicalVolume*>  vpPhysiSSD;
		vector<G4double>   fHouCell;
		int Nx,Ny;
		G4double sizeCell;
};
#endif