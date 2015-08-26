#include "SheepApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

#include "ThermoTimeDerivative.h"
#include "ThermalConduction.h"
#include "StaticLoad.h"

#include "SheepMaterial.h"

template<>
InputParameters validParams<SheepApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

SheepApp::SheepApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  SheepApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  SheepApp::associateSyntax(_syntax, _action_factory);
}

SheepApp::~SheepApp()
{
}

// External entry point for dynamic application loading
extern "C" void SheepApp__registerApps() { SheepApp::registerApps(); }
void
SheepApp::registerApps()
{
  registerApp(SheepApp);
}

// External entry point for dynamic object registration
extern "C" void SheepApp__registerObjects(Factory & factory) { SheepApp::registerObjects(factory); }
void
SheepApp::registerObjects(Factory & factory)
{
  // Kernels
  registerKernel(ThermoTimeDerivative);
  registerKernel(ThermalConduction);
  registerKernel(StaticLoad);

  // Materials
  registerKernel(SheepMaterial);
}

// External entry point for dynamic syntax association
extern "C" void SheepApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { SheepApp::associateSyntax(syntax, action_factory); }
void
SheepApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
