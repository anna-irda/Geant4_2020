
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "SteppingAction.hh"
#include "EventAction.hh"

EventAction::EventAction()
{

}
 
EventAction::~EventAction()
{
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
    std::cout << SteppingAction::nrOfSec << std::endl; 
    SteppingAction::nrOfSec=0;
}
