// workflow_engineDoc.cpp : implementation of the CWorkflow_engineDoc class
//

#include "stdafx.h"
#include "workflow_engine.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "line.h"

#include "workflow_engineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkflow_engineDoc

IMPLEMENT_DYNCREATE(CWorkflow_engineDoc, CDocument)

BEGIN_MESSAGE_MAP(CWorkflow_engineDoc, CDocument)
	//{{AFX_MSG_MAP(CWorkflow_engineDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkflow_engineDoc construction/destruction

CWorkflow_engineDoc::CWorkflow_engineDoc()
{
	// TODO: add one-time construction code here
	m_up=0;
	tag=0;
	m_ptrArray_sessible_size=0;
	cursor_replaced=false;
	cursor_flag=false;

	new_point1.x=180;
	new_point1.y=45;

	new_point2.x=330;
	new_point2.y=80;

	function[0]="开始";
	function[1]="输入 X";
	function[2]="X = X + 1";
	function[3]="保存 X";
	function[4]="显示 X";
	function[5]="调用 notepad.exe";
	function[6]="根据 X 打开网页";
	function[7]="结束";

	CPoint point1(30,30);
	CPoint point2(100,90);
	CBasicShape *temp=new CEllipse;
	temp->SetPoint(point1,point2); //开始结点
	temp->SetTag(3);
	temp->SetFunction(0);
	temp->SetTitle("开始");
	temp->in=true; //设置只能为折线起点
	m_ptrArray.Add(temp);

	CPoint point3(1090,320);
	CPoint point4(1160,380);
	temp=new CEllipse;
	temp->SetPoint(point3,point4); //结束结点
	temp->SetTag(3);
	temp->SetFunction(7);
	temp->SetTitle("结束");
	temp->out=true; //设置只能为折线终点
	m_ptrArray.Add(temp);

}

CWorkflow_engineDoc::~CWorkflow_engineDoc()
{
}

BOOL CWorkflow_engineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWorkflow_engineDoc serialization

void CWorkflow_engineDoc::Serialize(CArchive& ar)
{
}

/////////////////////////////////////////////////////////////////////////////
// CWorkflow_engineDoc diagnostics

#ifdef _DEBUG
void CWorkflow_engineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWorkflow_engineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkflow_engineDoc commands
