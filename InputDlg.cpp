// InputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "workflow_engine.h"
#include "InputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InputDlg dialog


InputDlg::InputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(InputDlg)
	m_edit = 0;
	//}}AFX_DATA_INIT
}


void InputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InputDlg)
	DDX_Text(pDX, IDC_EDIT, m_edit);
	DDV_MinMaxInt(pDX, m_edit, 0, 2147483647);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InputDlg, CDialog)
	//{{AFX_MSG_MAP(InputDlg)
	ON_EN_KILLFOCUS(IDC_EDIT, OnKillfocusEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InputDlg message handlers

void InputDlg::OnKillfocusEdit() 
{
	// TODO: Add your control notification handler code here
    int a = m_edit;
    UpdateData(true);
    if (m_edit>=2147483647)
    {
        MessageBoxA(_T("ÊıÖµ³¬¹ı·¶Î§!"), _T("´íÎó"), MB_OK);
        m_edit = a;
        UpdateData(false);
    }
}

int InputDlg::getX()
{
	return m_edit;
}
