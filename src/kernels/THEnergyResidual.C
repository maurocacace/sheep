/****************************************************************/
/*             DO NOT MODIFY OR REMOVE THIS HEADER              */
/*          FALCON - Fracturing And Liquid CONvection           */
/*                                                              */
/*       (c)     2012 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "THEnergyResidual.h"

template<>
InputParameters validParams<THEnergyResidual>()
{
    InputParameters params = validParams<Kernel>();
    params.addCoupledVar("coupled_pressure","This coupled variable will be used as pressure");
    return params;
}

THEnergyResidual::THEnergyResidual(const InputParameters & parameters):
    Kernel(parameters),
    _has_coupled_pres(isCoupled("coupled_pressure")),
    _stab(getMaterialProperty<unsigned int>("stabilization_options")),
    _thco(getMaterialProperty<Real>("thermal_conductivity")),
    _wsph(getMaterialProperty<Real>("specific_heat_water")),
    _epor(getMaterialProperty<Real>("porous_media_energy")),
    _tau1(getMaterialProperty<Real>("supg_tau1")),
    _wdmfx(getMaterialProperty<RealGradient>("darcy_mass_flux_water")),
    _evelo(getMaterialProperty<RealGradient>("energy_convective_velocity")),
    _pres_var(_has_coupled_pres ? coupled("coupled_pressure") : zero)
{
}

Real
THEnergyResidual::computeQpResidual()
{
  r = _thco[_qp] * _grad_u[_qp] * _grad_test[_i][_qp];
  r += -_evelo[_qp] * _u[_qp] * _grad_test[_i][_qp];
  if (_stab[_qp] == 2)
  {
    sres = _epor[_qp]*_u_dot[_qp] + _evelo[_qp]*_grad_u[_qp];     // strong-form residual = time derivative + convection
    r += _tau1[_qp] * _evelo[_qp] * sres * _grad_test[_i][_qp];   // SUPG stabilization term
  }
  return r;
}

Real
THEnergyResidual::computeQpJacobian()
{
  r = _thco[_qp] * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
  r += -_evelo[_qp] * _phi[_j][_qp] * _grad_test[_i][_qp];
  if (_stab[_qp] == 2)
  {
    sres = _epor[_qp]*_phi[_j][_qp]*_du_dot_du[_qp] + _evelo[_qp]*_grad_phi[_j][_qp];
    r += _tau1[_qp] * _evelo[_qp] * sres * _grad_test[_i][_qp];
  }
  return r;
}
