// FunctionDlg1.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication5.h"
#include "afxdialogex.h"
#include "FunctionDlg1.h"


// FunctionDlg1 对话框

IMPLEMENT_DYNAMIC(FunctionDlg1, CDialogEx)

FunctionDlg1::FunctionDlg1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, point_x(0)
	, point_y(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

FunctionDlg1::~FunctionDlg1()
{
}

void FunctionDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, point_x);
	DDX_Text(pDX, IDC_EDIT2, point_y);
}


BEGIN_MESSAGE_MAP(FunctionDlg1, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &FunctionDlg1::OnEnChangeEdit1)
END_MESSAGE_MAP()


// FunctionDlg1 消息处理程序


void FunctionDlg1::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
