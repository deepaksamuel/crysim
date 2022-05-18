//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file SteppingAction.cc
/// \brief Implementation of the B1::SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
: fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
//   if (!fScoringVolume) {
//     const DetectorConstruction* detConstruction
//       = static_cast<const DetectorConstruction*>
//         (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
//     fScoringVolume = detConstruction->GetScoringVolume();
//   }
// const PrimaryGeneratorAction* prim_gen =   static_cast<const PrimaryGeneratorAction*> (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
// double event_id = (double) prim_gen->GetCurrentEventId(); // use to get the event id for multiplicity 2 events

if(step->GetPreStepPoint()->GetPhysicalVolume()->GetName()=="glassplate"){
    if(step->GetTrack()->GetDefinition()->GetPDGEncoding()==abs(13) ){
      G4RootAnalysisManager *man = G4RootAnalysisManager::Instance();
      //G4cout<<event_id<<G4endl;
      
      man->FillNtupleDColumn(0, G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID());
      // man->FillNtupleDColumn(0, event_id);
      man->FillNtupleDColumn(1, step->GetPreStepPoint()->GetPosition().x());
      man->FillNtupleDColumn(2, step->GetPreStepPoint()->GetPosition().y());
      man->FillNtupleDColumn(3, step->GetPreStepPoint()->GetPosition().z());
      man->FillNtupleDColumn(4, step->GetPreStepPoint()->GetProperTime());
      man->FillNtupleDColumn(5, step->GetTrack()->GetDefinition()->GetPDGEncoding());
      man->FillNtupleDColumn(6,step->GetTrack()->GetMomentum().x());
      man->FillNtupleDColumn(7,step->GetTrack()->GetMomentum().y());
      man->FillNtupleDColumn(8,step->GetTrack()->GetMomentum().z());
      man->AddNtupleRow();
    // }
  }
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
}

}