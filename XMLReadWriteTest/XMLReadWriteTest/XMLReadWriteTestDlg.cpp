
// XMLReadWriteTestDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CXMLReadWriteTestDlg 对话框



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


// CXMLReadWriteTestDlg 消息处理程序

BOOL CXMLReadWriteTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CXMLReadWriteTestDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CXMLReadWriteTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CXMLReadWriteTestDlg::OnBnClickedCreatxml()
{
	//创建一个XML文件;
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
	XMLROOT->setAttribute("ID", "12345");  //设置根标签的属性; 
	XMLDOC->appendChild(XMLROOT);

	CString TMP;
	MSXML2::IXMLDOMElementPtr XMLNODE;
	for (int I = 0; I<10; I++)
	{ 
		//<NODE0 ID="0" NAME="NODENAME">NODETEXTS</NODE0>
		TMP.Format(_T("%d"), I);
		XMLNODE = XMLDOC->createElement((_bstr_t)(_T("NODE") + TMP));
		XMLNODE->put_text((_bstr_t)"NODETEXTS");//设置标签的文本内容;  
		XMLNODE->setAttribute("ID", (_variant_t)TMP);//设置标签的属性及内容;    
		XMLNODE->setAttribute("NAME", "NODENAME");
		XMLROOT->appendChild(XMLNODE);
	}
	XMLDOC->save("XMLTEST.XML");
	XMLNODE.Release();
	XMLROOT.Release();
	XMLDOC.Release();
	::CoUninitialize();
	MessageBox(_T("创建XML成功！"));
}


void CXMLReadWriteTestDlg::OnBnClickedReadxml()
{
	//读取一个XML;

	::CoInitialize(NULL);
	MSXML2::IXMLDOMDocumentPtr XMLDOC;
	MSXML2::IXMLDOMElementPtr XMLROOT;
	MSXML2::IXMLDOMElementPtr XMLELEMENT;
	MSXML2::IXMLDOMNodeListPtr XMLNODES; //某个节点的所有子节点  
	MSXML2::IXMLDOMNamedNodeMapPtr XMLNODEATTS;//某个节点的所有属性;
	MSXML2::IXMLDOMNodePtr XMLNODE;
	MSXML2::IXMLDOMNodePtr  XMLNODEATT;//某个节点的一个属性
	HRESULT HR = XMLDOC.CreateInstance(_uuidof(MSXML2::DOMDocument30));
	if (!SUCCEEDED(HR))
	{
		MessageBox(_T("faild!!"));
	}
	XMLDOC->load("XMLTEST.XML");
	XMLROOT = XMLDOC->GetdocumentElement();//获得根节点;  
	XMLROOT->get_childNodes(&XMLNODES);//获得根节点的所有子节点;		
	long XMLNODESNUM, ATTSNUM;
	XMLNODES->get_length(&XMLNODESNUM);//获得所有子节点的个数;  
	CString TMP;
	TMP.Format(_T("%d"), XMLNODESNUM);
	MessageBox(TMP);
	for (int I = 0; I<XMLNODESNUM; I++)
	{
		//<NODE0 ID="0" NAME="NODENAME">NODETEXTS</NODE0>		
		XMLNODES->get_item(I, &XMLNODE);//获得某个子节点;
		XMLNODE->get_attributes(&XMLNODEATTS);//获得某个节点的所有属性;  
		XMLNODEATTS->get_length(&ATTSNUM);//获得所有属性的个数;  
		for (int J = 0; J<ATTSNUM; J++)
		{
			XMLNODEATTS->get_item(J, &XMLNODEATT);//获得某个属性;  
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
