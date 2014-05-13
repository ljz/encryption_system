#pragma once


const int MLENGTH=10;       //质数的长度
const int TESTNUM=30;       //测试质数时的比较的次数
const int DATALENGTH=350;   //大数类型的长度

typedef signed char mtype[MLENGTH];        //定义质数的大数类型
typedef signed char byteint[DATALENGTH];   //定义大数类型


// CRSAKeyPairDLG 对话框

class CRSAKeyPairDLG : public CDialog
{
	DECLARE_DYNAMIC(CRSAKeyPairDLG)

public:
	CRSAKeyPairDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRSAKeyPairDLG();
	mtype Model[TESTNUM];  //TESTNUM big number to be compared
	mtype mZEROVALUE,tempModel;  //0 constant

// 对话框数据
	enum { IDD = IDD_RSA_KEY_DLG };

public:
		/*
		byteint ONEVALUE;
		byteint TWOVALUE;
		byteint ZEROVALUE;
		const int SKLENGTH;       //私钥的长度
		*/
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
/*	void SetZero(byteint A); 
	int IntValid(byteint validtemp);
	int IntCmp(byteint A,byteint B);
	void LoadInt(byteint A,mtype B);
	int PowerMode(byteint A,byteint C,byteint D,signed char flag[400]);
	void Multiply(byteint A,byteint B,byteint C);
	void Plus(byteint A,byteint B,byteint C);


	void SetMode(byteint A,byteint B,byteint C,byteint D);
	void TransBi(byteint B,signed char flag[400]);

	void IntRandom(byteint RandomA,int num);
	void IntCpy(byteint A,byteint B);
	void Substract(byteint SA,byteint SB,byteint SC);

	void Mdata();                                           //产生用于生成质数中进行比较的数
	int Prime(byteint Prm);                                 //产生一个长度为MLENGTH的质数
	void ComputingR(byteint p,byteint q,byteint R);
	void ComputingRvalue(byteint p,byteint q,byteint Rvalue);
	int ComputingPK(byteint Rvalue,byteint SK,byteint PK);
	CString PrtInt(byteint A);*/

	DECLARE_MESSAGE_MAP()
public:
	CString m_strPublicKey;
	CString m_strPrivateKey;
};
