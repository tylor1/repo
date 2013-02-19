// TstSockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TstSock.h"
#include "TstSockDlg.h"

#include "..\utils\api.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUF_SIZE											1024
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTstSockDlg dialog

CTstSockDlg::CTstSockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTstSockDlg::IDD, pParent),
	m_pINet(0)
{
	//{{AFX_DATA_INIT(CTstSockDlg)
	m_strMsg = _T("");
	m_nPort1 = 1500;
	m_nPort2 = 1500;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bServer = FALSE;
}

CTstSockDlg::~CTstSockDlg()
{

}

void CTstSockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTstSockDlg)
	DDX_Control(pDX, IDC_SVRIPADDR, m_ctrlSvrAddr);
	DDX_Control(pDX, IDC_LSTMSG, m_lstMsg);
	DDX_Text(pDX, IDC_EDTMSG, m_strMsg);
	DDX_Text(pDX, IDC_PORT1, m_nPort1);
	DDX_Text(pDX, IDC_PORT2, m_nPort2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTstSockDlg, CDialog)
	//{{AFX_MSG_MAP(CTstSockDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LISTEN, OnListen)
	ON_BN_CLICKED(IDC_CONNET, OnConnet)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_MESSAGE(WM_UPDATEMSG, OnUpdateMsg)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_Tst, OnTst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTstSockDlg message handlers

BOOL CTstSockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// m_lstMsg.AddString("你好吗?");
	// CEdit* pEdt = GetDlgItem(IDC_EDTMSG)

	BYTE ip[4] = {192, 168, 2, 106};
	m_ctrlSvrAddr.SetAddress(ip[0], ip[1], ip[2], ip[3]);

	m_strMsg = "你好吗？";

	UpdateData(FALSE);

	char szPath[MAX_PATH];
	ZeroMemory(szPath,MAX_PATH);
	// GetAppDirectory(szPath);
	// GetModuleFileName(NULL, szPath, MAX_PATH);
	CString fullPath;
	PrefixAppDir("ModNetCenter.dll",fullPath);

	// OutputDebugString(fullPath);
	// OutputDebugString(_T(".\r\n前面是应用所在的位置.\r\n"));
	// AfxMessageBox(fullPath);

	m_iniAccessor.WriteString("dbserver","ip","192.168.2.106");
	m_iniAccessor.WriteInt("dbserver","port", 1500);

	// Log(fullPath);

	// m_pINet = LoadNetFromModule("ModNetCenter.dll");
	LONG lPort=3024;
	struct sockaddr_in ServerHostAddr;	// 服务主机地址
	ServerHostAddr.sin_family=AF_INET;
	ServerHostAddr.sin_port=::htons(u_short(lPort));
	ServerHostAddr.sin_addr.s_addr=::inet_addr("192.168.1.10");
	HOSTENT* pResult=gethostbyaddr((const char *) &
		(ServerHostAddr.sin_addr.s_addr),4,AF_INET);
	if(NULL==pResult)
	{
		int nErrorCode=WSAGetLastError();
		TRACE("gethostbyaddr errorcode=%d",nErrorCode);
	}
	else
	{
		TRACE("gethostbyaddr %s\n",pResult->h_name);;
	}

	// { Test CSocket int thread 

	m_threadTst.CreateThread();
	// m_myThread.CreateThread();

	// { Test CSocket int thread 


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTstSockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTstSockDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTstSockDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTstSockDlg::Listen()
{
	UpdateData(TRUE);

	m_listenSocket.Close();
	if (m_listenSocket.Create(m_nPort1))
	{
		m_listenSocket.Listen();
		m_listenSocket.m_pMainWnd = this;
	}
}

void CTstSockDlg::Connect()
{
	UpdateData(TRUE);

	CString strSvrIP;
	BYTE ip[4] = {0};
	m_ctrlSvrAddr.GetAddress(ip[0], ip[1], ip[2], ip[3]);
	strSvrIP.Format("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

	m_clientSocket.Close();
	m_clientSocket.Create();

	if (m_clientSocket.Connect(strSvrIP,m_nPort2))
	{
		AfxMessageBox("联机成功!");
		m_clientSocket.m_pMainWnd = this;
	}
	else
	{
		OutputDebugString(_T("联机失败！"));
	}
/**/
	m_bServer = FALSE;

// 	SOCKET sock = m_clientSocket.Detach();
// 	m_threadTst.SetSocket(sock);

	SOCKET sock = 0;
	m_threadTst.SetSocket(sock);

	// // Can not set time for keep alive, so we used below
	// m_clientSocket.SetSockOpt(SO_KEEPALIVE, TRUE, sizeof(BOOL));
/*
	// Keep Alive
	SOCKET sock = m_clientSocket.m_hSocket;
    tcp_keepalive inKeepAlive = {0}; // 输入参数
    unsigned long ulInLen = sizeof(tcp_keepalive);
    tcp_keepalive outKeepAlive = {0}; // 输出参数
    unsigned long ulOutLen = sizeof(tcp_keepalive);
    unsigned long ulBytesReturn = 0;
    // 设置socket的keep alive为5秒，并且发送次数为3次
    inKeepAlive.onoff = 1;
    inKeepAlive.keepaliveinterval = 1000; // 两次KeepAlive探测间的时间间隔
    inKeepAlive.keepalivetime = 5000; // 开始首次KeepAlive探测前的TCP空闭时间

    if (WSAIoctl(sock, SIO_KEEPALIVE_VALS,
        (LPVOID)&inKeepAlive, ulInLen,
        (LPVOID)&outKeepAlive, ulOutLen,
        &ulBytesReturn, NULL, NULL) == SOCKET_ERROR)
    {
		return;
        // return 0;
    }
*/

}

void CTstSockDlg::Send()
{
	char buf[BUF_SIZE];
	ZeroMemory(buf, BUF_SIZE);

	int nRes = 0;
	CString str = "abdeeddd";
	UpdateData(TRUE);
	if ( !m_bServer )
	{
		nRes = m_clientSocket.Send(m_strMsg, m_strMsg.GetLength());
	}
	else
	{
		nRes = m_listenSocket.Send(m_strMsg, m_strMsg.GetLength());
	}
	str.Format("Send: nRes = %d.\r\n",nRes);
	OutputDebugString(str);
}

void CTstSockDlg::OnListen() 
{
	// TODO: Add your control notification handler code here
	Listen();
	m_bServer = TRUE;
}

void CTstSockDlg::OnConnet() 
{
	// TODO: Add your control notification handler code here
	Connect();
	
}

void CTstSockDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	Send();	
}

void CTstSockDlg::OnUpdateMsg(WPARAM wParam, LPARAM lParam)
{
	m_lstMsg.AddString(CString((char*)wParam));
}

void CTstSockDlg::OnDestroy() 
{
	// m_threadTst.Delete();
	// m_threadTst.PostThreadMessage(WM_QUIT,0,0);
	m_threadTst.PostThreadMessage(WM_CLEARUP,0,0);
	
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pINet)
	{
		delete m_pINet;
	}
}

void CTstSockDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_threadTst.PostThreadMessage(WM_CLEARUP,0,0);

	CDialog::OnClose();
}

void CTstSockDlg::OnTst() 
{
	// TODO: Add your control notification handler code here
	
	// m_threadTst.PostThreadMessage(WM_QUIT,0,0);

	m_threadTst.PostThreadMessage(WM_CLEARUP,0,0);
	
}
