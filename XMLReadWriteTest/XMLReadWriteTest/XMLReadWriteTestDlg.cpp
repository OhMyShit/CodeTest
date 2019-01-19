
// XMLReadWriteTestDlg.cpp : ʵ���ļ�
//

 
#include "stdafx.h"
#include "XMLReadWriteTest.h"
#include "XMLReadWriteTestDlg.h"
#include "afxdialogex.h"
#import <msxml3.dll>

using namespace MSXML2;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CXMLReadWriteTestDlg �Ի���



CXMLReadWriteTestDlg::CXMLReadWriteTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_XMLREADWRITETEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXMLReadWriteTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CXMLReadWriteTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATXML, &CXMLReadWriteTestDlg::OnBnClickedCreatxml)
	ON_BN_CLICKED(IDC_READXML, &CXMLReadWriteTestDlg::OnBnClickedReadxml)
END_MESSAGE_MAP()


// CXMLReadWriteTestDlg ��Ϣ�������

BOOL CXMLReadWriteTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CXMLReadWriteTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CXMLReadWriteTestDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CXMLReadWriteTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CXMLReadWriteTestDlg::OnBnClickedCreatxml()
{
	//����һ��XML�ļ�;
	::CoInitialize(NULL);
	MSXML2::IXMLDOMDocumentPtr XMLDOC;
	MSXML2::IXMLDOMElementPtr XMLROOT;

	HRESULT HR = XMLDOC.CreateInstance(_uuidof(MSXML2::DOMDocument30));
	if (!SUCCEEDED(HR))
	{
		MessageBox(_T("faild!!"));
		return;
	}
	XMLROOT = XMLDOC->createElement("ROOT");
	XMLROOT->setAttribute("ID", "12345");  //���ø���ǩ������; 
	XMLDOC->appendChild(XMLROOT);

	CString TMP;
	MSXML2::IXMLDOMElementPtr XMLNODE;
	for (int I = 0; I<10; I++)
	{ 
		//<NODE0 ID="0" NAME="NODENAME">NODETEXTS</NODE0>
		TMP.Format(_T("%d"), I);
		XMLNODE = XMLDOC->createElement((_bstr_t)(_T("NODE") + TMP));
		XMLNODE->put_text((_bstr_t)"NODETEXTS");//���ñ�ǩ���ı�����;  
		XMLNODE->setAttribute("ID", (_variant_t)TMP);//���ñ�ǩ�����Լ�����;    
		XMLNODE->setAttribute("NAME", "NODENAME");
		XMLROOT->appendChild(XMLNODE);
	}
	XMLDOC->save("XMLTEST.XML");
	XMLNODE.Release();
	XMLROOT.Release();
	XMLDOC.Release();
	::CoUninitialize();
	MessageBox(_T("����XML�ɹ���"));
}


void CXMLReadWriteTestDlg::OnBnClickedReadxml()
{
	//��ȡһ��XML;

	::CoInitialize(NULL);
	MSXML2::IXMLDOMDocumentPtr XMLDOC;
	MSXML2::IXMLDOMElementPtr XMLROOT;
	MSXML2::IXMLDOMElementPtr XMLELEMENT;
	MSXML2::IXMLDOMNodeListPtr XMLNODES; //ĳ���ڵ�������ӽڵ�  
	MSXML2::IXMLDOMNamedNodeMapPtr XMLNODEATTS;//ĳ���ڵ����������;
	MSXML2::IXMLDOMNodePtr XMLNODE;
	MSXML2::IXMLDOMNodePtr  XMLNODEATT;//ĳ���ڵ��һ������
	HRESULT HR = XMLDOC.CreateInstance(_uuidof(MSXML2::DOMDocument30));
	if (!SUCCEEDED(HR))
	{
		MessageBox(_T("faild!!"));
	}
	XMLDOC->load("XMLTEST.XML");
	XMLROOT = XMLDOC->GetdocumentElement();//��ø��ڵ�;  
	XMLROOT->get_childNodes(&XMLNODES);//��ø��ڵ�������ӽڵ�;		
	long XMLNODESNUM, ATTSNUM;
	XMLNODES->get_length(&XMLNODESNUM);//��������ӽڵ�ĸ���;  
	CString TMP;
	TMP.Format(_T("%d"), XMLNODESNUM);
	MessageBox(TMP);
	for (int I = 0; I<XMLNODESNUM; I++)
	{
		//<NODE0 ID="0" NAME="NODENAME">NODETEXTS</NODE0>		
		XMLNODES->get_item(I, &XMLNODE);//���ĳ���ӽڵ�;
		XMLNODE->get_attributes(&XMLNODEATTS);//���ĳ���ڵ����������;  
		XMLNODEATTS->get_length(&ATTSNUM);//����������Եĸ���;  
		for (int J = 0; J<ATTSNUM; J++)
		{
			XMLNODEATTS->get_item(J, &XMLNODEATT);//���ĳ������;  
			CString T1 = (_bstr_t)XMLNODEATT->nodeName;
			CString T2 = (_bstr_t)XMLNODEATT->text;
			MessageBox(T1 + " = " + T2);
		}

		MessageBox((_bstr_t)XMLNODE->nodeName + ": " + (_bstr_t)XMLNODE->text);
		
	}
	//XMLDOC->save("XMLTEST.XML");  
	XMLNODES.Release();
	XMLNODE.Release();
	XMLROOT.Release();
	XMLDOC.Release();
	::CoUninitialize();
}
