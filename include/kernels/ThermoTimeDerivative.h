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

#ifndef THERMOTIMEDERIVATIVE_H
#define THERMOTIMEDERIVATIVE_H

#include "TimeKernel.h"

class ThermoTimeDerivative;

template<>
InputParameters validParams<ThermoTimeDerivative>();

class ThermoTimeDerivative : public TimeKernel
{
public:
	ThermoTimeDerivative(const InputParameters & parameters);
	virtual void computeJacobian();

protected:
	virtual Real computeQpResidual();
	virtual Real computeQpJacobian();

	bool _lumping;
	const MaterialProperty<Real> & _bulk_specific_heat;
};

#endif //THERMOTIMEDERIVATIVE_H
