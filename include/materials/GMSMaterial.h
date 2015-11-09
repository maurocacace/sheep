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
#ifndef GMSMATERIAL_H
#define GMSMATERIAL_H

#include "Material.h"
#include "PropertyReadFile.h"

class GMSMaterial;

template<>
InputParameters validParams<Material>();

class GMSMaterial : public Material
{
public:
    GMSMaterial(const InputParameters & parameters);
protected:
    virtual void initQpStatefulProperties();
    virtual void computeQpProperties();
    // Coupled vars
    bool _is_temp_coupled;
    bool _is_load_coupled;
    // Parameters
    Real _rho_b;
    Real _lambda_b;
    Real _c_b;
    Real _h_prod;
    Real _scale_factor;
    // user object variable
    const PropertyReadFile * _read_prop_user_object;
    // Properties
    MaterialProperty<Real> & _bulk_density;
    MaterialProperty<Real> & _bulk_thermal_conductivity;
    MaterialProperty<Real> & _bulk_specific_heat;
    MaterialProperty<Real> & _heat_production;
    MaterialProperty<Real> & _scale;
    MaterialProperty<RealVectorValue> & _gravity;
    MaterialProperty<Real> & _bulk_density_old;
    MaterialProperty<Real> & _bulk_thermal_conductivity_old;
    MaterialProperty<Real> & _bulk_specific_heat_old;
    MaterialProperty<Real> & _heat_production_old;
    MaterialProperty<Real> & _scale_old;
};

#endif //GMSMATERIAL_H
