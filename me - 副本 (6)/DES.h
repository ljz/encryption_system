//DES类

#pragma once

class CDES
{
public:
	CDES(){};
public:
	void inttoch(_int64 temp,char ch[4]);

	unsigned int PM(unsigned int x);          /////////////32位置换

	unsigned int Sbox(unsigned int x[2]);         /////////////////// s 合置换

	void Extend(unsigned int x,unsigned int y[2]);     /////////////扩展换算
	unsigned int LTr(unsigned int x,unsigned int y);       ////////////// 28位密钥 移位
	void PC1(unsigned int x[2]);      ////////////// 密钥置换 64位到56位
	void PC2(unsigned x[2]);        //////////// 密钥置换 56位到 48位
	void Ckey(unsigned int x[2],unsigned int y[16][2]);
	void cryption(unsigned int text[2],unsigned int key[16][2],int flag);
	unsigned int chtoint(char ch[4]);
	int filecryption(char *fname,char ch[9],int crypflag);// 文件的DES加密函数
	int file_TriDES_encryption(char *fname,char ch[18],int crypflag);	// 文件的3DES加密函数
};




/*  DES 中的各个子函数   */
////////  \\\\\\\\\\各种表
char IP_PERMUTE[64]={\
58,50,42,34,26,18,10,2,\
60,52,44,36,28,20,12,4,\
62,54,46,38,30,22,14,6,\
64,56,48,40,32,24,16,8,\
57,49,41,33,25,17,9,1,\
59,51,43,35,27,19,11,3,\
61,53,45,37,29,21,13,5,\
63,55,47,39,31,23,15,7};

char IP_PERMUTE_1[64]={\
40,8,48,16,56,24,64,32,\
39,7,47,15,55,23,63,31,\
38,6,46,14,54,22,62,30,\
37,5,45,13,53,21,61,29,\
36,4,44,12,52,20,60,28,\
35,3,43,11,51,19,59,27,\
34,2,42,10,50,18,58,26,\
33,1,41,9,49,17,57,25};

char P_PERMUTE[32]={\
16,7,20,21,\
29,12,28,17,\
1,15,23,26,\
5,18,31,10,\
2,8,24,14,\
32,27,3,9,\
19,13,30,6,\
22,11,4,25};

char S_BOX1[4][16]={\
14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,\
0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,\
4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,\
15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};

char S_BOX2[4][16]={\
15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,\
3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,\
0,14,7,11,10,4,12,1,5,8,12,6,9,3,2,15,\
13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9};

char S_BOX3[4][16]={\
10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,\
13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,\
13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,\
1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,};

char S_BOX4[4][16]={\
7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,\
13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,\
10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,\
3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14};

char S_BOX5[4][16]={\
2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,\
14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,\
4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,\
11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3};

char S_BOX6[4][16]={\
12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,\
10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,\
9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,\
4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13};

char S_BOX7[4][16]={\
4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,2,\
13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,\
1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,\
6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12};

char S_BOX8[4][16]={\
13,2,8,4,6,14,11,1,10,9,3,14,5,0,12,7,\
1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,\
7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,\
2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};


char PC_PERMUTE1[56]={\
57,49,41,33,25,17,9,\
1,58,50,42,34,26,18,\
10,2,59,51,43,35,27,\
19,11,3,60,52,44,36,\
63,55,47,39,31,23,15,\
7,62,54,46,38,30,22,\
14,6,61,53,45,37,29,\
21,13,5,28,20,12,4};



char PC_PERMUTE2[48]={\
14,17,11,24,1,5,\
3,28,15,6,21,10,\
23,19,12,4,26,8,\
16,7,27,20,13,2,\
41,52,31,37,47,55,\
30,40,51,45,33,48,\
44,49,39,56,23,53,\
46,42,50,36,29,32};

char LTranslocation[16]={\
1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};



unsigned int CDES::PM(unsigned int x)          /////////////32位置换
{
	unsigned int temp,flag;
	unsigned int i;
	temp=x;
	x=0;
	for(i=0;i<32;i++)
	{
		flag=temp>>P_PERMUTE[i];
		flag=flag&0x1;
		x=x*2+flag;
	}
	return x;
}


unsigned int CDES::Sbox(unsigned int x[2])         /////////////////// s 合置换
{
	unsigned int ret=0;
	unsigned int i,j;
	unsigned int temp=0,flag=0;
	for(i=0,j=0;i<8;i++)
	{
		if(i>=4)
			j=1;
		temp=x[j]>>((3-i%4)*6);
		flag=temp&0x3;
		temp=temp>>2;
		temp=temp&0xf;
		switch(i)
		{
		case 0:temp=S_BOX1[flag][temp];break;
		case 1:temp=S_BOX2[flag][temp];break;
		case 2:temp=S_BOX3[flag][temp];break;
		case 3:temp=S_BOX4[flag][temp];break;
		case 4:temp=S_BOX5[flag][temp];break;
		case 5:temp=S_BOX6[flag][temp];break;
		case 6:temp=S_BOX7[flag][temp];break;
		case 7:temp=S_BOX8[flag][temp];break;
		}
		ret=ret<<4;
		ret+=temp;
	}
	return ret;
}

void CDES::Extend(unsigned int x,unsigned int y[2])     /////////////扩展换算
{
	unsigned int i;
	unsigned int temp=0;
	y[0]=0;
	y[1]=0;
	for(i=0;i<8;i++)
	{
		temp=(x>>(8*(7-i)+7))&0x1;
		temp=(temp<<4)+((x>>(8*(7-i)))&0xf);
		temp=temp*2+((x>>(8*(7-i)+7))&0x1);
		if(i<4)
			y[0]=(y[0]<<6)+temp;
		else
			y[1]=(y[1]<<6)+temp;
	}
}



unsigned int CDES::LTr(unsigned int x,unsigned int y)       ////////////// 28位密钥 移位
{
	unsigned int temp;
	unsigned int flag;
	flag=LTranslocation[x-1];
	temp=y>>(28-flag);
	if(flag=1)
		temp=temp&0x1;
	else
		temp=temp&0x3;
	y=(y<<flag)+temp;
	return y;
}

void CDES::PC1(unsigned int x[2])      ////////////// 密钥置换 64位到56位
{
	unsigned int temp[2],flag;
	temp[1] = x[1];
	temp[0] = x[0];
	x[0] = 0;
	x[1] = 0;
	for(int i=0;i<56;i++)
	{
		if(i<28)
		{
			if(PC_PERMUTE1[i]>32)
			{
				flag=64-PC_PERMUTE1[i];
				flag=temp[1]>>flag;
				flag=flag&0x1;
				x[0]= 2*x[0]+ flag;
			}
			else
			{
				flag=32-PC_PERMUTE1[i];
				flag=temp[0]>>flag;
				flag= flag&0x1;
				x[0]= 2*x[0]+ flag;
			}
		}
		else
		{
			if(PC_PERMUTE1[i]>32)
			{
				flag=64-PC_PERMUTE1[i];
				flag=temp[1]>>flag;
				flag=flag&0x1;
				x[1]= 2*x[1]+ flag;
			}
			else
			{
				flag=32-IP_PERMUTE_1[i];
				flag=temp[0]>>flag;
				flag= flag&0x1;
				x[1]= 2*x[1]+ flag;
			}
		}
	}
}

void CDES::PC2(unsigned x[2])        //////////// 密钥置换 56位到 48位
{
	unsigned int temp[2],flag;
	temp[1] = x[1];
	temp[0] = x[0];
	x[0] = 0;
	x[1] = 0;
	for(int i=0;i<48;i++)
	{
		if(i<24)
		{
			if(PC_PERMUTE2[i]>28)
			{
				flag=56-PC_PERMUTE2[i];
				flag=temp[1]>>flag;
				flag=flag&0x1;
				x[0]= 2*x[0]+ flag;
			}
			else
			{
				flag=28-PC_PERMUTE2[i];
				flag=temp[0]>>flag;
				flag= flag&0x1;
				x[0]= 2*x[0]+ flag;
			}
		}
		else
		{
			if(PC_PERMUTE2[i]>28)
			{
				flag=56-PC_PERMUTE2[i];
				flag=temp[1]>>flag;
				flag=flag&0x1;
				x[1]= 2*x[1]+ flag;
			}
			else
			{
				flag=28-PC_PERMUTE2[i];
				flag=temp[0]>>flag;
				flag= flag&0x1;
				x[1]= 2*x[1]+ flag;
			}
		}
	}
}

void CDES::Ckey(unsigned int x[2],unsigned int y[16][2])   ///////////密钥生成
{
	unsigned int i;
	PC1(x);
	for(i=0;i<16;i++)
	{
		x[0]=LTr(i+1,x[0]);
		x[1]=LTr(i+1,x[1]);
		y[i][0]=x[0];
		y[i][1]=x[1];
		PC2(y[i]);
	}
}

void CDES::cryption(unsigned int text[2],unsigned int key[16][2],int flag)
{
	unsigned int temp;
	unsigned int ex[2];
	int i=0;
	if(flag==1)
		i=15;
	for(;;)
	{

		temp=text[1];
		Extend(text[1],ex);
		ex[0]=ex[0]^key[i][0];
		ex[1]=ex[1]^key[i][1];
		text[1]=Sbox(ex);
		text[1]=PM(text[1]);
		text[1]=text[0]^text[1];
		text[0]=temp;
		if(flag==0)
		{
			i++;
			if(i==16)
				break;
		}
		else
		{
			i--;
			if(i<0)
				break;
		}

	}

	temp=text[1];
	text[1]=text[0];
	text[0]=temp;
}
unsigned int CDES::chtoint(char ch[4])   //func2
{
	unsigned int temp;
	unsigned int intt[4];
	for(int i=0;i<4;i++)
	{
		int flag=(ch[i]>>7)&0x1;
		if(flag==1)
			intt[i]=128+(ch[i]&0x7f);
		else
			intt[i]=ch[i];
	}
	temp=256*256*256*intt[0]+256*256*intt[1]+256*intt[2]+intt[3];
	return temp;
}
void CDES::inttoch(_int64 temp,char ch[4])
{
	ch[0]=temp/(256*256*256);
	ch[1]=(temp-256*256*256*ch[0])/(256*256);
	ch[2]=(temp-256*256*256*ch[0]-256*256*ch[1])/256;
	ch[3]=temp-256*256*256*ch[0]-256*256*ch[1]-256*ch[2];
}
 //DES加密函数
int CDES::filecryption(char *fname,char ch[9],int crypflag)
{
	//AfxMessageBox(__T("开始DES加密算法"));
	FILE *fp;


	char ckey1[4]={'\0','\0','\0','\0'},ckey2[4]={'\0','\0','\0','\0'};
	unsigned keyn[2];
	unsigned skeyn[16][2];
	char text1[4],text2[4];
	unsigned int textn[2];






	ckey1[0]=ch[0];     ckey1[1]=ch[1];     ckey1[2]=ch[2];		ckey1[3]=ch[3];
	ckey2[0]=ch[4];		ckey2[1]=ch[5];		ckey2[2]=ch[6];		ckey2[3]=ch[7];
	keyn[0]=chtoint(ckey1);
	keyn[1]=chtoint(ckey2);
	Ckey(keyn,skeyn);



	fp=fopen(fname,"rb+");
	if(fp==NULL)
	{
		return 2;

	}
	int ftel=fseek(fp,0,2);
	ftel=ftell(fp);

	ftel=ftel%8;
	for(int j=ftel;0<j&&j<=7;j++)
	{
		fputc(' ',fp);
	}

	char filetemp[20000];
	int filelength=ftell(fp);
	rewind(fp);
	fread(filetemp,filelength,1,fp);
	int endflag=0;
	for(;endflag+8<=filelength;)
	{

		text1[0]=filetemp[endflag+0];		text1[1]=filetemp[endflag+1];		text1[2]=filetemp[endflag+2];		text1[3]=filetemp[endflag+3];
		text2[0]=filetemp[endflag+4];		text2[1]=filetemp[endflag+5];		text2[2]=filetemp[endflag+6];		text2[3]=filetemp[endflag+7];

		textn[0]=chtoint(text1);
		textn[1]=chtoint(text2);
		cryption(textn,skeyn,crypflag);
		inttoch(textn[0],text1);
		inttoch(textn[1],text2);

		filetemp[endflag+0]=text1[0];		filetemp[endflag+1]=text1[1];		filetemp[endflag+2]=text1[2];		filetemp[endflag+3]=text1[3];
		filetemp[endflag+4]=text2[0];		filetemp[endflag+5]=text2[1];       filetemp[endflag+6]=text2[2];		filetemp[endflag+7]=text2[3];
		endflag+=8;
	}
	//rewind(fp);
	//fwrite(filetemp,filelength,1,fp);   //重新存储为原文件
	fclose(fp);

	//rewind(fp);
	//CmeApp * msApp = (CmeApp*)AfxGetApp( );
	//AfxMessageBox("msApp->AfxMiwenPath");
	//AfxMessageBox(msApp->AfxMiwenPath);


	CFileDialog miwen_dlg(FALSE);
	CString miwenfileName;
	if (miwen_dlg.DoModal() == IDOK)
	{
		miwenfileName = miwen_dlg.GetPathName();
	}
	FILE * pmiwenfile;
	pmiwenfile = fopen(miwenfileName,"wb+");
	//AfxMessageBox(pmiwenfile);
	//rewind(pmiwenfile);
	fwrite(filetemp,filelength,1,pmiwenfile);//pmiwenfile);
	CmeApp * mApp = (CmeApp*)AfxGetApp( );
	mApp->AfxFanwen = filetemp;

//	GetDlgItem(IDC_EDIT_MIWEN)->SetDlgItemText((CString)filetemp);
	//SetDlgItemText(IDC_EDIT_MIWEN,(CString)filetemp);
	//extern CString	m_edit_miwen;
	//CmeApp * mApp = (CmeApp*)AfxGetApp( );
	//mApp->AfxFanwen=filetemp;
	//AfxMessageBox(mApp->AfxFanwen);
	//UpdateData(FALSE);
	fclose(pmiwenfile);
	
	return 1;
};




//3DES加密解密函数

int CDES::file_TriDES_encryption(char *fname,char ch[27],int crypflag)
{
	//*/
	AfxMessageBox(__T("进入3DES函数"));
	char   ch_low[9];
	char   ch_mid[9];
	char   ch_high[9];
	for(int i =0;i<18;i++)
	{
		if (i<9)
		{
			ch_low[i] = ch[i];
		} 
		else if(i<18)
		{
			ch_mid[i-9]=ch[i];
		}
		else
		{
			ch_high[i-18] = ch[i];
		}
	}
	//AfxMessageBox(__T("开始DES加密算法"));
	FILE *fp;

	//地位
	char ckey1_low[4]={'\0','\0','\0','\0'},ckey2_low[4]={'\0','\0','\0','\0'};
	unsigned keyn_low[2];
	unsigned skeyn_low[16][2];
	char text1[4],text2[4];
	unsigned int textn[2];
	//中位
	char ckey1_mid[4]={'\0','\0','\0','\0'},ckey2_mid[4]={'\0','\0','\0','\0'};
	unsigned keyn_mid[2];
	unsigned skeyn_mid[16][2];
	//高位
	char ckey1_high[4]={'\0','\0','\0','\0'},ckey2_high[4]={'\0','\0','\0','\0'};
	unsigned keyn_high[2];
	unsigned skeyn_high[16][2];
	




	 //低位
	ckey1_low[0]=ch_low[0];     ckey1_low[1]=ch_low[1];     ckey1_low[2]=ch_low[2];		ckey1_low[3]=ch_low[3];
	ckey2_low[0]=ch_low[4];		ckey2_low[1]=ch_low[5];		ckey2_low[2]=ch_low[6];		ckey2_low[3]=ch_low[7];
	keyn_low[0]=chtoint(ckey1_low);
	keyn_low[1]=chtoint(ckey2_low);
	Ckey(keyn_low,skeyn_low);
	//中位
	ckey1_mid[0]=ch_mid[0];     ckey1_mid[1]=ch_mid[1];     ckey1_mid[2]=ch_mid[2];		ckey1_mid[3]=ch_mid[3];
	ckey2_mid[0]=ch_mid[4];		ckey2_mid[1]=ch_mid[5];		ckey2_mid[2]=ch_mid[6];		ckey2_mid[3]=ch_mid[7];
	keyn_mid[0]=chtoint(ckey1_mid);
	keyn_mid[1]=chtoint(ckey2_mid);
	Ckey(keyn_mid,skeyn_mid);
	//高位
	ckey1_high[0]=ch_high[0];     ckey1_high[1]=ch_high[1];     ckey1_high[2]=ch_high[2];		ckey1_high[3]=ch_high[3];
	ckey2_high[0]=ch_high[4];		ckey2_high[1]=ch_high[5];		ckey2_high[2]=ch_high[6];		ckey2_high[3]=ch_high[7];
	keyn_high[0]=chtoint(ckey1_high);
	keyn_high[1]=chtoint(ckey2_high);
	Ckey(keyn_high,skeyn_high);



	fp=fopen(fname,"rb+");
	if(fp==NULL)
	{
		return 2;

	}
	int ftel=fseek(fp,0,2);
	ftel=ftell(fp);

	ftel=ftel%8;
	for(int j=ftel;0<j&&j<=7;j++)
	{
		fputc(' ',fp);
	}

	char filetemp[20000];
	int filelength=ftell(fp);
	rewind(fp);
	fread(filetemp,filelength,1,fp);
	int endflag=0;
	for(;endflag+8<=filelength;)
	{

		text1[0]=filetemp[endflag+0];		text1[1]=filetemp[endflag+1];		text1[2]=filetemp[endflag+2];		text1[3]=filetemp[endflag+3];
		text2[0]=filetemp[endflag+4];		text2[1]=filetemp[endflag+5];		text2[2]=filetemp[endflag+6];		text2[3]=filetemp[endflag+7];

		textn[0]=chtoint(text1);
		textn[1]=chtoint(text2);
		if (crypflag == 1)
		{
			cryption(textn,skeyn_low,crypflag);
			cryption(textn,skeyn_mid,!crypflag);
			cryption(textn,skeyn_high,crypflag);
		} 
		else
		{
			cryption(textn,skeyn_high,crypflag);
			cryption(textn,skeyn_mid,!crypflag);
			cryption(textn,skeyn_low,crypflag);
		}
		
		inttoch(textn[0],text1);
		inttoch(textn[1],text2);

		filetemp[endflag+0]=text1[0];		filetemp[endflag+1]=text1[1];		filetemp[endflag+2]=text1[2];		filetemp[endflag+3]=text1[3];
		filetemp[endflag+4]=text2[0];		filetemp[endflag+5]=text2[1];       filetemp[endflag+6]=text2[2];		filetemp[endflag+7]=text2[3];
		endflag+=8;
	}
	//rewind(fp);
	//fwrite(filetemp,filelength,1,fp);   //重新存储为原文件
	fclose(fp);

	//rewind(fp);
	//CmeApp * msApp = (CmeApp*)AfxGetApp( );
	//AfxMessageBox("msApp->AfxMiwenPath");
	//AfxMessageBox(msApp->AfxMiwenPath);


	CFileDialog miwen_dlg(FALSE);
	CString miwenfileName;
	if (miwen_dlg.DoModal() == IDOK)
	{
		miwenfileName = miwen_dlg.GetPathName();
	}
	FILE * pmiwenfile;
	pmiwenfile = fopen(miwenfileName,"wb+");
	//AfxMessageBox(pmiwenfile);
	//rewind(pmiwenfile);
	fwrite(filetemp,filelength,1,pmiwenfile);//pmiwenfile);
	CmeApp * mApp = (CmeApp*)AfxGetApp( );
	mApp->AfxFanwen = filetemp;

	//	GetDlgItem(IDC_EDIT_MIWEN)->SetDlgItemText((CString)filetemp);
	//SetDlgItemText(IDC_EDIT_MIWEN,(CString)filetemp);
	//extern CString	m_edit_miwen;
	//CmeApp * mApp = (CmeApp*)AfxGetApp( );
	//mApp->AfxFanwen=filetemp;
	//AfxMessageBox(mApp->AfxFanwen);
	//UpdateData(FALSE);
	fclose(pmiwenfile);
	  //*/
	return 1;
};

