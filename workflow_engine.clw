; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=InputDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "workflow_engine.h"
LastPage=0

ClassCount=8
Class1=CWorkflow_engineApp
Class2=CWorkflow_engineDoc
Class3=CWorkflow_engineView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDD_SELECTDLG
Resource3=IDR_MAINFRAME
Class5=CChildFrame
Class6=CAboutDlg
Class7=SelectDlg
Resource4=IDR_WORKFLTYPE
Class8=InputDlg
Resource5=IDD_INPUTDLG

[CLS:CWorkflow_engineApp]
Type=0
HeaderFile=workflow_engine.h
ImplementationFile=workflow_engine.cpp
Filter=N

[CLS:CWorkflow_engineDoc]
Type=0
HeaderFile=workflow_engineDoc.h
ImplementationFile=workflow_engineDoc.cpp
Filter=N

[CLS:CWorkflow_engineView]
Type=0
HeaderFile=workflow_engineView.h
ImplementationFile=workflow_engineView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=workflow_engine.cpp
ImplementationFile=workflow_engine.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_
Command4=ID_RECTANGLE
Command5=ID_LINE
Command6=ID_RUN
Command7=ID_DELETE
Command8=ID_APP_ABOUT
Command9=ID
Command10=ID_
Command11=ID
CommandCount=11

[MNU:IDR_WORKFLTYPE]
Type=1
Class=CWorkflow_engineView
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_WINDOW_NEW
Command9=ID_WINDOW_CASCADE
Command10=ID_WINDOW_TILE_HORZ
Command11=ID_WINDOW_ARRANGE
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_SELECTDLG]
Type=1
Class=SelectDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO_INPUT,button,1342308361
Control4=IDC_RADIO_ADD,button,1342177289
Control5=IDC_RADIO_SHOW,button,1342177289
Control6=IDC_RADIO_NOTE,button,1342177289
Control7=IDC_RADIO_SAVE,button,1342177289
Control8=IDC_RADIO_NET,button,1342177289

[CLS:SelectDlg]
Type=0
HeaderFile=SelectDlg.h
ImplementationFile=SelectDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT

[DLG:IDD_INPUTDLG]
Type=1
Class=InputDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_EDIT,edit,1350639745
Control3=IDC_STATIC,static,1342308352

[CLS:InputDlg]
Type=0
HeaderFile=InputDlg.h
ImplementationFile=InputDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT
VirtualFilter=dWC

