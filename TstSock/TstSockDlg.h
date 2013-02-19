// TstSockDlg.h : header file
//

#if !defined(AFX_TSTSOCKDLG_H__07968E51_1D25_4234_9BE1_8F9828F2410A__INCLUDED_)
#define AFX_TSTSOCKDLG_H__07968E51_1D25_4234_9BE1_8F9828F2410A__INCLUDED_

#include "ListenSocket.h"	// Added by ClassView
#include "ClientSocket.h"	// Added by ClassView
#include "INIAccessor.h"	// Added by ClassView
#include "..\common\INet.h"
#include "TstThread.h"	// Added by ClassView
#include "MyThread.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTstSockDlg dialog

class CTstSockDlg : public CDialog
{
// Construction
public:
	CMyThread m_myThread;
	CTstThread m_threadTst;
	CINIAccessor m_iniAccessor;
	BOOL m_bServer;
	void Send();
	void Connect();
	void Listen();
	CClientSocket m_clientSocket;
	CListenSocket m_listenSocket;
	INet* m_pINet;
	CTstSockDlg(CWnd* pParent = NULL);	// standard constructor
	~CTstSockDlg();

// Dialog Data
	//{{AFX_DATA(CTstSockDlg)
	enum { IDD = IDD_TSTSOCK_DIALOG };
	CIPAddressCtrl	m_ctrlSvrAddr;
	CListBox	m_lstMsg;
	CString	m_strMsg;
	UINT	m_nPort1;
	UINT	m_nPort2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTstSockDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTstSockDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnListen();
	afx_msg void OnConnet();
	afx_msg void OnSend();
	afx_msg void OnUpdateMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TSTSOCKDLG_H__07968E51_1D25_4234_9BE1_8F9828F2410A__INCLUDED_)
