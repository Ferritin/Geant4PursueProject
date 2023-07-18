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

  G4double photonWavelength = utilityFunctions::evToLambda(newTrack->GetTotalEnergy());

  if(newTrack->GetDefinition()->GetParticleName() == "opticalphoton")
  {
    if(newTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov")
    {
      //G4double angleOfEmission = utilityFunctions::getCerenkovAngleOfEmission(1.5, newTrack->CalculateVelocityForOpticalPhoton());
      G4ThreeVector currentPosition = newTrack->GetPosition();
      G4cout << newTrack->GetMomentumDirection()[1] << G4endl;

      man->FillH1(2, currentEvent);
      man->FillH1(3, photonWavelength);
      //man->FillH1(9, angleOfEmission);
      man->FillH1(6, currentPosition[2]);

    }
    else if(newTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
    {
      man->FillH1(5, photonWavelength);
      man->FillH1(4, currentEvent);
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
