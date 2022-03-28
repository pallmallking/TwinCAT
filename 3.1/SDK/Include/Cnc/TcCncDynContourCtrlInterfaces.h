///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
/*
+----------------------------------------------------------------------------+
|                                                                            |
|                       TcCncDynContourCtrlInterfaces.h                      |
|                                                                            |
|  27.02.2015   CNC     ITcDynContourCtrl                                    |
|  12.03.2015   CNC     CalculateOffset, EtDcc_Standstill_Linear/Circular    |
|  17.03.2015   CNC     TcDynContourCtrlPath, EtDcc_Position_Change          |
|  19.03.2015   CNC     norm_factor, orientation_mcs/pcs                     |
|  27.01.2017   CNC     Version number for TcCOM interfaces.                 |
|                                                                            |
+----------------------------------------------------------------------------+
*/
#pragma once

#define TcCncVersionMinor        1      // define before header TcCncInterfaces.h

#include "TcInterfaces.h"
#include "TcCncInterfaces.h"

TCOM_DECL_INTERFACE("7C185AB5-9B54-4B30-883A-DD4262370DD9", ITcDynContourCtrl)

enum  EcDynContourCtrl
{
  EcDynContourCtrl_ParamInvalid  = 0,
  EcDynContourCtrl_ParamStandard = 1,
};
enum EtDynContourCtrl
{
  EtDcc_Position_Change     = 0,
  EtDcc_Standstill_Linear   = 1,
  EtDcc_Standstill_Circular = 2,
  EtDcc_Linear_Linear       = 3,
  EtDcc_Circular_Linear     = 4,
  EtDcc_Linear_Circular     = 5,
  EtDcc_Circular_Circular   = 6
};

struct TcDynContourCtrlPath
{
  TcDynContourCtrlPath() : i_element_type(EtDcc_Position_Change), i_circle_radius(0), i_tangent_variation(0), o_norm_factor(NULL), i_norm_factor(NULL), i_position(NULL), o_orientation_pcs(NULL), i_orientation_mcs(NULL), o_offset(NULL)
	{
	};
  // calculation on new block: CalculateOnNewGeometry()
  int                 i_element_type;        // input : <dim_path>-dim type of element, see enum EtDynContourCtrl
  double              i_circle_radius;       // input : radius of circle
  double              i_tangent_variation;   // input : actual tangent change (== 0 for C1-continuous contour elements), in radiant
  double            * o_norm_factor;         // output: <dim_path>-dim tangent rotation factor, dependent on geometry and technology (tool param): X0

  // calculation orientation on new sample position: CalculateOrientation()
  const double      * i_norm_factor;         // input : <dim_path>-dim normalization factor: X0
  const double      * i_position;            // input : 3-dim actual position of path: X,Y,Z
  double            * o_orientation_pcs;     // output: 3-dim normalized orientation vector of path, in programing coordinate system PCS

  // calculation offset : CalculateOffset()
  double            * i_orientation_mcs;     // input : 3-dim normalized offset vector of path, in machine coordinate system MCS
  double            * o_offset;              // output: 3-dim offset of path, in MCS
};
struct TcDynContourCtrlParam : public TcCncParam
{
  TcDynContourCtrlParam() : type(EcDynContourCtrl_ParamStandard), dim_tool_param(0), i_tool_param(NULL)
	{
	};
  EcDynContourCtrl    type;                  // config: EcDynContourCtrl_ParamStandard
  int                 dim_path;              // config: dimension of path : 1 or 2
  int                 dim_tool_param;        // config: dimension of tool parameter

  const double      * i_tool_param;          // input : <dim_tool_param>-dim actual parameter of tool
  double              i_velocity;            // input : path velocity [m/s]

  struct TcDynContourCtrlPath path[2];
};
typedef TcDynContourCtrlParam *PTcDynContourCtrlParam;

struct __declspec(novtable) ITcDynContourCtrl : public ITcUnknown
{
  virtual HRESULT TCOMAPI CalculateOnNewGeometry  (PTcDynContourCtrlParam dcc)=0;
  virtual HRESULT TCOMAPI CalculateOrientation    (PTcDynContourCtrlParam dcc)=0;
  virtual HRESULT TCOMAPI CalculateOffset         (PTcDynContourCtrlParam dcc)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcDynContourCtrl, IID_ITcDynContourCtrl);

