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

#ifndef THMASSTIMEDERIVATIVE_H
#define THMASSTIMEDERIVATIVE_H

#include "TimeDerivative.h"

class THMassTimeDerivative;

template<>
InputParameters validParams<THMassTimeDerivative>();

class THMassTimeDerivative : public TimeDerivative
{
public:
    THMassTimeDerivative(const InputParameters & parameters);
protected:
    virtual Real computeQpResidual();
    virtual Real computeQpJacobian();
    const MaterialProperty<Real> & _poro;
    const MaterialProperty<Real> & _wrho;
    const MaterialProperty<Real> & _drop;
};

#endif //THMASSTIMEDERIVATIVE_H
