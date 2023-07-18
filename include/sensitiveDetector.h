#pragma once

#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "utilityFunctions.h"

class G4Step;

class sensitiveDetector : public G4VSensitiveDetector
{
  public:
      sensitiveDetector(const G4String&);
     ~sensitiveDetector();

     virtual void Initialize(G4HCofThisEvent*);
     virtual G4bool ProcessHits(G4Step*, G4TouchableHistory *ROhist);
     virtual void EndOfEvent(G4HCofThisEvent*);

 private:

};
