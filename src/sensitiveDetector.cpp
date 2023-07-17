#include "sensitiveDetector.h"

sensitiveDetector::sensitiveDetector(const G4String& name)
  : G4VSensitiveDetector(name)
{
}

sensitiveDetector::~sensitiveDetector()
{
}

/*

Method originally written by Hans Wenzel,
https://github.com/hanswenzel/LArProperties/blob/main/scripts/Cerenkov.C

Modified so that energy input is MeV instead of eV
*/
G4double sensitiveDetector::evToLambda(G4double MeV)
{
  G4double h = 4.13566743E-15;
  G4double c = 299792458.;

  //Converts MeV to eV
  G4double eV = MeV * (1.e+6);

  double lambda = (h*c)/(eV * 1.e-9);
  return lambda;
}

void sensitiveDetector::Initialize(G4HCofThisEvent*)
{
}

G4bool sensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{

  //Gets current track, stores name of the particle
  G4Track *track = aStep->GetTrack();
  std::string particleName = track->GetDefinition()->GetParticleName();


  if(particleName == "opticalphoton")
  {
    //Stores particle energy, creator process and preStep Pointer
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    std::string creatorProcess = track->GetCreatorProcess()->GetProcessName();

    //Creates analysis manager
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    //Stores information regarding quantity of Cerenkov vs Scintillation photons detected by SD in an Ntuple
    if(creatorProcess == "Cerenkov")
    {
      man->FillNtupleDColumn(0, 0, eventID);
      man->AddNtupleRow(0);
    }
    else if(creatorProcess == "Scintillation")
    {
      man->FillNtupleDColumn(1, 0, eventID);
      man->AddNtupleRow(1);
    }

    G4double photonWavelength = evToLambda(preStepPoint->GetTotalEnergy());

    //Filling out SD Cerenkov Z position histogram
    if(track->GetCreatorProcess()->GetProcessName() == "Cerenkov")
    {
      G4ThreeVector currentPosition = track->GetPosition();
      man->FillH1(4, currentPosition[2]);
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
