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

#include "THMaterial.h"

template<>
InputParameters validParams<THMaterial>()
{
    InputParameters params = validParams<Material>();
    MooseEnum stat("constant compressibility wseos", "constant");
    params.addParam<MooseEnum>("fluid_property_formulation", stat, "Fluid property formulation, default=constant");
    MooseEnum stabilizer("none zero supg", "none");
    params.addParam<MooseEnum>("stabilizer", stabilizer, "Energy transport stabilizer, default = none");
    params.addParam<Real>("permeability", 1.0e-12,"Intrinsic permeability [m^2], default = 1.0e-12");
    params.addParam<Real>("porosity", 0.3,"Rock porosity, default = 0.3");
    params.addParam<Real>("compressibility", 1.0e-5,"Total compressibility of the reservoir, default = 1.0e-5");
    params.addParam<Real>("density_rock", 2.50e3,"Rock density [kg/m^3]");
    params.addParam<Real>("gravity", 9.80665,"Gravity acceleration constant [m/s^2], default = 9.80665");
    params.addParam<RealGradient>("gravity_direction", RealGradient(0,0,-1),"Gravity unit directional vector, default = '0 0 -1'");
    params.addParam<RealGradient>("constant_pressure_gradient", RealGradient(0,0,0),"Constant pressure gradient, default = '0 0 0'");
    params.addCoupledVar("pressure","Assign nonlinear variable for pressure [Pa], if mass balance is involved");
    params.addCoupledVar("temperature","Assign nonlinear variable for temperature [K], if energy balance is involved");
    params.addParam<Real>("density_water", 1000,"Initial water density [kg/m^3], default = 1000");
    params.addParam<Real>("viscosity_water", 0.12e-3,"Initial water viscosity [Pa.s], default = 0.12e-3");
    params.addParam<Real>("specific_heat_rock", 0.92e3,"Specific heat of the rock [J/(kg.K)], default = 0.92e3");
    params.addParam<Real>("specific_heat_water", 4.186e3,"Specific heat of water [J/(kg.K)], default = 4.186e3");
    params.addParam<Real>("thermal_conductivity", 2.5,"Thermal conductivity of the reservoir [W/(m.K)], default = 2.5");
    return params;
}

THMaterial::THMaterial(const InputParameters & parameters):
  Material(parameters),
  _istat(getParam<MooseEnum>("fluid_property_formulation")),
  _istab(getParam<MooseEnum>("stabilizer")),
  _has_pres(isCoupled("pressure")),
  _has_temp(isCoupled("temperature")),
//  _pres_dep_perm(getParam<bool>("pressure_dependent_permeability")),
  _iperm(getParam<Real>("permeability")),
  _iporo(getParam<Real>("porosity")),
  _irrho(getParam<Real>("density_rock")),
  _irsph(getParam<Real>("specific_heat_rock")),
  _icomp(getParam<Real>("compressibility")),
  _iwrho(getParam<Real>("density_water")),
  _iwvis(getParam<Real>("viscosity_water")),
  _iwsph(getParam<Real>("specific_heat_water")),
  _ithco(getParam<Real>("thermal_conductivity")),
  _igfor(getParam<Real>("gravity")),
  _igvec(getParam<RealGradient>("gravity_direction")),
  _igrdp(getParam<RealGradient>("constant_pressure_gradient")),
  _pres(_has_pres ? coupledValue("pressure")    : _zero),
  _temp(_has_temp ? coupledValue("temperature") : _zero),
  _grad_pres(_has_pres ? coupledGradient("pressure")    : _grad_zero),
  _grad_temp(_has_temp ? coupledGradient("temperature") : _grad_zero),
  _stat(declareProperty<unsigned int>("fluid_property_formulation")),
  _stab(declareProperty<unsigned int>("stabilization_options")),
  _perm(declareProperty<Real>("permeability")),
  _poro(declareProperty<Real>("porosity")),
  _rrho(declareProperty<Real>("density_rock")),
  _rsph(declareProperty<Real>("specific_heat_rock")),
  _comp(declareProperty<Real>("compressibility")),
  _wrho(declareProperty<Real>("density_water")),
  _wvis(declareProperty<Real>("viscosity_water")),
  _wtau(declareProperty<Real>("tau_water")),
  _wsph(declareProperty<Real>("specific_heat_water")),
  _thco(declareProperty<Real>("thermal_conductivity")),
  _gfor(declareProperty<Real>("gravity")),
  _epor(declareProperty<Real>("porous_media_energy")),
  _drop(declareProperty<Real>("partial_rho_over_partial_pres")),
  _drot(declareProperty<Real>("partial_rho_over_partial_temp")),
  _tau1(declareProperty<Real>("supg_tau1")),
  _guvec(declareProperty<RealGradient>("gravity_direction")),
  _wdflx(declareProperty<RealGradient>("darcy_flux_water")),
  _wdmfx(declareProperty<RealGradient>("darcy_mass_flux_water")),
  _evelo(declareProperty<RealGradient>("energy_convective_velocity"))
{
}

void
THMaterial::computeProperties()
{
    for(_qp=0; _qp<_qrule->n_points(); _qp++)
        computeQpProperties();
}

void
THMaterial::computeQpProperties()
{
    _stat[_qp] = _istat;
    _stab[_qp] = _istab;
    _perm[_qp] = _iperm;
    _poro[_qp] = _iporo;
    _rrho[_qp] = _irrho;
    _rsph[_qp] = _irsph;
    _comp[_qp] = _icomp;
    _wrho[_qp] = _iwrho;
    _wvis[_qp] = _iwvis;
    _wsph[_qp] = _iwsph;
    _thco[_qp] = _ithco;
    _gfor[_qp] = _igfor;
    _epor[_qp] = 0.0;
    _drop[_qp] = 0.0;
    _drot[_qp] = 0.0;
    _tau1[_qp] = 0.0;

    _guvec[_qp] = _igvec;
    gradp = _igrdp;

    if (_has_pres)
        gradp = _grad_pres[_qp];

  // options for calculating variable water properties

  if (_stat[_qp] == 1) // solely T-dependent fluid properties and use compressibility
  {
        if (!_has_pres)
            mooseError("In material GeoProc_PT: missing nonlinear variable for pressure!");
        if (!_has_temp)
            mooseError("In material GeoProc_PT: missing nonlinear variable for temperature!");
        _wrho[_qp] = computeTempBasedWaterDens(_temp[_qp]);
        _wvis[_qp] = computeTempBasedWaterVisc(_temp[_qp]);
        _drot[_qp] = computeTempBasedWaterPartialDensOverPartialTemp(_temp[_qp]);
        _drop[_qp] = _wrho[_qp]*_comp[_qp];
  }
  /*else if (_stat[_qp] == 2) // P-T dependent fluid properties
  {
    if (!_has_pres)
      mooseError("In material GeoProc_PT: missing nonlinear variable for pressure!");
    if (!_has_temp)
      mooseError("In material GeoProc_PT: missing nonlinear variable for temperature!");
    Real inp[2] = {_pres[_qp], _temp[_qp]};
    Real out[2] = {0.0, 0.0};
    Real inpd[2][2] = { {1.0, 0.0}, {0.0, 1.0} };
    Real outd[2][2] = { {0.0, 0.0}, {0.0, 0.0} };
    computeWaterEquationOfStatePT_dv(inp, inpd, out, outd, 2);
    _wrho[_qp] = out[0];
    _drop[_qp] = outd[0][0];
    _drot[_qp] = outd[0][1];
    computeViscosity(_wrho[_qp], _temp[_qp], _wvis[_qp]);
  }
*/
  // water mobility
    _wtau[_qp] = _perm[_qp]/_wvis[_qp];
  // compute the following vectors and use them in kernels and aux kernels
    _wdflx[_qp] = -_wtau[_qp]*(gradp-_wrho[_qp]*_gfor[_qp]*_guvec[_qp]);
    _wdmfx[_qp] =  _wrho[_qp]*_wdflx[_qp];
    _evelo[_qp] =  _wsph[_qp]*_wdmfx[_qp];
    if (_has_temp)
    {
        // to be used in both energy time derivative and residual kernels
        if (_is_transient)
            _epor[_qp] = (1.0-_poro[_qp])*_rrho[_qp]*_rsph[_qp] + _poro[_qp]*_wrho[_qp]*_wsph[_qp];

        // pre-compute a few varialbes upon stabilization options
        if (_stab[_qp] == 1)
            _evelo[_qp] = 0.0;
        else if (_stab[_qp] == 2)
        {
            // Streamline Upwind Petrov Galerkin
            // compute the SUPG h size
            const double hsupg = _current_elem->hmin();

            // compute the energy convective velocity magnitude
            Real amag = _wsph[_qp]*sqrt(_wdmfx[_qp](0)*_wdmfx[_qp](0)+
                                      _wdmfx[_qp](1)*_wdmfx[_qp](1)+
                                      _wdmfx[_qp](2)*_wdmfx[_qp](2));

            // compute the SUPG stabilization parameter: tau1
            _tau1[_qp] = hsupg / (2.0*(amag+1.0e-7));
        }
    }
}

Real
THMaterial::computeTempBasedWaterDens(Real temp)
{
    return  1e3*(1.0-pow(temp-277.1363,2)/508929.2*(temp+15.7914)/(temp-205.02037));
}

Real
THMaterial::computeTempBasedWaterVisc(Real temp)
{
  if (temp>=273.15 && temp<=313.15)
    return 1.787e-3*exp((-0.03288+1.962e-4*(temp-273.15))*(temp-273.15));
  else if (temp>313.15 && temp<=373.15)
    return 0.001*pow(1.0+0.015512*(temp-293.15),-1.572);
  else if (temp>373.15 && temp<=573.15)
    return 0.2414*pow(10.0,247.8/(temp-140)-4.0);
  else
  {
    _console<<"temp = "<<temp-273.15<<" Celsius degree"<<std::endl;
    mooseError("Temperature out of [0, 300] Celsius degree \
               in temperature dependent fluid properties");
  }
  return 0.0;
}

Real
THMaterial::computeTempBasedWaterPartialDensOverPartialTemp(Real temp)
{
  return
  -1e3*(
          2.0*(temp-277.1363)/508929.2*(temp+15.7914)/(temp-205.02037)
        + pow(temp-277.1363,2)/508929.2
          *(1.0/(temp-205.02037)-(temp+15.7914)/pow((temp-205.02037),2))
       );
}


