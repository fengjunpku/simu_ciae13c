#ifndef myHit_h
#define myHit_h 1

#include "globals.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class myHit : public G4VHit
{
public:
	myHit();
	virtual ~myHit();

	//????????????
	const myHit& operator=(const myHit &right);
	G4int operator==(const myHit &right) const;
	//////////////////
	inline void* operator new(size_t);
	inline void  operator delete(void* aHit);
	virtual void Print();

private:
	G4double deltaE;
	G4double hitT;
	G4double pX;
	G4double pY;
	G4int vStrip;
	G4int hStrip;

public:
	inline void SetDeltaE(G4double de){deltaE=de;}
	inline G4double GetDeltaE(){return deltaE;}
	inline void SetHitT(G4double hittime){hitT=hittime;}
	inline G4double GetHitT(){return hitT;}
	inline void SetXY(G4double x,G4double y){pX=x;pY=y;}
	inline void SetStrip(G4int vs,G4int hs){vStrip=vs;hStrip=hs;}
	inline G4double GetX(){return pX;}
	inline G4int GetVStrip(){return vStrip;}
	inline G4double GetY(){return pY;}
	inline G4int GetHStrip(){return hStrip;}

};
///////////////////////////////////////
typedef G4THitsCollection<myHit> myHitsCollection;
extern G4ThreadLocal G4Allocator<myHit>* myHitAllocator;

inline void* myHit::operator new(size_t)
{
	if(!myHitAllocator)
		myHitAllocator = new G4Allocator<myHit>;
	return (void*)myHitAllocator->MallocSingle();
}

inline void myHit::operator delete(void* aHit)
{
	myHitAllocator->FreeSingle((myHit*) aHit);
}
//////////////////////////////////////
#endif
