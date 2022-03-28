///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
/*
+----------------------------------------------------------------------------+
|                                                                            |
|                       TcCncToolRadiusCompInterfaces.h                      |
|                                                                            |
|  28.08.2013   CNC     first release                                        |
|  16.09.2013   CNC     unique GUID                                          |
|  29.07.2014   ISG     Added 2nd radius for tool radius compensation.       |
|  13.08.2014   ISG     Caller ID added.                                     |
|  15.08.2014   CN      common EcCncCallerID, TcCncParam                     |
|  27.01.2017   CNC     Version number for TcCOM interfaces.                 |
|                                                                            |
+----------------------------------------------------------------------------+
*/
#pragma once

#define TcCncVersionMinor        1

#include "TcInterfaces.h"
#include "TcCncInterfaces.h"

TCOM_DECL_INTERFACE("6BA03CCD-123F-435D-A3D8-94834700786F", ITcToolRadiusComp)

enum  EcToolRadiusComp
{
  EcToolRadiusComp_ParamInvalid  = 0,
  EcToolRadiusComp_ParamStandard = 1,
};

struct TcToolRadiusCompParam : public TcCncParam
{
  TcToolRadiusCompParam() : type(EcToolRadiusComp_ParamStandard), dimension(0), dim_radius(0), i_path(NULL), i_tangent(NULL), i_tool_direction(NULL), i_radius(NULL), o_path(NULL)
  {
  };
  EcToolRadiusComp    type;
  int                 dimension;         // dimension of positions, 3 or 6 for 2 pathes
  int                 dim_radius;        // dimension of radius, 1 or 2 for 2 pathes
  
  const double      * i_path;            // input: position of path, see dimension
  const double      * i_tangent;         // input: tangent of path, see dimension
  const double      * i_tool_direction;  // input: direction of tool, see dimension
  const double      * i_radius;          // input: actual tool radius, see dim_radius

  double            * o_path;            // output: position of compensated path
};
typedef TcToolRadiusCompParam *PTcToolRadiusCompParam;

struct __declspec(novtable) ITcToolRadiusComp : public ITcUnknown
{
  virtual HRESULT TCOMAPI CalculateTrcPath(PTcToolRadiusCompParam trc)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcToolRadiusComp, IID_ITcToolRadiusComp);

