// workflow_engine.h : main header file for the WORKFLOW_ENGINE application
//

#if !defined(AFX_WORKFLOW_ENGINE_H__F204E35B_31E3_48EB_AAF8_52F2A51729E5__INCLUDED_)
#define AFX_WORKFLOW_ENGINE_H__F204E35B_31E3_48EB_AAF8_52F2A51729E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWorkflow_engineApp:
// See workflow_engine.cpp for the implementation of this class
//

class CWorkflow_engineApp : public CWinApp
{
public:
	CWorkflow_engineApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkflow_engineApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWorkflow_engineApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKFLOW_ENGINE_H__F204E35B_31E3_48EB_AAF8_52F2A51729E5__INCLUDED_)
