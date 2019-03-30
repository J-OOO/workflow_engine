// workflow_engineDoc.h : interface of the CWorkflow_engineDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKFLOW_ENGINEDOC_H__E21978B4_ACFA_4A98_B000_57FB79B78435__INCLUDED_)
#define AFX_WORKFLOW_ENGINEDOC_H__E21978B4_ACFA_4A98_B000_57FB79B78435__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BasicShape.h"

class CWorkflow_engineDoc : public CDocument
{
protected: // create from serialization only
	CWorkflow_engineDoc();
	DECLARE_DYNCREATE(CWorkflow_engineDoc)

// Attributes
public:
    CPoint m_point1; //左上角点
	CPoint m_point2; //右下角点
	CPoint new_point1; //新添加时左上角点
	CPoint new_point2; //新添加时右下角点
	CRect rect;
	int move_ok;								 //拖动时tag和once标记不置
	int once;
	int num;
	int m_up;                       //标记鼠标up
    int tag;                 //是每次点击只出现一个图形
	CBasicShape *m_BasicShape;

	CPtrArray m_ptrArray;
	int m_ptrArray_sessible[1000];//记录当前选中图元编号
	int m_ptrArray_sessible_size;//记录当前选中多少图元

	bool cursor_replaced;//是否鼠标变为十字光标
	bool cursor_flag;	//同上

	CPtrArray cut1;//DELETE用

	CString function[8];//功能

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkflow_engineDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWorkflow_engineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWorkflow_engineDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKFLOW_ENGINEDOC_H__E21978B4_ACFA_4A98_B000_57FB79B78435__INCLUDED_)
