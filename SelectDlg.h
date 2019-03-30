#if !defined(AFX_SELECTDLG_H__B062A9FD_9543_482F_928C_A6960C7A7FE0__INCLUDED_)
#define AFX_SELECTDLG_H__B062A9FD_9543_482F_928C_A6960C7A7FE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelectDlg dialog

class SelectDlg : public CDialog
{
// Construction
public:
	SelectDlg(CWnd* pParent = NULL);   // standard constructor

	int No;
	void getNo();
	int returnNo();

// Dialog Data
	//{{AFX_DATA(SelectDlg)
	enum { IDD = IDD_SELECTDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelectDlg)
		// NOTE: the ClassWizard will add member functions here
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTDLG_H__B062A9FD_9543_482F_928C_A6960C7A7FE0__INCLUDED_)
