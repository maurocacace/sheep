#ifndef SHEEPAPP_H
#define SHEEPAPP_H

#include "MooseApp.h"

class SheepApp;

template<>
InputParameters validParams<SheepApp>();

class SheepApp : public MooseApp
{
public:
  SheepApp(InputParameters parameters);
  virtual ~SheepApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* SHEEPAPP_H */
