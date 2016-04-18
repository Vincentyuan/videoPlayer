// CWMPControls.cpp  : Definition of ActiveX Control wrapper class(es) created by Microsoft Visual C++


#include "stdafx.h"
#include "CWMPControls.h"

/////////////////////////////////////////////////////////////////////////////
// CWMPControls

//IMPLEMENT_DYNCREATE(CWMPControls, CWnd)

// CWMPControls properties

// CWMPControls operations

double CWMPControls::GetCurrentPosition()
{
	double result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CWMPControls::SetCurrentPosition(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		newValue);
}
void CWMPControls::play()
{
	InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CWMPControls::stop()
{
	InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CWMPControls::pause()
{
	InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CWMPControls::fastForward()
{
	InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CWMPControls::fastReverse()
{
	InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}