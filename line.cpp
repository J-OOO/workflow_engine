#include "stdafx.h"		
#include "workflow_engine.h"
#include "Line.h"
#include "math.h"
IMPLEMENT_SERIAL(CLine,CObject,1);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{
	width1=0;
	width2=0;
	mpoint1.x=mpoint2.x=mpoint3.x=mpoint4.x=0;
	mpoint1.y=mpoint2.y=mpoint3.y=mpoint4.y=0;
}

CLine::~CLine()
{

}

void CLine::SetTag(int mid_tag)
{
	tag=mid_tag;
}

void CLine::SetPoint(CPoint m_point1,CPoint m_point2)
{
	point1=m_point1;
	point2=m_point2;
}

void CLine::Draw(CDC* pDC)
{
	//重画以前图形为白色
	CPen pen(PS_SOLID,1,pDC->GetBkColor());  //白色实线画笔，决定画图的边线            
	CPen *pOldPen=pDC->SelectObject(&pen);  //画笔选入设备描述表

		if(point1.y<point2.y)
		{
			pDC->MoveTo(point2);
			pDC->LineTo(point2.x,(point1.y+point2.y)/2);
			pDC->LineTo(point1.x,(point1.y+point2.y)/2);
			pDC->LineTo(point1.x,point1.y);
		}
		if(point1.y>=point2.y&&point1.x!=point2.x)
		{
			pDC->MoveTo(point1);
			pDC->LineTo(point1.x,point1.y+20);
			if(((point2.x-point1.x)>=width1&&(point2.x-point1.x)>=width2)||((point1.x-point2.x)>=width1&&(point1.x-point2.x)>=width2))
			{
				pDC->LineTo((point1.x+point2.x)/2,point1.y+20);
				pDC->LineTo((point1.x+point2.x)/2,point2.y-20);
				pDC->LineTo(point2.x,point2.y-20);
			}
			else
			{
				if(point1.x<point2.x)
				{
					if(width1>width2)
					{
						pDC->LineTo(point2.x+width1/2+15,point1.y+20);
						pDC->LineTo(point2.x+width1/2+15,point2.y-20);
					}
					else		
					{
						pDC->LineTo(point2.x+width2/2+15,point1.y+20);
						pDC->LineTo(point2.x+width2/2+15,point2.y-20);
					}
					pDC->LineTo(point2.x,point2.y-20);
			
				}
				else
				{
					if(width1>width2)
					{
						pDC->LineTo(point2.x-width1/2-15,point1.y+20);
						pDC->LineTo(point2.x-width1/2-15,point2.y-20);
					}
					else		
					{
						pDC->LineTo(point2.x-width2/2-15,point1.y+20);
						pDC->LineTo(point2.x-width2/2-15,point2.y-20);
					}
					pDC->LineTo(point2.x,point2.y-20);
				}
			}
			pDC->LineTo(point2.x,point2.y);

		}
		    pDC->MoveTo(point2);
			pDC->LineTo(point2.x-5,point2.y-5);
			pDC->MoveTo(point2);
			pDC->LineTo(point2.x+5,point2.y-5);
	
	

	pDC->SelectObject(pOldPen);                
	//~重画白色


	point1=LineFront->GetPoint11();
	point2=LineBehind->GetPoint2();
	
	width1=LineFront->GetWidth();
	width2=LineBehind->GetWidth();


		if(point1.y<point2.y)
		{
			pDC->MoveTo(point1);
			pDC->LineTo(point1.x,(point1.y+point2.y)/2);
			pDC->LineTo(point2.x,(point1.y+point2.y)/2);
			pDC->LineTo(point2.x,point2.y);
			//获取中间点
			mpoint1.x=point1.x;
			mpoint1.y=(point1.y+point2.y)/2;
			mpoint2.x=point2.x;
			mpoint2.y=(point1.y+point2.y)/2;
			mpoint3=mpoint2;
			mpoint4=mpoint3;
		}
		if(point1.y>=point2.y&&point1.x!=point2.x)
		{
			pDC->MoveTo(point1);
			pDC->LineTo(point1.x,point1.y+20);
			
			mpoint1.x=point1.x;
			mpoint1.y=point1.y+20;
			
			if(((point2.x-point1.x)>=width1&&(point2.x-point1.x)>=width2)||((point1.x-point2.x)>=width1&&(point1.x-point2.x)>=width2))
			{
				pDC->LineTo((point1.x+point2.x)/2,point1.y+20);
				pDC->LineTo((point1.x+point2.x)/2,point2.y-20);
				pDC->LineTo(point2.x,point2.y-20);
				
				mpoint2.x=(point1.x+point2.x)/2;
				mpoint2.y=point1.y+20;
				mpoint3.x=(point1.x+point2.x)/2;
				mpoint3.y=point2.y-20;
				mpoint4.x=point2.x;
				mpoint4.y=point2.y-20;
				
			}
			else
			{
				if(point1.x<point2.x)
				{
					if(width1>width2)
					{
						pDC->LineTo(point2.x+width1/2+15,point1.y+20);
						pDC->LineTo(point2.x+width1/2+15,point2.y-20);
					
						mpoint2.x=point2.x+width1/2+15;
						mpoint2.y=point1.y+20;
						mpoint3.x=point2.x+width1/2+15;
						mpoint3.y=point2.y-20;
						
					}
					else		
					{
						pDC->LineTo(point2.x+width2/2+15,point1.y+20);
						pDC->LineTo(point2.x+width2/2+15,point2.y-20);
						mpoint2.x=point2.x+width2/2+15;
						mpoint2.y=point1.y+20;
						mpoint3.x=point2.x+width2/2+15;
						mpoint3.y=point2.y-20;
					}
					pDC->LineTo(point2.x,point2.y-20);
					mpoint4.x=point2.x;
					mpoint4.y=point2.y-20;
				}
				else
				{
					if(width1>width2)
					{
						pDC->LineTo(point2.x-width1/2-15,point1.y+20);
						pDC->LineTo(point2.x-width1/2-15,point2.y-20);
						mpoint2.x=point2.x-width1/2-15;
						mpoint2.y=point1.y+20;
						mpoint3.x=point2.x-width1/2-15;
						mpoint3.y=point2.y-20;
					}
					else		
					{
						pDC->LineTo(point2.x-width2/2-15,point1.y+20);
						pDC->LineTo(point2.x-width2/2-15,point2.y-20);
						mpoint2.x=point2.x-width2/2-15;
						mpoint2.y=point1.y+20;
						mpoint3.x=point2.x-width2/2-15;
						mpoint3.y=point2.y-20;
					}
					pDC->LineTo(point2.x,point2.y-20);
					mpoint4.x=point2.x;
					mpoint4.y=point2.y-20;
				}
			}
			pDC->LineTo(point2.x,point2.y);

		}
		    pDC->MoveTo(point2);
			pDC->LineTo(point2.x-5,point2.y-5);
			pDC->MoveTo(point2);
			pDC->LineTo(point2.x+5,point2.y-5);
}

bool CLine::CheckRect(CPoint c_point)
{
	CPoint t_point1,t_point2;
	if((pow((float)point1.x,2)+pow((float)point1.y,2))>(pow((float)mpoint1.x,2)+pow((float)mpoint1.y,2))) 
	{
		t_point1.x=mpoint1.x-10;
		t_point1.y=mpoint1.y-10;
		t_point2.x=point1.x+10;
		t_point2.y=point1.y;
		CRect crect1(t_point1,t_point2);
		if(crect1.PtInRect(c_point)) return true;
	}
	else if((pow((float)point1.x,2)+pow((float)point1.y,2))<(pow((float)mpoint1.x,2)+pow((float)mpoint1.y,2))) 
	{
		t_point2.x=mpoint1.x+10;
		t_point2.y=mpoint1.y+10;
		t_point1.x=point1.x-10;
		t_point1.y=point1.y;
		CRect crect1(t_point1,t_point2);
		if(crect1.PtInRect(c_point)) return true;
	}
	if((pow((float)mpoint2.x,2)+pow((float)mpoint2.y,2))>(pow((float)mpoint1.x,2)+pow((float)mpoint1.y,2))) 
	{
		t_point1.x=mpoint1.x-10;
		t_point1.y=mpoint1.y-10;
		t_point2.x=mpoint2.x+10;
		t_point2.y=mpoint2.y+10;
		CRect crect1(t_point1,t_point2);
		if(crect1.PtInRect(c_point)) return true;
	}
	else if((pow((float)mpoint2.x,2)+pow((float)mpoint2.y,2))<(pow((float)mpoint1.x,2)+pow((float)mpoint1.y,2))) 
	{
		t_point2.x=mpoint1.x+10;
		t_point2.y=mpoint1.y+10;
		t_point1.x=mpoint2.x-10;
		t_point1.y=mpoint2.y-10;
		CRect crect1(t_point1,t_point2);
		if(crect1.PtInRect(c_point)) 
			return true;
	}
	if((pow((float)mpoint2.x,2)+pow((float)mpoint2.y,2))>(pow((float)mpoint3.x,2)+pow((float)mpoint3.y,2))) 
	{
		t_point1.x=mpoint3.x-10;
		t_point1.y=mpoint3.y-10;
		t_point2.x=mpoint2.x+10;
		t_point2.y=mpoint2.y+10;
		CRect crect1(t_point1,t_point2);
		if(crect1.PtInRect(c_point)) 
			return true;
	}
	else if((pow((float)mpoint2.x,2)+pow((float)mpoint2.y,2))<(pow((float)mpoint3.x,2)+pow((float)mpoint3.y,2))) 
	{
		t_point2.x=mpoint3.x+10;
		t_point2.y=mpoint3.y+10;
		t_point1.x=mpoint2.x-10;
		t_point1.y=mpoint2.y-10;
		CRect crect1(t_point1,t_point2);
		if(crect1.PtInRect(c_point)) 
			return true;
	}
	if((pow((float)mpoint3.x,2)+pow((float)mpoint3.y,2))>(pow((float)mpoint4.x,2)+pow((float)mpoint4.y,2))) 
	{
		t_point1.x=mpoint4.x-10;
		t_point1.y=mpoint4.y-10;
		t_point2.x=mpoint3.x+10;
		t_point2.y=mpoint3.y+10;
		CRect crect1(t_point1,t_point2);
		if(crect1.PtInRect(c_point)) return true;
	}
	else if((pow((float)mpoint3.x,2)+pow((float)mpoint3.y,2))<(pow((float)mpoint4.x,2)+pow((float)mpoint4.y,2))) 
	{
		t_point2.x=mpoint4.x+10;
		t_point2.y=mpoint4.y+10;
		t_point1.x=mpoint3.x-10;
		t_point1.y=mpoint3.y-10;
		CRect crect1(t_point1,t_point2);
		if(crect1.PtInRect(c_point)) return true;
	}
	if((pow((float)point2.x,2)+pow((float)point2.y,2))>(pow((float)mpoint4.x,2)+pow((float)mpoint4.y,2))) 
	{
		t_point1.x=mpoint4.x-10;
		t_point1.y=mpoint4.y-10;
		t_point2.x=point2.x+10;
		t_point2.y=point2.y;
		CRect crect1(t_point1,t_point2);
		if(crect1.PtInRect(c_point)) return true;
	}
	else if((pow((float)point2.x,2)+pow((float)point2.y,2))<(pow((float)mpoint4.x,2)+pow((float)mpoint4.y,2))) 
	{
		t_point2.x=mpoint4.x+10;
		t_point2.y=mpoint4.y+10;
		t_point1.x=point2.x-10;
		t_point1.y=point2.y;
		CRect crect1(t_point1,t_point2);
		if(crect1.PtInRect(c_point)) return true;
	} 
		return FALSE;
}

void CLine::Serialize(CArchive &ar)
{
}

void CLine::DrawTag(CClientDC* pDC)
{	
	CPoint t_point1;
	CPoint t_point2;
	CBrush brushRed(RGB(255, 0, 0));
    CBrush* pOldBrush = pDC->SelectObject(&brushRed);

	t_point1.x=point1.x-5;
	t_point1.y=point1.y-5;
	t_point2.x=t_point1.x+10;
	t_point2.y=t_point1.y+10;
	pDC->Rectangle(CRect(t_point1,t_point2));
	t_point1.x=+point2.x-5;
	t_point1.y=point2.y-5;
	t_point2.x=t_point1.x+10;
	t_point2.y=t_point1.y+10;
	pDC->Rectangle(CRect(t_point1,t_point2));

	pDC->SelectObject(pOldBrush);
}

void CLine::In_Draw_Point(CClientDC* pDC)
{
	CPoint t_point1;
	CPoint t_point2;
	CPen pen(PS_SOLID,1,pDC->GetBkColor()); 
	CPen *pOldPen=pDC->SelectObject(&pen);
	CBrush brushBlue(pDC->GetBkColor());
    CBrush* pOldBrush = pDC->SelectObject(&brushBlue);

	t_point1.x=point1.x-5;
	t_point1.y=point1.y-5;
	t_point2.x=t_point1.x+10;
	t_point2.y=t_point1.y+10;
	pDC->Rectangle(CRect(t_point1,t_point2));
	t_point1.x=point2.x-5;
	t_point1.y=point2.y-5;
	t_point2.x=t_point1.x+10;
	t_point2.y=t_point1.y+10;
	pDC->Rectangle(CRect(t_point1,t_point2));

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

bool CLine::in_hot_point(CPoint m_point)
{
	return false;
}

bool CLine::Check_Out_Rect(CPoint c_point1,CPoint c_point2)
{
	CRect crect1(c_point1,c_point2);
	if((crect1.PtInRect(point1)&&crect1.PtInRect(point2)))
		return TRUE;
	else
		return FALSE;
}