/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef PROPERTYREADFILE_H
#define PROPERTYREADFILE_H

#include "GeneralUserObject.h"

/**
 * Read properties from file
 * Input file syntax: prop1 prop2 etc ...
*/

class PropertyReadFile;

template<>
InputParameters validParams<PropertyReadFile>();

class PropertyReadFile : public GeneralUserObject
{
public:
    PropertyReadFile(const InputParameters & parameters);
    virtual ~PropertyReadFile() {}
    virtual void initialize() {}
    virtual void execute() {}
    virtual void finalize() {}
    void readData();
    void setEleData();
    Real getData(const Elem * , unsigned int) const;
protected:
    std::string _prop_file_name;
    std::vector<Real> _data;
    std::vector<Real> _Eledata;
    unsigned int _nprop;
    unsigned int _nx;
    unsigned int _ny;
    unsigned int _nz;
private:
    unsigned int _npoint;
    unsigned int _nelem;
};

#endif // PROPERTYREADFILE_H
