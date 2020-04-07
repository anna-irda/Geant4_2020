#ifndef PET_H
#define PET_H 1
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"  //wbudowane materiały
#include "G4Material.hh" //materiały

class PET
{
    public:
    PET(double r_minimum, double r_maximum, double length, double radius, double NoOfDet);
    void Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo);
    
    private:
    void ConstructCylinder(double r_minimum, double r_maximum, double length);
    void ConstructNaIDet(double radius, double NoOfDet);
    
    G4LogicalVolume* cylinderLogVol;
    G4LogicalVolume* ConstructAluLayer();
    G4LogicalVolume* ConstructTeflonLayer();
    G4LogicalVolume* ConstructSodiumCrystal();

};

#endif
