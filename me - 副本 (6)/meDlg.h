// meDlg.h : 头文件
//

#pragma once


// CmeDlg 对话框
class CmeDlg : public CDialog
{
// 构造
public:
	CmeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChosePlainFile();
	CString strTemp ;//明文字符串
	double m_nLineCount1;
	double m_nLineCount2;
	CString m_edit_plain;
	CFile myMingwenFile;
	CFile myMiwenFile;
	//afx_msg void OnBnClickedButtonChoseEncrypAlogrithm();
	afx_msg void OnBnClickedButtonEncrypOption();
	afx_msg void OnBnClickedButtonEncryp();
	afx_msg void OnBnClickedButtonChoseCipherFile();
	afx_msg void OnBnClickedButtonChoseDncrypAlogrithm();
	afx_msg void OnBnClickedButtonDecryp();
	CString m_edit_miwen;
};
