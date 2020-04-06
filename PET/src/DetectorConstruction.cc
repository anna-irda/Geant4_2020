/// \file DetectorConstruction.cc
/// \brief DetectorConstruction class
//
//
#include "DetectorConstruction.hh"
#include "G4PVPlacement.hh" //tworzenie physical volume
#include "G4SystemOfUnits.hh" //jednostki
#include "G4VisAttributes.hh" //sposob wyświetlania, kolory itp

#include "G4Box.hh" //prostopadłościan
#include "G4Tubs.hh" //walec
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"

#include "HumanFantom.hh"


DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    fantomLogVol=0L;
    cylinderLogVol=0L;
    man = G4NistManager::Instance();
}



DetectorConstruction::~DetectorConstruction() 
{
    if(worldLogic != 0L)
        delete worldLogic;
    if(fantomLogVol != 0L)
        delete fantomLogVol;        
    if(cylinderLogVol != 0L)
        delete cylinderLogVol; 
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructHumanFantom();
    ConstructCylinder();
    ConstructNaIDet();
    return worldPhys;
}

G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{

    G4double worldX = 1.5*m;
    G4double worldY = 1.5*m;
    G4double worldZ = 1.5*m;
    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    
    G4Material* vaccum = new G4Material("GalacticVacuum", 1., 1.01*g/mole,
                           CLHEP::universe_mean_density, 
                           kStateGas, 3.e-18*pascal, 2.73*kelvin);
                           
    worldLogic = new G4LogicalVolume(worldSolid, vaccum, "worldLogic", 0,0,0);
                                             
    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;

}

void DetectorConstruction::ConstructHumanFantom()
{   
    G4double radiusMax = 15*cm;
    G4double length = 170*cm;
    HumanFantom *fantom = new HumanFantom(length, radiusMax);

	G4ThreeVector pos(0,0,0); 
	G4RotationMatrix *pRot = new G4RotationMatrix();
	fantom->Place(0, pos, "fantom", worldLogic, 0); 
	
}

void DetectorConstruction::ConstructCylinder()
{
     G4Material* ppy = man->FindOrBuildMaterial("G4_POLYPROPYLENE");
     G4double rMin = 40*cm;
     G4double rMax = 55*cm;
     G4double length = 15*cm;
     G4Tubs* theCylinder = new G4Tubs("theCylinder", rMin, rMax, length/2, 0*deg, 360*deg);
     cylinderLogVol = new G4LogicalVolume(theCylinder, ppy, "cylinderLogVol");

     G4VisAttributes* cylinderAtt = new G4VisAttributes(G4Colour(0.5,0.5,0.5, 0.7));
     cylinderAtt->SetForceAuxEdgeVisible(true);
     cylinderAtt->SetForceSolid(true);
     cylinderLogVol->SetVisAttributes(cylinderAtt);

     G4ThreeVector pos(0,0, 0);
     new G4PVPlacement(0, pos, cylinderLogVol, "cylinderPhys", worldLogic,0,0);
}

//NaI
//wysokość 10 cm
//promień 3 cm
//teflon 3 mm
//aluminium 3 mm

void DetectorConstruction::NaIDetector()
{
   G4double rMax1 = 3.6 *cm;
   G4double rMax2 = 3.3 *cm;
   G4double rMax3 = 3 *cm;
   G4double halfLength1 = 5.6 *cm;
   G4double halfLength2 = 5.3 *cm;
   G4double halfLength3 = 5 *cm;
   NaIDetector *detector = new NaIDetector(rMax1, rMax2, rMax3, halfLength1, halfLength2, halfLength3)

   	G4RotationMatrix *pRot = new G4RotationMatrix();
	detector->Place(0, pos, "detector", worldLogic, 0); 
	
   double ringRadius = 46.6*cm;
	
   int noDetectors = 36;
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

void DetectorConstruction::ConstructSDandField() 
{
}
