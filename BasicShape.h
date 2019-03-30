#ifndef FILE_H
#define FILE_H
#define round(a) ( int ) ( a + .5 )

class CBasicShape :public CObject
{
protected:
	LOGFONT logFont;  
	CFont m_font;      
	COLORREF m_clr;    
	int tag;           //���ͼ�α�ǣ�������1��������2����Բ��3

	CString m_title;                    //��ͼ���ڲ���ӵ��ı�

	int function; //����

public:
	CBasicShape* LineFront;			//�������õ�ָ�룬�������ӵ�ͼ��
	CBasicShape* LineBehind;	
	int tag1;
	int tag2;

	CPoint point1;                  //�洢���α߿��������
	CPoint point2;

	bool in;//��ڱ�־
	bool out;//���ڱ�־

	int no;//ͼԪ�����еڼ���

	
public:
	void SetlogFont(LOGFONT *lf);
	void SetClr(COLORREF clr);
	LOGFONT* GetlogFont();
	CFont* GetFont();
	COLORREF GetClr();
	void SetTitle(CString title);//�����ı�����
	CString GetTitle() const;//�õ��ı�����
	CBasicShape();
	virtual ~CBasicShape();
	virtual void SetTag(int mid_tag);             //����ͼ�α��
	virtual int GetTag();						  //���ͼ�α��
	virtual void SetPoint(CPoint m_point1, CPoint m_point2);   //���ò�����
	virtual void Draw(CDC* pDC);					//��д��draw������
	virtual void Serialize(CArchive& ar);         //��д�����л����溯��
	virtual bool CheckRect(CPoint c_point);//����������Ƿ�����ͼԪ�ڣ���ѡ��
	virtual bool Check_Out_Rect(CPoint c_point1, CPoint c_point2);//�������Ƿ��ѡͼԪ�������ѡ��
	virtual void DrawTag(CClientDC* pDC);//�����ȵ�С����
	virtual void MovePoint(CPoint m_point1, CPoint m_point2);//�ı�ͼԪ����
	virtual bool in_hot_point(CPoint m_point);//����Ƿ����ȵ㷽����
	virtual void Zoom(CPoint m_point1, CPoint m_point2);//��������
	virtual void In_Draw(CClientDC* pDC);//�ػ�ͼԪ
	virtual void In_Draw_Point(CClientDC* pDC);//��ȥ�ȵ�
	void SetCharacter(CString mid_title);       //���ڴ洢���ֵĺ����������ĵ���serializa����

	CPoint GetPoint11();					
	CPoint GetPoint2();	//����ȡͼԪ�����µ�

	CBasicShape* GetLine_ptr1();				//������ߵ�ָ��
	CBasicShape* GetLine_ptr2();
	void AddTag();								//����ͼ�α��

	int GetWidth();								//���ͼ�ο�ȣ����������Զ�����

	void SetFunction(int f);//���ù���
	int GetFunction();//�õ�����
private:

};
#endif