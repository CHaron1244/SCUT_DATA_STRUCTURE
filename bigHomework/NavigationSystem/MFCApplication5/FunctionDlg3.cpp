// FunctionDlg3.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication5.h"
#include "afxdialogex.h"
#include "FunctionDlg3.h"


// FunctionDlg3 对话框

IMPLEMENT_DYNAMIC(FunctionDlg3, CDialogEx)

FunctionDlg3::FunctionDlg3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	PosA = NULL;
	PosB = NULL;
}

FunctionDlg3::~FunctionDlg3()
{
}

void FunctionDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, PosA);
	DDX_Text(pDX, IDC_EDIT2, PosB);
}


BEGIN_MESSAGE_MAP(FunctionDlg3, CDialogEx)
END_MESSAGE_MAP()


// FunctionDlg3 消息处理程序
