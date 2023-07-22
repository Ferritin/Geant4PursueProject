#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"

class ParticleGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    ParticleGeneratorAction();
    ~ParticleGeneratorAction();

    void GeneratePrimaries(G4Event* anEvent);

  private:
    G4ParticleGun* particleGun;


};
