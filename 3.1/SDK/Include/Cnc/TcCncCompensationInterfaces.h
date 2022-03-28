///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
/*
+----------------------------------------------------------------------------+
|                                                                            |
|                       TcCncCompensationInterfaces.h                        |
|                                                                            |
+----------------------------------------------------------------------------+
*/
#pragma once

#define TcCncVersionMinor        1      // define before header TcCncInterfaces.h

#include "TcInterfaces.h"
#include "TcCncInterfaces.h"

TCOM_DECL_INTERFACE("2A927EA0-848A-40CA-8CC0-D0DE69921AA3", ITcMcComExtComp)

enum eMcComExtCompParameter
{
  eMcComExtCompParameter_Invalid = 0,
  eMcComExtCompParameter_Standard = 1,
};

struct TcMcComBase
{

  double ret_value1;   // out: additional error value
  double ret_value2;   // out: additional error value
  char   ret_text[24]; // out: additional error text, max. 24 byte
};

struct TcMcComExtCompParameter : public TcMcComBase
{
  TcMcComExtCompParameter() : type(eMcComExtCompParameter_Standard),cyclic_i(0),dim_cyclic_i(0),cyclic_o(0),dim_cyclic_o(0),parameters(0),dim_parameters(0)
  {
  }
  eMcComExtCompParameter  type;
  signed __int64* cyclic_i;
  long dim_cyclic_i;

  signed __int64* cyclic_o;
  long dim_cyclic_o;

  signed __int64* parameters;
  long dim_parameters;

};

typedef TcMcComExtCompParameter* PTcMcComExtCompParameter;

struct TcMcComCmdParameter : public TcMcComBase
{
  char   para_string[24];
  double para_value;
};

typedef TcMcComCmdParameter* PTcMcComCmdParameter;

struct __declspec(novtable) ITcMcComExtComp : public ITcUnknown
{
  virtual HRESULT TCOMAPI computeStartOffsets(PTcMcComExtCompParameter p) = 0;

  virtual HRESULT TCOMAPI computeOffsets(PTcMcComExtCompParameter p) = 0;

  virtual HRESULT TCOMAPI writeNcCmd(PTcMcComCmdParameter s) = 0;

  virtual HRESULT TCOMAPI initCompensation(PTcMcComExtCompParameter p) = 0;

};

//typedef ITcMcComExtComp* ITcMcComExtCompPtr;

_TCOM_SMARTPTR_TYPEDEF(ITcMcComExtComp, IID_ITcMcComExtComp);

#define DECLARE_ITCCNCCOMPENSATION() 
#define IMPLEMENT_ITCCNCCOMPENSATION(theClass)
