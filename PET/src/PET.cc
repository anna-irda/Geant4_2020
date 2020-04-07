#include "PET.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh" //jednostki
#include "G4PVPlacement.hh"


PET::PET(double r_minimum, double r_maximum, double length, double radius, double NoOfDet)
{
    ConstructCylinder(r_minimum, r_maximum, length);
    ConstructNaIDet(radius, NoOfDet);
}

void PET::ConstructCylinder(double r_minimum, double r_maximum, double length0)
{
     G4Material* ppy = man->FindOrBuildMaterial("G4_POLYPROPYLENE");
     G4double rMin = r_minimum;
     G4double rMax = r_maximum;
     G4double length = length0;
     G4Tubs* theCylinder = new G4Tubs("theCylinder", rMin, rMax, length/2, 0*deg, 360*deg);
     cylinderLogVol = new G4LogicalVolume(theCylinder, ppy, "cylinderLogVol");

     G4VisAttributes* cylinderAtt = new G4VisAttributes(G4Colour(0.5,0.5,0.5, 0.7));
     cylinderAtt->SetForceAuxEdgeVisible(true);
     cylinderAtt->SetForceSolid(true);
     cylinderLogVol->SetVisAttributes(cylinderAtt);

     //G4ThreeVector pos(0, 0, 0);
     //new G4PVPlacement(0, pos, cylinderLogVol, "cylinderPhys", worldLogic,0,0);
}

void PET::ConstructNaIDet(double radius, double NoOfDet)
{
   G4LogicalVolume* aluLogic = ConstructAluLayer();
   G4LogicalVolume* teflonLogic = ConstructTeflonLayer(); 
   G4LogicalVolume* naiLogic = ConstructSodiumCrystal();   
   G4ThreeVector pos(0, 0, 0);
   new G4PVPlacement(0, pos, naiLogic, "naiPhys", teflonLogic, 0, 0);   
   new G4PVPlacement(0, pos, teflonLogic, "teflonPhys", aluLogic, 0, 0);

   double ringRadius = radius;
	
   int noDetectors = NoOfDet;
   double angle = 360./noDetectors*deg;
   for(int i = 0; i !=36; ++i)
   {
       G4RotationMatrix* rot = new G4RotationMatrix();
       rot->rotateZ(angle*i);
       rot->rotateX(90*deg);
       G4ThreeVector detPos(ringRadius*sin(angle*i),ringRadius*cos(angle*i),0);
       new G4PVPlacement(rot, detPos, aluLogic, "aluPhys", cylinderLogVol, 0, i);
   }
}

G4LogicalVolume* PET::ConstructAluLayer()
{
   G4double rMin = 0;
   G4double rMax = 3.6 *cm;
   G4double halfLength = 5.6 *cm; 
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

G4LogicalVolume* PET::ConstructTeflonLayer()
{
   G4double rMin = 0;
   G4double rMax = 3.3 *cm;
   G4double halfLength = 5.3 *cm; 
   G4Tubs* solid = new G4Tubs("solid", rMin, rMax, halfLength, 0*deg, 360*deg);
	
   G4Material* teflon = man->FindOrBuildMaterial("G4_TEFLON");

   G4LogicalVolume* teflonLogic = new G4LogicalVolume(solid, teflon,"teflonLogic");
   G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(1,1,1, 0.5));
   visAttr->SetForceSolid(true);
   visAttr->SetForceAuxEdgeVisible(true);
   teflonLogic->SetVisAttributes(visAttr);
   return teflonLogic;
}

G4LogicalVolume* PET::ConstructSodiumCrystal()
{
   G4double rMin = 0;
   G4double rMax = 3. *cm;
   G4double halfLength = 5. *cm; 
   G4Tubs* crystal = new G4Tubs("crystal", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* nai = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");

   G4LogicalVolume* naiLogic = new G4LogicalVolume(crystal, nai,"naiLogic");
   G4VisAttributes* naiVis = new G4VisAttributes(G4Colour(1,1,0));
   naiVis->SetForceSolid(true);
   naiVis->SetForceAuxEdgeVisible(true);
   naiLogic->SetVisAttributes(naiVis);
   return naiLogic;
}

void PET::Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo)
{
    new G4PVPlacement(pRot, tlate, cylinderLogVol, pName,  pMotherLogical, 0, pCopyNo);
}
