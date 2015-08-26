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

#ifndef THERMALCONDUCTION_H
#define THERMALCONDUCTION_H

#include "Kernel.h"

class ThermalConduction;

template<>
InputParameters validParams<ThermalConduction>();

class ThermalConduction : public Kernel
{
public:
	ThermalConduction(const InputParameters & parameters);

protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();

	const MaterialProperty<Real> & _bulk_thermal_conductivity;
};

#endif //THERMALCONDUCTION_H