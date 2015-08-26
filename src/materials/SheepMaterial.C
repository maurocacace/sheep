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

#include "SheepMaterial.h"

template<>
InputParameters validParams<SheepMaterial>()
{
	InputParameters params = validParams<Material>();

	params.addCoupledVar("temperature", "temperature");
	params.addCoupledVar("load", "load");
	params.addParam<Real>("bulk_density", "The bulk density");
    params.addParam<Real>("bulk_thermal_conductivity", "The bulk thermal conductivity");
    params.addParam<Real>("bulk_heat_capacity", "The bulk heat capacity");
     
	return params;
}

SheepMaterial::SheepMaterial(const InputParameters & parameters) :
	Material(parameters),

	// Coupled variables
	_is_temp_coupled(isCoupled("temperature")),
	_is_load_coupled(isCoupled("load")),

	// Parameters
	_rho_b(_is_load_coupled || _fe_problem.isTransient() ? getParam<Real>("bulk_density") : 0.),
	_lambda_b(_is_temp_coupled ? getParam<Real>("bulk_thermal_conductivity") : 0.),
	_c_b(_is_temp_coupled && _fe_problem.isTransient() ? getParam<Real>("bulk_heat_capacity") : 0.),

	// Properties
	_bulk_density(declareProperty<Real>("bulk_density")),
	_bulk_thermal_conductivity(declareProperty<Real>("bulk_thermal_conductivity")),
	_bulk_specific_heat(declareProperty<Real>("bulk_specific_heat")),
	_gravity(declareProperty<RealVectorValue>("gravity"))
{
}

void
SheepMaterial::computeQpProperties()
{
	_bulk_density[_qp] = _rho_b;
	_bulk_thermal_conductivity[_qp] = _lambda_b;
	_bulk_specific_heat[_qp] = _rho_b * _c_b;

	if (_mesh.dimension() == 3)
		_gravity[_qp] = RealVectorValue(0., 0., -9.81);
	else if (_mesh.dimension() == 2)
		_gravity[_qp] = RealVectorValue(0., -9.81, 0.);
	else
		_gravity[_qp] = RealVectorValue(-9.81, 0., 0.);

}