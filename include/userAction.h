#pragma once

#include "G4VUserActionInitialization.hh"
#include "runAction.h"

class userActionInitialization : public G4VUserActionInitialization
{
public:
  userActionInitialization();
  ~userActionInitialization();

  virtual void Build() const;

};
