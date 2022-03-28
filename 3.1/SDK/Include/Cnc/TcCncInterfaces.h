///////////////////////////////////////////////////////////////////////////////
// TcCncInterfaces.h
/*
+----------------------------------------------------------------------------+
|                                                                            |
|                       TcCncInterfaces.h                                    |
|                                                                            |
|  14.08.2014   CNC     common EcCncCallerID, TcCncParam                     |
|  16.03.2015   CNC     common TcCncInputParam                               |
|  23.04.2015   CNC     EcCncTrcCallerID_GeometricFeedAdaption, ITcCncBase   |
|  27.01.2017   CNC     Version number for TcCOM interfaces.                 |
|  10.04.2017   CNC     ITcCncBase as interface, inherits public ITcUnknown  |
|  12.04.2017   CNC     TcCncBarrierSync(), MULTIPLE_TASK_SUPPORT            |
|  01.08.2018   CNC     CNC_TC_EVENT_LOG                                     |
|  04.04.2019   CNC     FR#611: Optimization external tool change (SDA task) |
|  05.12.2019   CNC     EcCncTrcCallerID_TargetPos defined.                  |
|  29.03.2021   CNC     ITcCncGeoTask::TcCncGeoAdsRead/Write                 |
|                                                                            |
+----------------------------------------------------------------------------+
*/

#pragma once

#include "TcInterfaces.h"
#include "TcCncServices.h"


#define	CNC_BODEPLOT_INTERFACE				// HKP: activates the new bodeplot interfaces for CncAxis


#define WITH_TIME_MEAS                1

#if TC_VER >= 301
#define	CNC_TC_FILEACCESS
#endif
#ifdef	CNC_TC_FILEACCESS
const		ULONG		TCCNCTLSTYPE_ITcFileAccessCrt						= DrvID_TcCnc | 0x0001;
extern DWORD g_dwCCncFileAccessTlsIndex;
#endif
extern DWORD g_dwCCncRTimeTaskTlsIndex;


// defining new interfaces provided by this driver
struct __declspec(novtable) ITcCncKernel : public ITcUnknown
{
	virtual HRESULT TCOMAPI LookupAxisInfo(LONG axisId, ISG_AXIS_ADS_INFO& info)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcCncKernel, IID_ITcCncKernel);

///////////////////////////////////////////////////////////////////////////////
// ITcCncComTask
struct	__declspec(novtable)	ITcCncComTask : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI TcCncComReadReq( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength ) = 0;
	virtual	HRESULT	TCOMAPI TcCncComWriteReq( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength, PVOID pData ) = 0;
	virtual	HRESULT	TCOMAPI TcCncComReadWriteReq( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, PVOID pData ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcCncComTask, IID_ITcCncComTask);

///////////////////////////////////////////////////////////////////////////////
// ITcCncSdaTask
struct	__declspec(novtable)	ITcCncSdaTask : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI TcCncSdaReadReq( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength ) = 0;
	virtual	HRESULT	TCOMAPI TcCncSdaWriteReq( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbLength, PVOID pData ) = 0;
	virtual	HRESULT	TCOMAPI TcCncSdaReadWriteReq( AmsAddr& rAddr, ULONG invokeId, ULONG indexGroup, ULONG indexOffset, ULONG cbReadLength, ULONG cbWriteLength, PVOID pData ) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcCncSdaTask, IID_ITcCncSdaTask);

///////////////////////////////////////////////////////////////////////////////
// ITcCncGeoTask
struct	__declspec(novtable)	ITcCncGeoTask : public ITcUnknown
{
	virtual	HRESULT	TCOMAPI TcCncCommandStateReadReq( long sercAddr ) = 0;
	virtual	HRESULT	TCOMAPI	TcCncBarrierSync( unsigned long barrierId) = 0;    // MULTIPLE_TASK_SUPPORT
  virtual	HRESULT	TCOMAPI TcCncMutexLock   ( unsigned long mutexId ) = 0;
  virtual	HRESULT	TCOMAPI TcCncMutexUnlock ( unsigned long mutexId ) = 0;

  virtual	HRESULT	TCOMAPI TcCncGeoAdsRead ( ULONG indexGroup, ULONG indexOffset, void * pData, ULONG maxData, ULONG &nRead) = 0;
  virtual	HRESULT	TCOMAPI TcCncGeoAdsWrite( ULONG indexGroup, ULONG indexOffset, void * pData, ULONG maxData, ULONG &nWritten) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcCncGeoTask, IID_ITcCncGeoTask);


#ifdef CNC_CALLER_TEST
///////////////////////////////////////////////////////////////////////////////
// TEST
struct __declspec(novtable) ITcCncGenericCall : public ITcUnknown
{
	virtual HRESULT TCOMAPI GenericCall(ITcUnknown* ipUnk, UINT callId, UINT instId, UINT dataId, UINT nData, PBYTE pData)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcCncGenericCall, IID_ITcCncGenericCall);

struct __declspec(novtable) ITcCncGenericCaller : public ITcUnknown
{
	virtual HRESULT TCOMAPI RegisterCallee(ITcCncGenericCall* ipCallee)=0;
	virtual HRESULT TCOMAPI UnregisterCallee(ITcCncGenericCall* ipCallee)=0;
	virtual HRESULT TCOMAPI GetCallee(ITcCncGenericCall** pipCallee)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcCncGenericCaller, IID_ITcCncGenericCaller);
#endif

#ifdef CNC_REGISTER_OBJECT
struct __declspec(novtable) ITcCncRegisterObject : public ITcUnknown
{
	virtual HRESULT TCOMAPI RegisterObject(TcCncRegisterObject& id, ITcUnknown* ipUnk)=0;
	virtual HRESULT TCOMAPI UnregisterObject(TcCncRegisterObject& id)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcCncRegisterObject, IID_ITcCncRegisterObject);
#endif


enum  EcCncCallerID
{
  EcCncCallerID_Undefined = 0,

	EcCncTrafoCallerID_Decode                 = 1, // caller-ID of kinematic transformations
	EcCncTrafoCallerID_ToolRadiusCorrection,
	EcCncTrafoCallerID_PathPreparation,
	EcCncTrafoCallerID_Interpolation,
	EcCncTrafoCallerID_Display,
	EcCncTrafoCallerID_BlockSearch,

  EcCncTrcCallerID_Display               = 1000, // caller-ID of TRC
  EcCncTrcCallerID_Interpolation,
  EcCncTrcCallerID_GeometricFeedAdaption,
  EcCncTrcCallerID_TargetPos,
};


#define TcCncVersionMajor        3

struct TcCncVersion
{
  long      major;      // defined by CNC in TcCncInterfaces.h :                 basic interface version of CNC
  long      minor;      // defined by CNC in TcCnc<type>Interfaces.h:            TcCom-specific interface version of CNC
};

#ifdef TcCncVersionMinor
///////////////////////////////////////////////////////////////////////////////
// ITcCncBase
struct __declspec(novtable) ITcCncBase : public ITcUnknown
{
	virtual HRESULT TCOMAPI	GetInterfaceVersion(TcCncVersion * pVersion) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcCncBase, IID_ITcCncBase);

#define DECLARE_ITCCNCBASE() \
	virtual	HRESULT	TCOMAPI	GetInterfaceVersion(TcCncVersion * pVersion);

#define IMPLEMENT_ITCCNCBASE(theClass) \
	HRESULT	theClass::GetInterfaceVersion(TcCncVersion * pVersion) \
	{ \
		pVersion->major = TcCncVersionMajor; \
		pVersion->minor = TcCncVersionMinor; \
		return S_OK; \
	};
#endif

struct TcCncInputParam
{
  TcCncInputParam() : i_param(0), f_param(0)
  {
  };
  long              * i_param;           // in: individual programmed 32bit signed integer parameter
  double            * f_param;           // in: individual programmed float parameter of 64bit precision
};

struct TcCncParam : public TcCncInputParam
{
  TcCncParam() : caller_id(EcCncCallerID_Undefined), block_number(0), cnc_channel(0), ret_value1(0), ret_value2(0)
  {
    ret_text[0] = 0;
  };
  EcCncCallerID       caller_id;         // in: identification of caller of TRC
  unsigned long       block_number;      // in: block number of actual executed CNC-program, MDI (not yet supported)
  unsigned short      cnc_channel;       // in: calling CNC channel
  double              ret_value1;        // out: additional error value
  double              ret_value2;        // out: additional error value
  char                ret_text[24];      // out: additional error text, max. 24 byte
};

/*
+----------------------------------------------------------------------------+
| CNC Events send to Event Logger                                            |
+----------------------------------------------------------------------------+
*/
#if !defined(_TC_TYPE_3AFE1771_EB17_4B85_9958_18E33AFD4791_INCLUDED_) // 3AFE1771-EB17-4B85-9958-18E33AFD4791
#define _TC_TYPE_3AFE1771_EB17_4B85_9958_18E33AFD4791_INCLUDED_
namespace TcEvents
{
	namespace CncEventClass
	{
    // {3AFE1771-EB17-4B85-9958-18E33AFD4791}
		CONSTEXPR const GUID uuidCncEventClass = {0x3afe1771,0xeb17,0x4b85,{0x99,0x58,0x18,0xe3,0x3a,0xfd,0x47,0x91}};

    // {3FD56AAE-0711-4359-89A5-3E1ECCCC634E}
    CONSTEXPR const GUID uuidCncUserEventClass = {0x3fd56aae,0x711,0x4359,{0x89,0xa5,0x3e,0x1e,0xcc,0xcc,0x63,0x4e}};

    // Definition of "fixed" EventIds (EventIds are generated dynamically, EventId = CncErrorId)
    struct EventIds
    {
      enum
      {
          Message =  1, //My Cpp Message DisplayText
          Alarm   =  2, //My Cpp Alarm DisplayText
          Init    =  3, //Startup/Shutdown Behaviour..: '{0}'
      };
    };

    // TcEventSeverity::TCEVENTSEVERITY_VERBOSE, TCEVENTSEVERITY_CRITICAL
    CONSTEXPR const TcEventEntry CncMsgVerbose   = { uuidCncEventClass, EventIds::Message, TcEventSeverity::Verbose };
    CONSTEXPR const TcEventEntry CncMsgInfo      = { uuidCncEventClass, EventIds::Message, TcEventSeverity::Info };
    CONSTEXPR const TcEventEntry CncMsgWarning   = { uuidCncEventClass, EventIds::Message, TcEventSeverity::Warning };
    CONSTEXPR const TcEventEntry CncMsgError     = { uuidCncEventClass, EventIds::Message, TcEventSeverity::Error };
    CONSTEXPR const TcEventEntry CncMsgCritical  = { uuidCncEventClass, EventIds::Message, TcEventSeverity::Critical };

    CONSTEXPR const TcEventEntry CncUserMsgVerbose   = { uuidCncUserEventClass, EventIds::Message, TcEventSeverity::Verbose };
    CONSTEXPR const TcEventEntry CncUserMsgInfo      = { uuidCncUserEventClass, EventIds::Message, TcEventSeverity::Info };
    CONSTEXPR const TcEventEntry CncUserMsgWarning   = { uuidCncUserEventClass, EventIds::Message, TcEventSeverity::Warning };
    CONSTEXPR const TcEventEntry CncUserMsgError     = { uuidCncUserEventClass, EventIds::Message, TcEventSeverity::Error };
    CONSTEXPR const TcEventEntry CncUserMsgCritical  = { uuidCncUserEventClass, EventIds::Message, TcEventSeverity::Critical };

    CONSTEXPR const TcEventEntry MyCppAlarm   = { uuidCncEventClass, EventIds::Alarm,   TcEventSeverity::Critical };
    CONSTEXPR const TcEventEntry MyInit       = { uuidCncEventClass, EventIds::Init,    TcEventSeverity::Verbose };
  };
};
#endif // !defined(_TC_TYPE_3AFE1771_EB17_4B85_9958_18E33AFD4791_INCLUDED_)

