#ifndef NaIDetector_H
#define NaIDetector_H 1
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

class NaIDetector
{
    public:
    NaIDetector(double radius1, double radius2, double radius3, double length1, double length2, double length3);
    void Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo);
    
    private:
    void ConstructAluLayer(double radius1, double length1);
    void ConstructTeflonLayer(double radius2, double length2);
    void ConstructSodiumCrystal(double radius3, double length3);
    
    G4LogicalVolume* fantomLogVol;

};

#endif
