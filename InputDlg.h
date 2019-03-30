#if !defined(AFX_INPUTDLG_H__7021A102_C1A0_4AC4_A62A_470D05B13BF0__INCLUDED_)
#define AFX_INPUTDLG_H__7021A102_C1A0_4AC4_A62A_470D05B13BF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// InputDlg dialog

class InputDlg : public CDialog
{
// Construction
public:
	InputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(InputDlg)
	enum { IDD = IDD_INPUTDLG };
	int		m_edit;
	//}}AFX_DATA

	int getX();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(InputDlg)
	afx_msg void OnKillfocusEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDLG_H__7021A102_C1A0_4AC4_A62A_470D05B13BF0__INCLUDED_)
