/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "PropertyReadFile.h"

template<>
InputParameters validParams<PropertyReadFile>()
{
    InputParameters params = validParams<GeneralUserObject>();
    params.addClassDescription("User Object to read property data from an external file and assign to elements");
    params.addParam<std::string>("prop_file_name", "", "Name of the property file name");
    params.addParam<unsigned int>("nprop", 0, "number of property to read");
    params.addParam<unsigned int>("nx", 0, "Number of nodes along the x-direction (block-wise)");
    params.addParam<unsigned int>("ny", 0, "Number of nodes along the y-direction (block-wise)");
    params.addParam<unsigned int>("nz", 0, "Number of nodes along the z-direction (block-wise)");
    return params;
}

PropertyReadFile::PropertyReadFile(const InputParameters & parameters) :
    GeneralUserObject(parameters),
    _prop_file_name(getParam<std::string>("prop_file_name")),
    _nprop(getParam<unsigned int>("nprop")),
    _nx(getParam<unsigned int>("nx")),
    _ny(getParam<unsigned int>("ny")),
    _nz(getParam<unsigned int>("nz"))
{
    _npoint = _nx * _ny * _nz;
    _nelem = (_nx - 1) * (_ny - 1) * _nz;
    readData();
}

void
PropertyReadFile::readData()
{
    _data.resize(4 * _npoint);
    MooseUtils::checkFileReadable(_prop_file_name);
    std::ifstream file_prop;
    file_prop.open(_prop_file_name.c_str());
    for ( unsigned int i=0; i < _npoint; ++i )
        for( unsigned int j = 0; j < _nprop; ++j)
            if(!(file_prop >> _data[i*_nprop + j]))
                mooseError("Error PropertyReadFile : Premature end of file");
    file_prop.close();
    setEleData();
}

void
PropertyReadFile::setEleData()
{
    _Eledata.resize(_nelem * 4);
    unsigned int _c1, _c2, _c3, _c4;
    unsigned int _count_elem = 0;
    Real _prop = 0.0;
    for(unsigned int k = 0; k < _nz; ++k){
        for(unsigned int i = 0; i < _ny - 1; ++i){
            for(unsigned int j = 0; j < _nx - 1; ++j){
                _prop = 0.0;
                _c1 = (k + 0) * (_ny * _nx) + (i + 0) * _nx + j + 0;
                _c2 = (k + 0) * (_ny * _nx) + (i + 0) * _nx + j + 1;
                _c3 = (k + 0) * (_ny * _nx) + (i + 1) * _nx + j + 1;
                _c4 = (k + 0) * (_ny * _nx) + (i + 1) * _nx + j + 0;
                for(unsigned int p = 0; p < _nprop; ++p){
                    _prop = (_data[_c1*_nprop + p] + _data[_c2*_nprop + p] + _data[_c3*_nprop + p] + _data[_c4*_nprop + p]) / 4.0;
                    _Eledata[_count_elem*_nprop + p] = _prop;
                }
                _count_elem++;
            }
        }
    }
}

Real
PropertyReadFile::getData(const Elem * elem, unsigned int prop_num) const
{
    unsigned int jelem = elem->id();
    mooseAssert( jelem < _nelem, "Error PropertyReadFile: Element " << jelem << " greater than total number of block elements " << _ele_id[_nelem - 1]);
    mooseAssert( prop_num < _nprop, "Error PropertyReadFile: Property number " << prop_num << " greater than total number of properties " << 4);
    return _Eledata[jelem * _nprop + prop_num];
}

