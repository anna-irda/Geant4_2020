
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "SpineHit.hh"

EventAction::EventAction()
{
    //output.open("Secondaries.txt");
    output.open("SpineEn.txt");
}
 
EventAction::~EventAction()
{
    output.close();
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
    //output << SteppingAction::nrOfSec << std::endl; 
    //SteppingAction::nrOfSec=0;
 
    G4int eventID = anEvent->GetEventID();
    if( eventID % 10 == 0 )
    {
        G4cout << "Finished Running Event # " << eventID << G4endl;
    }
 
    outputFile<< eventID << " " << SteppingAction::totalEnergyDep << G4endl;
    SteppingAction::totalEnergyDep = 0;
}

