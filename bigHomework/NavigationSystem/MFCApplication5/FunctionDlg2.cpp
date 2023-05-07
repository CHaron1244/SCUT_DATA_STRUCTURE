// FunctionDlg2.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication5.h"
#include "afxdialogex.h"
#include "FunctionDlg2.h"


// FunctionDlg2 对话框

IMPLEMENT_DYNAMIC(FunctionDlg2, CDialogEx)

FunctionDlg2::FunctionDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, level(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

FunctionDlg2::~FunctionDlg2()
{
}

void FunctionDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, level);
}


BEGIN_MESSAGE_MAP(FunctionDlg2, CDialogEx)
END_MESSAGE_MAP()


// FunctionDlg2 消息处理程序
