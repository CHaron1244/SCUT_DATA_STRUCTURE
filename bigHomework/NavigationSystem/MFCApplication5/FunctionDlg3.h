#pragma once
#include "afxdialogex.h"


// FunctionDlg3 对话框

class FunctionDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(FunctionDlg3)

public:
	FunctionDlg3(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FunctionDlg3();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int PosA;
	int PosB;
};
