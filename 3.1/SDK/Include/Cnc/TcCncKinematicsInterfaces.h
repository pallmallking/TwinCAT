///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
/*
+----------------------------------------------------------------------------+
|                                                                            |
|                       TcCncKinematicsInterfaces.h                          |
|                                                                            |
|  28.06.2013   CNC     TcNcTrafoParameterExtCnc                             |
|  11.12.2013   CNC     TcNcTrafoParameterExtCnc::control extended           |
|  15.08.2014   CN      common EcCncCallerID, TcCncParam                     |
|  27.01.2017   CNC     Version number for TcCOM interfaces.                 |
|  03.02.2017   CNC     EcCnc_Mcs/AcsModuo                                   |
|  03.04.2017   CNC     _e_tcom_kin_trafo_errors                             |
|  10.04.2017   CNC     ITcCncTrafo fromn ITcUnknown, standard names TcCnc<*>|
|  20.09.2018   CNC     EcCnc_TrafoOriModeActual adapted                     |
|  03.02.2021   CNC     EcCnc_TrafoModeSupported                             |
|                                                                            |
+----------------------------------------------------------------------------+
*/
#pragma once

#define TcCncVersionMinor        2                //Version of TcCOM<->CNC interface, must be incremented if interface has changed!

#include "TcInterfaces.h"
#include "TcCncInterfaces.h"
#include "TcNcKinematicsInterfaces.h"

/* Deprecated class and parameter names (backward compatibility) */
#define PTcNcTrafoParameter_Cnc     PTcCncTrafoParameter
#define PTcNcTrafoParameterExtCnc   PTcCncTrafoParameter
#define ITcNcTrafoExtCnc            ITcCncTrafo
#define ITcNcTrafo_Cnc              ITcCncTrafo

TCOM_DECL_INTERFACE("CA92EC02-8F19-407B-8D1D-2022CA551BB7", ITcCncTrafo) 

enum EcCncTrafoOption
{
	EcCncTrafoOption_None                   = 0,
	EcCncTrafoOption_Interpolation_AddInput = 1,
};

#define EcCncTrafoCtrl_cartesianTrafoInactive	        0x0001    // no intersection calculation during kinematic backward trafo (MCS is active)

typedef enum _EcCnc_TrafoOriModeActual
{
  EcCncTrafoOri_None = 0,                                              /* orientation with rotation angle with YPR sequence C, B, A                    */
  EcCncTrafoOri_YPR  = 1,                                              /* orientation with rotation angle with YPR sequence C, B, A                    */
  EcCncTrafoOri_CBC1 = 2,                                              /* orientation with rotation angle with standard euler sequence C1, B, C2       */
  EcCncTrafoOri_CBA  = 3,                                              /* orientation with rotation angle with CBA sequence C, B, A                    */
  EcCncTrafoOri_CAB  = 4,                                              /* orientation with rotation angle with sequence C, A, B                        */

} EcCnc_TrafoOriModeActual;
typedef struct _EcCnc_TrafoOriModeSupported
{
  unsigned long   f_YPR  : 1;                                      /* orientation with rotation angle with YPR sequence C, B, A                    */
  unsigned long   f_CBC1 : 1;                                      /* orientation with rotation angle with standard euler sequence C1, B, C2       */
  unsigned long   f_CBA  : 1;                                      /* orientation with rotation angle with CBA sequence C, B, A                    */
  unsigned long   f_CAB  : 1;                                      /* orientation with rotation angle with sequence C, A, B                        */

} EcCnc_TrafoOriModeSupported;

typedef struct _EcCnc_TrafoModeSupported
{
  unsigned long   f_YPR  : 1;                                      /* orientation with rotation angle with YPR sequence C, B, A                    */
  unsigned long   f_CBC1 : 1;                                      /* orientation with rotation angle with standard euler sequence C1, B, C2       */
  unsigned long   f_CBA  : 1;                                      /* orientation with rotation angle with CBA sequence C, B, A                    */
  unsigned long   f_CAB  : 1;                                      /* orientation with rotation angle with sequence C, A, B                        */
  unsigned long   f_UniqueTrafo  : 1;                              /* TC-Com Trafo is unique in backward. No need to get positions from LR         */

} EcCnc_TrafoModeSupported;


typedef enum : char
{
  EcCnc_McsModulo_None    = 0,                                                   /*                                                                                */
  EcCnc_McsModulo_180_180 = 1,                                                   /*                                                                                */

} EcCnc_McsModulo;
typedef enum : char
{
  EcCnc_AcsModulo_None    = 0,                                                   /*                                                                                */
  EcCnc_AcsModulo_180_180 = 1,                                                   /*                                                                                */
  EcCnc_AcsModulo_0_360   = 2,                                                   /*                                                                                */

} EcCnc_AcsModulo;


struct TcCncTrafoParameter : public TcNcTrafoParameter, TcCncParam
{
  TcCncTrafoParameter() : TcNcTrafoParameter()
	{
     type = EcNcTrafoParameter_ExtCnc;
	}
  unsigned short      kin_id;                     // in: used kinematic ID
  unsigned long       control;                    // in: control trafo calculation, e.g. EcCncTrafoCtrl_cartesianTrafoInactive
  EcCncTrafoOption    ret_option;                 // out: select option of transformation during TrafoSupported()
  TcCncVersion        CncInterfaceVersion;        // Interface version TcCncVersionMajor.TcCncVersionMinor

  // orientation
  EcCnc_TrafoOriModeActual      actual_orientation_mode;      // Treatment of orientation, actual rotation sequence
  union
  {
    EcCnc_TrafoOriModeSupported   supported_orientation_modes;  // Orientations modes supported by the TcCom transforamtion
    EcCnc_TrafoModeSupported      supported_modes;              // modes supported by the TcCom transforamtion
  };

  // modulo configuration
  ULONG						   dim_modulo;		               // dim of modulo vector
  EcCnc_McsModulo  * mcs_modulo;
  EcCnc_AcsModulo  * acs_modulo;
};
typedef TcCncTrafoParameter *PTcCncTrafoParameter;

struct __declspec(novtable) ITcCncTrafo : public ITcUnknown
{
  virtual HRESULT TCOMAPI Forward( PTcCncTrafoParameter p) = 0;                                 // i == acs; o == mcs
  virtual HRESULT TCOMAPI Backward( PTcCncTrafoParameter p) = 0;                                // i == mcs; o == acs
  virtual HRESULT TCOMAPI TrafoSupported( PTcCncTrafoParameter p, bool fwd) = 0;                // check if trafo type is supported (yes = S_OK; no = S_FALSE)
  virtual HRESULT TCOMAPI GetDimensions( PULONG pForwardInput, PULONG pForwardOutput) = 0;         // get axis and machine dimensions
};
_TCOM_SMARTPTR_TYPEDEF(ITcCncTrafo, IID_ITcCncTrafo);

/* Makros for internal implemented transformation methods */
#define DECLARE_ITCCNCTRAFO() 
#define IMPLEMENT_ITCCNCTRAFO(theClass)

// error IDs of kinematic transformations
enum _e_tcom_kin_trafo_errors
{
  E_TCOM_KIN_TRF_MIN       = 400000,
  E_TCOM_KIN_TRF_PARAM_NIL = E_TCOM_KIN_TRF_MIN,      // TcCOM kinematic transformation: Input parameter reference is NIL.
  E_TCOM_KIN_TRF_INPUT_NIL,                           // TcCOM kinematic transformation: Reference of Inputvector is NIL.
  E_TCOM_KIN_TRF_OUTPUT_NIL,                          // TcCOM kinematic transformation: Reference of Outputvector is NIL.
  E_TCOM_KIN_TRF_INVALID_PARAM_TYPE,                  // TcCOM kinematic transformation: Type of parameter is unknown.
  E_TCOM_KIN_TRF_INVALID_INPUT_DIM,                   // TcCOM kinematic transformation: Wrong dimension of Inputvector.
  E_TCOM_KIN_TRF_INVALID_OUTPUT_DIM,                  // TcCOM kinematic transformation: Wrong dimension of Outputvector.
  E_TCOM_KIN_TRF_INVALID_INPUT,                       // TcCOM kinematic transformation: Value of inputvector is out of range.
  E_TCOM_KIN_TRF_DIV_ZERO,                            // TcCOM kinematic transformation: division by zero.
  E_TCOM_KIN_TRF_ARG_SQRT_SIGN,                       // TcCOM kinematic transformation: Negative argument of square root.
  E_TCOM_KIN_TRF_ASIN_ARG,                            // TcCOM kinematic transformation: Argument of arcssine out of range.
  E_TCOM_KIN_TRF_ACOS_ARG,                            // TcCOM kinematic transformation: Argument of arcscosine out of range.
  E_TCOM_KIN_TRF_ATAN_ARG,                            // TcCOM kinematic transformation: Argument of arcstangent out of range.
  E_TCOM_KIN_TRF_TAN_ARG,                             // TcCOM kinematic transformation: Argument of tangents out of range.
  E_TCOM_KIN_TRF_ITERATION_OVERFLOW,                  // TcCOM kinematic transformation: Overflow during iteration.
  E_TCOM_KIN_TRF_SINGULAR_MATRIX,                     // TcCOM kinematic transformation: singularity in kinematic transformation.
  E_TCOM_KIN_TRF_MAX
};
