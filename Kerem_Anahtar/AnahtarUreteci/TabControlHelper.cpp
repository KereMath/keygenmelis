
#include "stdafx.h"
#include "TabControlHelper.h"
#include <commctrl.h>





int InitTabControl(LPTABCONTROLHELPER lptch)
{
	int a;
	TCITEM tie;

	// Verify that the tab count is between the limits
	if( (lptch->nTabs < 1) || (lptch->nTabs > MAX_TAB_CONTROL) ) return -1;

	// Add the tabs
    tie.mask = TCIF_TEXT | TCIF_IMAGE; 
	tie.iImage = -1; 

	for(a = 0; a < lptch->nTabs; a++)
	{
		tie.pszText = lptch->TabData[a].szTitle;
		TabCtrl_InsertItem(lptch->hwndTab, a, &tie); 
	}

	// Initialize the dialog handles to NULL
	for(a = 0; a < lptch->nTabs; a++)	lptch->TabData[a].hwndDialog = NULL;

	// Create and show the first dialog
	lptch->TabData[0].hwndDialog = CreateDialogParam(lptch->hInstance, 
												MAKEINTRESOURCE(lptch->TabData[0].nID),
												lptch->hwndTab, 
												lptch->TabData[0].DlgProc,
												lptch->TabData[0].lParam);

	// Could not create the dialog
	if(lptch->TabData[0].hwndDialog == NULL) return -2;

	// Adjust the tab dialog and show it
	SetWindowPos(lptch->TabData[0].hwndDialog, NULL, 5, 20, NULL, NULL, SWP_NOSIZE);
	ShowWindow(lptch->TabData[0].hwndDialog, SW_SHOW);

	// Set the current tab value
	lptch->nCurTab = 0;

	// Create the other dialogs as well
	for(a = 1; a < lptch->nTabs; a++)
	{
		lptch->TabData[a].hwndDialog = CreateDialogParam(lptch->hInstance, 
			MAKEINTRESOURCE(lptch->TabData[a].nID),
			lptch->hwndTab, 
			lptch->TabData[a].DlgProc,
			lptch->TabData[a].lParam);

			ShowWindow(lptch->TabData[a].hwndDialog, SW_HIDE);
			SetWindowPos(lptch->TabData[a].hwndDialog, NULL, 5, 20, NULL, NULL, SWP_NOSIZE);

	}

	return 0;
}


int OnTabControlSelChange(LPTABCONTROLHELPER lptch)
{
	int nNewTab = TabCtrl_GetCurSel(lptch->hwndTab);

	// No change
	if(lptch->nCurTab == nNewTab) return 0;

	if(lptch->bDestroyOnChange)
	{
		// Destroy the dialog losing focus
		if(lptch->TabData[lptch->nCurTab].hwndDialog != NULL)
		{
			DestroyWindow(lptch->TabData[lptch->nCurTab].hwndDialog);
			lptch->TabData[lptch->nCurTab].hwndDialog = NULL;
		}
	}
	else
	{
		//	Do not destroy, just hide
		ShowWindow(lptch->TabData[lptch->nCurTab].hwndDialog, SW_HIDE);
	}

	lptch->nCurTab = nNewTab;

	if(lptch->TabData[lptch->nCurTab].hwndDialog == NULL)
	{
		lptch->TabData[lptch->nCurTab].hwndDialog = CreateDialogParam(lptch->hInstance, 
													MAKEINTRESOURCE(lptch->TabData[lptch->nCurTab].nID),
													lptch->hwndTab, 
													lptch->TabData[lptch->nCurTab].DlgProc,
													lptch->TabData[lptch->nCurTab].lParam);
		
		// Could not create dialog
		if(lptch->TabData[lptch->nCurTab].hwndDialog == NULL) return -1;


		SetWindowPos(lptch->TabData[lptch->nCurTab].hwndDialog, NULL, 5, 20, NULL, NULL, SWP_NOSIZE);
		ShowWindow(lptch->TabData[lptch->nCurTab].hwndDialog, SW_SHOW);
	}
	else
	{
		// Already created, show it
		ShowWindow(lptch->TabData[lptch->nCurTab].hwndDialog, SW_SHOW);
	}

	return 0;
}

int OnTabControlSelChanging(LPTABCONTROLHELPER lptch)
{
	return TRUE;
}


int DestroyTabControl(LPTABCONTROLHELPER lptch)
{
	// Destroy the tab dialogs
	for(int a = 0; a < lptch->nTabs; a++)
	{
		if(lptch->TabData[a].hwndDialog != NULL) DestroyWindow(lptch->TabData[a].hwndDialog);
		lptch->TabData[a].hwndDialog = NULL;
	}

	// Remove the tab items ( necessary ? )
	TabCtrl_DeleteAllItems(lptch->hwndTab);
	
	return 0;
}
