; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTstSockDlg
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TstSock.h"

ClassCount=8
Class1=CTstSockApp
Class2=CTstSockDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CListenSocket
Class6=CClientSocket
Class4=CServerSocket
Class7=CTstThread
Class8=CMyThread
Resource3=IDD_TSTSOCK_DIALOG

[CLS:CTstSockApp]
Type=0
HeaderFile=TstSock.h
ImplementationFile=TstSock.cpp
Filter=N

[CLS:CTstSockDlg]
Type=0
HeaderFile=TstSockDlg.h
ImplementationFile=TstSockDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_PORT1

[CLS:CAboutDlg]
Type=0
HeaderFile=TstSockDlg.h
ImplementationFile=TstSockDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TSTSOCK_DIALOG]
Type=1
Class=CTstSockDlg
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LISTEN,button,1342242816
Control4=IDC_CONNET,button,1342242816
Control5=IDC_SEND,button,1342242816
Control6=IDC_EDTMSG,edit,1350631552
Control7=IDC_LSTMSG,listbox,1352728835
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,button,1342177287
Control10=IDC_SVRIPADDR,SysIPAddress32,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_PORT2,edit,1350631552
Control14=IDC_PORT1,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_Tst,button,1342242816

[CLS:CServerSocket]
Type=0
HeaderFile=ServerSocket.h
ImplementationFile=ServerSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq

[CLS:CListenSocket]
Type=0
HeaderFile=ListenSocket.h
ImplementationFile=ListenSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq

[CLS:CClientSocket]
Type=0
HeaderFile=ClientSocket.h
ImplementationFile=ClientSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq

[CLS:CTstThread]
Type=0
HeaderFile=TstThread.h
ImplementationFile=TstThread.cpp
BaseClass=CWinThread
Filter=N
VirtualFilter=TC

[CLS:CMyThread]
Type=0
HeaderFile=MyThread.h
ImplementationFile=MyThread.cpp
BaseClass=CWinThread
Filter=N

