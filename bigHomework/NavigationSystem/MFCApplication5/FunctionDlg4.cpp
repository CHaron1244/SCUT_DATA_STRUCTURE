// FunctionDlg4.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication5.h"
#include "afxdialogex.h"
#include "FunctionDlg4.h"


// FunctionDlg4 对话框

IMPLEMENT_DYNAMIC(FunctionDlg4, CDialogEx)

FunctionDlg4::FunctionDlg4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, PosA_Car(0)
	, PosB_Car(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

FunctionDlg4::~FunctionDlg4()
{
}

void FunctionDlg4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, PosA_Car);
	DDX_Text(pDX, IDC_EDIT2, PosB_Car);
}


BEGIN_MESSAGE_MAP(FunctionDlg4, CDialogEx)
END_MESSAGE_MAP()


// FunctionDlg4 消息处理程序
