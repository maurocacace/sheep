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

#include "GMSEnergyResidual.h"

template<>
InputParameters validParams<GMSEnergyResidual>()
{
    InputParameters params = validParams<Kernel>();
    return params;
}

GMSEnergyResidual::GMSEnergyResidual(const InputParameters & parameters)  :
    Kernel(parameters),
    _bulk_thermal_conductivity(getMaterialProperty<Real>("bulk_thermal_conductivity")),
    _heat_production(getMaterialProperty<Real>("heat_production")),
    _bulk_specific_heat(getMaterialProperty<Real>("bulk_specific_heat")),
    _bulk_density(getMaterialProperty<Real>("bulk_density")),
    _scale_factor(getMaterialProperty<Real>("scale_factor"))
{
}

Real
GMSEnergyResidual::computeQpResidual()
{
    Real diff;
    Real e_source;
    if(_fe_problem.isTransient())
    {
        diff = _scale_factor[_qp] * _bulk_thermal_conductivity[_qp] / (_bulk_density[_qp] * _bulk_specific_heat[_qp]);
        e_source = _scale_factor[_qp] * _heat_production[_qp] / (_bulk_density[_qp] * _bulk_specific_heat[_qp]);
    }
    else
    {
        diff = _bulk_thermal_conductivity[_qp];
        e_source = _heat_production[_qp];
    }
    return diff * _grad_u[_qp] * _grad_test[_i][_qp] - e_source * _test[_i][_qp];
}

Real
GMSEnergyResidual::computeQpJacobian()
{
    Real diff;
    if(_fe_problem.isTransient())
        diff = _scale_factor[_qp] * _bulk_thermal_conductivity[_qp] / (_bulk_density[_qp] * _bulk_specific_heat[_qp]);
    else
        diff = _bulk_thermal_conductivity[_qp];
    return diff * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}
