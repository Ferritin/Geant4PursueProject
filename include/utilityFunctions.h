#pragma once

#include "G4Types.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"



namespace utilityFunctions
{
  G4double evToLambda(G4double MeV);
  G4double getCerenkovAngleOfEmission(G4double refractiveIndex, G4double velocity);
}
