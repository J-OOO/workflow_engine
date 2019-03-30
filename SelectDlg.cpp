// SelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "workflow_engine.h"
#include "SelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelectDlg dialog


SelectDlg::SelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	No=0;
}


void SelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectDlg, CDialog)
	//{{AFX_MSG_MAP(SelectDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectDlg message handlers
void SelectDlg::OnOK()
{
	getNo();
	CDialog::OnOK();
}

void SelectDlg::getNo()
{
	No=0;
	CButton *p;
	p= (CButton *)GetDlgItem(IDC_RADIO_INPUT); 
    if (p->GetCheck()) 
	{
		No=1;
		return;
	}
	p= (CButton *)GetDlgItem(IDC_RADIO_ADD); 
    if (p->GetCheck()) 
	{
		No=2;
		return;
	}
	p= (CButton *)GetDlgItem(IDC_RADIO_SAVE); 
    if (p->GetCheck()) 
	{
		No=3;
		return;
	}
	p= (CButton *)GetDlgItem(IDC_RADIO_SHOW); 
    if (p->GetCheck()) 
	{
		No=4;
		return;
	}
	p= (CButton *)GetDlgItem(IDC_RADIO_NOTE); 
    if (p->GetCheck()) 
	{
		No=5;
		return;
	}
	p= (CButton *)GetDlgItem(IDC_RADIO_NET); 
    if (p->GetCheck()) 
	{
		No=6;
		return;
	}
}

int SelectDlg::returnNo()
{
	return No;
}
