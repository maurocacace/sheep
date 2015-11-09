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

#include "GMSMassResidual.h"

template<>
InputParameters validParams<GMSMassResidual>()
{
    InputParameters params = validParams<Kernel>();
    return params;
}

GMSMassResidual::GMSMassResidual(const InputParameters & parameters)  :
    Kernel(parameters),
    _rho_b(getMaterialProperty<Real>("bulk_density")),
    _gravity(getMaterialProperty<RealVectorValue>("gravity"))
{
}

Real
GMSMassResidual::computeQpResidual()
{
    return (_grad_u[_qp] - _rho_b[_qp] * _gravity[_qp]) * _grad_test[_i][_qp];
}

Real
GMSMassResidual::computeQpJacobian()
{
    return _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}
