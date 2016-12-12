; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CT2sDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "t2s.h"

ClassCount=4
Class1=CT2sApp
Class2=CT2sDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CTextProg
Resource3=IDD_T2S_DIALOG

[CLS:CT2sApp]
Type=0
HeaderFile=t2s.h
ImplementationFile=t2s.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CT2sDlg]
Type=0
HeaderFile=t2sDlg.h
ImplementationFile=t2sDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CT2sDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=t2sDlg.h
ImplementationFile=t2sDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_T2S_DIALOG]
Type=1
Class=CT2sDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_EDIT1,edit,1085341892
Control5=IDC_BUTTON2,button,1342242816
Control6=IDC_CHECK1,button,1342242819
Control7=IDC_CHECK2,button,1342242819
Control8=IDC_BUTTON3,button,1208025088
Control9=IDC_PROG,static,1342312704
Control10=IDC_BUTTON4,button,1342242816
Control11=IDC_BUTTON5,button,1342242816
Control12=IDC_BUTTON6,button,1342242816

[CLS:CTextProg]
Type=0
HeaderFile=TextProg.h
ImplementationFile=TextProg.cpp
BaseClass=CStatic
Filter=D
VirtualFilter=WC

