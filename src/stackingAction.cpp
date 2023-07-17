#include "stackingAction.h"

stackingAction::stackingAction() : G4UserStackingAction()
{
  currentEvent = 0;
  man = G4AnalysisManager::Instance();
}

stackingAction::~stackingAction()
{ }

G4ClassificationOfNewTrack stackingAction::ClassifyNewTrack(const G4Track* newTrack)
{

  G4ClassificationOfNewTrack classification = fWaiting;

  if(newTrack->GetDefinition()->GetParticleName() == "opticalphoton")
  {
    if(newTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov")
    {
      G4double cerenkovPhotonWavelength = sensitiveDetector::evToLambda(newTrack->GetTotalEnergy());
      man->FillH1(2, currentEvent);
      man->FillH1(3, cerenkovPhotonWavelength);
    }
    if(newTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
    {
      G4double scintillationPhotonWavelength = sensitiveDetector::evToLambda(newTrack->GetTotalEnergy());
      man->FillH1(6, scintillationPhotonWavelength);
      man->FillH1(5, currentEvent);
    }

  }
  if(currentEvent == 0)
  {
    currentEvent++;
  }

  return classification;
}

void stackingAction::PrepareNewEvent()
{
  if(currentEvent == 0)
  {
    return;
  }
  else
  {
    currentEvent++;
  }
}
