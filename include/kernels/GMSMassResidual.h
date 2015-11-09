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

#ifndef GMSMASSRESIDUAL_H
#define GMSMASSRESIDUAL_H

#include "Kernel.h"

class GMSMassResidual;

template<>
InputParameters validParams<GMSMassResidual>();

class GMSMassResidual : public Kernel
{
public:
    GMSMassResidual(const InputParameters & parameters);
protected:
    virtual Real computeQpResidual();
    virtual Real computeQpJacobian();
    const MaterialProperty<Real> & _rho_b;
    const MaterialProperty<RealVectorValue> & _gravity;
};

#endif //GMSMASSRESIDUAL_H
