// me.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CmeApp:
// 有关此类的实现，请参阅 me.cpp
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

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};
//CString mingwendlgStr;// 用于获取明文路径的全局变量

extern CmeApp theApp;