#ifndef FILE_H
#define FILE_H
#define round(a) ( int ) ( a + .5 )

class CBasicShape :public CObject
{
protected:
	LOGFONT logFont;  
	CFont m_font;      
	COLORREF m_clr;    
	int tag;           //标记图形标记，矩形是1，折线是2，椭圆是3

	CString m_title;                    //在图形内部添加的文本

	int function; //功能

public:
	CBasicShape* LineFront;			//折现内用的指针，用于连接的图形
	CBasicShape* LineBehind;	
	int tag1;
	int tag2;

	CPoint point1;                  //存储矩形边框的两个点
	CPoint point2;

	bool in;//入口标志
	bool out;//出口标志

	int no;//图元数组中第几个

	
public:
	void SetlogFont(LOGFONT *lf);
	void SetClr(COLORREF clr);
	LOGFONT* GetlogFont();
	CFont* GetFont();
	COLORREF GetClr();
	void SetTitle(CString title);//设置文本内容
	CString GetTitle() const;//得到文本内容
	CBasicShape();
	virtual ~CBasicShape();
	virtual void SetTag(int mid_tag);             //设置图形标记
	virtual int GetTag();						  //获得图形标记
	virtual void SetPoint(CPoint m_point1, CPoint m_point2);   //设置参数点
	virtual void Draw(CDC* pDC);					//重写的draw（）。
	virtual void Serialize(CArchive& ar);         //重写的序列化保存函数
	virtual bool CheckRect(CPoint c_point);//检查鼠标左键是否点击在图元内，即选中
	virtual bool Check_Out_Rect(CPoint c_point1, CPoint c_point2);//检查鼠标是否框选图元，即多个选中
	virtual void DrawTag(CClientDC* pDC);//绘制热点小方块
	virtual void MovePoint(CPoint m_point1, CPoint m_point2);//改变图元数据
	virtual bool in_hot_point(CPoint m_point);//鼠标是否在热点方块内
	virtual void Zoom(CPoint m_point1, CPoint m_point2);//放缩功能
	virtual void In_Draw(CClientDC* pDC);//重绘图元
	virtual void In_Draw_Point(CClientDC* pDC);//擦去热点
	void SetCharacter(CString mid_title);       //用于存储文字的函数，用于文档类serializa函数

	CPoint GetPoint11();					
	CPoint GetPoint2();	//用于取图元的上下点

	CBasicShape* GetLine_ptr1();				//获得折线的指针
	CBasicShape* GetLine_ptr2();
	void AddTag();								//设置图形标记

	int GetWidth();								//获得图形宽度，用于折现自动绕行

	void SetFunction(int f);//设置功能
	int GetFunction();//得到功能
private:

};
#endif