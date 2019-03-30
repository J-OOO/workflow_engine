// workflow_engineView.cpp : implementation of the CWorkflow_engineView class
//

#include "stdafx.h"
#include "workflow_engine.h"

#include "workflow_engineDoc.h"
#include "workflow_engineView.h"
#include "BasicShape.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "line.h"
#include "SelectDlg.h"
#include "InputDlg.h"
#include "fstream.h"
#include <windows.h>
#include <shellapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkflow_engineView

IMPLEMENT_DYNCREATE(CWorkflow_engineView, CView)

BEGIN_MESSAGE_MAP(CWorkflow_engineView, CView)
	//{{AFX_MSG_MAP(CWorkflow_engineView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CANCELMODE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_DELETE, OnDelete)
	//}}AFX_MSG_MAP
	// Standard printing commands
	
	ON_COMMAND(ID_RECTANGLE,SetRectangle)
	ON_COMMAND(ID_LINE,SetLine)
	ON_COMMAND(ID_RUN,Run)
	ON_COMMAND(ID_DELETE,OnDelete)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkflow_engineView construction/destruction

CWorkflow_engineView::CWorkflow_engineView()
{
	// TODO: add construction code here
	run=false;

	WebPage[0]="https://weibo.com";
	WebPage[1]="https://www.sina.com";
	WebPage[2]="https://www.baidu.com";
	WebPage[3]="https://jwc.scnu.edu.cn";
	WebPage[4]="http://www.scholat.com";
	WebPage[5]="https://sso.scnu.edu.cn";
	WebPage[6]="https://www.163.com";
	WebPage[7]="https://www.taobao.com";
	WebPage[8]="https://www.jd.com";
	WebPage[9]="https://www.youku.com";

	WebName[0]="΢��";
	WebName[1]="����";
	WebName[2]="�ٶ�";
	WebName[3]="��ʦ�������ϵͳ";
	WebName[4]="ѧ����";
	WebName[5]="��ʦͳһ�����֤ƽ̨";
	WebName[6]="����";
	WebName[7]="�Ա�";
	WebName[8]="����";
	WebName[9]="�ſ�";
}

CWorkflow_engineView::~CWorkflow_engineView()
{
}

BOOL CWorkflow_engineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWorkflow_engineView drawing

void CWorkflow_engineView::OnDraw(CDC* pDC)
{
	CWorkflow_engineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if(pDoc->tag!=0&&pDoc->m_up==1)
	{	
		pDoc->m_BasicShape->Draw(pDC);
		pDoc->tag=0;
		pDoc->m_up=0;
	}
	
	for(int i=0;i<pDoc->m_ptrArray.GetSize();i++)
	{
		((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->Draw(pDC);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CWorkflow_engineView diagnostics

#ifdef _DEBUG
void CWorkflow_engineView::AssertValid() const
{
	CView::AssertValid();
}

void CWorkflow_engineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWorkflow_engineDoc* CWorkflow_engineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorkflow_engineDoc)));
	return (CWorkflow_engineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkflow_engineView message handlers


void CWorkflow_engineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWorkflow_engineDoc* pDoc = GetDocument();
	pDoc->m_point1=point;

	pDoc->rect.left=point.x;
	pDoc->rect.top=point.y;
	bool flag1=false; //�ж��Ƿ�����֮ǰ��ѡ��ͼ�λ������������־Ϊtrue
	if(pDoc->tag==0)
	{
		for(int i=0;i<pDoc->m_ptrArray_sessible_size;i++)
		{

			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[i]))->CheckRect(point)) //ѡ����
			{
					flag1=true;
					break;
			}
			if(pDoc->m_ptrArray_sessible_size==1&&(((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->in_hot_point(point))) //һ��ͼԪ�߽����
			{
				flag1=true;
			}
		}
	}
	if(pDoc->tag==2)    //������߰�ť
	{
		int i;
		bool m_select;
		for(i=0;i<pDoc->m_ptrArray.GetSize();i++)
		{
			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->GetTag()!=2)
			{		
				m_select = ((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->CheckRect(point);			
				if(m_select==TRUE)
				break;
			}
		}
		if(m_select==TRUE) //����������������ͼԪ����ȡ������ʼ��
		{	
				
				pDoc->m_BasicShape=new CLine;
			    pDoc->m_BasicShape->LineFront=(CBasicShape*)pDoc->m_ptrArray.GetAt(i);
				pDoc->m_BasicShape->LineFront->no=i;

				pDoc->m_BasicShape->tag1=((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->GetTag();
					
				pDoc->m_point1=((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->GetPoint11();                
		}					                          			
		else //ȡ�����߹���
		{
			pDoc->tag=0;
		}
		
	}                                                            

	if(pDoc->tag==0&&flag1==false) //û��ѡ���е��
	{
		InvalidateRect(NULL,FALSE);
		CClientDC dc(this);	
		bool if_any_select=false;

		for(int i=pDoc->m_ptrArray.GetSize()-1;i>=0;i--) //�ص�ʱ�����ͼԪѡ��
		{
			
			bool m_select = ((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->CheckRect(point);
			if(m_select==TRUE) //���µ��һ��ͼԪ,ȥ��֮ǰ��ѡ��
			{	
				for(int k=0;k<pDoc->m_ptrArray_sessible_size;k++) 
				{
					((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[k]))->In_Draw_Point(&dc);
				}
				pDoc->m_ptrArray_sessible[0]=i;
				pDoc->m_ptrArray_sessible_size=1;
				((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->DrawTag(&dc);
				if_any_select=true;
				break;
			}
		}
		if(if_any_select==false) //����ѡ���µ�����
		{	
			for(int i=0;i<pDoc->m_ptrArray_sessible_size;i++)
			{	
				((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[i]))->In_Draw_Point(&dc);	
			}
			pDoc->m_ptrArray_sessible_size=0;
		}

	}

	CView::OnLButtonDown(nFlags, point);
}
	

void CWorkflow_engineView::OnLButtonUp(UINT nFlags, CPoint point) //���̧����Ӧ
{
	CWorkflow_engineDoc* pDoc = GetDocument();
	pDoc->m_point2=point;
	pDoc->rect.right=point.x;
	pDoc->rect.bottom=point.y;
	CClientDC dc(this);	

	if(pDoc->tag==2)//����
	{
		int i;
		bool m_select;
		for(i=0;i<pDoc->m_ptrArray.GetSize();i++) //�ж������յ�
		{
			
			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->GetTag()!=2 && pDoc->m_BasicShape->LineFront->no!=i) //�յ㲻��Ϊ���ߣ�����յ㲻��ͬһ��
			{		
				m_select = ((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->CheckRect(point);			
				if(m_select==TRUE)
				break;
			}
		}
				
		if(m_select==TRUE)	//�յ�Ϊ������	
		{	
			pDoc->m_BasicShape->LineBehind=(CBasicShape*)pDoc->m_ptrArray.GetAt(i); //�յ�ͼԪ
			if(pDoc->m_BasicShape->LineFront->out==false && pDoc->m_BasicShape->LineBehind->in==false)
			{
				pDoc->m_BasicShape->LineFront->out=true;
				pDoc->m_BasicShape->LineBehind->in=true;
		
				pDoc->m_BasicShape->tag2=((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->GetTag();		
				pDoc->m_point2=((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->GetPoint2();																											
				
			pDoc->m_BasicShape->SetPoint(pDoc->m_point1,pDoc->m_point2);			
			pDoc->m_BasicShape->SetTag(2);			
			pDoc->m_ptrArray.Add(pDoc->m_BasicShape);

			pDoc->m_up=1;
	    	pDoc->num++;
			}
			else 
				MessageBox("������ͼΪ��·������ʼ���ֻ��Ϊ���ߵ���㣬�������ֻ��Ϊ���ߵ��յ㣬�����ظ�����","����������");
		}

		else
		{
			pDoc->tag=0;
		}

	}

	else if(pDoc->tag==0)
	{
		//������ƶ�ѡ��
		if(pDoc->m_ptrArray_sessible_size>1)
		{
			InvalidateRect(NULL,FALSE);	
			CClientDC dc(this);	
	
			for(int i=0;i<pDoc->m_ptrArray_sessible_size;i++)
			{	
		    	((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[i]))->In_Draw(&dc);	
		    	((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[i]))->MovePoint(pDoc->m_point1,pDoc->m_point2);
			    if(((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[i]))->CheckRect(point)==TRUE);
	    		else
	    		InvalidateRect(NULL,TRUE);
	    		((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[i]))->DrawTag(&dc);
			}
     		for(int m=0;m<pDoc->m_ptrArray_sessible_size;m++)
			{	
    			((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[m]))->In_Draw_Point(&dc);	
			}
	    	pDoc->m_ptrArray_sessible_size=0;
		}
 
		else if(pDoc->m_ptrArray_sessible_size==1)
		{
			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->GetTag()!=2)//��ȥ����
			{
			//����һ��ͼԪ
			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->in_hot_point(pDoc->m_point1))
			{
	        	InvalidateRect(NULL,FALSE);
         		CClientDC dc(this);	
	        	((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->In_Draw(&dc);	
        		((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->Zoom(pDoc->m_point1,pDoc->m_point2);     		
				((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->DrawTag(&dc);
			}

			//�ƶ�һ��ͼԪ	
			else if(pDoc->m_point1!=pDoc->m_point2)
			{
		
				InvalidateRect(NULL,FALSE);
		        CClientDC dc(this);			

	        	((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->In_Draw(&dc);			
				((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->MovePoint(pDoc->m_point1,pDoc->m_point2);			
				if(((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->CheckRect(point)==TRUE);		
				else			
					InvalidateRect(NULL,TRUE);			
				((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->DrawTag(&dc);				
	
	         	((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->In_Draw_Point(&dc);	
	        	pDoc->m_ptrArray_sessible_size=0;
			}
			}
		}

		//����ѡ��
		else
		{
     		InvalidateRect(NULL,FALSE);
      		CClientDC dc(this);	
     		bool if_any_select=false;
      		int j=0;
      		bool flag=false;
		
     		for(int i=0;i<pDoc->m_ptrArray.GetSize();i++)
			{
			
       			bool m_select = ((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->Check_Out_Rect(pDoc->m_point1,point);
     			if(m_select==true)
				{	
     				pDoc->m_ptrArray_sessible[j++]=i;
    				pDoc->m_ptrArray_sessible_size++;
    				((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->DrawTag(&dc);
     				flag=true;
    				if_any_select=true;
				}
			}
    		if(if_any_select==false&&pDoc->m_ptrArray_sessible_size!=0&&!((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->in_hot_point(pDoc->m_point1))
			{	
    			for(int i=0;i<pDoc->m_ptrArray_sessible_size;i++)
				{	
 	        			((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[i]))->In_Draw_Point(&dc);	
				}
	    		pDoc->m_ptrArray_sessible_size=0;
			}
		}

	}
	InvalidateRect(NULL,FALSE);
	
	CView::OnLButtonUp(nFlags, point);

}

void CWorkflow_engineView::SetRectangle()//ѡ����ӹ��ܾ���
{
	if(run==false)
	{
	CWorkflow_engineDoc* pDoc = GetDocument();	
	
	SelectDlg s;    
	s.DoModal();
    int no=s.returnNo();
	if(no!=0)
	{
	pDoc->m_BasicShape=new CRectangle;
    pDoc->m_BasicShape->SetPoint(pDoc->new_point1,pDoc->new_point2);
    pDoc->new_point1.x+=20;
	pDoc->new_point1.y+=20;
	pDoc->new_point2.x+=20;
	pDoc->new_point2.y+=20;
	pDoc->m_BasicShape->SetTag(1);
	pDoc->m_BasicShape->SetFunction(no);
	pDoc->m_BasicShape->SetTitle(pDoc->function[no]);
	pDoc->m_ptrArray.Add(pDoc->m_BasicShape);

	pDoc->m_up=0;
	pDoc->num++;
	}
	pDoc->tag=0;

	CClientDC dc(this);
	for(int i=0;i<pDoc->m_ptrArray_sessible_size;i++)
	{	
		((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[i]))->In_Draw_Point(&dc);	
	}
	pDoc->m_ptrArray_sessible_size=0;

	InvalidateRect(NULL,FALSE);
	}
}


void CWorkflow_engineView::SetLine() 
{
	if(run==false)
	{
	CWorkflow_engineDoc* pDoc = GetDocument();

	pDoc->tag=2;
	
	CClientDC dc(this);
	for(int i=0;i<pDoc->m_ptrArray_sessible_size;i++)
	{	
		((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[i]))->In_Draw_Point(&dc);	
	}
	pDoc->m_ptrArray_sessible_size=0;
	InvalidateRect(NULL,FALSE);
	}
}


void CWorkflow_engineView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWorkflow_engineDoc* pDoc = GetDocument();
	pDoc->m_point2=point;
	pDoc->cursor_replaced=false;
	if(pDoc->m_up==0&&pDoc->move_ok!=0){

		if(pDoc->m_ptrArray_sessible_size==1&&pDoc->tag==0)
		{
			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->in_hot_point(point)&&((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->GetTag()!=2)
			{	
				HCURSOR   hc;

				hc=LoadCursor(NULL,IDC_CROSS);

				SetCursor(hc);
				pDoc->cursor_replaced=true;
			}
		}
	}
	
	CView::OnMouseMove(nFlags, point); 
}

void CWorkflow_engineView::OnCancelMode() 
{
	CView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}


void CWorkflow_engineView::OnDelete()              //ɾ������
{
	
	CWorkflow_engineDoc* pDoc = GetDocument();
	InvalidateRect(NULL,FALSE);
	CClientDC dc(this);	
	pDoc->cut1.RemoveAll();	

	bool wrong=false;
	 	for(int i=0;i<pDoc->m_ptrArray_sessible_size;i++)
		{
			if(pDoc->m_ptrArray_sessible[i]==0 || pDoc->m_ptrArray_sessible[i]==1)
			{
				MessageBox("��ʼ�ͽ�����㲻��ɾ��","����");
				wrong=true;
				break;
			}
			for(int j=i;j<=i;j++)
				pDoc->m_ptrArray_sessible[j]-=i;
			pDoc->cut1.Add((CBasicShape*)pDoc->m_ptrArray[pDoc->m_ptrArray_sessible[i]]);
	 		((CBasicShape*)pDoc->m_ptrArray[pDoc->m_ptrArray_sessible[i]])->In_Draw(&dc);
			if(((CBasicShape*)pDoc->m_ptrArray[pDoc->m_ptrArray_sessible[i]])->GetTag()==2)//��ɾ��ѡ�е�����
			{	
					((CBasicShape*)pDoc->m_ptrArray[pDoc->m_ptrArray_sessible[i]])->LineFront->out=false;
					((CBasicShape*)pDoc->m_ptrArray[pDoc->m_ptrArray_sessible[i]])->LineBehind->in=false;
			}

	 		pDoc->m_ptrArray.RemoveAt(pDoc->m_ptrArray_sessible[i]);
					
		}
	if(wrong==false)
	{
		for(int m=0;m<pDoc->cut1.GetSize();m++)
		{
			if(((CBasicShape*)pDoc->cut1[m])->GetTag()!=2)//ɾ��������
			{
				for(int t=0;t<pDoc->m_ptrArray.GetSize();t++)
				{
					if(((CBasicShape*)pDoc->m_ptrArray[t])->GetTag()==2)
					{
							if(((CBasicShape*)pDoc->m_ptrArray[t])->LineBehind==(CBasicShape*)pDoc->cut1[m] || ((CBasicShape*)pDoc->m_ptrArray[t])->LineFront==((CBasicShape*)pDoc->cut1[m]))
							{
								if(((CBasicShape*)pDoc->m_ptrArray[t])->LineFront==((CBasicShape*)pDoc->cut1[m]))						
									((CBasicShape*)pDoc->m_ptrArray[t])->LineBehind->in=false;							
								else
									((CBasicShape*)pDoc->m_ptrArray[t])->LineFront->out=false;	
								
								pDoc->cut1.Add((CBasicShape*)pDoc->m_ptrArray[t]);
	 							((CBasicShape*)pDoc->m_ptrArray[t])->In_Draw(&dc);
	 							pDoc->m_ptrArray.RemoveAt(t);	
								t--;
							}
					}
				}
			}
		}
	}

	pDoc->m_ptrArray_sessible_size=0;
	pDoc->cut1.RemoveAll();
	InvalidateRect(NULL,TRUE);

}


void CWorkflow_engineView::Run() //ִ��
{
	if(run==false)
	{
		run=true;
		int i,j;
		CString s;

		CWorkflow_engineDoc* pDoc = GetDocument();
	
	    CClientDC dc(this);
    	for(i=0;i<pDoc->m_ptrArray_sessible_size;i++)
		{	
    		((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[i]))->In_Draw_Point(&dc);
		}
    	pDoc->m_ptrArray_sessible_size=0;
    	pDoc->tag=3;
    	InvalidateRect(NULL,FALSE);

	
		int link[100][2];	
		int line_num=0;
		int order[100];//λ�ô���
		int f_order[100];//ִ�й��ܴ���
		bool connect=false;//��ͨ��־
		bool end_correct=false; //������ȷ��־
		int X=0;
		int max=2147483647;
		bool suspend=false;
		int last;
		
		for(i=0;i<pDoc->m_ptrArray.GetSize();i++)
		{
			((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->no=i;
		}

		for(i=0;i<pDoc->m_ptrArray.GetSize();i++)
		{
			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->GetTag()==2) //�ҳ�����
			{
				link[line_num][0]=((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->LineFront->no;
				link[line_num++][1]=((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->LineBehind->no;
			}
		}

		order[0]=0;
		f_order[0]=0;
		for(i=0;i<line_num;i++)
		{
			for(j=0;j<line_num;j++)
			{
				if(link[j][0]==order[i])
				{
					order[i+1]=link[j][1];
					f_order[i+1]=((CBasicShape*)pDoc->m_ptrArray.GetAt(order[i+1]))->GetFunction();
					if(order[i+1]==1) end_correct=true;
					connect=true;
					break;
				}
			}
			if(connect==false || end_correct==true) break;
		}

		if(connect==true && end_correct) 
		{
			j=i+1;
			for(i=0;i<=j;i++)
			{
				switch(f_order[i])
				{
				    case 0:
					{
						MessageBox("��ʼִ�У�X��ʼΪ0","��ʼ");
						break;
					}
					case 1:
					{
						InputDlg input;
						input.DoModal();
						X=input.getX();
						if(X==max)
						{
							MessageBox("X Խ�磬ִ���ж�","�ж�");
							suspend=true;
						}
						break;
					}
					case 2:
					{
						X=X+1;
						if(X==max)
						{
							MessageBox("X Խ�磬ִ���ж�","�ж�");
							suspend=true;
						}
						MessageBox("X ���Լ�1","�Լ�");
						break;
					}
					case 3:
					{
						ofstream outfile;
						outfile.open("X.txt");
						if(!outfile) 
						{
							MessageBox("�����ļ���������ִ���ж�","�ж�");
							suspend=true;
						}
						outfile<<"#"<<X<<"#";
						outfile.close(); 
						MessageBox("X �������ѳɹ������� X.txt �ļ���","����");
						break;
					}
					case 4:
					{					
						s.Format(_T("%d"), X);
						MessageBox("X = "+s,"��ʾX");
						break;
					}
					case 5:
					{
						ShellExecute(NULL,"open","NOTEPAD.EXE",NULL,NULL,SW_SHOWNORMAL);
						MessageBox("�Ѵ򿪼��±�","���±�");
						break;
					}
					case 6:
					{
						last=X%10;
						ShellExecute(NULL,"open",WebPage[last],NULL,NULL,SW_SHOW);
						MessageBox("�Ѵ���ҳ : "+WebName[last],"��ҳ");
						break;
					}
					case 7:
					{
						MessageBox("ִ�����","����");
						break;
					}		
				}
				if(suspend==true)
					break;
			}

		}
		else MessageBox("������ͼ����ͨ������ִ��","��ʾ");

		pDoc->tag=0;
		run=false;
	}

}
