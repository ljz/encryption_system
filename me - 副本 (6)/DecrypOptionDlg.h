#pragma once


// DecrypOptionDlg 对话框

class DecrypOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(DecrypOptionDlg)

public:
	DecrypOptionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DecrypOptionDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DECRYP_CHOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChoseFinish();
	//CString mDesUnKey;
	CString m3DesUnKey;
	//CString mAesUnKey;
	int CheckState;
	CString mDesUnKey;
	CString mAesUnKey;
};
