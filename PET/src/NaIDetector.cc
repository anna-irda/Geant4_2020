#include "NaIDetector.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh" //jednostki
#include "G4PVPlacement.hh"


NaIDetector::NaIDetector(double radius1, double radius2, double radius3, double length1, double length2, double length3)
{
    ConstructAluLayer(radius1, length1);
    ConstructTeflonLayer(radius2, length2);
    ConstructSodiumCrystal(radius3, length3);
}

void NaIDetector::ConstructAluLayer(double radius1, double length1)
{
   G4double rMin = 0;
   G4double rMax = radius1;
   G4double halfLength = length; 
   G4Tubs* aluSolid = new G4Tubs("aluSolid", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* alu = new G4Material("aluminum", 2.7*g/cm3, 1);
   G4Element* Al = man->FindOrBuildElement("Al");
   alu->AddElement(Al, 1);
   
   G4LogicalVolume* aluLogic = new G4LogicalVolume(aluSolid, alu,"aluLogic");
   G4VisAttributes* aluVis = new G4VisAttributes(G4Colour(255./255,102./255.,0));
   //aluVis->SetForceSolid(true);
   aluVis->SetForceAuxEdgeVisible(true);
   aluLogic->SetVisAttributes(aluVis);
   return aluLogic;
}

void NaIDetector::ConstructTeflonLayer(double radius2, double length2)
{
   G4double rMin = 0;
   G4double rMax = radius2;
   G4double halfLength = length; 
   G4Tubs* solid = new G4Tubs("solid", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* teflon = man->FindOrBuildMaterial("G4_TEFLON");
   
   G4LogicalVolume* teflonLogic = new G4LogicalVolume(solid, teflon,"teflonLogic");
   G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(1,1,1));
   visAttr->SetForceSolid(true);
   visAttr->SetForceAuxEdgeVisible(true);
   teflonLogic->SetVisAttributes(visAttr);
   return teflonLogic;
}

void NaIDetector::ConstructSodiumCrystal(double radius3, double length3)
{
   G4double rMin = 0;
   G4double rMax = radius3;
   G4double halfLength = length; 
   G4Tubs* crystal = new G4Tubs("crystal", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* nai = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");
   
   G4LogicalVolume* naiLogic = new G4LogicalVolume(crystal, nai,"naiLogic");
   G4VisAttributes* naiVis = new G4VisAttributes(G4Colour(1,1,0));
   naiVis->SetForceSolid(true);
   naiVis->SetForceAuxEdgeVisible(true);
   naiLogic->SetVisAttributes(naiVis);
   return naiLogic;
}

void NaIDetector::Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo)
{
    new G4PVPlacement(pRot, tlate, fantomLogVol, pName,  pMotherLogical, 0, pCopyNo);
}
