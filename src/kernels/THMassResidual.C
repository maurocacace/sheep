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

#include "THMassResidual.h"

template<>
InputParameters validParams<THMassResidual>()
{
    InputParameters params = validParams<Kernel>();
    params.addCoupledVar("coupled_temperature","This coupled variable will be used as temperature");
    return params;
}

THMassResidual::THMassResidual(const InputParameters & parameters):
    Kernel(parameters),
    _has_coupled_temp(isCoupled("coupled_temperature")),
    _wrho(getMaterialProperty<Real>("density_water")),
    _wtau(getMaterialProperty<Real>("tau_water")),
    _gfor(getMaterialProperty<Real>("gravity")),
    _drot(getMaterialProperty<Real>("partial_rho_over_partial_temp")),
    _guvec(getMaterialProperty<RealGradient>("gravity_direction")),
    _wdmfx(getMaterialProperty<RealGradient>("darcy_mass_flux_water")),
    _temp_var(_has_coupled_temp ? coupled("coupled_temperature") : zero)
{
}

Real
THMassResidual::computeQpResidual()
{
    return -_wdmfx[_qp]*_grad_test[_i][_qp];
}

Real
THMassResidual::computeQpJacobian()
{
    Real r = 0.0;
    // contribution from Darcy mass flux due to pressure gradient
    r += _wtau[_qp]*_wrho[_qp]*_grad_phi[_j][_qp]*_grad_test[_i][_qp];
    // contribution from Darcy mass flux due to elevation ... omitted
    return r;
}

Real
THMassResidual::computeQpOffDiagJacobian(unsigned int jvar)
{
    Real r = 0.0;
    // contribution from Darcy mass flux due to pressure gradient ... omitted
    // contribution from Darcy mass flux due to elevation
    if (jvar == _temp_var && _has_coupled_temp)
        r += 2.0 * _wtau[_qp] * _wrho[_qp] * _drot[_qp] * _phi[_j][_qp] * _gfor[_qp] * (_guvec[_qp] * _grad_test[_i][_qp]);
    return r;
}
