// MFCApplication5Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
#include "afxdialogex.h"
#include "Graph.h"
#include "Point.h"
#include "FunctionDlg1.h"
#include "FunctionDlg2.h"
#include "FunctionDlg3.h"
#include "FunctionDlg4.h"
#include <queue>
#include <GdiPlus.h>
#include "string"

using namespace std;
using namespace Gdiplus;

// 全局地图变量
Graph G;

// 显示倍率等级 设置为1~10，分别显示1000，900，800~100
int level = 1;

// 移动方向
enum left_right
{
	_left, _m_, _right
};
enum up_down
{
	_up, _m, _down
};

// 缩放时rect位置
double widthCut = 0;		// 左上角x
double heightCut = 0;		// 左上角y
double widthNow = 1018;		// 宽度
double heightNow = 1047;	// 高度

// 当前模式 0 代表无车流量 1 代表有车流量
bool car_Consider = 0;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFCApplication5Dlg 对话框
CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION5_DIALOG, pParent)
	, point_info(_T("未选择点")), rect(0, 0, 1000, 1000)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	//m_memDC = nullptr;
	m_pDrawWnd = nullptr;
	m_pDC = nullptr;
}

CMFCApplication5Dlg::~CMFCApplication5Dlg()
{
	//m_pDrawWnd->ReleaseDC(m_pDC);
}

void CMFCApplication5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, point_info);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication5Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication5Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication5Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication5Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication5Dlg::OnBnClickedButton5)
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void CMFCApplication5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// CMFCApplication5Dlg 消息处理程序
BOOL CMFCApplication5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 添加随机数种子
	srand((unsigned)time(nullptr));
	// 根据样式计算窗口大小
	AdjustWindowRectEx(&rect, WS_CAPTION, FALSE, 0);
	// 设置窗口大小
	SetWindowPos(NULL, GetSystemMetrics(SM_CXSCREEN) / 2 - 500, 0, rect.Width() + 125, rect.Height(), 0);
	// 获得静态窗口对象指针
	m_pDrawWnd = GetDlgItem(IDC_STATIC);
	// 移动并重新设置静态对话框大小
	m_pDrawWnd->MoveWindow(125, 0, rect.Width(), rect.Height());
	// 初始化pDC
	m_pDC = m_pDrawWnd->GetDC();
	// 初始化双缓冲相关的数据
	InitialDBB();
	// 将静态对话框清空为白色
	clear();
	//
	GetDlgItem(IDC_STATIC_MAP)->MoveWindow(0, rect.Height() - 300, 100, 100);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，这将由框架自动完成。
void CMFCApplication5Dlg::OnPaint()
{
	CDialog::OnPaint();

	//绘图
	PAINTSTRUCT ps;
	CDC* pDC = m_pDrawWnd->BeginPaint(&ps);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_memDC, 0, 0, SRCCOPY);
	m_pDrawWnd->EndPaint(&ps);
	m_pDrawWnd->ReleaseDC(pDC);
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CMFCApplication5Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetBkColor(RGB(255, 255, 255));
	}
	return hbr;
}

void CMFCApplication5Dlg::InitialDBB()
{
	CDC* sDC = m_pDrawWnd->GetDC();
	// 为屏幕DC创建兼容的内存DC
	if (!m_memDC.CreateCompatibleDC(sDC))
	{
		::PostQuitMessage(0);
	}
	// 创建位图,不能是m_memDC，否则无颜色
	CBitmap m_Bmp;
	m_Bmp.CreateCompatibleBitmap(sDC, rect.Width(), rect.Height());
	// 相当于选择画布,m_pDrawWnd->
	::SelectObject(m_memDC.GetSafeHdc(), m_Bmp);
	m_pDrawWnd->ReleaseDC(sDC);
}

void CMFCApplication5Dlg::clear()
{
	//设置白色画刷
	CBrush Brush(RGB(255, 255, 255));
	m_memDC.FillRect(rect, &Brush);
	m_pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_memDC, 0, 0, SRCCOPY);
}

void CMFCApplication5Dlg::draw(int level = 1)
{
	// 清屏
	clear();

	// 设置画刷和画笔
	CBrush newBrush;
	newBrush.CreateSolidBrush(RGB(0, 0, 0));
	m_memDC.SelectObject(&newBrush);
	CPen pen(PS_SOLID, 1, RGB(172, 229, 255));
	m_memDC.SelectObject(&pen);

	if (level >= 1 && level <= 4)
	{
		int win_row = pow(2, level) * 4, win_col = pow(2, level) * 4;
		int win_num = win_row * win_col;
		int len_row = ROW / win_row, len_col = COL / win_col;
		for (int i = 1; i <= G.NodeNum; ++i)
		{
			int x = (G.p[i].x - 1) / len_row + 1, y = (G.p[i].y - 1) / len_col + 1;
			//点不在有效区域内
			if (x > win_row || x < 1 || y < 1 || y>win_col)
			{
				continue;
			}
			int tmp = (x - 1) * win_col + y;
			if (G.point_much[level][tmp])
			{
				int u = G.behalf_point[level][tmp];
				if (u < 0) continue;
				for (auto& o : G.e[i]) {
					int pos = G.findpos(G.p[o.v], level);
					if (pos<1 || pos>win_num) continue;
					int v = o.v;
					if (G.point_much[level][pos])
					{
						v = G.behalf_point[level][pos];
					}
					m_memDC.Ellipse(G.p[u].x - 3, G.p[u].y - 3, G.p[u].x + 3, G.p[u].y + 3);
					m_memDC.Ellipse(G.p[v].x - 3, G.p[v].y - 3, G.p[v].x + 3, G.p[v].y + 3);
					m_memDC.MoveTo(G.p[u].x, G.p[u].y);
					m_memDC.LineTo(G.p[v].x, G.p[v].y);
				}
			}
		}
	}
	else
	{
		for (int i = 1; i <= G.NodeNum; i++)
		{
			//画点
			m_memDC.Ellipse(G.p[i].x - 3, G.p[i].y - 3, G.p[i].x + 3, G.p[i].y + 3);
			for (auto& v : G.e[i])
			{
				//画线
				m_memDC.MoveTo(G.p[i].x, G.p[i].y);
				m_memDC.LineTo(G.p[v.v].x, G.p[v.v].y);
			}
		}
	}

	// 一次性的将内存设备环境上绘制完毕的图形"贴"到屏幕上
	m_pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_memDC, 0, 0, SRCCOPY);
}

void CMFCApplication5Dlg::drawCar()
{
	//清屏
	clear();

	//设置画刷和画笔
	CBrush newBrush;
	newBrush.CreateSolidBrush(RGB(0, 0, 0));
	m_memDC.SelectObject(&newBrush);

	// 根据车流量程度显示不同颜色
	CPen pen1(PS_SOLID, 1, RGB(55, 125, 35));
	CPen pen2(PS_SOLID, 1, RGB(161, 251, 142));
	CPen pen3(PS_SOLID, 1, RGB(185, 122, 87));
	CPen pen4(PS_SOLID, 1, RGB(235, 51, 36));

	for (int i = 1; i <= G.NodeNum; i++)
	{
		//画点
		m_memDC.Ellipse(G.p[i].x - 3, G.p[i].y - 3, G.p[i].x + 3, G.p[i].y + 3);
		for (auto& v : G.e[i])
		{
			switch (v.flow)
			{
			case 1:
			case 2:
			case 3:
				m_memDC.SelectObject(&pen1);
				break;
			case 4:
			case 5:
			case 6:
				m_memDC.SelectObject(&pen2);
				break;
			case 7:
			case 8:
				m_memDC.SelectObject(&pen3);
				break;
			case 9:
			case 10:
				m_memDC.SelectObject(&pen4);
				break;
			default:
				break;
			}
			//画线
			m_memDC.MoveTo(G.p[i].x, G.p[i].y);
			m_memDC.LineTo(G.p[v.v].x, G.p[v.v].y);
		}
	}
	m_pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_memDC, 0, 0, SRCCOPY);
}

void CMFCApplication5Dlg::drawFind(double x, double y, int num = 100)
{
	// 清屏
	clear();

	// 调用找最近num个点的函数
	G.FindNearestPoint(point(x, y), num);
	vector<int> nearestPoints = G.NearestPoint;

	// 设置画刷和画笔
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	m_memDC.SelectObject(&brush);
	CPen pen(PS_SOLID, 1, RGB(172, 229, 255));
	m_memDC.SelectObject(&pen);

	for (int v : nearestPoints)
	{
		// 画点
		m_memDC.Ellipse(G.p[v].x - 2, G.p[v].y - 2, G.p[v].x + 2, G.p[v].y + 2);
		for (Edge& u : G.e[v])
		{
			if (find(nearestPoints.begin(), nearestPoints.end(), u.v) != nearestPoints.end())
			{
				// 画线
				m_memDC.MoveTo(G.p[v].x, G.p[v].y);
				m_memDC.LineTo(G.p[u.v].x, G.p[u.v].y);
			}
		}
	}

	// 一次性的将内存设备环境上绘制完毕的图形"贴"到屏幕上
	m_pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_memDC, 0, 0, SRCCOPY);
}

void CMFCApplication5Dlg::printDij(int x, int y)
{
	//清屏
	clear();

	G.Dij(x, y);

	//创造画笔和画刷
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));//点的颜色为黑色
	m_memDC.SelectObject(&brush);
	CPen pen(PS_SOLID, 1, RGB(172, 229, 255)); //线的颜色为红色
	m_memDC.SelectObject(&pen);

	for (Edge& edge : G.Shortestpath)
	{
		//画点
		m_memDC.Ellipse(G.p[edge.u].x - 2, G.p[edge.u].y - 2, G.p[edge.u].x + 2, G.p[edge.u].y + 2);
		m_memDC.Ellipse(G.p[edge.v].x - 2, G.p[edge.v].y - 2, G.p[edge.v].x + 2, G.p[edge.v].y + 2);
		//画线
		m_memDC.MoveTo(G.p[edge.u].x, G.p[edge.u].y);
		m_memDC.LineTo(G.p[edge.v].x, G.p[edge.v].y);
	}

	// 一次性的将内存设备环境上绘制完毕的图形"贴"到屏幕上
	m_pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_memDC, 0, 0, SRCCOPY);
}

void CMFCApplication5Dlg::printDijCar(int x, int y)
{
	//清屏
	clear();
	G.LeastCrossTime(x, y);

	//创造画笔和画刷
	CBrush newBrush;
	newBrush.CreateSolidBrush(RGB(0, 0, 0));
	m_memDC.SelectObject(&newBrush);
	CPen pen1(PS_SOLID, 1, RGB(55, 125, 35));
	CPen pen2(PS_SOLID, 1, RGB(161, 251, 142));
	CPen pen3(PS_SOLID, 1, RGB(185, 122, 87));
	CPen pen4(PS_SOLID, 1, RGB(235, 51, 36));

	for (Edge& edge : G.LeastTime)
	{
		//画点
		m_memDC.Ellipse(G.p[edge.u].x - 3, G.p[edge.u].y - 3, G.p[edge.u].x + 3, G.p[edge.u].y + 3);
		m_memDC.Ellipse(G.p[edge.v].x - 3, G.p[edge.v].y - 3, G.p[edge.v].x + 3, G.p[edge.v].y + 3);
		switch (edge.flow)
		{
		case 1:
		case 2:
		case 3:
			m_memDC.SelectObject(&pen1);
			break;
		case 4:
		case 5:
		case 6:
			m_memDC.SelectObject(&pen2);
			break;
		case 7:
		case 8:
			m_memDC.SelectObject(&pen3);
			break;
		case 9:
		case 10:
			m_memDC.SelectObject(&pen4);
			break;
		default:
			break;
		}
		//画线
		m_memDC.MoveTo(G.p[edge.u].x, G.p[edge.u].y);
		m_memDC.LineTo(G.p[edge.v].x, G.p[edge.v].y);
	}

	// 一次性的将内存设备环境上绘制完毕的图形"贴"到屏幕上
	m_pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_memDC, 0, 0, SRCCOPY);
}

void CMFCApplication5Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;				// 用于保存DoModal函数的返回值   
	FunctionDlg1 Dlg;			// 构造对话框类CDlg的实例   
	nRes = Dlg.DoModal();		// 弹出对话框  

	if (IDOK == nRes) {
		drawFind(Dlg.point_x, Dlg.point_y, 10);
	}
	else if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;
}

void CMFCApplication5Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;				// 用于保存DoModal函数的返回值   
	FunctionDlg2 Dlg;           // 构造对话框类CDlg的实例   
	nRes = Dlg.DoModal();		// 弹出对话框   

	if (IDOK == nRes) {
		level = Dlg.level;

		// 根据 level 选择绘图
		draw((level + 1) / 2);

		double num = (level - 1) * 100;
		widthNow = 1018 - num;
		heightNow = 1047 - num;
		widthCut = num / 2;
		heightCut = num / 2;
		m_pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &m_memDC, widthCut, heightCut, widthNow, heightNow, SRCCOPY);
	}

	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;
}

void CMFCApplication5Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   
	FunctionDlg3 Dlg;           // 构造对话框类CDlg的实例   
	nRes = Dlg.DoModal();  // 弹出对话框   

	if (IDOK == nRes)
	{
		if (Dlg.PosA <= 0 && Dlg.PosB <= 0)
		{
			MessageBoxA(0, "param error", "error", MB_OK);
			return;
		}
		if (car_Consider == 0)
			printDij(Dlg.PosA, Dlg.PosB);
		else
			//画考虑了车流的最短路径
			printDijCar(Dlg.PosA, Dlg.PosB);
	}
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;
}

void CMFCApplication5Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码  
	if (car_Consider == 0)
	{
		car_Consider = 1;
		G.update_flow();
		drawCar();
		GetDlgItem(IDC_BUTTON4)->SetWindowText(L"设置为\n无车流");
	}
	else
	{
		car_Consider = 0;
		draw();
		GetDlgItem(IDC_BUTTON4)->SetWindowText(L"设置为\n有车流");
	}
}

void CMFCApplication5Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	// 重新生成随机大地图
	G.NewGraph1_1(10000, 10500);

	// 使用绘图函数
	draw();

	// 初始化状态信息
	car_Consider = 0;
	widthCut = 0;
	heightCut = 0;
	widthNow = 1018;
	heightNow = 1047;
	level = 1;

	// 激活所有按钮控件
	GetDlgItem(IDC_BUTTON1)->EnableWindow();
	GetDlgItem(IDC_BUTTON2)->EnableWindow();
	GetDlgItem(IDC_BUTTON3)->EnableWindow();
	GetDlgItem(IDC_BUTTON4)->EnableWindow();
}

BOOL CMFCApplication5Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//将鼠标位置转换为相对静态对话框位置
	m_pDrawWnd->ScreenToClient(&point);

	//鼠标放在图片窗口
	if (rect.PtInRect(point))
	{
		//放大图片
		if (zDelta > 0)
		{
			if (level < 10)
			{
				level++;
			}
			else
				return CDialogEx::OnMouseWheel(nFlags, zDelta, point);
		}
		//缩小图片
		else if (zDelta < 0)
		{
			if (level > 1)
			{
				level--;
			}
			else
				return CDialogEx::OnMouseWheel(nFlags, zDelta, point);
		}

		// 根据 level 选择绘图
		draw((level + 1) / 2);

		// 根据 level 进行缩放
		double num = (level - 1) * 100;
		widthNow = 1018 - num;
		heightNow = 1047 - num;
		widthCut = num / 2;
		heightCut = num / 2;

		// 重新绘制图片
		m_pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &m_memDC, widthCut, heightCut, widthNow, heightNow, SRCCOPY);
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, point);
}

void CMFCApplication5Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// 更新鼠标相对于静态对话框位置
	CPoint tmpP = CPoint(point.x - 125, point.y);

	// 鼠标放在图片窗口
	if (rect.PtInRect(tmpP))
	{
		// 判断当前是否点击到某个点
		for (int i = 1; i <= G.NodeNum; i++)
		{
			if (point.x - 125 - G.p[i].x <= 2
				&& point.x - 125 - G.p[i].x >= -2
				&& point.y - G.p[i].y <= 2
				&& point.y - G.p[i].y >= -2)
			{
				// 更新点信息到 point_info
				string str;
				str = to_string(i) + "号点\r\n坐标:\n(" + to_string(G.p[i].x) + ",\n" + to_string(G.p[i].y) + ")";
				point_info = str.c_str();
				UpdateData(FALSE);
			}
		}
	}
}

BOOL CMFCApplication5Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		int dir_left_rigth = _m, dir_up_down = _m;

		// 判断当前键盘状态 哪个键被按下
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			dir_left_rigth = _left;
			break;
		case VK_RIGHT:
			dir_left_rigth = _right;
			break;
		case VK_UP:
			dir_up_down = _up;
			break;
		case VK_DOWN:
			dir_up_down = _down;
			break;
		default:
			break;
		}

		// 根据按下键盘的信息更新绘图位置
		switch (dir_left_rigth)
		{
		case _left:
			if (widthCut > 100)
				widthCut -= 100;
			break;
		case _right:
			if (widthCut + widthNow <= 918)
				widthCut += 100;
			break;
		case _m:
		default:
			break;
		}
		switch (dir_up_down)
		{
		case _up:
			if (heightCut >= 100)
				heightCut -= 100;
			break;
		case _down:
			if (heightCut + heightNow <= 947)
				heightCut += 100;
			break;
		case _m:
		default:
			break;
		}

		// 重新绘制图片
		m_pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &m_memDC, widthCut, heightCut, widthNow, heightNow, SRCCOPY);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}