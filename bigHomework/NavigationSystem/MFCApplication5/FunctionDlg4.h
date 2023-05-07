#pragma once
#include "afxdialogex.h"


// FunctionDlg4 对话框

class FunctionDlg4 : public CDialogEx
{
	DECLARE_DYNAMIC(FunctionDlg4)

public:
	FunctionDlg4(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FunctionDlg4();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double PosA_Car;
	double PosB_Car;
};
