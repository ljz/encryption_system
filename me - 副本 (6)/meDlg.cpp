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




	//
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
	case 3:
		AfxMessageBox(__T("ѡ��DES�����㷨��3DES�㷨"));//000011
		break;
	case 4:
		AfxMessageBox(__T("ѡ��AES�����㷨"));//0000100
		//*/
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
			//AfxMessageBox(aestext);
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
		//�������

		//*/

		break;
	case 5:
		AfxMessageBox(__T("ѡ��AES��DES�����㷨"));/////0000101
		break;
	case 6:
		AfxMessageBox(__T("ѡ��AES��3DES�����㷨"));/////0000110
		break;
	case 7:
		AfxMessageBox(__T("ѡ��DES��3DES��AES�����㷨"));//000000111
		break;
	case 8:
		AfxMessageBox(__T("ѡ��SM5�����㷨"));//0001000
		break;
	case 9:
		AfxMessageBox(__T("ѡ��DES��SM5�����㷨"));	///0001001
		break ;
	case 10:
		AfxMessageBox(__T("ѡ��3DES��SM5�����㷨"));//00001010
		break;
	case 11:
		AfxMessageBox(__T("ѡ��DES��3DES��SM5�����㷨"));//000001011
		break;
	case 12:
		AfxMessageBox(__T("ѡ��AES��SM5�����㷨"));//000001100
		break;
	case 13:
		AfxMessageBox(__T("ѡ��DES��AES��SM5�����㷨"));//000001101
		break;
	case 14:
		AfxMessageBox(__T("ѡ��3DES��AES��SM5�����㷨"));//000001110
		break;
	case 15:
		AfxMessageBox(__T("ѡ��ES��3DES�ͺ�AES��SM5�����㷨"));//1111
		break;
	case 16:
		AfxMessageBox(__T("ѡ��RSA�����㷨"));//10000
		break;
	case 17:
		AfxMessageBox(__T("ѡ��DES��RSA�����㷨"));//10001
		break;
	case 18:
		AfxMessageBox(__T("ѡ��3DES��RSA�����㷨"));//10010
		break;
	case 19:
		AfxMessageBox(__T("ѡ��DES��3DES��RSA�����㷨"));//10011
		break;
	case 20:
		AfxMessageBox(__T("ѡ��AES��RSA�����㷨"));//10100
		break;
	case 21:
		AfxMessageBox(__T("ѡ��DES��AES��RSA�����㷨"));//10101
		break;
	case 22:
		AfxMessageBox(__T("ѡ��3DES��AES��RSA�����㷨"));//10110
		break;
	case 23:
		AfxMessageBox(__T("ѡ��DES��3DES��AES��RSA�����㷨"));//10111
		break;
	case 24:
		AfxMessageBox(__T("ѡ��SM5��RSA�����㷨"));//11000
		break;
	case 25:
		AfxMessageBox(__T("ѡ��DES��SM5��RSA�����㷨"));//11001
		break;
	case 26:
		AfxMessageBox(__T("ѡ��3DES��SM5��RSA�����㷨"));//11010
		break;
	case 27:
		AfxMessageBox(__T("ѡ��DES��3DES��SM5��RSA�����㷨"));//11011
		break;
	case 28:
		AfxMessageBox(__T("ѡ��AES��SM5��RSA�����㷨"));//11100
		break;
	case 29:
		AfxMessageBox(__T("ѡ��DES��AES��SM5��RSA�����㷨"));//11101
		break;
	case 30:
		AfxMessageBox(__T("ѡ��3DES��AES��SM5��RSA�����㷨"));//11110
		break;
	case 31:
		AfxMessageBox(__T("ѡ��DES��3DES��AES��SM5��RSA�����㷨"));//11111
		break;
	case 32://100000
		AfxMessageBox(__T("ѡ��MD5�㷨"));
		break;
	case 33://100001
		AfxMessageBox(__T("ѡ��MD5��DES�����㷨"));
		break;
	case 34:	 //0100010
		AfxMessageBox(__T("ѡ��MD5��3DES�����㷨"));
		break;
	case 35: //100011
		AfxMessageBox(__T("ѡ��DES�����㷨��3DES��MD5�㷨"));
		break;
	case 36:  //100100
		AfxMessageBox(__T("ѡ��AES��MD5�����㷨"));
		break;
	case 37: //100101
		AfxMessageBox(__T("ѡ��AES��DES��MD5�����㷨"));
		break;
	case 38://100110
		AfxMessageBox(__T("ѡ��AES��3DES��MD5�����㷨"));
		break;
	case 39: //100111
		AfxMessageBox(__T("ѡ��DES��3DES��AES��MD5�����㷨"));
		break;
	case 40://101000
		AfxMessageBox(__T("ѡ��SM5��MD5�����㷨"));
		break;
	case 41://101001
		AfxMessageBox(__T("ѡ��DES��SM5��MD5�����㷨"));	
		break ;
	case 42://101010
		AfxMessageBox(__T("ѡ��3DES��SM5��MD5�����㷨"));
		break;
	case 43: //101011
		AfxMessageBox(__T("ѡ��DES��3DES��SM5��MD5�����㷨"));
		break;
	case 44: //101100
		AfxMessageBox(__T("ѡ��AES��SM5��MD5�����㷨"));
		break;
	case 45: //101101
		AfxMessageBox(__T("ѡ��DES��AES��SM5��MD5�����㷨"));
		break;
	case 46: //101110
		AfxMessageBox(__T("ѡ��3DES��AES��SM5��MD5�����㷨"));
		break;
	case 47: //101111
		AfxMessageBox(__T("ѡ��DES��3DES�ͺ�AES��SM5��MD5�����㷨"));
		break;
	case 48://110000
		AfxMessageBox(__T("ѡ��RSA��MD5�����㷨"));
		break;
	case 49://110001
		AfxMessageBox(__T("ѡ��DES��RSA��MD5�����㷨"));
		break;
	case 50:
		AfxMessageBox(__T("ѡ��3DES��RSA��MD5�����㷨"));//10010
		break;
	case 51:
		AfxMessageBox(__T("ѡ��DES��3DES��RSA��MD5�����㷨"));//10011
		break;
	case 52:
		AfxMessageBox(__T("ѡ��AES��RSA��MD5�����㷨"));//10100
		break;
	case 53:
		AfxMessageBox(__T("ѡ��DES��AES��RSA��MD5�����㷨"));//10101
		break;
	case 54:
		AfxMessageBox(__T("ѡ��3DES��AES��RSA��MD5�����㷨"));//10110
		break;
	case 55:
		AfxMessageBox(__T("ѡ��DES��3DES��AES��RSA��MD5�����㷨"));//10111
		break;
	case 56:
		AfxMessageBox(__T("ѡ��SM5��RSA��MD5�����㷨"));//11000
		break;
	case 57:
		AfxMessageBox(__T("ѡ��DES��SM5��RSA��MD5�����㷨"));//11001
		break;
	case 58:
		AfxMessageBox(__T("ѡ��3DES��SM5��RSA��MD5�����㷨"));//11010
		break;
	case 59:
		AfxMessageBox(__T("ѡ��DES��3DES��SM5��RSA��MD5�����㷨"));//11011
		break;
	case 60:
		AfxMessageBox(__T("ѡ��AES��SM5��RSA��MD5�����㷨"));//11100
		break;
	case 61:
		AfxMessageBox(__T("ѡ��DES��AES��SM5��RSA��MD5�����㷨"));//11101
		break;
	case 62:
		AfxMessageBox(__T("ѡ��3DES��AES��SM5��RSA��MD5�����㷨"));//11110
		break;
	case 63:
		AfxMessageBox(__T("ѡ��DES��3DES��AES��SM5��RSA��MD5�����㷨"));//11111
		break;
	default:
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


	//AfxMessageBox(AfxCheckState);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//AfxMessageBox(mApp->AfxMingwenPath);
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

	char chDes_UnKey[9];
	char ch3Des_UnKey[27];
	//CString strDesKey = CEncrypOptionDlg::mDesKey;
	//chDes_Key =(LPSTR)(LPCSTR)mApp->AfxDesKey; //	��Կ
	memcpy(chDes_UnKey,mApp->AfxDesUnKey,mApp->AfxDesUnKey.GetLength());
	memcpy(ch3Des_UnKey,mApp->Afx3DesUnKey,mApp->Afx3DesUnKey.GetLength());
	memcpy(chAes_UnKey,mApp->AfxAesUnKey,mApp->AfxAesUnKey.GetLength());//�����AESUNKEY��ֵ��
	AES myaes(chAes_UnKey);


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
		//�������
		break;

	case 5:
		AfxMessageBox(__T("ѡ��AES��DES�����㷨"));/////0000101
		break;
	case 6:
		AfxMessageBox(__T("ѡ��AES��3DES�����㷨"));/////0000110
		break;
	case 7:
		AfxMessageBox(__T("ѡ��DES��3DES��AES�����㷨"));//000000111
		break;
	case 8:
		AfxMessageBox(__T("ѡ��SM5�����㷨"));//0001000
		break;
	case 9:
		AfxMessageBox(__T("ѡ��DES��SM5�����㷨"));	///0001001
		break ;
	case 10:
		AfxMessageBox(__T("ѡ��3DES��SM5�����㷨"));//00001010
		break;
	case 11:
		AfxMessageBox(__T("ѡ��DES��3DES��SM5�����㷨"));//000001011
		break;
	case 12:
		AfxMessageBox(__T("ѡ��AES��SM5�����㷨"));//000001100
		break;
	case 13:
		AfxMessageBox(__T("ѡ��DES��AES��SM5�����㷨"));//000001101
		break;
	case 14:
		AfxMessageBox(__T("ѡ��3DES��AES��SM5�����㷨"));//000001110
		break;
	case 15:
		AfxMessageBox(__T("ѡ��ES��3DES�ͺ�AES��SM5�����㷨"));//1111
		break;
	case 16:
		AfxMessageBox(__T("ѡ��RSA�����㷨"));//10000
		break;
	case 17:
		AfxMessageBox(__T("ѡ��DES��RSA�����㷨"));//10001
		break;
	case 18:
		AfxMessageBox(__T("ѡ��3DES��RSA�����㷨"));//10010
		break;
	case 19:
		AfxMessageBox(__T("ѡ��DES��3DES��RSA�����㷨"));//10011
		break;
	case 20:
		AfxMessageBox(__T("ѡ��AES��RSA�����㷨"));//10100
		break;
	case 21:
		AfxMessageBox(__T("ѡ��DES��AES��RSA�����㷨"));//10101
		break;
	case 22:
		AfxMessageBox(__T("ѡ��3DES��AES��RSA�����㷨"));//10110
		break;
	case 23:
		AfxMessageBox(__T("ѡ��DES��3DES��AES��RSA�����㷨"));//10111
		break;
	case 24:
		AfxMessageBox(__T("ѡ��SM5��RSA�����㷨"));//11000
		break;
	case 25:
		AfxMessageBox(__T("ѡ��DES��SM5��RSA�����㷨"));//11001
		break;
	case 26:
		AfxMessageBox(__T("ѡ��3DES��SM5��RSA�����㷨"));//11010
		break;
	case 27:
		AfxMessageBox(__T("ѡ��DES��3DES��SM5��RSA�����㷨"));//11011
		break;
	case 28:
		AfxMessageBox(__T("ѡ��AES��SM5��RSA�����㷨"));//11100
		break;
	case 29:
		AfxMessageBox(__T("ѡ��DES��AES��SM5��RSA�����㷨"));//11101
		break;
	case 30:
		AfxMessageBox(__T("ѡ��3DES��AES��SM5��RSA�����㷨"));//11110
		break;
	case 31:
		AfxMessageBox(__T("ѡ��DES��3DES��AES��SM5��RSA�����㷨"));//11111
		break;
	case 32://100000
		AfxMessageBox(__T("ѡ��MD5�㷨"));
		break;
	case 33://100001
		AfxMessageBox(__T("ѡ��MD5��DES�����㷨"));
		break;
	case 34:	 //0100010
		AfxMessageBox(__T("ѡ��MD5��3DES�����㷨"));
		break;
	case 35: //100011
		AfxMessageBox(__T("ѡ��DES�����㷨��3DES��MD5�㷨"));
		break;
	case 36:  //100100
		AfxMessageBox(__T("ѡ��AES��MD5�����㷨"));
		break;
	case 37: //100101
		AfxMessageBox(__T("ѡ��AES��DES��MD5�����㷨"));
		break;
	case 38://100110
		AfxMessageBox(__T("ѡ��AES��3DES��MD5�����㷨"));
		break;
	case 39: //100111
		AfxMessageBox(__T("ѡ��DES��3DES��AES��MD5�����㷨"));
		break;
	case 40://101000
		AfxMessageBox(__T("ѡ��SM5��MD5�����㷨"));
		break;
	case 41://101001
		AfxMessageBox(__T("ѡ��DES��SM5��MD5�����㷨"));	
		break ;
	case 42://101010
		AfxMessageBox(__T("ѡ��3DES��SM5��MD5�����㷨"));
		break;
	case 43: //101011
		AfxMessageBox(__T("ѡ��DES��3DES��SM5��MD5�����㷨"));
		break;
	case 44: //101100
		AfxMessageBox(__T("ѡ��AES��SM5��MD5�����㷨"));
		break;
	case 45: //101101
		AfxMessageBox(__T("ѡ��DES��AES��SM5��MD5�����㷨"));
		break;
	case 46: //101110
		AfxMessageBox(__T("ѡ��3DES��AES��SM5��MD5�����㷨"));
		break;
	case 47: //101111
		AfxMessageBox(__T("ѡ��DES��3DES�ͺ�AES��SM5��MD5�����㷨"));
		break;
	case 48://110000
		AfxMessageBox(__T("ѡ��RSA��MD5�����㷨"));
		break;
	case 49://110001
		AfxMessageBox(__T("ѡ��DES��RSA��MD5�����㷨"));
		break;
	case 50:
		AfxMessageBox(__T("ѡ��3DES��RSA��MD5�����㷨"));//10010
		break;
	case 51:
		AfxMessageBox(__T("ѡ��DES��3DES��RSA��MD5�����㷨"));//10011
		break;
	case 52:
		AfxMessageBox(__T("ѡ��AES��RSA��MD5�����㷨"));//10100
		break;
	case 53:
		AfxMessageBox(__T("ѡ��DES��AES��RSA��MD5�����㷨"));//10101
		break;
	case 54:
		AfxMessageBox(__T("ѡ��3DES��AES��RSA��MD5�����㷨"));//10110
		break;
	case 55:
		AfxMessageBox(__T("ѡ��DES��3DES��AES��RSA��MD5�����㷨"));//10111
		break;
	case 56:
		AfxMessageBox(__T("ѡ��SM5��RSA��MD5�����㷨"));//11000
		break;
	case 57:
		AfxMessageBox(__T("ѡ��DES��SM5��RSA��MD5�����㷨"));//11001
		break;
	case 58:
		AfxMessageBox(__T("ѡ��3DES��SM5��RSA��MD5�����㷨"));//11010
		break;
	case 59:
		AfxMessageBox(__T("ѡ��DES��3DES��SM5��RSA��MD5�����㷨"));//11011
		break;
	case 60:
		AfxMessageBox(__T("ѡ��AES��SM5��RSA��MD5�����㷨"));//11100
		break;
	case 61:
		AfxMessageBox(__T("ѡ��DES��AES��SM5��RSA��MD5�����㷨"));//11101
		break;
	case 62:
		AfxMessageBox(__T("ѡ��3DES��AES��SM5��RSA��MD5�����㷨"));//11110
		break;
	case 63:
		AfxMessageBox(__T("ѡ��DES��3DES��AES��SM5��RSA��MD5�����㷨"));//11111
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
