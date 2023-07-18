#include "sensitiveDetector.h"

sensitiveDetector::sensitiveDetector(const G4String& name)
  : G4VSensitiveDetector(name)
{
}

sensitiveDetector::~sensitiveDetector()
{
}

void sensitiveDetector::Initialize(G4HCofThisEvent*)
{
}

G4bool sensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{

  //Gets current track, stores name of the particle
  G4Track *track = aStep->GetTrack();
  std::string particleName = track->GetDefinition()->GetParticleName();

  std::string volumeName = aStep->GetPreStepPoint()->GetTouchable()->GetVolume()->GetName();


  if(particleName == "opticalphoton")
  {
    //Stores particle energy, creator process and preStep Pointer
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    std::string creatorProcess = track->GetCreatorProcess()->GetProcessName();

    //Creates analysis manager
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    //Records photon wavelength
    G4double photonWavelength = utilityFunctions::evToLambda(preStepPoint->GetTotalEnergy());

    G4ThreeVector currentPosition = track->GetPosition();
    //Records position of Photons as it hits SD 1 or 2, separating by Cerenkov and Scintillation
    if(creatorProcess == "Cerenkov")
    {
      if(volumeName == "SD1")
      {
        man->FillH2(0, currentPosition[0], currentPosition[1]);
        man->FillH1(7, photonWavelength);
      }
      if(volumeName == "SD2")
      {
        man->FillH2(2, currentPosition[0], currentPosition[1]);
        man->FillH1(8, photonWavelength);
      }
    }
    else if(creatorProcess == "Scintillation")
    {
      if(volumeName == "SD1")
      {
        man->FillH2(1, currentPosition[0], currentPosition[1]);
        man->FillH1(7, photonWavelength);
      }
      if(volumeName == "SD2")
      {
        man->FillH2(3, currentPosition[0], currentPosition[1]);
        man->FillH1(8, photonWavelength);
      }
    }

    //Each time a photon hits the SD, the corresponding event ID is incremented
    man->FillH1(0, eventID);
    //Fills histogram with all the energies of the photons detected by SD
    man->FillH1(1, photonWavelength);


    //Kills optical photon
    track->SetTrackStatus(fStopAndKill);

    return true;

  }
  return true;
}

void sensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{

}
