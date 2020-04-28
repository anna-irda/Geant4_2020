
// $Id: PrimaryGeneratorAction.cc 15.10.2018 A Fijalkowska $
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
#include <math.h>
#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun();
    particleTable = G4ParticleTable::GetParticleTable();
	SetUpDefault();
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::SetUpDefault()
{
	
	G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
	particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	particleGun->SetParticleEnergy(500.0*keV);

}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{	
    particleGun->GeneratePrimaryVertex(anEvent);
}

void PrimaryGeneratorAction::GeneratePositronIncident(G4Event* anEvent)
{
    G4ParticleDefinition* particle = particleTable->FindParticle("e+");
    particleGun->SetParticleDefinition(particle);			
    particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
    particleGun->SetParticleEnergy(600*keV);
    particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection());
    particleGun->GeneratePrimaryVertex(anEvent);
}

void PrimaryGeneratorAction::GenerateBackgroundIncident(G4Event* anEvent)
{
    G4double worldX = 1.5*m;
    G4double worldY = 1.5*m;
    G4double worldZ = 1.5*m;
    G4double randX = FindRandomFromHalfSize(worldX);
    G4double randY = FindRandomFromHalfSize(worldY);
    G4double randZ = FindRandomFromHalfSize(worldZ);
    particleGun->SetParticlePosition(G4ThreeVector(randX,randY,randZ));
    
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleEnergy(1460*keV);
    particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection());
    particleGun->GeneratePrimaryVertex(anEvent);
}
