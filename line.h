#include "BasicShape.h"	

class CLine : public CBasicShape   
{
protected:
	DECLARE_SERIAL(CLine)
public:
	CLine();						
	virtual ~CLine();
	void SetTag(int mid_tag);
	void SetPoint(CPoint m_point1,CPoint m_point2);
	void Draw(CDC* pDC);
    void Serialize(CArchive &ar);
	bool CheckRect(CPoint c_point);
	void DrawTag(CClientDC* pDC);
	void In_Draw_Point(CClientDC* pDC);
	bool in_hot_point(CPoint m_point);
	 bool Check_Out_Rect(CPoint c_point1,CPoint c_point2);
public:
	int width1;				//���ڱ�����������ͼ�εĿ��
	int width2;
	CPoint mpoint1;			//���������м�Ĺյ�
	CPoint mpoint2;
	CPoint mpoint3;
	CPoint mpoint4;

};