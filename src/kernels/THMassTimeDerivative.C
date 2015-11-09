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

#include "THMassTimeDerivative.h"

template<>
InputParameters validParams<THMassTimeDerivative>()
{
    InputParameters params = validParams<TimeDerivative>();
    return params;
}

THMassTimeDerivative::THMassTimeDerivative(const InputParameters & parameters)  :
    TimeDerivative(parameters),
    _poro(getMaterialProperty<Real>("porosity")),
    _wrho(getMaterialProperty<Real>("density_water")),
    _drop(getMaterialProperty<Real>("partial_rho_over_partial_pres"))
{
}

Real
THMassTimeDerivative::computeQpResidual()
{
    return _poro[_qp] * _drop[_qp] * TimeDerivative::computeQpResidual();
}

Real
THMassTimeDerivative::computeQpJacobian()
{
    return _poro[_qp] * _drop[_qp] *  TimeDerivative::computeQpJacobian();
}
