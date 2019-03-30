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
    CPoint m_point1; //���Ͻǵ�
	CPoint m_point2; //���½ǵ�
	CPoint new_point1; //�����ʱ���Ͻǵ�
	CPoint new_point2; //�����ʱ���½ǵ�
	CRect rect;
	int move_ok;								 //�϶�ʱtag��once��ǲ���
	int once;
	int num;
	int m_up;                       //������up
    int tag;                 //��ÿ�ε��ֻ����һ��ͼ��
	CBasicShape *m_BasicShape;

	CPtrArray m_ptrArray;
	int m_ptrArray_sessible[1000];//��¼��ǰѡ��ͼԪ���
	int m_ptrArray_sessible_size;//��¼��ǰѡ�ж���ͼԪ

	bool cursor_replaced;//�Ƿ�����Ϊʮ�ֹ��
	bool cursor_flag;	//ͬ��

	CPtrArray cut1;//DELETE��

	CString function[8];//����

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
