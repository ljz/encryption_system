// meDlg.h : ͷ�ļ�
//

#pragma once


// CmeDlg �Ի���
class CmeDlg : public CDialog
{
// ����
public:
	CmeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChosePlainFile();
	CString strTemp ;//�����ַ���
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
