
// XMLReadWriteTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CXMLReadWriteTestApp: 
// �йش����ʵ�֣������ XMLReadWriteTest.cpp
//

class CXMLReadWriteTestApp : public CWinApp
{
public:
	CXMLReadWriteTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CXMLReadWriteTestApp theApp;