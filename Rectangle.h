#include "BasicShape.h"	
class CRectangle : public CBasicShape  
{
protected:
	DECLARE_SERIAL(CRectangle)
		int x1,x2,y1,y2;

public:
	CRectangle();
	virtual ~CRectangle();
	void SetTag(int mid_tag);
    int GetTag();	
	void SetPoint(CPoint m_point1,CPoint m_point2);
	void Draw(CDC* pDC);
	void Serialize(CArchive &ar);
		void DrawTag(CClientDC* pDC);
	bool CheckRect(CPoint c_point);
	bool Check_Out_Rect(CPoint c_point1,CPoint c_point2);
	void MovePoint(CPoint m_point1,CPoint m_point2);
	bool in_hot_point(CPoint m_point);
	void Zoom(CPoint m_point1,CPoint m_point2);
	void In_Draw(CClientDC* pDC);
	void In_Draw_Point(CClientDC* pDC);
};