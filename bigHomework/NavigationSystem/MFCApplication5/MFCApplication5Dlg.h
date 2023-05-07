// MFCApplication5Dlg.h: 头文件
//

#pragma once
#include <afxwin.h>
#include "afxdialogex.h"

// CMFCApplication5Dlg 对话框
class CMFCApplication5Dlg : public CDialogEx
{
// 构造
public:
	// 标准构造函数
	CMFCApplication5Dlg(CWnd* pParent = nullptr);
	// 析构函数
	~CMFCApplication5Dlg();
	
	// 屏幕DC兼容的内存DC
	CDC m_memDC;
	// 用于保存静态文本框的对象指针
	CWnd* m_pDrawWnd;
	// 静态文本框大小矩形
	CRect rect;
	// 上下文CDC
	CDC* m_pDC;
	// 鼠标选中点的信息
	CString point_info;

	// 初始化和双缓冲相关的数据
	void InitialDBB();
	// 清空静态文本框
	void clear();
	// 无车流量画图
	void draw(int level);
	// 有车流量画图
	void drawCar();
	// 画最近100点
	void drawFind(double x, double y, int num);
	// 无车流量Dij
	void printDij(int x,int y);
	// 有车流量Dij
	void printDijCar(int x, int y);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//更改颜色的消息响应函数
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	BOOL PreTranslateMessage(MSG* pMsg);
};

