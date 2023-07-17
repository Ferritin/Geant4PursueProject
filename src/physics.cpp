#include "physics.h"

TestPhysicsList::TestPhysicsList()
{

  RegisterPhysics (new G4EmStandardPhysics());
  RegisterPhysics (new G4OpticalPhysics());

}

TestPhysicsList::~TestPhysicsList()
{}
