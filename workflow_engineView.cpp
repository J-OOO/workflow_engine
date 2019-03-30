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

	WebName[0]="微博";
	WebName[1]="新浪";
	WebName[2]="百度";
	WebName[3]="华师教务管理系统";
	WebName[4]="学者网";
	WebName[5]="华师统一身份认证平台";
	WebName[6]="网易";
	WebName[7]="淘宝";
	WebName[8]="京东";
	WebName[9]="优酷";
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
	bool flag1=false; //判断是否点击在之前已选中图形或区域，若是则标志为true
	if(pDoc->tag==0)
	{
		for(int i=0;i<pDoc->m_ptrArray_sessible_size;i++)
		{

			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[i]))->CheckRect(point)) //选区中
			{
					flag1=true;
					break;
			}
			if(pDoc->m_ptrArray_sessible_size==1&&(((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->in_hot_point(point))) //一个图元边界点中
			{
				flag1=true;
			}
		}
	}
	if(pDoc->tag==2)    //点击连线按钮
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
		if(m_select==TRUE) //若点击除折线以外的图元，获取折线起始点
		{	
				
				pDoc->m_BasicShape=new CLine;
			    pDoc->m_BasicShape->LineFront=(CBasicShape*)pDoc->m_ptrArray.GetAt(i);
				pDoc->m_BasicShape->LineFront->no=i;

				pDoc->m_BasicShape->tag1=((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->GetTag();
					
				pDoc->m_point1=((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->GetPoint11();                
		}					                          			
		else //取消连线功能
		{
			pDoc->tag=0;
		}
		
	}                                                            

	if(pDoc->tag==0&&flag1==false) //没在选区中点击
	{
		InvalidateRect(NULL,FALSE);
		CClientDC dc(this);	
		bool if_any_select=false;

		for(int i=pDoc->m_ptrArray.GetSize()-1;i>=0;i--) //重叠时，从最顶图元选择
		{
			
			bool m_select = ((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->CheckRect(point);
			if(m_select==TRUE) //若新点击一个图元,去除之前的选区
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
		if(if_any_select==false) //可能选择新的区域
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
	

void CWorkflow_engineView::OnLButtonUp(UINT nFlags, CPoint point) //鼠标抬起响应
{
	CWorkflow_engineDoc* pDoc = GetDocument();
	pDoc->m_point2=point;
	pDoc->rect.right=point.x;
	pDoc->rect.bottom=point.y;
	CClientDC dc(this);	

	if(pDoc->tag==2)//连线
	{
		int i;
		bool m_select;
		for(i=0;i<pDoc->m_ptrArray.GetSize();i++) //判断折线终点
		{
			
			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->GetTag()!=2 && pDoc->m_BasicShape->LineFront->no!=i) //终点不能为折线，起点终点不能同一个
			{		
				m_select = ((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->CheckRect(point);			
				if(m_select==TRUE)
				break;
			}
		}
				
		if(m_select==TRUE)	//终点为非折线	
		{	
			pDoc->m_BasicShape->LineBehind=(CBasicShape*)pDoc->m_ptrArray.GetAt(i); //终点图元
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
				MessageBox("工作流图为单路径，开始结点只能为连线的起点，结束结点只能为连线的终点，不能重复相连","请重新连接");
		}

		else
		{
			pDoc->tag=0;
		}

	}

	else if(pDoc->tag==0)
	{
		//点击或移动选区
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
			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->GetTag()!=2)//除去折线
			{
			//变形一个图元
			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->in_hot_point(pDoc->m_point1))
			{
	        	InvalidateRect(NULL,FALSE);
         		CClientDC dc(this);	
	        	((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->In_Draw(&dc);	
        		((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->Zoom(pDoc->m_point1,pDoc->m_point2);     		
				((CBasicShape*)pDoc->m_ptrArray.GetAt(pDoc->m_ptrArray_sessible[0]))->DrawTag(&dc);
			}

			//移动一个图元	
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

		//建立选区
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

void CWorkflow_engineView::SetRectangle()//选择添加功能矩形
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


void CWorkflow_engineView::OnDelete()              //删除功能
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
				MessageBox("开始和结束结点不能删除","错误");
				wrong=true;
				break;
			}
			for(int j=i;j<=i;j++)
				pDoc->m_ptrArray_sessible[j]-=i;
			pDoc->cut1.Add((CBasicShape*)pDoc->m_ptrArray[pDoc->m_ptrArray_sessible[i]]);
	 		((CBasicShape*)pDoc->m_ptrArray[pDoc->m_ptrArray_sessible[i]])->In_Draw(&dc);
			if(((CBasicShape*)pDoc->m_ptrArray[pDoc->m_ptrArray_sessible[i]])->GetTag()==2)//先删除选中的折线
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
			if(((CBasicShape*)pDoc->cut1[m])->GetTag()!=2)//删除非折线
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


void CWorkflow_engineView::Run() //执行
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
		int order[100];//位置次序
		int f_order[100];//执行功能次序
		bool connect=false;//连通标志
		bool end_correct=false; //结束正确标志
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
			if(((CBasicShape*)pDoc->m_ptrArray.GetAt(i))->GetTag()==2) //找出连线
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
						MessageBox("开始执行，X初始为0","开始");
						break;
					}
					case 1:
					{
						InputDlg input;
						input.DoModal();
						X=input.getX();
						if(X==max)
						{
							MessageBox("X 越界，执行中断","中断");
							suspend=true;
						}
						break;
					}
					case 2:
					{
						X=X+1;
						if(X==max)
						{
							MessageBox("X 越界，执行中断","中断");
							suspend=true;
						}
						MessageBox("X 已自加1","自加");
						break;
					}
					case 3:
					{
						ofstream outfile;
						outfile.open("X.txt");
						if(!outfile) 
						{
							MessageBox("保存文件操作出错，执行中断","中断");
							suspend=true;
						}
						outfile<<"#"<<X<<"#";
						outfile.close(); 
						MessageBox("X 的内容已成功保存在 X.txt 文件中","保存");
						break;
					}
					case 4:
					{					
						s.Format(_T("%d"), X);
						MessageBox("X = "+s,"显示X");
						break;
					}
					case 5:
					{
						ShellExecute(NULL,"open","NOTEPAD.EXE",NULL,NULL,SW_SHOWNORMAL);
						MessageBox("已打开记事本","记事本");
						break;
					}
					case 6:
					{
						last=X%10;
						ShellExecute(NULL,"open",WebPage[last],NULL,NULL,SW_SHOW);
						MessageBox("已打开网页 : "+WebName[last],"网页");
						break;
					}
					case 7:
					{
						MessageBox("执行完成","结束");
						break;
					}		
				}
				if(suspend==true)
					break;
			}

		}
		else MessageBox("工作流图不连通，不能执行","提示");

		pDoc->tag=0;
		run=false;
	}

}
