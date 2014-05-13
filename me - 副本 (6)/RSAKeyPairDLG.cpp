// RSAKeyPairDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "me.h"
#include "RSAKeyPairDLG.h"


// CRSAKeyPairDLG �Ի���

IMPLEMENT_DYNAMIC(CRSAKeyPairDLG, CDialog)

CRSAKeyPairDLG::CRSAKeyPairDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CRSAKeyPairDLG::IDD, pParent)
	, m_strPublicKey(_T(""))
	, m_strPrivateKey(_T(""))
{
	//SKLENGTH = 4;       //˽Կ�ĳ���
}

CRSAKeyPairDLG::~CRSAKeyPairDLG()
{
}

void CRSAKeyPairDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PublicKey, m_strPublicKey);
	DDX_Text(pDX, IDC_PrivateKey, m_strPrivateKey);
}

/*---------------------------------------------------------------------------
���ܣ���ָ�����Զ���Ĵ�������0��ʼ��
��ڲ���������A��
����ֵ����
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::SetZero(byteint A)  
{
	memset(A,0,DATALENGTH);                    //����ϵͳ�������г�ʼ��
}
*/
/*---------------------------------------------------------------------------
���ܣ��õ�һ�������ķ���λ��
��ڲ���������validtemp
����ֵ�������з����λ��
----------------------------------------------------------------------------*/
/*
int CRSAKeyPairDLG::IntValid(byteint validtemp)
{
	int i=0;
	while(validtemp[i]==0 && i<DATALENGTH)
		i++;
	return DATALENGTH-i;
}
*/


/*---------------------------------------------------------------------------
���ܣ��Ƚ���������A��B�Ĵ�С
��ڲ���������A�ʹ���B
����ֵ��A>B:return 1 ; A=B:return 0 ; A<B:return -1
----------------------------------------------------------------------------*/
/*
int CRSAKeyPairDLG::IntCmp(byteint A,byteint B)
{
	int stat;
	stat=memcmp(A,B,DATALENGTH);    //ϵͳ����
	if(stat==0)
		return 0;
	if(stat>0)
		return 1;
	return -1;
}

*/

/*---------------------------------------------------------------------------
���ܣ��������A��B�Ľ������������C�У�����D��
��ڲ�����������A������B������C����D
����ֵ����
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::SetMode(byteint A,byteint B,byteint C,byteint D)
{
	int i,j,k;
	int valid_1,valid_2,valid,sbits,cmpval;
	byteint buf1,buf2;

	SetZero(buf1);  SetZero(buf2);
	SetZero(D);                       //������D���������ʼ��
	IntCpy(C,A);                      //��������A������C��
	valid_2=IntValid(B);              //����B(����)��λ��,
	while((cmpval=IntCmp(C,B))>0)     //�����Ϊ����,ÿ��һ�ξ��ж��Ƿ���C>B,�������ͼ�������
	{
		valid_1=IntValid(C);          //����C(������)��λ��,��Ϊ����λ����ѭ���������Ǳ仯��
		//��������(C-B)��Ȼ�����C��
		valid=valid_1-valid_2;        //C�ĳ�����B�ĳ��ȵĲ��ֵ��СΪ0��
		if(valid>0)                   //����������ȳ�����λ����
		{
			i=DATALENGTH-valid_1;     //������ǰ����ĸ���
			j=DATALENGTH-valid_2;     //����ǰ����ĸ��������±�ָʾ��
			sbits=0;
			for(k=j;k<DATALENGTH;k++)
			{
				if(C[i]>B[j])         //��C��B�����λ��ʼ���αȽ϶�Ӧλ�Ĵ�С���ж��Ƿ񹻼�
					break;
				if(C[i]<B[j])
				{
					sbits=1;          //�������������ôC����һλ����������
					break;
				}
				i++;j++;              //��C��B�����λ���ʱ,�ͱȽ϶��ߵĴθ�λ
			}
			valid=valid-sbits;
			SetZero(buf1);            //buf1����
			for(i=valid;i<DATALENGTH;i++)
			{
				j=i-valid;
				buf1[j]=B[i];         //buf1�д�ŵ���B��������λ֮��õ���ֵ
				//�������,��B���ƺ����λ��C�����λ����,
				//������C�Ĵθ�λ����
			}
		}
		else
			IntCpy(buf1,B);           //��C��B��λ����ͬʱ,��ֱ�Ӱ�B���뻺����buf1��

		D[DATALENGTH-1-valid]++;      //���ﱣ�������ĳһλ�������ļ����Ĵ�����ÿ��һ�ξͼ�1
		Substract(C,buf1,buf2);       //����C�ĳ�����B�ĳ��ȵĲ��Ƿ����0����Ҫ��������ֱ��C<=B
		IntCpy(C,buf2);
	}
	if(cmpval==0)                     //���������
	{
		SetZero(C);                   //����Ϊ0
		D[DATALENGTH-1]++;            //��Ϊ1
	}
}

*/

/*---------------------------------------------------------------------------
���ܣ��ú���������ʮ���ƵĴ�����ת���ɶ����Ƶ���
��ڲ�������ת���Ĵ���B�������ƽ��flag[400]
����ֵ����
----------------------------------------------------------------------------*/
/*void CRSAKeyPairDLG::TransBi(byteint B,signed char flag[400])
{
	byteint buf;
	byteint result;
	byteint temp;
	int i;
	SetZero(buf);  SetZero(result);  SetZero(temp);
	memset(flag,0,400);                     //��flag��������

	i=399;
	IntCpy(buf,B);                          //��B������buf��
	while(IntCmp(buf,ZEROVALUE)==1)         //���buf����Ϊ0
	{
		SetMode(buf,TWOVALUE,temp,result);  //��buf���д�����ģ2���㣬����result�У�����temp
		flag[i]=temp[DATALENGTH-1];         
		IntCpy(buf,result);                 //���̼�������ģ2����
		i--;
	}
	flag[i]=-1;                             //����һ����־λ���������������Ŀ�ʼ
}
*/

/*---------------------------------------------------------------------------
���ܣ�����������B������A�У�ʵ������ת��
��ڲ���������A����������B
����ֵ����
----------------------------------------------------------------------------*/
//���ܣ�����B����������A��ʵ������ת��
/*void CRSAKeyPairDLG::LoadInt(byteint A,mtype B)
{
	int i,j;
	SetZero(A);                  //A���������ʼ��
	i=DATALENGTH-1;
	j=MLENGTH-1;
	while(j>0)                   //ѭ��������λ����
	{
		A[i--]=B[j--];
	}
}
*/
/*---------------------------------------------------------------------------
���ܣ�����A�����B��ˣ��������C�� A��B->C
��ڲ�����������A�ͳ���B�����C
����ֵ����
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::Multiply(byteint A,byteint B,byteint C)
{
	int i,j,w;
	int X,Y,Z;
	int Avalid=0;								//Avalid=validating bits of A
	int Bvalid=0;								//Avalid=validating bits of B
	while (A[Avalid]==0 && Avalid<DATALENGTH)
		Avalid++;								//����Avalid
	while (B[Bvalid]==0 && Bvalid<DATALENGTH)
		Bvalid++;								//����Bvalid

	SetZero(C);									//��C�����ʼ��

	for(i=DATALENGTH-1;i>=Avalid;i--)
		for(j=DATALENGTH-1;j>=Bvalid;j--)       //��λ�����������
		{
			X=A[i]*B[j];        
			Y=X/10;
			Z=X-10*Y;
			w=i+j-(DATALENGTH-1);
			C[w]=C[w]+Z;
			C[w-1]=C[w-1]+(C[w]/10)+Y;
			C[w]=C[w]-(C[w]/10)*10;
		}
		return;
}
*/

/*---------------------------------------------------------------------------
���ܣ��ú�����������ģ���㷨��AΪ������ģΪc�������Ƶ�ָ��B���������flag��
��ڲ���������A��ģC�����D������������flag[400]
����ֵ��A^B=1(mod C),����1��A^B=p-1(mod C),����2�����򷵻�0
----------------------------------------------------------------------------*/
/*
int CRSAKeyPairDLG::PowerMode(byteint A,byteint C,byteint D,signed char flag[400])
{
	byteint buf;
	byteint result;
	byteint temp,P;
	int i;
	SetZero(D);   SetZero(buf); SetZero(result); SetZero(temp); SetZero(P);  //��D����

	IntCpy(temp,A);                       //��A��ֵ������temp��
	if(flag[399]==1)                      //���λΪ1����������flag[i]ֻ��1����0�������
		IntCpy(result,A);
	else								  //���λΪ0������Ϊ1
		IntCpy(result,ONEVALUE);
	i=398;
	while(flag[i]!=-1)                    //�ж��Ƿ��Ѿ�����ָ����ͷ
	{
		Multiply(temp,temp,buf);          //temp*temp->buf 
		SetMode(buf,C,temp,P);            //buf%c����->temp,��->p
		if(flag[i]!=0)                    //�����λ����0�������ǰһ����һλ�Ľ�����г˷�����
		{                                 //���򣬽�����Ϊ��λ��ģ���ڸ�һλ�������У�ֻҪ����һ��
			Multiply(temp,result,buf);    //ƽ�����㣬�Ϳ��Եõ���һλ��ģ
			SetMode(buf,C,result,P);
		}
		i--;
	}                                     //result�д�ŵ������ս��
	IntCpy(buf,C);
	IntCpy(D,result);
	Substract(buf,ONEVALUE,temp);
	if(IntCmp(result,ONEVALUE)==0)        //p mod n=1���ж��Ƿ���A^B=1(mod C)
		return 1;
	if(IntCmp(result,temp)==0)            //p mod n=-1[p-1=-1(mod p)]���ж��Ƿ���A^B=p-1(mod C)
		return 2;
	return 0;
}
*/

/*---------------------------------------------------------------------------
���ܣ�����ز���һ����������������Ϊnum�����λ����0�������RandomA��
��ڲ���������A������num
����ֵ����
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::IntRandom(byteint RandomA,int num)
{
	int i;
	SetZero(RandomA);                     //��RandomA����

	while(!(RandomA[DATALENGTH-1]%2))     //�ж�������֤RandomA�����һλ��������
		RandomA[DATALENGTH-1]=rand()%10;  //������һλ��ż��������²������һλ
	while(!(RandomA[DATALENGTH-num]))     //�ж�������֤RandomA���λ����0
		RandomA[DATALENGTH-num]=rand()%10;//������λ��0,����²������λ

	i=DATALENGTH-2;
	while(i>=DATALENGTH-num+1)            //ѭ�������Ӵε�λ��ʼ���θ�λ������λ�ϵ���
		RandomA[i--]=rand()%10;
}
*/

/*---------------------------------------------------------------------------
���ܣ�������B����������A��
��ڲ���������A������B
����ֵ����
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::IntCpy(byteint A,byteint B)
{
	memcpy(A,B,DATALENGTH);                    //����ϵͳ������ɿ���
}
*/

/*---------------------------------------------------------------------------
���ܣ�����SA��ȥ����SB���������SC
��ڲ�����������SA������SB����SC
����ֵ����
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::Substract(byteint SA,byteint SB,byteint SC)
{
	byteint buf;
	int i,j;
	int X;
	IntCpy(buf,SA);                  //��SA�����ݿ�����buf��
	SetZero(SC);                 //SC�����ʼ��
	for(i=DATALENGTH-1;i>=0;i--)	
	{
		if(buf[i]<SB[i])             //������λ������
		{
			buf[i]=buf[i]+10;        //���λ��1
			if(buf[i-1]>0)           //�����λ������ֱ�Ӽ�1
				(buf[i-1])--;    
			else                     //����һֱ�ҵ�������λ
			{
				j=i-1;
				while(buf[j]==0)     //j�������Խ�磬����Ϊ��֤�����λ��Ϊ0
					buf[j--]=9;
				buf[j]=buf[j]-1;
			}
		}
		X=buf[i]-SB[i];              //����λ���Ľ������SC��
		SC[i]=X;
	}
}
*/


/*---------------------------------------------------------------------------
���ܣ��ú��������Ӽ���[1,b-1]�в������ɸ����ڼ������������Model[]��
��ڲ�������
����ֵ����
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::Mdata()
{
	int i,j;                     //Randomly choose a set of 100 numbers in [1,b-1]
	int k=MLENGTH-2;

	memset(Model,0,TESTNUM*MLENGTH);  //������������������������������㣬���г�ʼ��
	srand( (unsigned)time( NULL ) );  //������������ĳ�ʼ��
	for(i=0;i<TESTNUM;i++)            //TESTNUMΪ��Ҫ�����ĸ���
	{
		for(j=MLENGTH-1;j>=k;j--)
		{
			Model[i][j]=rand()%10;    //ע����������������ĳ����е�����
		}
		if((memcmp(Model[i],mZEROVALUE,MLENGTH))==0)  
			i--;
		k--;                          //��֤������������Ϊ0
		if (k<0) k=MLENGTH-2;
	}

}
*/
/*---------------------------------------------------------------------------
���ܣ�����һ������
��ڲ���������Prm
����ֵ�������ɹ�������0
----------------------------------------------------------------------------*/
/*
int CRSAKeyPairDLG::Prime(byteint Prm)
{
	int i,k,ok;
	signed char flag[400];
	byteint A,B,D,buf1,buf2;
	SetZero(A); SetZero(B); SetZero(D); SetZero(buf1); SetZero(buf2);

	while(1)                                 //һֱѭ��ֱ���ҵ�һ������Ϊֹ
	{
		int pass=0;
		srand( (unsigned)time( NULL ) );     //��ʼ��srand
		IntRandom(B,MLENGTH);                //�������һ������B  try b if prime,B��һ������

		IntCpy(Prm,B);                       //��B������prm�� C=N result prime
		Substract(B,ONEVALUE,buf1);          //��B-ONEVALUE�Ľ���ŵ�buf1��
		SetMode(buf1,TWOVALUE,buf2,B);       //B=(B-1)/2����,buf2=(B-1)/2������=0
		TransBi(B,flag);                     //��Bת��Ϊ�����ƴ���
		ok=1;
		for(i=0;i<TESTNUM;i++)
		{
			LoadInt(A,Model[i]);             //������Model�еĵ�i+1������ȡ��A��
			k=PowerMode(A,Prm,D,flag);       //(A^flag) mod Prm ->D
			if(k!=1 && k!=2)                 //�������ж�����
			{
				ok=0;
				break;
			}
			if(k==1)                         //�ж�����1��G=A^(n-1)/2=1
			{
			}
			if(k==2)                         //�ж�����2��G=A^(n-1)/2=p-1
			{
			}

		}
		if (ok)//if(ok && pass_2)
		{
			return 0;
		}//forѭ���������IntRandom(B,MLENGTH)��������B�Ƿ���һ������	
	}
}
*/

/*---------------------------------------------------------------------------
���ܣ�����ģR
��ڲ���������������p��q��ģR
����ֵ����
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::ComputingR(byteint p,byteint q,byteint R)
{
	Multiply(p,q,R);              // R=p*q, public mode number
}
*/

/*---------------------------------------------------------------------------
���ܣ�����$(r)
��ڲ���������p������q��ģ$(r)����Rvalue
����ֵ����
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::ComputingRvalue(byteint p,byteint q,byteint Rvalue)
{
	byteint buf1,buf2;
	SetZero(buf1); SetZero(buf2);

	Substract(p,ONEVALUE,buf1);   // buf1=p-1
	Substract(q,ONEVALUE,buf2);   // buf2=q-1
	Multiply(buf1,buf2,Rvalue);   // Rvalue=(p-1)*(q-1)
}
*/

/*---------------------------------------------------------------------------
���ܣ�A��B�Ľ����C
��ڲ���������A,B,C
����ֵ����
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::Plus(byteint A,byteint B,byteint C)
{
	int i;//,w;
	int X,Y,Z,m,n,valid;
	m=IntValid(A);                 //����A�ĳ���         
	n=IntValid(B);                 //����B�ĳ���
	valid=(m>n)?m+1:n+1;           //����ʱҪ�������Ϊ׼
	SetZero(C);                    //��C����
	for(i=DATALENGTH-1;i>=DATALENGTH-valid;i--)
	{
		X=A[i]+B[i];               //��λ���
		Y=X/10;
		Z=X-10*Y;

		C[i]=C[i]+Z;               //�����λ
		C[i-1]=C[i-1]+Y;
	}
}
*/

/*---------------------------------------------------------------------------
���ܣ����㹫ԿPK
��ڲ�����$(r)��ֵ��Rvalue�У�˽ԿSK����ԿPK
����ֵ���ɹ��ҵ�������1
----------------------------------------------------------------------------*/
/*
int CRSAKeyPairDLG::ComputingPK(byteint Rvalue,byteint SK,byteint PK)
{
	int i;
	SKLENGTH=4;       //˽Կ�ĳ���

	byteint PA,PB,PC,buf1,temp,buf2;
	SetZero(PK); SetZero(PA); SetZero(PB); SetZero(PC); SetZero(buf1);   //�����ʼ��
	SetZero(temp); SetZero(buf2);
	while(1)
	{
		IntRandom(SK,SKLENGTH);        //�������һ������������ΪGenerated secret key

		IntCpy(PB,SK);
		IntCpy(PA,Rvalue);
		while(1)
		{
			SetMode(PA,PB,PC,PK);     //PA=PB*PK+PC
			i=IntCmp(PC,ONEVALUE);
			if(i==0)                  //PC=1, i=0
				break;                //�����������ǻ��ʵ�
			i=IntCmp(PC,ZEROVALUE);
			if(i==0)
			{
				i=-1;                 //PC=0,i=-1
				break;                //�����㻥������������ѭ������������һ�������
			}
			IntCpy(PA,PB);            //����ŷ����Ķ�������ж�

			IntCpy(PB,PC);
		}
		if(i==0)                      //���㣬��������ѭ��
			break;
	}

	IntCpy(temp,ONEVALUE);
	IntCpy(PA,Rvalue);
	IntCpy(PB,SK);
	while(1)
	{
		Multiply(PA,temp,buf1);  //buf1=PA*temp
		Plus(buf1,ONEVALUE,buf2);//buf2=(PA*temp)+1
		SetMode(buf2,PB,buf1,PK);//buf=((PA*temp)+1)%PB
		if(IntCmp(buf1,ZEROVALUE)==0)
			break;
		Plus(temp,ONEVALUE,buf1);
		IntCpy(temp,buf1);
	}
	return 1;                   //SK and PK found
}
*/

/*---------------------------------------------------------------------------
���ܣ���һ������Aת��Ϊ��Ӧ���ַ�����ʽ
��ڲ���������A
����ֵ�����Ӧ���ַ���
----------------------------------------------------------------------------*/
/*
CString CRSAKeyPairDLG::PrtInt(byteint A)
{
	int int i=0;
	int m,n;
	while(i<DATALENGTH && A[i]==0)          //����������ʼ�Ŀհ�0
		i++;
	if(i<DATALENGTH)
		m=DATALENGTH-i;                     //������õĴ�������
	n=0;
	//ע�⵽�����i�Ѿ��������е�һ������Ԫ�صĶ�Ӧλ�ã�
	CString str="";							//��������ѭ�����Ǵ�������
	//��ŵ��������λ��ʼ�����
	while(i<DATALENGTH)
	{
		str += (A[i++]+'0');
	}
	return str;
}
*/

BEGIN_MESSAGE_MAP(CRSAKeyPairDLG, CDialog)
END_MESSAGE_MAP()


// CRSAKeyPairDLG ��Ϣ�������
