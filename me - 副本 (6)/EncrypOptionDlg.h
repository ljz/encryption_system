#pragma once
#include "resource.h"
#include "meDlg.h"
// CEncrypOptionDlg �Ի���


class CEncrypOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(CEncrypOptionDlg)

public:
	CEncrypOptionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEncrypOptionDlg();

// �Ի�������			   
	enum { IDD = IDD_DIALOG_ENCRYP_CHOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChoseFinish();
	CString mDesKey;
	CString m3DesKey;
	CString mAesKey;
	int CheckState;
	afx_msg void OnBnClickedButtonCreateKeys();
};

