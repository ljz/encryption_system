#pragma once
#include "resource.h"
#include "meDlg.h"
// CEncrypOptionDlg 对话框


class CEncrypOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(CEncrypOptionDlg)

public:
	CEncrypOptionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEncrypOptionDlg();

// 对话框数据			   
	enum { IDD = IDD_DIALOG_ENCRYP_CHOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChoseFinish();
	CString mDesKey;
	CString m3DesKey;
	CString mAesKey;
	int CheckState;
	afx_msg void OnBnClickedButtonCreateKeys();
};

