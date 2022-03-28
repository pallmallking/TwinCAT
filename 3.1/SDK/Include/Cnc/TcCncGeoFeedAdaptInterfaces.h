///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
/*
+----------------------------------------------------------------------------+
|                                                                            |
|                       TcCncGeoFeedAdaptInterfaces.h                        |
|                                                                            |
|  17.04.2015   CNC     ITcGeoFeedAdapt                                      |
|  17.04.2015   CNC     TcCncVersionMinor                                    |
|  15.05.2015   CNC     i_position_theo added.                               |
|  22.05.2015   CNC     i_position_display                                   |
|  21.04.2017   CNC     TcCncVersionMinor        1                           |
|                                                                            |
+----------------------------------------------------------------------------+
*/
#pragma once

#define TcCncVersionMinor        1      // define before header TcCncInterfaces.h

#include "TcInterfaces.h"
#include "TcCncInterfaces.h"

TCOM_DECL_INTERFACE("13FB2CEA-4FE2-4365-B891-F27B13F2906A", ITcGeoFeedAdapt)

enum  EcGeoFeedAdapt
{
  EcGeoFeedAdapt_ParamInvalid  = 0,
  EcGeoFeedAdapt_ParamStandard = 1,
};

struct TcGeoFeedAdaptPath
{
  TcGeoFeedAdaptPath() : i_position_gfa(NULL), i_position_display(NULL)
	{
	};
  // calculation orientation on new sample position: CalculateFeedAdaption()
  const double      * i_position_gfa;       // input : 3-dim actual position of path: X,Y,Z
  const double      * i_position_display;   // input : 3-dim theoretical position of path: X,Y,Z
};
struct TcGeoFeedAdaptParam : public TcCncParam
{
  TcGeoFeedAdaptParam() : type(EcGeoFeedAdapt_ParamStandard), dim_tool_param(0), i_tool_param(NULL), o_feed_adaption(NULL)
	{
	};
  EcGeoFeedAdapt      type;                  // config: EcGeoFeedAdapt_ParamStandard
  int                 dim_path;              // config: dimension of path : 1 or 2
  int                 dim_tool_param;        // config: dimension of tool parameter

  const double      * i_tool_param;          // input : <dim_tool_param>-dim actual parameter of tool

  double            * o_feed_adaption;       // output: 

  struct TcGeoFeedAdaptPath path[2];
};
typedef TcGeoFeedAdaptParam *PTcGeoFeedAdaptParam;

typedef TcGeoFeedAdaptParam *PTcGeoFeedAdaptParam;

struct __declspec(novtable) ITcGeoFeedAdapt : public ITcUnknown // , ITcCncBase
{
  virtual HRESULT TCOMAPI CalculateFeedAdaption  (PTcGeoFeedAdaptParam dcc)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcGeoFeedAdapt, IID_ITcGeoFeedAdapt);

