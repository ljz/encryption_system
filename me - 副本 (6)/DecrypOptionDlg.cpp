// DecrypOptionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "me.h"
#include "DecrypOptionDlg.h"


// DecrypOptionDlg �Ի���

IMPLEMENT_DYNAMIC(DecrypOptionDlg, CDialog)

DecrypOptionDlg::DecrypOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DecrypOptionDlg::IDD, pParent)
	, mDesUnKey(_T(""))
	, mAesUnKey(_T(""))
{

}

DecrypOptionDlg::~DecrypOptionDlg()
{
}

void DecrypOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UNDES_KEY, mDesUnKey);
	DDX_Text(pDX, IDC_EDIT_AES_UNKEY, mAesUnKey);
}  


BEGIN_MESSAGE_MAP(DecrypOptionDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CHOSE_FINISH, &DecrypOptionDlg::OnBnClickedButtonChoseFinish)
END_MESSAGE_MAP()


// DecrypOptionDlg ��Ϣ�������

void DecrypOptionDlg::OnBnClickedButtonChoseFinish()
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
	UpdateData(true);//��edit�е����ݴ�������
	mApp->mMiwendlg = CheckState;  //���ܵ�ѡ������
	mApp->AfxDesUnKey = mDesUnKey;	//��DES������Կ��ֵ��һ��ȫ�ֱ����洢��
	mApp->Afx3DesUnKey = m3DesUnKey;	//��3DES������Կ��ֵ��һ��ȫ�ֱ����洢��
	mApp->AfxAesUnKey = mAesUnKey;
	//MessageBox(mApp->mMiwendlg);
	//AfxMessageBox(mApp->AfxDesUnKey);
	EndDialog(0);  
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
