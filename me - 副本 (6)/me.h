// me.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmeApp:
// �йش����ʵ�֣������ me.cpp
//

class CmeApp : public CWinApp
{
public:
	CmeApp();
public:
   int mMingwendlg;
   int mMiwendlg;
   int RSA_d,RSA_n,RSA_e;
   CString AfxMingwenPath ;
   CString AfxMiwenPath;
   CString AfxDesKey;
   CString Afx3DesKey;
   CString Afx3DesUnKey;
   CString AfxAesUnKey;
   CString AfxAesKey;
   CString Afx_RSA_PK;
   CString Afx_RSA_SK;
   CString Afxhash;

   CString AfxDesUnKey;
   CString AfxFanwen;

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};
//CString mingwendlgStr;// ���ڻ�ȡ����·����ȫ�ֱ���

extern CmeApp theApp;