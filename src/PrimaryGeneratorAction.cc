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
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the B1::PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(1);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle  = particleTable->FindParticle(particleName="mu-");
  fParticleGun->SetParticleDefinition(particle);
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  // fParticleGun->SetParticleEnergy(6.*MeV);

  TFile *file= new TFile("test.root", "READ");
  cry_data = (TTree*)file->Get("cry_data");
  cry_data->SetBranchAddress("n",&n);
  cry_data->SetBranchAddress("nEvents",&nEvents);
  cry_data->SetBranchAddress("nSec",&nSec);
  cry_data->SetBranchAddress("KE",&KE);
  cry_data->SetBranchAddress("x",&x);
  cry_data->SetBranchAddress("y",&y);
  cry_data->SetBranchAddress("z",&z);
  cry_data->SetBranchAddress("u",&u);
  cry_data->SetBranchAddress("v",&v);
  cry_data->SetBranchAddress("w",&w);
  event_id=0;
  // cry_data->GetEntry(event_id++,1);
  // G4cout <<event_id <<nEvents<<" " << n<<G4endl;
  // cry_data->GetEntry(event_id++,1);
  // G4cout <<event_id <<nEvents<<" " << n<<G4endl;
  // cry_data->GetEntry(event_id++,1);
  // G4cout <<event_id <<nEvents<<" " << n<<G4endl;


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // 53 is a double mult event
  t.Form("n==%u",event_id);
  mult=cry_data->Draw(">>event",t);
  elist = (TEventList*)gDirectory->Get("event");
  if(elist==NULL)
        G4cout<<"Error in TEventList pointer"<<G4endl;
  else{
        cry_data->SetEventList(elist);
        for(int i=0;i<mult;i++){  
        cry_data->GetEntry(elist->GetEntry(i));
        fParticleGun->SetParticleEnergy(KE*GeV);
        fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(u,v,w));
        fParticleGun->GeneratePrimaryVertex(anEvent);
        }
        cry_data->SetEventList(0); //reset the entry list
        event_id++;
        }    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
}


