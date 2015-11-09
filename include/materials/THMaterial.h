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

#ifndef THMATERIAL_H
#define THMATERIAL_H

#include "Material.h"

class THMaterial;

template<>
InputParameters validParams<THMaterial>();

class THMaterial : public Material
{
public:
    THMaterial(const InputParameters & parameters);
protected:
    virtual void computeProperties();
    virtual void computeQpProperties();
    Real computeTempBasedWaterDens(Real temp);
    Real computeTempBasedWaterVisc(Real temp);
    Real computeTempBasedWaterPartialDensOverPartialTemp(Real temp);
    MooseEnum _istat; // fluid property formulation
    MooseEnum _istab; // stabilization
    // coupled variables
    bool _has_pres; // pressure-based mass balance equation
    bool _has_temp; // temperature-based energy balance equation
    // Parameters
    Real _iperm;
    Real _iporo;
    Real _irrho;
    Real _irsph;
    Real _icomp;
    Real _iwrho;
    Real _iwvis;
    Real _iwsph;
    Real _ithco;
    Real _igfor;
    RealGradient _igvec; // gravity unidirectional vector
    RealGradient _igrdp; // pressure gradient
    // Coupled variables
    VariableValue & _pres; // pressure
    VariableValue & _temp; // temperature
    VariableGradient & _grad_pres; // pressure gradient
    VariableGradient & _grad_temp; // temperature gradient
    // Properties
    MaterialProperty<unsigned int> & _stat; // fluid property formulation
    MaterialProperty<unsigned int> & _stab; // stabilization options
    MaterialProperty<Real> & _perm;
    MaterialProperty<Real> & _poro;
    MaterialProperty<Real> & _rrho;
    MaterialProperty<Real> & _rsph;
    MaterialProperty<Real> & _comp;
    MaterialProperty<Real> & _wrho;
    MaterialProperty<Real> & _wvis;
    MaterialProperty<Real> & _wtau;
    MaterialProperty<Real> & _wsph;
    MaterialProperty<Real> & _thco;
    MaterialProperty<Real> & _gfor;
    MaterialProperty<Real> & _epor;
    MaterialProperty<Real> & _drop;
    MaterialProperty<Real> & _drot;
    MaterialProperty<Real> & _tau1;
    MaterialProperty<RealGradient> & _guvec;
    MaterialProperty<RealGradient> & _wdflx;
    MaterialProperty<RealGradient> & _wdmfx;
    MaterialProperty<RealGradient> & _evelo;
private:
    RealGradient gradp;
};

#endif // THMATERIAL_H
