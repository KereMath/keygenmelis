#include "StdAfx.h"
#include "maindlg.h"
#include "resource.h"
#include <commctrl.h>

CMainDlg::CMainDlg()
{
	m_nID = KG_MAIN;
}

CMainDlg::~CMainDlg()
{
}

LRESULT CALLBACK CMainDlg::DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_INITDIALOG:
		return OnInitDialog(wParam, lParam);

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_ABOUT:
			DialogBox(m_hInstance, (LPCTSTR)IDD_ABOUTBOX, m_hDlg, (DLGPROC)About);
			break;

		case IDM_EXIT:
		case IDCANCEL:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_NOTIFY:
		if (((LPNMHDR)lParam)->code == TCN_SELCHANGE) OnTabControlSelChange(&m_tch);
		break;
	}

	return 0;
}

LRESULT CMainDlg::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	DIALOGBASEPARAM dbp;

	m_tch.hInstance = m_hInstance;
	m_tch.bDestroyOnChange = FALSE;
	m_tch.hwndTab = GetDlgItem(m_hDlg, IDC_TAB1);
	m_tch.nTabs = 1;

	dbp.pDialogBase = &neddlg;
	dbp.lParam = NULL;
	mbstowcs(m_tch.TabData[0].szTitle, "Anahtar Uretme", 260);
	m_tch.TabData[0].DlgProc = (DLGPROC)CNEDDlg::StaticDlgProc;
	m_tch.TabData[0].lParam = (LPARAM)&dbp;
	m_tch.TabData[0].nID = KG_KEYGENERATION;

	InitTabControl(&m_tch);

	return 0;
}


LRESULT CALLBACK CMainDlg::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

