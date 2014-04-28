// EncrypOptionDlg.cpp : 实现文件
//
#include "resource.h"
#include "stdafx.h"
#include "me.h"
#include "meDlg.h"
#include "EncrypOptionDlg.h"


// CEncrypOptionDlg 对话框

IMPLEMENT_DYNAMIC(CEncrypOptionDlg, CDialog)

CEncrypOptionDlg::CEncrypOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEncrypOptionDlg::IDD, pParent)
	, mDesKey(_T(""))
	, m3DesKey(_T(""))
	, mAesKey(_T(""))
{

}

CEncrypOptionDlg::~CEncrypOptionDlg()
{
}

void CEncrypOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DES_KEY, mDesKey);
	DDX_Text(pDX, IDC_EDIT_3DES_KEY, m3DesKey);
	DDX_Text(pDX, IDC_EDIT_AES_KEY, mAesKey);
}


BEGIN_MESSAGE_MAP(CEncrypOptionDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CHOSE_FINISH, &CEncrypOptionDlg::OnBnClickedButtonChoseFinish)
END_MESSAGE_MAP()


// CEncrypOptionDlg 消息处理程序

void CEncrypOptionDlg::OnBnClickedButtonChoseFinish()
{
	CButton* pDesCheck = (CButton*)GetDlgItem(IDC_CHECK_DES);
	int pDesCheckState = pDesCheck->GetCheck();
	CButton* p3DesCheck = (CButton*)GetDlgItem(IDC_CHECK_3DES);
	int p3DesCheckState = p3DesCheck->GetCheck();
	p3DesCheckState = p3DesCheckState<<1;
	CButton* pAesCheck = (CButton*)GetDlgItem(IDC_CHECK_AES);
	int pAesCheckState = pAesCheck->GetCheck();
	pAesCheckState = pAesCheckState<<2;
	CButton* pRc5Check = (CButton*)GetDlgItem(IDC_CHECK_RC5);
	int pRc5CheckState = pRc5Check->GetCheck();
	pRc5CheckState = pRc5CheckState<<3;
	CButton* pRsaCheck = (CButton*)GetDlgItem(IDC_CHECK_RSA);
	int pRsaCheckState = pRsaCheck->GetCheck();
	pRsaCheckState = pRsaCheckState<<4;
	CButton* pMd5Check = (CButton*)GetDlgItem(IDC_CHECK_MD5);
	int pMd5CheckState = pMd5Check->GetCheck();
	pMd5CheckState = pMd5CheckState<<5;
	CheckState = pDesCheckState + p3DesCheckState + pAesCheckState + pRc5CheckState + pRsaCheckState + pMd5CheckState ;    
	CmeApp * mApp = (CmeApp*)AfxGetApp( );
	UpdateData(true);//将edit中的内容传给变量
	mApp->mMingwendlg = CheckState;
	mApp->AfxDesKey = mDesKey;	//将DES密钥赋值给一个全局变量存储。
	mApp->Afx3DesKey = m3DesKey;	//将3DES密钥赋值给一个全局变量存储。
	EndDialog(0);  
	// TODO: 在此添加控件通知处理程序代码
}
