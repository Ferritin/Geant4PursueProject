#include "particleGun.h"

ParticleGeneratorAction::ParticleGeneratorAction()
{

  //Initiates particle gun
  particleGun = new G4ParticleGun();

  //Creates particle table, then looks for a muon definition
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName = "mu-");

  //Sets particle definition
  particleGun->SetParticleDefinition(particle);

  //Sets energy and momentum direction and position
  particleGun->SetParticleEnergy(1.*CLHEP::GeV);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));
  particleGun->SetParticlePosition(G4ThreeVector(0.0,0.0,-10.0));


}

ParticleGeneratorAction::~ParticleGeneratorAction()
{

}

void ParticleGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{


  //Generates the particle
  particleGun->GeneratePrimaryVertex(anEvent);

}
