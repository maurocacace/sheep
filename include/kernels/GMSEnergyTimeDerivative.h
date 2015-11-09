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

#ifndef GMSENERGYTIMEDERIVATIVE_H
#define GMSENERGYTIMEDERIVATIVE_H

#include "TimeDerivative.h"

class GMSEnergyTimeDerivative;

template<>
InputParameters validParams<GMSEnergyTimeDerivative>();

class GMSEnergyTimeDerivative : public TimeDerivative
{
public:
    GMSEnergyTimeDerivative(const InputParameters & parameters);
protected:
    virtual Real computeQpResidual();
    virtual Real computeQpJacobian();
};

#endif //GMSENERGYTIMEDERIVATIVE_H
