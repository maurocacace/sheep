/****************************************************************/
/*             DO NOT MODIFY OR REMOVE THIS HEADER              */
/*          FALCON - Fracturing And Liquid CONvection           */
/*                                                              */
/*       (c)     2012 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef THENERGYRESIDUAL_H
#define THENERGYRESIDUAL_H

#include "Kernel.h"
#include "Material.h"

class THEnergyResidual;

template<>
InputParameters validParams<THEnergyResidual>();

class THEnergyResidual : public Kernel
{
public:
    THEnergyResidual(const InputParameters & parameters);
protected:
    virtual Real computeQpResidual();
    virtual Real computeQpJacobian();

    bool _has_coupled_pres;
    const MaterialProperty<unsigned int> & _stab;
    const MaterialProperty<Real> & _thco;
    const MaterialProperty<Real> & _wsph;
    const MaterialProperty<Real> & _epor;
    const MaterialProperty<Real> & _tau1;
    const MaterialProperty<RealGradient> & _wdmfx;
    const MaterialProperty<RealGradient> & _evelo;
private:
    unsigned int _pres_var;
    Real r;
    Real sres;
};

#endif //THENERGYRESIDUAL_H
