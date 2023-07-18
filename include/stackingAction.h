#pragma once

#include "G4ClassificationOfNewTrack.hh"
#include "G4Types.hh"
#include "G4UserStackingAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "G4GenericMessenger.hh"
#include "G4AnalysisManager.hh"
#include "G4ThreeVector.hh"
#include "utilityFunctions.h"



class G4Track;
class G4GenericMessenger;

class stackingAction : public G4UserStackingAction
{
public:
  stackingAction();
  ~stackingAction();

  G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack) final;
  virtual void PrepareNewEvent();

private:
  G4AnalysisManager *man;
  G4int currentEvent;

};
