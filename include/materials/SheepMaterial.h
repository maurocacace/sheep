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

#ifndef SHEEPMATERIAL_H
#define SHEEPMATERIAL_H

#include "Material.h"

class SheepMaterial;

template<>
InputParameters validParams<Material>();

class SheepMaterial : public Material
{
public:
	SheepMaterial(const InputParameters & parameters);

protected:
	virtual void computeQpProperties();

    // Coupled vars
    bool _is_temp_coupled;
    bool _is_load_coupled;
    
    // Parameters
    Real _rho_b;
    Real _lambda_b;
    Real _c_b;

    // Properties
    MaterialProperty<Real> & _bulk_density;
    MaterialProperty<Real> & _bulk_thermal_conductivity;
    MaterialProperty<Real> & _bulk_specific_heat;
    MaterialProperty<RealVectorValue> & _gravity;
};

#endif //SHEEPMATERIAL_H