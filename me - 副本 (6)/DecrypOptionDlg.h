#pragma once


// DecrypOptionDlg �Ի���

class DecrypOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(DecrypOptionDlg)

public:
	DecrypOptionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DecrypOptionDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_DECRYP_CHOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
