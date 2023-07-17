#include "userAction.h"

userActionInitialization::userActionInitialization()
{ }

userActionInitialization::~userActionInitialization()
{ }

void userActionInitialization::Build() const
{
  runAction *userRunAction = new runAction();
  SetUserAction(userRunAction);
}
