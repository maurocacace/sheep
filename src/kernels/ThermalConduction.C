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

#include "ThermalConduction.h"

template<>
InputParameters validParams<ThermalConduction>()
{
	InputParameters params = validParams<Kernel>();
	return params;
}

ThermalConduction::ThermalConduction(const InputParameters & parameters)  :
	Kernel(parameters),

	_bulk_thermal_conductivity(getMaterialProperty<Real>("bulk_thermal_conductivity"))
{
}

Real
ThermalConduction::computeQpResidual()
{
	return _bulk_thermal_conductivity[_qp] * _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
ThermalConduction::computeQpJacobian()
{
	return _bulk_thermal_conductivity[_qp] * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}