//
// $Id: SteppingAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
#include "SteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4String.hh"
#include "G4VPhysicalVolume.hh"
#include <iostream>

SteppingAction::SteppingAction():G4UserSteppingAction()
{

}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* theStep)
{
    G4Track* theTrack = theStep->GetTrack();
    G4String volumeName = theTrack->GetVolume()->GetName();
    
    if (volumeName == "fantom")
    {
        auto secondaries = theStep -> GetSecondaryInCurrentStep();
        nrOfSec+=secondaries->size();
        //std::cout << nrOfSec << std::endl;      
    }
    /*if (secondaries->size()>0)
    {
        std::cout << "size" << secondaries->size();
        PrintStep(theStep);
    }*/

    G4VPhysicalVolume *physVol = theTrack->GetVolume();
    G4LogicalVolume* logVol = physVol->GetLogicalVolume();
    G4Material* material = logVol->GetMaterial();
    G4String materialName = material->GetName();

    if(materialName =="G4_BONE_COMPACT_ICRU")
    {
     double eneDepInStep = theStep->GetTotalEnergyDeposit()/keV;
     totalEnergyDep += eneDepInStep;
    }

     //PrintStep(theStep);
}

void SteppingAction::PrintStep(const G4Step* theStep)
{
    
    G4Track* theTrack = theStep->GetTrack();
    G4String processName = theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4String particleName = theTrack->GetDefinition()->GetParticleName();
    G4double energy = thTrack->GetKineticEnergy();
    G4String volumeName = theTrack->GetVolume()->GetName();
    G4double deltaEn = theStep->GetDeltaEnergy();
    int trackNo = theTrack->GetTrackID();

    std::cout << " trackNo: " << trackNo
              << " particle: " << particleName
              << " process: " << processName
              << " kinetic energy: " << energy/MeV
	      << " delta en: " << deltaEn
	      << " voulme name: " << volumeName << std::endl;

}
int SteppingAction::nrOfSec=0;
