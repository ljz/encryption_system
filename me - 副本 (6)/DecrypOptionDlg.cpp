// DecrypOptionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "me.h"
#include "DecrypOptionDlg.h"
#include "RSAKeyPairDLG.h"
#include <math.h>


// DecrypOptionDlg 对话框

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
	ON_BN_CLICKED(IDC_BUTTON_CREATE_KEYS, &DecrypOptionDlg::OnBnClickedButtonCreateKeys)
	ON_BN_CLICKED(IDC_CHECK_SM3, &DecrypOptionDlg::OnBnClickedCheckSM3)
END_MESSAGE_MAP()


// DecrypOptionDlg 消息处理程序

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
	CButton* pSM3Check = (CButton*)GetDlgItem(IDC_CHECK_SM3);
	int pSM3CheckState = pSM3Check->GetCheck();
	pSM3CheckState = pSM3CheckState<<3;
	CButton* pRsaCheck = (CButton*)GetDlgItem(IDC_CHECK_RSA);
	int pRsaCheckState = pRsaCheck->GetCheck();
	pRsaCheckState = pRsaCheckState<<4;
	//CButton* pMd5Check = (CButton*)GetDlgItem(IDC_CHECK_MD5);
	//int pMd5CheckState = pMd5Check->GetCheck();
	//pMd5CheckState = pMd5CheckState<<5;
	CheckState = pDesCheckState + p3DesCheckState + pAesCheckState + pSM3CheckState + pRsaCheckState;// + pMd5CheckState ;    
	CmeApp * mApp = (CmeApp*)AfxGetApp( );
	UpdateData(true);//将edit中的内容传给变量
	mApp->mMiwendlg = CheckState;  //解密的选择项数
	mApp->AfxDesUnKey = mDesUnKey;	//将DES解密密钥赋值给一个全局变量存储。
	mApp->Afx3DesUnKey = m3DesUnKey;	//将3DES解密密钥赋值给一个全局变量存储。
	mApp->AfxAesUnKey = mAesUnKey;
	//MessageBox(mApp->mMiwendlg);
	//AfxMessageBox(mApp->AfxDesUnKey);
	EndDialog(0);  
	// TODO: 在此添加控件通知处理程序代码
}

///////////////////////////////判断素数//////////////////////////// 
int DecrypOptionDlg::judge_num(long n) 
{ 
	long temp=0,i; 
	for(i=37;i<=sqrt((double)n);i+=2)
	{
		if (n%i == 0 ) return 0;
	}
	return 1; 
} 
//二进制转换
int DecrypOptionDlg::BianaryTransform(int num, int bin_num[])
{
	int i = 0,  mod = 0;
	//转换为二进制，逆向暂存temp[]数组中
	while(num != 0)
	{
		mod = num%2;
		bin_num[i] = mod;
		num = num/2;
		i++;
	}
	//返回二进制数的位数
	return i;
}

//生成密钥RSA对
void DecrypOptionDlg::OnBnClickedButtonCreateKeys()
{

	bool k=0;//标识是否找到符合条件的
	int P,Q,n,m,e,d;//大素数
	do{
		do{
			srand( (unsigned)time( NULL ) );
			P = rand();
			do 
			{
				P++;
			} while (!(P%2 && P%3&& P%5  && P%7 && P%11 && P%13 && P%17 && P%19 && P%23 && P%27 && P%29 && P%31));
		 }while(!judge_num(P));

		do{
			srand( (unsigned)time( NULL ) );  
			Q = rand();
			do 
			{
				Q++;
			} while (!(Q%2 && Q%3&& Q%5  && Q%7 && Q%11 && Q%13 && Q%17 && Q%19 && Q%23 && Q%27 && Q%29 && Q%31)||( Q == P));
		  }while(!judge_num(Q));
		//计算n,m,e,d
		n=P*Q;
		m=(P-1)*(Q-1);

		for(e=2;e<=m/2;e++)
		{
		
			for(d=sqrt((double)n);d>0;d--)
				if((e*d)%m==1) 
				{

					AfxMessageBox(__T("OK了！"));
					k =1;
					break;

				}
				if (k )
				{
					break;
				}
		}
	}while(!k);
	CmeApp * mApp = (CmeApp*)AfxGetApp( );
	mApp->RSA_d = d;
	mApp->RSA_n = n;
    mApp->RSA_e = e;
	/*CString sn,se,sd ;
	sn.Format("%d",n );se.Format("%d",e );sd.Format("%d",d);
	AfxMessageBox(sn);
	AfxMessageBox(se);
	AfxMessageBox(sd);*/
	//生成密钥对完成。
}
//反复平方求幂
long long DecrypOptionDlg::Modular_Exonentiation(long long a, int b, int n)
 {
   int c = 0, bin_num[1000];
    long long d = 1;
     int k = BianaryTransform(b, bin_num)-1;

   for(int i = k; i >= 0; i--)
    {
	       c = 2*c;
          d = (d*d)%n;
	      if(bin_num[i] == 1)
	        {
		         c = c + 1;
	             d = (d*a)%n;
	         }
	 }
   return d;
 }


void DecrypOptionDlg::OnBnClickedCheckSM3()
{
	// TODO: 在此添加控件通知处理程序代码
}
