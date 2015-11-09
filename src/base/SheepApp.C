#include "SheepApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

//Auxiliary Kernels
#include "THDarcyFluxAux.h"
#include "THFluidVelocityAux.h"
#include "VariableGradientAux.h"
//Kernels
#include "GMSEnergyTimeDerivative.h"
#include "GMSEnergyResidual.h"
#include "GMSMassResidual.h"
#include "THEnergyTimeDerivative.h"
#include "THMassTimeDerivative.h"
#include "THEnergyResidual.h"
#include "THMassResidual.h"
//Functions
#include "SheepFunctionBC.h"
//Materials
#include "GMSMaterial.h"
#include "THMaterial.h"
//User Objects
#include "PropertyReadFile.h"

template<>
InputParameters validParams<SheepApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;
  
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
  // Auxiliary Kernels
  registerAux(THDarcyFluxAux);
  registerAux(THFluidVelocityAux);
  registerAux(VariableGradientAux);
  // Kernels
  registerKernel(GMSEnergyTimeDerivative);
  registerKernel(GMSEnergyResidual);
  registerKernel(GMSMassResidual);
  registerKernel(THEnergyTimeDerivative);
  registerKernel(THMassTimeDerivative);
  registerKernel(THEnergyResidual);
  registerKernel(THMassResidual);
  // Functions
  registerFunction(SheepFunctionBC);
  // Materials
  registerMaterial(GMSMaterial);
  registerMaterial(THMaterial);
  // User Object
  registerUserObject(PropertyReadFile);
}

// External entry point for dynamic syntax association
extern "C" void SheepApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { SheepApp::associateSyntax(syntax, action_factory); }
void
SheepApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
