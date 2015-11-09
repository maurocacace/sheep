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

#include "GMSMaterial.h"

template<>
InputParameters validParams<GMSMaterial>()
{
    InputParameters params = validParams<Material>();
    params.addClassDescription("material class to run steady pressure load and steady/transient heat with parameters from file");
    params.addCoupledVar("temperature", "temperature");
    params.addCoupledVar("load", "load");
    params.addParam<Real>("density", "The bulk density");
    params.addParam<Real>("thermal_conductivity", "The bulk thermal conductivity");
    params.addParam<Real>("heat_capacity", "The bulk heat capacity");
    params.addParam<Real>("heat_production", "The heat production");
    params.addParam<Real>("scale_factor", "The scale factor");
    params.addParam<UserObjectName> ("read_prop_user_object", "The ReadPropertyFile GeneralUserObject to read specific property values from file");
    return params;
}

GMSMaterial::GMSMaterial(const InputParameters & parameters) :
    Material(parameters),
    // Coupled variables
    _is_temp_coupled(isCoupled("temperature")),
    _is_load_coupled(isCoupled("load")),
    // Parameters
    _rho_b(_is_load_coupled || _fe_problem.isTransient() ? getParam<Real>("density") : 0.),
    _lambda_b(_is_temp_coupled ? getParam<Real>("thermal_conductivity") : 0.),
    _c_b(_is_temp_coupled && _fe_problem.isTransient() ? getParam<Real>("heat_capacity") : 0.),
    _h_prod(_is_temp_coupled ? getParam<Real>("heat_production") : 0.),
    _scale_factor(_is_temp_coupled &&  _fe_problem.isTransient() ? getParam<Real>("scale_factor") : 1.),
    _read_prop_user_object(isParamValid("read_prop_user_object") ? & getUserObject<PropertyReadFile>("read_prop_user_object") : NULL),
    // Properties
    _bulk_density(declareProperty<Real>("bulk_density")),
    _bulk_thermal_conductivity(declareProperty<Real>("bulk_thermal_conductivity")),
    _bulk_specific_heat(declareProperty<Real>("bulk_specific_heat")),
    _heat_production(declareProperty<Real>("heat_production")),
    _scale(declareProperty<Real>("scale_factor")),
    _gravity(declareProperty<RealVectorValue>("gravity")),
    _bulk_density_old(declarePropertyOld<Real>("bulk_density")),
    _bulk_thermal_conductivity_old(declarePropertyOld<Real>("bulk_thermal_conductivity")),
    _bulk_specific_heat_old(declarePropertyOld<Real>("bulk_specific_heat")),
    _heat_production_old(declarePropertyOld<Real>("heat_production")),
    _scale_old(declarePropertyOld<Real>("scale_factor"))
{
}

void
GMSMaterial::initQpStatefulProperties()
{
    _bulk_density[_qp] = 0.0;
    _bulk_thermal_conductivity[_qp] = 0.0;
    _bulk_specific_heat[_qp] = 0.0;
    _heat_production[_qp] = 0.0;
    if ( _read_prop_user_object ){
        _bulk_density[_qp] =  _read_prop_user_object->getData(_current_elem, 0);
        _bulk_thermal_conductivity[_qp] = _read_prop_user_object->getData(_current_elem, 1);
        _bulk_specific_heat[_qp] = _read_prop_user_object->getData(_current_elem, 2);
        _heat_production[_qp] = _read_prop_user_object->getData(_current_elem, 3);
    }else{
        _bulk_density[_qp] = _rho_b;
        _bulk_thermal_conductivity[_qp] = _lambda_b;
        _bulk_specific_heat[_qp] =  _c_b;
        _heat_production[_qp] = _h_prod;
    }
    _scale[_qp] = _scale_old[_qp] = _scale_factor;
    if (_mesh.dimension() == 3)
        _gravity[_qp] = RealVectorValue(0., 0., -9.81);
    else if (_mesh.dimension() == 2)
        _gravity[_qp] = RealVectorValue(0., -9.81, 0.);
    else
        _gravity[_qp] = RealVectorValue(-9.81, 0., 0.);
}

void
GMSMaterial::computeQpProperties()
{
    if ( _read_prop_user_object ){
        _bulk_density[_qp] = _bulk_density_old[_qp];
        _bulk_thermal_conductivity[_qp] = _bulk_thermal_conductivity_old[_qp];
        _bulk_specific_heat[_qp] = _bulk_specific_heat_old[_qp];
        _heat_production[_qp] = _heat_production_old[_qp];
    }
    else{
        _bulk_density[_qp] = _rho_b;
        _bulk_thermal_conductivity[_qp] = _lambda_b;
        _bulk_specific_heat[_qp] = _c_b;
        _heat_production[_qp] = _h_prod;
    }
    _scale[_qp] = _scale_factor;
    if (_mesh.dimension() == 3)
        _gravity[_qp] = RealVectorValue(0., 0., -9.81);
    else if (_mesh.dimension() == 2)
        _gravity[_qp] = RealVectorValue(0., -9.81, 0.);
    else
        _gravity[_qp] = RealVectorValue(-9.81, 0., 0.);
}
