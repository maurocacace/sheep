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

#ifndef GMSENERGYRESIDUAL_H
#define GMSENERGYRESIDUAL_H

#include "Kernel.h"

class GMSEnergyResidual;

template<>
InputParameters validParams<GMSEnergyResidual>();

class GMSEnergyResidual : public Kernel
{
public:
    GMSEnergyResidual(const InputParameters & parameters);
protected:
    virtual Real computeQpResidual();
    virtual Real computeQpJacobian();
    const MaterialProperty<Real> & _bulk_thermal_conductivity;
    const MaterialProperty<Real> & _heat_production;
    const MaterialProperty<Real> & _bulk_specific_heat;
    const MaterialProperty<Real> & _bulk_density;
    const MaterialProperty<Real> & _scale_factor;
};

#endif //GMSENERGYRESIDUAL_H
