
#ifndef TABCONTROLHELPER_H
#define TABCONTROLHELPER_H

#include "stdafx.h"

// Maximum allowed tab controls
#define MAX_TAB_CONTROL 10

typedef struct _tagTabControlHelper
{
	HINSTANCE	hInstance;			// HINSTANCE of the application
	HWND		hwndTab;			// Handle of the tab control
	int			nTabs;				// Number of tabs
	int			nCurTab;			// Current tab
	BOOL		bDestroyOnChange;	// Destroys tabs losing focus and recreates when activated

	struct{

		UINT		nID;				// ID of the Dialog
		HWND		hwndDialog;			// Handle of the tab dialog
		DLGPROC		DlgProc;			// DialogProc of the dialog
		TCHAR		szTitle[MAX_PATH];	// Title of the tab
		LPARAM		lParam;

	} TabData[MAX_TAB_CONTROL];

} TABCONTROLHELPER, *LPTABCONTROLHELPER;


// Function definitions
int InitTabControl(LPTABCONTROLHELPER);
int DestroyTabControl(LPTABCONTROLHELPER);

// Tab Control Notification Handlers
int OnTabControlSelChange(LPTABCONTROLHELPER);
int OnTabControlSelChanging(LPTABCONTROLHELPER);

// Macros
#define CUR_TAB(tch)	(tch.TabData[tch.nCurTab])

#define NM_CODE(lParam) (((LPNMHDR)lParam)->code)


#endif // TABCONTROLHELPER_H