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

#ifndef THMASSRESIDUAL_H
#define THMASSRESIDUAL_H

#include "Kernel.h"

class THMassResidual;

template<>
InputParameters validParams<THMassResidual>();

class THMassResidual : public Kernel
{
public:
    THMassResidual(const InputParameters & parameters);
protected:
    virtual Real computeQpResidual();
    virtual Real computeQpJacobian();
    virtual Real computeQpOffDiagJacobian(unsigned int jvar);
    bool _has_coupled_temp;
    const MaterialProperty<Real> & _wrho;
    const MaterialProperty<Real> & _wtau;
    const MaterialProperty<Real> & _gfor;
    const MaterialProperty<Real> & _drot;
    const MaterialProperty<RealGradient> & _guvec;
    const MaterialProperty<RealGradient> & _wdmfx;
private:
    unsigned int _temp_var;
};

#endif //THMASSRESIDUAL_H
