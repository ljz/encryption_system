// RSAKeyPairDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "me.h"
#include "RSAKeyPairDLG.h"


// CRSAKeyPairDLG 对话框

IMPLEMENT_DYNAMIC(CRSAKeyPairDLG, CDialog)

CRSAKeyPairDLG::CRSAKeyPairDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CRSAKeyPairDLG::IDD, pParent)
	, m_strPublicKey(_T(""))
	, m_strPrivateKey(_T(""))
{
	//SKLENGTH = 4;       //私钥的长度
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
功能：将指定的自定义的大数进行0初始化
入口参数：大数A名
返回值：无
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::SetZero(byteint A)  
{
	memset(A,0,DATALENGTH);                    //调用系统函数进行初始化
}
*/
/*---------------------------------------------------------------------------
功能：得到一个大数的非零位数
入口参数：大数validtemp
返回值：大数中非零的位数
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
功能：比较两个大数A和B的大小
入口参数：大数A和大数B
返回值：A>B:return 1 ; A=B:return 0 ; A<B:return -1
----------------------------------------------------------------------------*/
/*
int CRSAKeyPairDLG::IntCmp(byteint A,byteint B)
{
	int stat;
	stat=memcmp(A,B,DATALENGTH);    //系统函数
	if(stat==0)
		return 0;
	if(stat>0)
		return 1;
	return -1;
}

*/

/*---------------------------------------------------------------------------
功能：计算大数A÷B的结果，余数放在C中，商在D中
入口参数：被除数A，除数B，余数C，商D
返回值：无
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::SetMode(byteint A,byteint B,byteint C,byteint D)
{
	int i,j,k;
	int valid_1,valid_2,valid,sbits,cmpval;
	byteint buf1,buf2;

	SetZero(buf1);  SetZero(buf2);
	SetZero(D);                       //将大数D进行清零初始化
	IntCpy(C,A);                      //将被除数A拷贝到C中
	valid_2=IntValid(B);              //计算B(除数)的位数,
	while((cmpval=IntCmp(C,B))>0)     //变除法为减法,每减一次就判断是否有C>B,如果满足就继续减。
	{
		valid_1=IntValid(C);          //计算C(被除数)的位数,因为它的位数在循环过程中是变化的
		//做减法后(C-B)仍然存放在C中
		valid=valid_1-valid_2;        //C的长度与B的长度的差（该值最小为0）
		if(valid>0)                   //如果被除数比除数的位数多
		{
			i=DATALENGTH-valid_1;     //被除数前导零的个数
			j=DATALENGTH-valid_2;     //除数前导零的个数，作下标指示器
			sbits=0;
			for(k=j;k<DATALENGTH;k++)
			{
				if(C[i]>B[j])         //从C和B的最高位开始依次比较对应位的大小，判断是否够减
					break;
				if(C[i]<B[j])
				{
					sbits=1;          //如果不够减，那么C就退一位，再做减法
					break;
				}
				i++;j++;              //当C和B的最高位相等时,就比较二者的次高位
			}
			valid=valid-sbits;
			SetZero(buf1);            //buf1清零
			for(i=valid;i<DATALENGTH;i++)
			{
				j=i-valid;
				buf1[j]=B[i];         //buf1中存放的是B左移若干位之后得到的值
				//如果够减,则B左移后最高位与C的最高位对齐,
				//否则与C的次高位对齐
			}
		}
		else
			IntCpy(buf1,B);           //当C和B的位数相同时,就直接把B放入缓冲区buf1中

		D[DATALENGTH-1-valid]++;      //这里保存的是在某一位上所做的减法的次数，每做一次就加1
		Substract(C,buf1,buf2);       //不论C的长度与B的长度的差是否大于0，都要做减法，直到C<=B
		IntCpy(C,buf2);
	}
	if(cmpval==0)                     //两个数相等
	{
		SetZero(C);                   //余数为0
		D[DATALENGTH-1]++;            //商为1
	}
}

*/

/*---------------------------------------------------------------------------
功能：该函数用来将十进制的大整数转换成二进制的数
入口参数：需转换的大数B，二进制结果flag[400]
返回值：无
----------------------------------------------------------------------------*/
/*void CRSAKeyPairDLG::TransBi(byteint B,signed char flag[400])
{
	byteint buf;
	byteint result;
	byteint temp;
	int i;
	SetZero(buf);  SetZero(result);  SetZero(temp);
	memset(flag,0,400);                     //将flag数组清零

	i=399;
	IntCpy(buf,B);                          //将B拷贝到buf中
	while(IntCmp(buf,ZEROVALUE)==1)         //如果buf内容为0
	{
		SetMode(buf,TWOVALUE,temp,result);  //将buf进行大数的模2运算，商在result中，余数temp
		flag[i]=temp[DATALENGTH-1];         
		IntCpy(buf,result);                 //对商继续进行模2运算
		i--;
	}
	flag[i]=-1;                             //设置一个标志位，表明二进制数的开始
}
*/

/*---------------------------------------------------------------------------
功能：将质数类型B拷贝到A中，实现类型转换
入口参数：大数A，质数类型B
返回值：无
----------------------------------------------------------------------------*/
//功能：将数B拷贝到大数A，实现类型转换
/*void CRSAKeyPairDLG::LoadInt(byteint A,mtype B)
{
	int i,j;
	SetZero(A);                  //A进行清零初始化
	i=DATALENGTH-1;
	j=MLENGTH-1;
	while(j>0)                   //循环拷贝各位数字
	{
		A[i--]=B[j--];
	}
}
*/
/*---------------------------------------------------------------------------
功能：大数A与大数B相乘，结果放入C中 A×B->C
入口参数：被乘数A和乘数B，结果C
返回值：无
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::Multiply(byteint A,byteint B,byteint C)
{
	int i,j,w;
	int X,Y,Z;
	int Avalid=0;								//Avalid=validating bits of A
	int Bvalid=0;								//Avalid=validating bits of B
	while (A[Avalid]==0 && Avalid<DATALENGTH)
		Avalid++;								//计算Avalid
	while (B[Bvalid]==0 && Bvalid<DATALENGTH)
		Bvalid++;								//计算Bvalid

	SetZero(C);									//将C清零初始化

	for(i=DATALENGTH-1;i>=Avalid;i--)
		for(j=DATALENGTH-1;j>=Bvalid;j--)       //逐位进行相乘运算
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
功能：该函数用来进行模幂算法，A为底数，模为c，二进制的指数B存放在数组flag中
入口参数：底数A，模C，结果D，二进制质数flag[400]
返回值：A^B=1(mod C),返回1；A^B=p-1(mod C),返回2；否则返回0
----------------------------------------------------------------------------*/
/*
int CRSAKeyPairDLG::PowerMode(byteint A,byteint C,byteint D,signed char flag[400])
{
	byteint buf;
	byteint result;
	byteint temp,P;
	int i;
	SetZero(D);   SetZero(buf); SetZero(result); SetZero(temp); SetZero(P);  //将D清零

	IntCpy(temp,A);                       //将A的值拷贝到temp中
	if(flag[399]==1)                      //最低位为1，拷贝本身，flag[i]只有1或者0两种情况
		IntCpy(result,A);
	else								  //最低位为0，则幂为1
		IntCpy(result,ONEVALUE);
	i=398;
	while(flag[i]!=-1)                    //判断是否已经到达指数尽头
	{
		Multiply(temp,temp,buf);          //temp*temp->buf 
		SetMode(buf,C,temp,P);            //buf%c余数->temp,商->p
		if(flag[i]!=0)                    //如果该位不是0，则将其和前一步低一位的结果进行乘法运算
		{                                 //否则，将其作为该位的模，在高一位的运算中，只要进行一次
			Multiply(temp,result,buf);    //平方运算，就可以得到高一位的模
			SetMode(buf,C,result,P);
		}
		i--;
	}                                     //result中存放的是最终结果
	IntCpy(buf,C);
	IntCpy(D,result);
	Substract(buf,ONEVALUE,temp);
	if(IntCmp(result,ONEVALUE)==0)        //p mod n=1，判断是否有A^B=1(mod C)
		return 1;
	if(IntCmp(result,temp)==0)            //p mod n=-1[p-1=-1(mod p)]，判断是否有A^B=p-1(mod C)
		return 2;
	return 0;
}
*/

/*---------------------------------------------------------------------------
功能：随机地产生一个大数奇数，长度为num，最高位不是0，存放在RandomA中
入口参数：大数A，长度num
返回值：无
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::IntRandom(byteint RandomA,int num)
{
	int i;
	SetZero(RandomA);                     //将RandomA清零

	while(!(RandomA[DATALENGTH-1]%2))     //判断条件保证RandomA的最后一位数是奇数
		RandomA[DATALENGTH-1]=rand()%10;  //如果最后一位是偶数，则从新产生最后一位
	while(!(RandomA[DATALENGTH-num]))     //判断条件保证RandomA最高位不是0
		RandomA[DATALENGTH-num]=rand()%10;//如果最高位是0,则从新产生最高位

	i=DATALENGTH-2;
	while(i>=DATALENGTH-num+1)            //循环产生从次低位开始到次高位的所有位上的数
		RandomA[i--]=rand()%10;
}
*/

/*---------------------------------------------------------------------------
功能：将大数B拷贝到大数A中
入口参数：大数A，大数B
返回值：无
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::IntCpy(byteint A,byteint B)
{
	memcpy(A,B,DATALENGTH);                    //调用系统函数完成拷贝
}
*/

/*---------------------------------------------------------------------------
功能：大数SA减去大数SB，结果放入SC
入口参数：被减数SA，减数SB，差SC
返回值：无
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::Substract(byteint SA,byteint SB,byteint SC)
{
	byteint buf;
	int i,j;
	int X;
	IntCpy(buf,SA);                  //将SA的内容拷贝到buf中
	SetZero(SC);                 //SC清零初始化
	for(i=DATALENGTH-1;i>=0;i--)	
	{
		if(buf[i]<SB[i])             //如果最低位不够减
		{
			buf[i]=buf[i]+10;        //向高位借1
			if(buf[i-1]>0)           //如果高位够减，直接减1
				(buf[i-1])--;    
			else                     //否则一直找到够减的位
			{
				j=i-1;
				while(buf[j]==0)     //j不会出现越界，是因为保证了最高位不为0
					buf[j--]=9;
				buf[j]=buf[j]-1;
			}
		}
		X=buf[i]-SB[i];              //将各位减的结果存入SC中
		SC[i]=X;
	}
}
*/


/*---------------------------------------------------------------------------
功能：该函数用来从集合[1,b-1]中产生若干个用于检测的数，存放在Model[]中
入口参数：无
返回值：无
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::Mdata()
{
	int i,j;                     //Randomly choose a set of 100 numbers in [1,b-1]
	int k=MLENGTH-2;

	memset(Model,0,TESTNUM*MLENGTH);  //这个函数在这里用来将整个数组清零，进行初始化
	srand( (unsigned)time( NULL ) );  //进行随机函数的初始化
	for(i=0;i<TESTNUM;i++)            //TESTNUM为需要产生的个数
	{
		for(j=MLENGTH-1;j>=k;j--)
		{
			Model[i][j]=rand()%10;    //注意这里与测试素数的程序中的区别，
		}
		if((memcmp(Model[i],mZEROVALUE,MLENGTH))==0)  
			i--;
		k--;                          //保证所产生的数不为0
		if (k<0) k=MLENGTH-2;
	}

}
*/
/*---------------------------------------------------------------------------
功能：产生一个质数
入口参数：大数Prm
返回值：产生成功，返回0
----------------------------------------------------------------------------*/
/*
int CRSAKeyPairDLG::Prime(byteint Prm)
{
	int i,k,ok;
	signed char flag[400];
	byteint A,B,D,buf1,buf2;
	SetZero(A); SetZero(B); SetZero(D); SetZero(buf1); SetZero(buf2);

	while(1)                                 //一直循环直到找到一个素数为止
	{
		int pass=0;
		srand( (unsigned)time( NULL ) );     //初始化srand
		IntRandom(B,MLENGTH);                //随机产生一个大数B  try b if prime,B是一个奇数

		IntCpy(Prm,B);                       //将B拷贝到prm中 C=N result prime
		Substract(B,ONEVALUE,buf1);          //将B-ONEVALUE的结果放到buf1中
		SetMode(buf1,TWOVALUE,buf2,B);       //B=(B-1)/2的商,buf2=(B-1)/2的余数=0
		TransBi(B,flag);                     //将B转换为二进制大数
		ok=1;
		for(i=0;i<TESTNUM;i++)
		{
			LoadInt(A,Model[i]);             //将数组Model中的第i+1个数读取到A中
			k=PowerMode(A,Prm,D,flag);       //(A^flag) mod Prm ->D
			if(k!=1 && k!=2)                 //不符合判定规则
			{
				ok=0;
				break;
			}
			if(k==1)                         //判定条件1，G=A^(n-1)/2=1
			{
			}
			if(k==2)                         //判定条件2，G=A^(n-1)/2=p-1
			{
			}

		}
		if (ok)//if(ok && pass_2)
		{
			return 0;
		}//for循环用来检测IntRandom(B,MLENGTH)产生的数B是否是一个素数	
	}
}
*/

/*---------------------------------------------------------------------------
功能：计算模R
入口参数：产生的质数p，q，模R
返回值：无
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::ComputingR(byteint p,byteint q,byteint R)
{
	Multiply(p,q,R);              // R=p*q, public mode number
}
*/

/*---------------------------------------------------------------------------
功能：计算$(r)
入口参数：质数p，质数q，模$(r)放在Rvalue
返回值：无
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
功能：A＋B的结果送C
入口参数：大数A,B,C
返回值：无
----------------------------------------------------------------------------*/
/*
void CRSAKeyPairDLG::Plus(byteint A,byteint B,byteint C)
{
	int i;//,w;
	int X,Y,Z,m,n,valid;
	m=IntValid(A);                 //计算A的长度         
	n=IntValid(B);                 //计算B的长度
	valid=(m>n)?m+1:n+1;           //计算时要以最长的数为准
	SetZero(C);                    //将C清零
	for(i=DATALENGTH-1;i>=DATALENGTH-valid;i--)
	{
		X=A[i]+B[i];               //按位相加
		Y=X/10;
		Z=X-10*Y;

		C[i]=C[i]+Z;               //计算进位
		C[i-1]=C[i-1]+Y;
	}
}
*/

/*---------------------------------------------------------------------------
功能：计算公钥PK
入口参数：$(r)的值在Rvalue中，私钥SK，公钥PK
返回值：成功找到，返回1
----------------------------------------------------------------------------*/
/*
int CRSAKeyPairDLG::ComputingPK(byteint Rvalue,byteint SK,byteint PK)
{
	int i;
	SKLENGTH=4;       //私钥的长度

	byteint PA,PB,PC,buf1,temp,buf2;
	SetZero(PK); SetZero(PA); SetZero(PB); SetZero(PC); SetZero(buf1);   //清零初始化
	SetZero(temp); SetZero(buf2);
	while(1)
	{
		IntRandom(SK,SKLENGTH);        //随机产生一个大数奇数作为Generated secret key

		IntCpy(PB,SK);
		IntCpy(PA,Rvalue);
		while(1)
		{
			SetMode(PA,PB,PC,PK);     //PA=PB*PK+PC
			i=IntCmp(PC,ONEVALUE);
			if(i==0)                  //PC=1, i=0
				break;                //满足条件，是互质的
			i=IntCmp(PC,ZEROVALUE);
			if(i==0)
			{
				i=-1;                 //PC=0,i=-1
				break;                //不满足互质条件，跳出循环，从新生成一个随机数
			}
			IntCpy(PA,PB);            //按照欧几里的定理继续判断

			IntCpy(PB,PC);
		}
		if(i==0)                      //满足，跳出查找循环
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
功能：将一个大数A转换为相应的字符串形式
入口参数：大数A
返回值：相对应的字符串
----------------------------------------------------------------------------*/
/*
CString CRSAKeyPairDLG::PrtInt(byteint A)
{
	int int i=0;
	int m,n;
	while(i<DATALENGTH && A[i]==0)          //跳过大数开始的空白0
		i++;
	if(i<DATALENGTH)
		m=DATALENGTH-i;                     //求出有用的大数长度
	n=0;
	//注意到这里的i已经是数组中第一个非零元素的对应位置，
	CString str="";							//因此下面的循环就是从数组中
	//存放的数的最高位开始输出。
	while(i<DATALENGTH)
	{
		str += (A[i++]+'0');
	}
	return str;
}
*/

BEGIN_MESSAGE_MAP(CRSAKeyPairDLG, CDialog)
END_MESSAGE_MAP()


// CRSAKeyPairDLG 消息处理程序
