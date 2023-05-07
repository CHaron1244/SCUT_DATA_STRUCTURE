#pragma once
#include "afxdialogex.h"


// FunctionDlg1 对话框

class FunctionDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(FunctionDlg1)

public:
	FunctionDlg1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FunctionDlg1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	double point_x;
	double point_y;
};
