// meDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CmeDlg 对话框




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


// CmeDlg 消息处理程序

BOOL CmeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 获取EDIT可以显示的行数 
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



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

 //选中明文文件响应函数
/*
选中明文文件，得到路径，读取文件内容到strTemp字符串中。
将strTemp字符串内容显示在Edit控件里。
显示edit控件的下拉框
*/
void CmeDlg::OnBnClickedButtonChosePlainFile()
{
	// TODO: 在此添加控件通知处理程序代码
	char buf[1000] ="";
	int ret=1000;
	strTemp = "";
	CFileDialog mingwen_dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	mingwen_dlg.m_ofn.lpstrTitle=__T("打开明文对话框");
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
		//显示下拉条


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
  加密选项函数：
  弹出加密选项对话框
  */
void CmeDlg::OnBnClickedButtonEncrypOption()
{
	CEncrypOptionDlg *myEncrypOptionldg=new CEncrypOptionDlg;
	myEncrypOptionldg->DoModal();
}

  extern int AfxCheckState;

  /*
  加密GO函数：
	  对指定的文件（路径），获得密钥字符串，加密GO

  */
void CmeDlg::OnBnClickedButtonEncryp()		
{
	//公共变量声明区域
	CmeApp * mApp = (CmeApp*)AfxGetApp( );
	CFileDialog miwen_dlg(FALSE);//密文选择dlg
	CString miwenfileName;
	FILE * pmiwenfile;//密文文件指针




	char chDes_Key[9];
	char ch3Des_Key[18];
	//AES相关变量声明区域
	unsigned char AesKey[16];/*/ =	  //Aes密钥
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
		AfxMessageBox(__T("没有选中任何加密算法"));
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
		AfxMessageBox(__T("选中DES加密算法和3DES算法"));//000011
		break;
	case 4:
		AfxMessageBox(__T("选中AES加密算法"));//0000100
		//*/
		AesFp=fopen((LPSTR)(LPCSTR)mApp->AfxMingwenPath,"rb+");//打开明文文件  ，可以调到switch语句前面。
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
		//加密完成

		//*/

		break;
	case 5:
		AfxMessageBox(__T("选中AES和DES加密算法"));/////0000101
		break;
	case 6:
		AfxMessageBox(__T("选中AES和3DES加密算法"));/////0000110
		break;
	case 7:
		AfxMessageBox(__T("选中DES和3DES和AES加密算法"));//000000111
		break;
	case 8:
		AfxMessageBox(__T("选中SM5加密算法"));//0001000
		break;
	case 9:
		AfxMessageBox(__T("选中DES和SM5加密算法"));	///0001001
		break ;
	case 10:
		AfxMessageBox(__T("选中3DES和SM5加密算法"));//00001010
		break;
	case 11:
		AfxMessageBox(__T("选中DES和3DES和SM5加密算法"));//000001011
		break;
	case 12:
		AfxMessageBox(__T("选中AES和SM5加密算法"));//000001100
		break;
	case 13:
		AfxMessageBox(__T("选中DES和AES和SM5加密算法"));//000001101
		break;
	case 14:
		AfxMessageBox(__T("选中3DES和AES和SM5加密算法"));//000001110
		break;
	case 15:
		AfxMessageBox(__T("选中ES和3DES和和AES和SM5加密算法"));//1111
		break;
	case 16:
		AfxMessageBox(__T("选中RSA加密算法"));//10000
		break;
	case 17:
		AfxMessageBox(__T("选中DES和RSA加密算法"));//10001
		break;
	case 18:
		AfxMessageBox(__T("选中3DES和RSA加密算法"));//10010
		break;
	case 19:
		AfxMessageBox(__T("选中DES和3DES和RSA加密算法"));//10011
		break;
	case 20:
		AfxMessageBox(__T("选中AES和RSA加密算法"));//10100
		break;
	case 21:
		AfxMessageBox(__T("选中DES和AES和RSA加密算法"));//10101
		break;
	case 22:
		AfxMessageBox(__T("选中3DES和AES和RSA加密算法"));//10110
		break;
	case 23:
		AfxMessageBox(__T("选中DES和3DES和AES和RSA加密算法"));//10111
		break;
	case 24:
		AfxMessageBox(__T("选中SM5和RSA加密算法"));//11000
		break;
	case 25:
		AfxMessageBox(__T("选中DES和SM5和RSA加密算法"));//11001
		break;
	case 26:
		AfxMessageBox(__T("选中3DES和SM5和RSA加密算法"));//11010
		break;
	case 27:
		AfxMessageBox(__T("选中DES和3DES和SM5和RSA加密算法"));//11011
		break;
	case 28:
		AfxMessageBox(__T("选中AES和SM5和RSA加密算法"));//11100
		break;
	case 29:
		AfxMessageBox(__T("选中DES和AES和SM5和RSA加密算法"));//11101
		break;
	case 30:
		AfxMessageBox(__T("选中3DES和AES和SM5和RSA加密算法"));//11110
		break;
	case 31:
		AfxMessageBox(__T("选中DES和3DES和AES和SM5和RSA加密算法"));//11111
		break;
	case 32://100000
		AfxMessageBox(__T("选中MD5算法"));
		break;
	case 33://100001
		AfxMessageBox(__T("选中MD5和DES加密算法"));
		break;
	case 34:	 //0100010
		AfxMessageBox(__T("选中MD5和3DES加密算法"));
		break;
	case 35: //100011
		AfxMessageBox(__T("选中DES加密算法和3DES和MD5算法"));
		break;
	case 36:  //100100
		AfxMessageBox(__T("选中AES和MD5加密算法"));
		break;
	case 37: //100101
		AfxMessageBox(__T("选中AES和DES和MD5加密算法"));
		break;
	case 38://100110
		AfxMessageBox(__T("选中AES和3DES和MD5加密算法"));
		break;
	case 39: //100111
		AfxMessageBox(__T("选中DES和3DES和AES和MD5加密算法"));
		break;
	case 40://101000
		AfxMessageBox(__T("选中SM5和MD5加密算法"));
		break;
	case 41://101001
		AfxMessageBox(__T("选中DES和SM5和MD5加密算法"));	
		break ;
	case 42://101010
		AfxMessageBox(__T("选中3DES和SM5和MD5加密算法"));
		break;
	case 43: //101011
		AfxMessageBox(__T("选中DES和3DES和SM5和MD5加密算法"));
		break;
	case 44: //101100
		AfxMessageBox(__T("选中AES和SM5和MD5加密算法"));
		break;
	case 45: //101101
		AfxMessageBox(__T("选中DES和AES和SM5和MD5加密算法"));
		break;
	case 46: //101110
		AfxMessageBox(__T("选中3DES和AES和SM5和MD5加密算法"));
		break;
	case 47: //101111
		AfxMessageBox(__T("选中DES和3DES和和AES和SM5和MD5加密算法"));
		break;
	case 48://110000
		AfxMessageBox(__T("选中RSA和MD5加密算法"));
		break;
	case 49://110001
		AfxMessageBox(__T("选中DES和RSA和MD5加密算法"));
		break;
	case 50:
		AfxMessageBox(__T("选中3DES和RSA和MD5加密算法"));//10010
		break;
	case 51:
		AfxMessageBox(__T("选中DES和3DES和RSA和MD5加密算法"));//10011
		break;
	case 52:
		AfxMessageBox(__T("选中AES和RSA和MD5加密算法"));//10100
		break;
	case 53:
		AfxMessageBox(__T("选中DES和AES和RSA和MD5加密算法"));//10101
		break;
	case 54:
		AfxMessageBox(__T("选中3DES和AES和RSA和MD5加密算法"));//10110
		break;
	case 55:
		AfxMessageBox(__T("选中DES和3DES和AES和RSA和MD5加密算法"));//10111
		break;
	case 56:
		AfxMessageBox(__T("选中SM5和RSA和MD5加密算法"));//11000
		break;
	case 57:
		AfxMessageBox(__T("选中DES和SM5和RSA和MD5加密算法"));//11001
		break;
	case 58:
		AfxMessageBox(__T("选中3DES和SM5和RSA和MD5加密算法"));//11010
		break;
	case 59:
		AfxMessageBox(__T("选中DES和3DES和SM5和RSA和MD5加密算法"));//11011
		break;
	case 60:
		AfxMessageBox(__T("选中AES和SM5和RSA和MD5加密算法"));//11100
		break;
	case 61:
		AfxMessageBox(__T("选中DES和AES和SM5和RSA和MD5加密算法"));//11101
		break;
	case 62:
		AfxMessageBox(__T("选中3DES和AES和SM5和RSA和MD5加密算法"));//11110
		break;
	case 63:
		AfxMessageBox(__T("选中DES和3DES和AES和SM5和RSA和MD5加密算法"));//11111
		break;
	default:
		break;
		
	}
	 //显示下拉框
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
	// TODO: 在此添加控件通知处理程序代码
}

void CmeDlg::OnBnClickedButtonChoseCipherFile()
{
	strTemp = "";
	char buf[1000];
	int ret=1000;
	CFileDialog miwen_dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	miwen_dlg.m_ofn.lpstrTitle=__T("打开密文对话框");
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
		//显示下拉条
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
	// TODO: 在此添加控件通知处理程序代码
}

void CmeDlg::OnBnClickedButtonChoseDncrypAlogrithm()
{
	DecrypOptionDlg *myDecrypOptionldg=new DecrypOptionDlg;
	myDecrypOptionldg->DoModal();
	// TODO: 在此添加控件通知处理程序代码
}

void CmeDlg::OnBnClickedButtonDecryp()
{
	//公共变量声明
	CmeApp * mApp = (CmeApp*)AfxGetApp( );
	CFileDialog  mingwen_dlg(FALSE);
	CString mingwenfileName;
	 FILE * pmingwenfile;//明文file指针
	

	///////////一下是AES解密变量声明区域 。

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
	
	 ////////////AES解密变量声明结束行 。
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	char chDes_UnKey[9];
	char ch3Des_UnKey[27];
	//CString strDesKey = CEncrypOptionDlg::mDesKey;
	//chDes_Key =(LPSTR)(LPCSTR)mApp->AfxDesKey; //	密钥
	memcpy(chDes_UnKey,mApp->AfxDesUnKey,mApp->AfxDesUnKey.GetLength());
	memcpy(ch3Des_UnKey,mApp->Afx3DesUnKey,mApp->Afx3DesUnKey.GetLength());
	memcpy(chAes_UnKey,mApp->AfxAesUnKey,mApp->AfxAesUnKey.GetLength());//获得了AESUNKEY的值。
	AES myaes(chAes_UnKey);


	CDES myundes;
	switch (mApp->mMiwendlg)
	{
	case 0://00000
		AfxMessageBox(__T("没有选中任何加密算法"));
		break;											
	case 1://00001
		myundes.filecryption((LPSTR)(LPCSTR)mApp->AfxMiwenPath,chDes_UnKey,1);
		SetDlgItemText(IDC_EDIT_MINGWEN,mApp->AfxFanwen);
		break;
	case 2:	 //000010
		AfxMessageBox(__T("选中3DES加密算法"));
		myundes.file_TriDES_encryption((LPSTR)(LPCSTR)mApp->AfxMiwenPath,ch3Des_UnKey,1);
		SetDlgItemText(IDC_EDIT_MINGWEN,mApp->AfxFanwen);
		break;
	case 3:
		AfxMessageBox(__T("选中DES加密算法和3DES算法"));//000011
		break;
	case 4:
		AfxMessageBox(__T("选中AES解密算法"));//0000100
		AesFp=fopen((LPSTR)(LPCSTR)mApp->AfxMiwenPath,"rb+");//打开密文文件
		fseek(AesFp,0,SEEK_SET);
		fseek(AesFp,0,SEEK_END);
		aesfilelength=ftell(AesFp);	//得到密文的长度
		rewind(AesFp);
		fread(aesfiletemp,aesfilelength,1,AesFp);//读取密文的内容到aesfiletemp临时变量中。
		for(;aesendflag+16<=aesfilelength;)	 //如果结束标志没有达到文件的长度，那说明还没结束。
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
		fclose(AesFp);//关闭密文文件

		if (mingwen_dlg.DoModal() == IDOK)
		{
		 mingwenfileName = mingwen_dlg.GetPathName();
		}
		//FILE * aespmingwenfile;
		pmingwenfile = fopen(mingwenfileName,"wb+");
		fwrite(aesfiletemp,aesfilelength,1,pmingwenfile);
		fclose(pmingwenfile);
		//解密完成
		break;

	case 5:
		AfxMessageBox(__T("选中AES和DES加密算法"));/////0000101
		break;
	case 6:
		AfxMessageBox(__T("选中AES和3DES加密算法"));/////0000110
		break;
	case 7:
		AfxMessageBox(__T("选中DES和3DES和AES加密算法"));//000000111
		break;
	case 8:
		AfxMessageBox(__T("选中SM5加密算法"));//0001000
		break;
	case 9:
		AfxMessageBox(__T("选中DES和SM5加密算法"));	///0001001
		break ;
	case 10:
		AfxMessageBox(__T("选中3DES和SM5加密算法"));//00001010
		break;
	case 11:
		AfxMessageBox(__T("选中DES和3DES和SM5加密算法"));//000001011
		break;
	case 12:
		AfxMessageBox(__T("选中AES和SM5加密算法"));//000001100
		break;
	case 13:
		AfxMessageBox(__T("选中DES和AES和SM5加密算法"));//000001101
		break;
	case 14:
		AfxMessageBox(__T("选中3DES和AES和SM5加密算法"));//000001110
		break;
	case 15:
		AfxMessageBox(__T("选中ES和3DES和和AES和SM5加密算法"));//1111
		break;
	case 16:
		AfxMessageBox(__T("选中RSA加密算法"));//10000
		break;
	case 17:
		AfxMessageBox(__T("选中DES和RSA加密算法"));//10001
		break;
	case 18:
		AfxMessageBox(__T("选中3DES和RSA加密算法"));//10010
		break;
	case 19:
		AfxMessageBox(__T("选中DES和3DES和RSA加密算法"));//10011
		break;
	case 20:
		AfxMessageBox(__T("选中AES和RSA加密算法"));//10100
		break;
	case 21:
		AfxMessageBox(__T("选中DES和AES和RSA加密算法"));//10101
		break;
	case 22:
		AfxMessageBox(__T("选中3DES和AES和RSA加密算法"));//10110
		break;
	case 23:
		AfxMessageBox(__T("选中DES和3DES和AES和RSA加密算法"));//10111
		break;
	case 24:
		AfxMessageBox(__T("选中SM5和RSA加密算法"));//11000
		break;
	case 25:
		AfxMessageBox(__T("选中DES和SM5和RSA加密算法"));//11001
		break;
	case 26:
		AfxMessageBox(__T("选中3DES和SM5和RSA加密算法"));//11010
		break;
	case 27:
		AfxMessageBox(__T("选中DES和3DES和SM5和RSA加密算法"));//11011
		break;
	case 28:
		AfxMessageBox(__T("选中AES和SM5和RSA加密算法"));//11100
		break;
	case 29:
		AfxMessageBox(__T("选中DES和AES和SM5和RSA加密算法"));//11101
		break;
	case 30:
		AfxMessageBox(__T("选中3DES和AES和SM5和RSA加密算法"));//11110
		break;
	case 31:
		AfxMessageBox(__T("选中DES和3DES和AES和SM5和RSA加密算法"));//11111
		break;
	case 32://100000
		AfxMessageBox(__T("选中MD5算法"));
		break;
	case 33://100001
		AfxMessageBox(__T("选中MD5和DES加密算法"));
		break;
	case 34:	 //0100010
		AfxMessageBox(__T("选中MD5和3DES加密算法"));
		break;
	case 35: //100011
		AfxMessageBox(__T("选中DES加密算法和3DES和MD5算法"));
		break;
	case 36:  //100100
		AfxMessageBox(__T("选中AES和MD5加密算法"));
		break;
	case 37: //100101
		AfxMessageBox(__T("选中AES和DES和MD5加密算法"));
		break;
	case 38://100110
		AfxMessageBox(__T("选中AES和3DES和MD5加密算法"));
		break;
	case 39: //100111
		AfxMessageBox(__T("选中DES和3DES和AES和MD5加密算法"));
		break;
	case 40://101000
		AfxMessageBox(__T("选中SM5和MD5加密算法"));
		break;
	case 41://101001
		AfxMessageBox(__T("选中DES和SM5和MD5加密算法"));	
		break ;
	case 42://101010
		AfxMessageBox(__T("选中3DES和SM5和MD5加密算法"));
		break;
	case 43: //101011
		AfxMessageBox(__T("选中DES和3DES和SM5和MD5加密算法"));
		break;
	case 44: //101100
		AfxMessageBox(__T("选中AES和SM5和MD5加密算法"));
		break;
	case 45: //101101
		AfxMessageBox(__T("选中DES和AES和SM5和MD5加密算法"));
		break;
	case 46: //101110
		AfxMessageBox(__T("选中3DES和AES和SM5和MD5加密算法"));
		break;
	case 47: //101111
		AfxMessageBox(__T("选中DES和3DES和和AES和SM5和MD5加密算法"));
		break;
	case 48://110000
		AfxMessageBox(__T("选中RSA和MD5加密算法"));
		break;
	case 49://110001
		AfxMessageBox(__T("选中DES和RSA和MD5加密算法"));
		break;
	case 50:
		AfxMessageBox(__T("选中3DES和RSA和MD5加密算法"));//10010
		break;
	case 51:
		AfxMessageBox(__T("选中DES和3DES和RSA和MD5加密算法"));//10011
		break;
	case 52:
		AfxMessageBox(__T("选中AES和RSA和MD5加密算法"));//10100
		break;
	case 53:
		AfxMessageBox(__T("选中DES和AES和RSA和MD5加密算法"));//10101
		break;
	case 54:
		AfxMessageBox(__T("选中3DES和AES和RSA和MD5加密算法"));//10110
		break;
	case 55:
		AfxMessageBox(__T("选中DES和3DES和AES和RSA和MD5加密算法"));//10111
		break;
	case 56:
		AfxMessageBox(__T("选中SM5和RSA和MD5加密算法"));//11000
		break;
	case 57:
		AfxMessageBox(__T("选中DES和SM5和RSA和MD5加密算法"));//11001
		break;
	case 58:
		AfxMessageBox(__T("选中3DES和SM5和RSA和MD5加密算法"));//11010
		break;
	case 59:
		AfxMessageBox(__T("选中DES和3DES和SM5和RSA和MD5加密算法"));//11011
		break;
	case 60:
		AfxMessageBox(__T("选中AES和SM5和RSA和MD5加密算法"));//11100
		break;
	case 61:
		AfxMessageBox(__T("选中DES和AES和SM5和RSA和MD5加密算法"));//11101
		break;
	case 62:
		AfxMessageBox(__T("选中3DES和AES和SM5和RSA和MD5加密算法"));//11110
		break;
	case 63:
		AfxMessageBox(__T("选中DES和3DES和AES和SM5和RSA和MD5加密算法"));//11111
		break;
	default:
		break;

	}   
	//显示下拉框
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
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
}
