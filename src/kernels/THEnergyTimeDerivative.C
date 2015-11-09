/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "THEnergyTimeDerivative.h"

template<>
InputParameters validParams<THEnergyTimeDerivative>()
{
    InputParameters params = validParams<TimeDerivative>();
    return params;
}

THEnergyTimeDerivative::THEnergyTimeDerivative(const InputParameters & parameters)  :
    TimeDerivative(parameters),
    _epor(getMaterialProperty<Real>("porous_media_energy"))
{
}

Real
THEnergyTimeDerivative::computeQpResidual()
{
    return _epor[_qp] * TimeDerivative::computeQpResidual();
}

Real
THEnergyTimeDerivative::computeQpJacobian()
{
    return _epor[_qp] * TimeDerivative::computeQpJacobian();
}
