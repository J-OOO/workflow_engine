// workflow_engineView.h : interface of the CWorkflow_engineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKFLOW_ENGINEVIEW_H__10702DBD_D0E8_4235_B60E_8384D418F449__INCLUDED_)
#define AFX_WORKFLOW_ENGINEVIEW_H__10702DBD_D0E8_4235_B60E_8384D418F449__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWorkflow_engineView : public CView
{
protected: // create from serialization only
	CWorkflow_engineView();
	DECLARE_DYNCREATE(CWorkflow_engineView)

	afx_msg void SetRectangle();
	afx_msg void SetLine();
	afx_msg void Run();//执行

// Attributes
public:
	CWorkflow_engineDoc* GetDocument();
	bool run;//执行标志

	CString WebPage[10]; //网址
	CString WebName[10]; //网页名


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkflow_engineView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWorkflow_engineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWorkflow_engineView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in workflow_engineView.cpp
inline CWorkflow_engineDoc* CWorkflow_engineView::GetDocument()
   { return (CWorkflow_engineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKFLOW_ENGINEVIEW_H__10702DBD_D0E8_4235_B60E_8384D418F449__INCLUDED_)
