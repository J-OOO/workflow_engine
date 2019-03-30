#include "BasicShape.h"		
class CEllipse : public CBasicShape  
{
protected:
		DECLARE_SERIAL(CEllipse)
public:
	CEllipse();
	virtual ~CEllipse();
	void SetTag(int mid_tag);
    int GetTag();
	void SetPoint(CPoint m_point1,CPoint m_point2);
	void Draw(CDC* pDC);
	void Serialize(CArchive &ar);
	bool CheckRect(CPoint c_point);
	bool Check_Out_Rect(CPoint c_point1,CPoint c_point2);
	void DrawTag(CClientDC* pDC);
	void MovePoint(CPoint m_point1,CPoint m_point2);
	bool in_hot_point(CPoint m_point);
	void Zoom(CPoint m_point1,CPoint m_point2);
	void In_Draw(CClientDC* pDC);
	void In_Draw_Point(CClientDC* pDC);
};