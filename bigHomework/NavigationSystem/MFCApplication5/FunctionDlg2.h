#pragma once
#include "afxdialogex.h"


// FunctionDlg2 对话框

class FunctionDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(FunctionDlg2)

public:
	FunctionDlg2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FunctionDlg2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int level;
};
