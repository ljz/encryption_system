// meDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "me.h"
#include "meDlg.h"
#include "EncrypOptionDlg.h"
#include "DecrypOptionDlg.h"
#include <stdlib.h>
#include "DES.h"
#include "AES.h"
#include "SM3.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CmeDlg �Ի���




CmeDlg::CmeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmeDlg::IDD, pParent)
	, m_edit_plain(_T(""))
	, m_edit_miwen(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MINGWEN, m_edit_plain);
	DDX_Text(pDX, IDC_EDIT_MIWEN, m_edit_miwen);
}

BEGIN_MESSAGE_MAP(CmeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CHOSE_PLAIN_FILE, &CmeDlg::OnBnClickedButtonChosePlainFile)
	//ON_BN_CLICKED(IDC_BUTTON_CHOSE_ENCRYP_ALOGRITHM, &CmeDlg::OnBnClickedButtonChoseEncrypAlogrithm)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYP_OPTION, &CmeDlg::OnBnClickedButtonEncrypOption)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYP, &CmeDlg::OnBnClickedButtonEncryp)
	ON_BN_CLICKED(IDC_BUTTON_CHOSE_CIPHER_FILE, &CmeDlg::OnBnClickedButtonChoseCipherFile)
	ON_BN_CLICKED(IDC_BUTTON_CHOSE_DNCRYP_ALOGRITHM, &CmeDlg::OnBnClickedButtonChoseDncrypAlogrithm)
	ON_BN_CLICKED(IDC_BUTTON_DECRYP, &CmeDlg::OnBnClickedButtonDecryp)
END_MESSAGE_MAP()


// CmeDlg ��Ϣ�������

BOOL CmeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	// ��ȡEDIT������ʾ������ 
	TEXTMETRIC tm1;
	CRect rect1;
	GetDlgItem(IDC_EDIT_MINGWEN)->GetClientRect(&rect1);
	CDC* pdc1 = GetDlgItem(IDC_EDIT_MINGWEN)->GetDC();
	::GetTextMetrics(pdc1->m_hDC,&tm1);
	GetDlgItem(IDC_EDIT_MINGWEN)->ReleaseDC(pdc1);
	m_nLineCount1 = rect1.bottom/(tm1.tmHeight-1.5);
	/*int nLine1 = ((CEdit*)GetDlgItem(IDC_EDIT_MINGWEN))->GetLineCount();
	if( nLine1 > m_nLineCount1)
	{
		GetDlgItem(IDC_EDIT_MINGWEN)->ShowScrollBar(SB_VERT, TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MINGWEN)->ShowScrollBar(SB_VERT, FALSE);
	}  */





	TEXTMETRIC tm2;
	CRect rect2;
	GetDlgItem(IDC_EDIT_MIWEN)->GetClientRect(&rect2);
	CDC* pdc2 = GetDlgItem(IDC_EDIT_MIWEN)->GetDC();
	::GetTextMetrics(pdc2->m_hDC,&tm2);
	GetDlgItem(IDC_EDIT_MIWEN)->ReleaseDC(pdc2);
	m_nLineCount2 = rect2.bottom/(tm2.tmHeight-1.5);


	//*/
	int nLine = ((CEdit*)GetDlgItem(IDC_EDIT_MIWEN))->GetLineCount();
	if( nLine > m_nLineCount2)
	{
		GetDlgItem(IDC_EDIT_MIWEN)->ShowScrollBar(SB_VERT, TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MIWEN)->ShowScrollBar(SB_VERT, FALSE);
	}  
	//*/



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

 //ѡ�������ļ���Ӧ����
/*
ѡ�������ļ����õ�·������ȡ�ļ����ݵ�strTemp�ַ����С�
��strTemp�ַ���������ʾ��Edit�ؼ��
��ʾedit�ؼ���������
*/
void CmeDlg::OnBnClickedButtonChosePlainFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char buf[1000] ="";
	int ret=1000;
	strTemp = "";
	CFileDialog mingwen_dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	mingwen_dlg.m_ofn.lpstrTitle=__T("�����ĶԻ���");
	mingwen_dlg.m_ofn.lpstrFilter=__T("Text Files(*.txt)\0*.txt\0Document Files(*.doc)\0*.doc\0\0");
	if(mingwen_dlg.DoModal()==IDOK)	   
	{
		myMingwenFile.Open(mingwen_dlg.GetPathName(),CFile::modeRead);
		CmeApp * mApp = (CmeApp*)AfxGetApp( );
		mApp->AfxMingwenPath = mingwen_dlg.GetPathName();
		while(ret == 1000)
		{
			ret = myMingwenFile.Read(buf,sizeof(buf));
			if (ret < 1000)
			{
				for (int i = ret;i<1000;i++)
				{
					buf[i] = '\0';
				}
			}
			strTemp +=buf;
		}
		myMingwenFile.Close();
		SetDlgItemText(IDC_EDIT_MINGWEN,strTemp);
		//��ʾ������


		int nLine = ((CEdit*)GetDlgItem(IDC_EDIT_MINGWEN))->GetLineCount();
		if( nLine > m_nLineCount1)
		{
			GetDlgItem(IDC_EDIT_MINGWEN)->ShowScrollBar(SB_VERT, TRUE);
		}
		else
		{
			GetDlgItem(IDC_EDIT_MINGWEN)->ShowScrollBar(SB_VERT, FALSE);
		}  
	}
}   
  /*
  ����ѡ�����
  ��������ѡ��Ի���
  */
void CmeDlg::OnBnClickedButtonEncrypOption()
{
	CEncrypOptionDlg *myEncrypOptionldg=new CEncrypOptionDlg;
	myEncrypOptionldg->DoModal();
}

  extern int AfxCheckState;

  /*
  ����GO������
	  ��ָ�����ļ���·�����������Կ�ַ���������GO

  */
void CmeDlg::OnBnClickedButtonEncryp()		
{
	//����������������
	CmeApp * mApp = (CmeApp*)AfxGetApp( );
	CFileDialog miwen_dlg(FALSE);//����ѡ��dlg
	CString miwenfileName;
	FILE * pmiwenfile;//�����ļ�ָ��




	char chDes_Key[9];
	char ch3Des_Key[18];
	//AES��ر�����������
	unsigned char AesKey[16];/*/ =	  //Aes��Կ
	{
		0x2b, 0x7e, 0x15, 0x16, 
		0x28, 0xae, 0xd2, 0xa6, 
		0xab, 0xf7, 0x15, 0x88, 
		0x09, 0xcf, 0x4f, 0x3c
	};						  /*/
	char aesfiletemp[20000];
	int aesfilelength;
	int aesendflag=0;
	char aestext[17];
	FILE *AesFp;
	//sm3������������ 
	FILE *Sm3Fp;
	char sm3filetemp[200000];
	int sm3filelength;



	////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////һ����RSA���ܱ����������� ��
	DecrypOptionDlg desRsa(NULL);

	FILE *RsaFp;
	char rsafiletemp[20000];
	int rsafilelength;
	int rsaendflag=0;
	unsigned char rsatext[16];
	int rsa_d = mApp->RSA_d;
	int rsa_e = mApp->RSA_e;
	int rsa_n = mApp->RSA_n;
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	memcpy(chDes_Key,mApp->AfxDesKey,9);
	memcpy(ch3Des_Key,mApp->Afx3DesKey,18);
	memcpy(AesKey,mApp->AfxAesKey,16);
	CDES mydes;
	switch (mApp->mMingwendlg)
	{
	case 0://00000
		AfxMessageBox(__T("û��ѡ���κμ����㷨"));
		break;											
	case 1://00001
		mydes.filecryption((LPSTR)(LPCSTR)mApp->AfxMingwenPath,chDes_Key,0);
			SetDlgItemText(IDC_EDIT_MIWEN,mApp->AfxFanwen);
		UpdateData();
		break;
	case 2:	 //000010
		 mydes.file_TriDES_encryption((LPSTR)(LPCSTR)mApp->AfxMingwenPath,ch3Des_Key,0);
		 SetDlgItemText(IDC_EDIT_MIWEN,mApp->AfxFanwen);
		break;
	case 4:
		AesFp=fopen((LPSTR)(LPCSTR)mApp->AfxMingwenPath,"rb+");//�������ļ�  �����Ե���switch���ǰ�档
		aesfilelength=ftell(AesFp);
		fseek(AesFp,0,SEEK_SET);
		fseek(AesFp,0,SEEK_END);
		aesfilelength=ftell(AesFp);
		rewind(AesFp);
		fread(aesfiletemp,aesfilelength,1,AesFp);
		for(;aesendflag+16<=aesfilelength;)
		{
			aestext[0]=aesfiletemp[aesendflag+0];		aestext[1]=aesfiletemp[aesendflag+1];		aestext[2]=aesfiletemp[aesendflag+2];		aestext[3]=aesfiletemp[aesendflag+3];
			aestext[4]=aesfiletemp[aesendflag+4];		aestext[5]=aesfiletemp[aesendflag+5];		aestext[6]=aesfiletemp[aesendflag+6];		aestext[7]=aesfiletemp[aesendflag+7];	 
			aestext[8]=aesfiletemp[aesendflag+8];		aestext[9]=aesfiletemp[aesendflag+9];		aestext[10]=aesfiletemp[aesendflag+10];	aestext[11]=aesfiletemp[aesendflag+11];
			aestext[12]=aesfiletemp[aesendflag+12];	aestext[13]=aesfiletemp[aesendflag+13];	aestext[14]=aesfiletemp[aesendflag+14];	aestext[15]=aesfiletemp[aesendflag+15];
			aestext[16]='\0';
			AES myaes(AesKey);
			myaes.Cipher(aestext,16);
			aesfiletemp[aesendflag+0] = aestext[0];	aesfiletemp[aesendflag+1]=aestext[1];		aesfiletemp[aesendflag+2]=aestext[2];		aesfiletemp[aesendflag+3]=aestext[3];
			aesfiletemp[aesendflag+4]=aestext[4];		aesfiletemp[aesendflag+5]=aestext[5];		aesfiletemp[aesendflag+6]=aestext[6];		aesfiletemp[aesendflag+7]=aestext[7];	 
			aesfiletemp[aesendflag+8]=aestext[8];		aesfiletemp[aesendflag+9]=aestext[9];		aesfiletemp[aesendflag+10]=aestext[10];	aesfiletemp[aesendflag+11]=aestext[11];
			aesfiletemp[aesendflag+12]=aestext[12];	aesfiletemp[aesendflag+13]=aestext[13];	aesfiletemp[aesendflag+14]=aestext[14];	aesfiletemp[aesendflag+15]=aestext[15];
			aesendflag+=16;
		}
		fclose(AesFp);
		if (miwen_dlg.DoModal() == IDOK)
		{
		miwenfileName = miwen_dlg.GetPathName();
		}
		pmiwenfile = fopen(miwenfileName,"wb+");
		fwrite(aesfiletemp,aesfilelength,1,pmiwenfile);
		fclose(pmiwenfile);
		SetDlgItemText(IDC_EDIT_MIWEN,aesfiletemp);
		break;
	case 8://SM3
		Sm3Fp=fopen((LPSTR)(LPCSTR)mApp->AfxMingwenPath,"rb+");//�������ļ�
		fseek(Sm3Fp,0,SEEK_SET);
		fseek(Sm3Fp,0,SEEK_END);
		sm3filelength=ftell(Sm3Fp);
		rewind(Sm3Fp);
		fread(sm3filetemp,sm3filelength,1,Sm3Fp);//��ȡ���ĵ����ݵ�aesfiletemp��ʱ�����С�
		SM3_Init();
		for (DWORD i = 0; i<16; i++)
		{
			SM3_Update((BYTE *)sm3filetemp, sm3filelength);
		}
		SM3_Final(hash);
		fclose(Sm3Fp);
	/*	if (miwen_dlg.DoModal() == IDOK)
		{
			miwenfileName = miwen_dlg.GetPathName();
		}*/
		pmiwenfile = fopen(__T("E:\happy\myFile\me - ���� (6)\sm3Miwen.txt"),"wb+");
		fwrite(hash,8,1,pmiwenfile);
		mApp->Afxhash .Format("%s",hash);
		fclose(pmiwenfile);
		SetDlgItemText(IDC_EDIT_MIWEN,mApp->Afxhash);
		break;
	case 16://AfxMessageBox(__T("ѡ��RSA�����㷨"));//10000
		RsaFp=fopen((LPSTR)(LPCSTR)mApp->AfxMiwenPath,"rb+");//�������ļ�
		fseek(RsaFp,0,SEEK_SET);
		fseek(RsaFp,0,SEEK_END);
		rsafilelength=ftell(RsaFp);	//�õ����ĵĳ���
		rewind(RsaFp);
		fread(rsafiletemp,rsafilelength,1,RsaFp);//��ȡ���ĵ����ݵ�aesfiletemp��ʱ�����С�
		for(;rsaendflag+16<=rsafilelength;)	 //���������־û�дﵽ�ļ��ĳ��ȣ���˵����û������
		{
			rsatext[0]=rsafiletemp[rsaendflag+0];		rsatext[1]=rsafiletemp[rsaendflag+1];		rsatext[2]=rsafiletemp[rsaendflag+2];		rsatext[3]=rsafiletemp[rsaendflag+3];
			rsatext[4]=rsafiletemp[rsaendflag+4];		rsatext[5]=rsafiletemp[rsaendflag+5];		rsatext[6]=rsafiletemp[rsaendflag+6];		rsatext[7]=rsafiletemp[rsaendflag+7];	 
			rsatext[8]=rsafiletemp[rsaendflag+8];		rsatext[9]=rsafiletemp[rsaendflag+9];		rsatext[10]=rsafiletemp[rsaendflag+10];		rsatext[11]=rsafiletemp[rsaendflag+11];
			rsatext[12]=rsafiletemp[rsaendflag+12];	    rsatext[13]=rsafiletemp[rsaendflag+13]; 	rsatext[14]=rsafiletemp[rsaendflag+14];		rsatext[15]=rsafiletemp[rsaendflag+15];
			for (int i = 0; i<=15;i++)
			{
				rsatext[i] = desRsa.Modular_Exonentiation(rsatext[i], rsa_e, rsa_n);
			}
			rsafiletemp[rsaendflag+0] = rsatext[0];rsafiletemp[rsaendflag+1]=rsatext[1];		rsafiletemp[rsaendflag+2]=rsatext[2];		rsafiletemp[rsaendflag+3]=rsatext[3];
			rsafiletemp[rsaendflag+4]=rsatext[4];		rsafiletemp[rsaendflag+5]=rsatext[5];		rsafiletemp[rsaendflag+6]=rsatext[6];		rsafiletemp[rsaendflag+7]=rsatext[7];	 
			rsafiletemp[rsaendflag+8]=rsatext[8];		rsafiletemp[rsaendflag+9]=rsatext[9];		rsafiletemp[rsaendflag+10]=rsatext[10];	rsafiletemp[rsaendflag+11]=rsatext[11];
			rsafiletemp[rsaendflag+12]=rsatext[12];	rsafiletemp[rsaendflag+13]=rsatext[13];	rsafiletemp[rsaendflag+14]=rsatext[14];	rsafiletemp[rsaendflag+15]=rsatext[15];
			rsaendflag+=16;
		}
		fclose(RsaFp);//�ر������ļ�
		if (miwen_dlg.DoModal() == IDOK)
		{
			miwenfileName = miwen_dlg.GetPathName();
		}
	/*	else{
		 AfxMessageBox(__T("���ִ���"));
		 return ;
		}*/
		pmiwenfile = fopen(miwenfileName,"wb+");
		fwrite(rsafiletemp,rsafilelength,1,pmiwenfile);
		fclose(pmiwenfile);
		SetDlgItemText(IDC_EDIT_MIWEN,rsafiletemp);
		break;
	default:
		AfxMessageBox(__T("ֻ��ѡ��һ���㷨�㷨"));
		break;
	}
	 //��ʾ������
	int nLine = ((CEdit*)GetDlgItem(IDC_EDIT_MIWEN))->GetLineCount();
	if( nLine > m_nLineCount2)
	{
		GetDlgItem(IDC_EDIT_MIWEN)->ShowScrollBar(SB_VERT, TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MIWEN)->ShowScrollBar(SB_VERT, FALSE);
	}
}
void CmeDlg::OnBnClickedButtonChoseCipherFile()
{
	strTemp = "";
	char buf[1000];
	int ret=1000;
	CFileDialog miwen_dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	miwen_dlg.m_ofn.lpstrTitle=__T("�����ĶԻ���");
	miwen_dlg.m_ofn.lpstrFilter=__T("Text Files(*.txt)\0*.txt\0Document Files(*.doc)\0*.doc\0\0");
	if(miwen_dlg.DoModal()==IDOK)	   
	{
		myMiwenFile.Open(miwen_dlg.GetPathName(),CFile::modeRead);
		CmeApp * mApp = (CmeApp*)AfxGetApp( );
		mApp->AfxMiwenPath = miwen_dlg.GetPathName();
		while(ret == 1000)
		{
			ret = myMiwenFile.Read(buf,sizeof(buf));
			if (ret < 1000)
			{
				for (int i = ret;i<1000;i++)
				{
					buf[i] = '\0';
				}
			}
			strTemp +=buf;
		}
		myMiwenFile.Close();
		SetDlgItemText(IDC_EDIT_MIWEN,strTemp);
		//��ʾ������
		int nLine = ((CEdit*)GetDlgItem(IDC_EDIT_MIWEN))->GetLineCount();
		if( nLine > m_nLineCount2)
		{
			GetDlgItem(IDC_EDIT_MIWEN)->ShowScrollBar(SB_VERT, TRUE);
		}
		else
		{
			GetDlgItem(IDC_EDIT_MIWEN)->ShowScrollBar(SB_VERT, FALSE);
		}
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CmeDlg::OnBnClickedButtonChoseDncrypAlogrithm()
{
	DecrypOptionDlg *myDecrypOptionldg=new DecrypOptionDlg;
	myDecrypOptionldg->DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}



void CmeDlg::OnBnClickedButtonDecryp()
{
	//������������
	CmeApp * mApp = (CmeApp*)AfxGetApp( );
	CFileDialog  mingwen_dlg(FALSE);
	CString mingwenfileName;
	 FILE * pmingwenfile;//����fileָ��
	

	///////////һ����AES���ܱ����������� ��

	 unsigned char chAes_UnKey[16] =	 
	{
		0x2b, 0x7e, 0x15, 0x16, 
		0x28, 0xae, 0xd2, 0xa6, 
		0xab, 0xf7, 0x15, 0x88, 
		0x09, 0xcf, 0x4f, 0x3c
	};

	FILE *AesFp;
	char aesfiletemp[20000];
	int aesfilelength;
	int aesendflag=0;
	unsigned char aestext[16];
	
	 ////////////AES���ܱ������������� ��
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////RSA���ܱ����������� ��
	FILE *RsaFp;
	char rsafiletemp[20000];
	int rsafilelength;
	int rsaendflag=0;
	unsigned char rsatext[16];
	int rsa_d = mApp->RSA_d;
	int rsa_e = mApp->RSA_e;
	int rsa_n = mApp->RSA_n;

	////////////RSA���ܱ������������� ��
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	char chDes_UnKey[9];
	char ch3Des_UnKey[27];
	//CString strDesKey = CEncrypOptionDlg::mDesKey;
	//chDes_Key =(LPSTR)(LPCSTR)mApp->AfxDesKey; //	��Կ
	memcpy(chDes_UnKey,mApp->AfxDesUnKey,mApp->AfxDesUnKey.GetLength());
	memcpy(ch3Des_UnKey,mApp->Afx3DesUnKey,mApp->Afx3DesUnKey.GetLength());
	memcpy(chAes_UnKey,mApp->AfxAesUnKey,mApp->AfxAesUnKey.GetLength());//�����AESUNKEY��ֵ��
	AES myaes(chAes_UnKey);
	DecrypOptionDlg desRsa(NULL);
	//sm3������������ 
	FILE *Sm3Fp;
	char sm3filetemp[200000];
	int sm3filelength;
	CString CStrhashTemp;

	CDES myundes;
	switch (mApp->mMiwendlg)
	{
	case 0://00000
		AfxMessageBox(__T("û��ѡ���κμ����㷨"));
		break;											
	case 1://00001
		myundes.filecryption((LPSTR)(LPCSTR)mApp->AfxMiwenPath,chDes_UnKey,1);
		SetDlgItemText(IDC_EDIT_MINGWEN,mApp->AfxFanwen);
		break;
	case 2:	 //000010
		AfxMessageBox(__T("ѡ��3DES�����㷨"));
		myundes.file_TriDES_encryption((LPSTR)(LPCSTR)mApp->AfxMiwenPath,ch3Des_UnKey,1);
		SetDlgItemText(IDC_EDIT_MINGWEN,mApp->AfxFanwen);
		break;
	case 3:
		AfxMessageBox(__T("ѡ��DES�����㷨��3DES�㷨"));//000011
		break;
	case 4:
		AfxMessageBox(__T("ѡ��AES�����㷨"));//0000100
		AesFp=fopen((LPSTR)(LPCSTR)mApp->AfxMiwenPath,"rb+");//�������ļ�
		fseek(AesFp,0,SEEK_SET);
		fseek(AesFp,0,SEEK_END);
		aesfilelength=ftell(AesFp);	//�õ����ĵĳ���
		rewind(AesFp);
		fread(aesfiletemp,aesfilelength,1,AesFp);//��ȡ���ĵ����ݵ�aesfiletemp��ʱ�����С�
		for(;aesendflag+16<=aesfilelength;)	 //���������־û�дﵽ�ļ��ĳ��ȣ���˵����û������
		{
		aestext[0]=aesfiletemp[aesendflag+0];		aestext[1]=aesfiletemp[aesendflag+1];		aestext[2]=aesfiletemp[aesendflag+2];		aestext[3]=aesfiletemp[aesendflag+3];
		aestext[4]=aesfiletemp[aesendflag+4];		aestext[5]=aesfiletemp[aesendflag+5];		aestext[6]=aesfiletemp[aesendflag+6];		aestext[7]=aesfiletemp[aesendflag+7];	 
		aestext[8]=aesfiletemp[aesendflag+8];		aestext[9]=aesfiletemp[aesendflag+9];		aestext[10]=aesfiletemp[aesendflag+10];	aestext[11]=aesfiletemp[aesendflag+11];
		aestext[12]=aesfiletemp[aesendflag+12];	aestext[13]=aesfiletemp[aesendflag+13];	aestext[14]=aesfiletemp[aesendflag+14];	aestext[15]=aesfiletemp[aesendflag+15];
		myaes.InvCipher(aestext);
		aesfiletemp[aesendflag+0] = aestext[0];	aesfiletemp[aesendflag+1]=aestext[1];		aesfiletemp[aesendflag+2]=aestext[2];		aesfiletemp[aesendflag+3]=aestext[3];
		aesfiletemp[aesendflag+4]=aestext[4];		aesfiletemp[aesendflag+5]=aestext[5];		aesfiletemp[aesendflag+6]=aestext[6];		aesfiletemp[aesendflag+7]=aestext[7];	 
		aesfiletemp[aesendflag+8]=aestext[8];		aesfiletemp[aesendflag+9]=aestext[9];		aesfiletemp[aesendflag+10]=aestext[10];	aesfiletemp[aesendflag+11]=aestext[11];
		aesfiletemp[aesendflag+12]=aestext[12];	aesfiletemp[aesendflag+13]=aestext[13];	aesfiletemp[aesendflag+14]=aestext[14];	aesfiletemp[aesendflag+15]=aestext[15];
		aesendflag+=16;
		}
		fclose(AesFp);//�ر������ļ�

		if (mingwen_dlg.DoModal() == IDOK)
		{
		 mingwenfileName = mingwen_dlg.GetPathName();
		}
		//FILE * aespmingwenfile;
		pmingwenfile = fopen(mingwenfileName,"wb+");
		fwrite(aesfiletemp,aesfilelength,1,pmingwenfile);
		fclose(pmingwenfile);
		break;
	case 8:
		Sm3Fp=fopen((LPSTR)(LPCSTR)mApp->AfxMiwenPath,"rb+");//�������ļ�
		fseek(Sm3Fp,0,SEEK_SET);
		fseek(Sm3Fp,0,SEEK_END);
		sm3filelength=ftell(Sm3Fp);
		rewind(Sm3Fp);
		fread(sm3filetemp,sm3filelength,1,Sm3Fp);//��ȡ���ĵ����ݵ�aesfiletemp��ʱ�����С�
		SM3_Init();
		for (DWORD i = 0; i<16; i++)
		{
			SM3_Update((BYTE *)sm3filetemp, sm3filelength);
		}
		SM3_Final(hash);
		fclose(Sm3Fp);
		CStrhashTemp.Format("%s",hash);
		if(CStrhashTemp.Compare(mApp->Afxhash)==0)
		{
			AfxMessageBox(__T("ƥ��ɹ���"));
		}
		else
		{
			AfxMessageBox(__T("ƥ��ʧ��"));
		}
		break;
	case 16:
		AfxMessageBox(__T("ѡ��RSA�����㷨"));//10000
		RsaFp=fopen((LPSTR)(LPCSTR)mApp->AfxMiwenPath,"rb+");//�������ļ�
		fseek(RsaFp,0,SEEK_SET);
		fseek(RsaFp,0,SEEK_END);
		rsafilelength=ftell(RsaFp);	//�õ����ĵĳ���
		rewind(RsaFp);
		fread(rsafiletemp,rsafilelength,1,RsaFp);//��ȡ���ĵ����ݵ�aesfiletemp��ʱ�����С�
		for(;rsaendflag+16<=rsafilelength;)	 //���������־û�дﵽ�ļ��ĳ��ȣ���˵����û������
		{

			rsatext[0]=rsafiletemp[rsaendflag+0];		rsatext[1]=rsafiletemp[rsaendflag+1];		rsatext[2]=rsafiletemp[rsaendflag+2];		rsatext[3]=rsafiletemp[rsaendflag+3];
			rsatext[4]=rsafiletemp[rsaendflag+4];		rsatext[5]=rsafiletemp[rsaendflag+5];		rsatext[6]=rsafiletemp[rsaendflag+6];		rsatext[7]=rsafiletemp[rsaendflag+7];	 
			rsatext[8]=rsafiletemp[rsaendflag+8];		rsatext[9]=rsafiletemp[rsaendflag+9];		rsatext[10]=rsafiletemp[rsaendflag+10];	rsatext[11]=rsafiletemp[rsaendflag+11];
			rsatext[12]=rsafiletemp[rsaendflag+12];	rsatext[13]=rsafiletemp[rsaendflag+13];	rsatext[14]=rsafiletemp[rsaendflag+14];	rsatext[15]=rsafiletemp[rsaendflag+15];
			//myaes.InvCipher(aestext);
			for (int i = 0; i<=15;i++)
			{
			rsatext[i] = desRsa.Modular_Exonentiation(rsatext[i], rsa_d, rsa_n);
			}
			rsafiletemp[rsaendflag+0] = rsatext[0];rsafiletemp[rsaendflag+1]=rsatext[1];		rsafiletemp[rsaendflag+2]=rsatext[2];		rsafiletemp[rsaendflag+3]=rsatext[3];
			rsafiletemp[rsaendflag+4]=rsatext[4];		rsafiletemp[rsaendflag+5]=rsatext[5];		rsafiletemp[rsaendflag+6]=rsatext[6];		rsafiletemp[rsaendflag+7]=rsatext[7];	 
			rsafiletemp[rsaendflag+8]=rsatext[8];		rsafiletemp[rsaendflag+9]=rsatext[9];		rsafiletemp[rsaendflag+10]=rsatext[10];	rsafiletemp[rsaendflag+11]=rsatext[11];
			rsafiletemp[rsaendflag+12]=rsatext[12];	rsafiletemp[rsaendflag+13]=rsatext[13];	rsafiletemp[rsaendflag+14]=rsatext[14];	rsafiletemp[rsaendflag+15]=rsatext[15];
			rsaendflag+=16;
		}
		fclose(RsaFp);//�ر������ļ�

		if (mingwen_dlg.DoModal() == IDOK)
		{
			mingwenfileName = mingwen_dlg.GetPathName();
		}
		pmingwenfile = fopen(mingwenfileName,"wb+");
		fwrite(rsafiletemp,rsafilelength,1,pmingwenfile);
		fclose(pmingwenfile);
		break;
	default:
		break;

	}   
	//��ʾ������
	int nLine = ((CEdit*)GetDlgItem(IDC_EDIT_MINGWEN))->GetLineCount();
	if( nLine > m_nLineCount1)
	{
		GetDlgItem(IDC_EDIT_MINGWEN)->ShowScrollBar(SB_VERT, TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MINGWEN)->ShowScrollBar(SB_VERT, FALSE);
	}
	//AfxMessageBox(AfxCheckState);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
