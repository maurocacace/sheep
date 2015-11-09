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

#include "GMSEnergyTimeDerivative.h"

template<>
InputParameters validParams<GMSEnergyTimeDerivative>()
{
    InputParameters params = validParams<TimeDerivative>();
    return params;
}

GMSEnergyTimeDerivative::GMSEnergyTimeDerivative(const InputParameters & parameters)  :
    TimeDerivative(parameters)
{
}

Real
GMSEnergyTimeDerivative::computeQpResidual()
{
    return TimeDerivative::computeQpResidual();
}

Real
GMSEnergyTimeDerivative::computeQpJacobian()
{
    return TimeDerivative::computeQpJacobian();
}
