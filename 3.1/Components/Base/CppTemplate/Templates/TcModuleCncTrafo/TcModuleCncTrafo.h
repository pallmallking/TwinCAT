///////////////////////////////////////////////////////////////////////////////
// [!output HEADER_FILE_NAME]
#pragma once

#include "[!output PROJECT_NAME]Interfaces.h"
#include "Cnc/TcCncKinematicsInterfaces.h"

class [!output CLASS_NAME] 
	: public ITComObject
	, public ITcADI
	, public ITcWatchSource
	, public ITcCncBase
	, public ITcCncTrafo
///<AutoGeneratedContent id="InheritanceList">
///</AutoGeneratedContent>
{
public:
	DECLARE_IUNKNOWN()
[!if VERSIONED_CLASSFACTORY]	DECLARE_IPERSIST_LIB()[!else]	DECLARE_IPERSIST(CID_[!output PROJECT_NAME][!output CLASS_NAME])[!endif]
	DECLARE_ITCOMOBJECT_LOCKOP()
	DECLARE_ITCADI()
	DECLARE_ITCWATCHSOURCE()
	DECLARE_ITCCNCBASE()
	DECLARE_ITCCNCTRAFO()
	DECLARE_OBJPARAWATCH_MAP()
	DECLARE_OBJDATAAREA_MAP()

	[!output CLASS_NAME]();
	virtual	~[!output CLASS_NAME]();

	virtual HRESULT TCOMAPI Forward(PTcCncTrafoParameter p);			
	virtual HRESULT TCOMAPI Backward(PTcCncTrafoParameter p);		
	virtual HRESULT TCOMAPI TrafoSupported(PTcCncTrafoParameter p, bool fwd);
	virtual HRESULT TCOMAPI GetDimensions(PULONG pForwardInput, PULONG pForwardOutput);

///<AutoGeneratedContent id="InterfaceMembers">
///</AutoGeneratedContent>

protected:
	DECLARE_ITCOMOBJECT_SETSTATE();

	ITcCncRegisterObjectPtr    m_spCnc;	 

	const ULONG                m_forwardNbrIn;	
	const ULONG                m_forwardNbrOut;

///<AutoGeneratedContent id="Members">
///</AutoGeneratedContent>
};