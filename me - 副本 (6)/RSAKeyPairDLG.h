#pragma once


const int MLENGTH=10;       //�����ĳ���
const int TESTNUM=30;       //��������ʱ�ıȽϵĴ���
const int DATALENGTH=350;   //�������͵ĳ���

typedef signed char mtype[MLENGTH];        //���������Ĵ�������
typedef signed char byteint[DATALENGTH];   //�����������


// CRSAKeyPairDLG �Ի���

class CRSAKeyPairDLG : public CDialog
{
	DECLARE_DYNAMIC(CRSAKeyPairDLG)

public:
	CRSAKeyPairDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRSAKeyPairDLG();
	mtype Model[TESTNUM];  //TESTNUM big number to be compared
	mtype mZEROVALUE,tempModel;  //0 constant

// �Ի�������
	enum { IDD = IDD_RSA_KEY_DLG };

public:
		/*
		byteint ONEVALUE;
		byteint TWOVALUE;
		byteint ZEROVALUE;
		const int SKLENGTH;       //˽Կ�ĳ���
		*/
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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

	void Mdata();                                           //�����������������н��бȽϵ���
	int Prime(byteint Prm);                                 //����һ������ΪMLENGTH������
	void ComputingR(byteint p,byteint q,byteint R);
	void ComputingRvalue(byteint p,byteint q,byteint Rvalue);
	int ComputingPK(byteint Rvalue,byteint SK,byteint PK);
	CString PrtInt(byteint A);*/

	DECLARE_MESSAGE_MAP()
public:
	CString m_strPublicKey;
	CString m_strPrivateKey;
};
