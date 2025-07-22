#include "StdAfx.h"
#include "dialogbase.h"
//#include "resource.h"

extern HINSTANCE g_hInstance;

CDialogBase::CDialogBase() : m_nID(NULL), m_hDlg(NULL), m_hInstance(NULL)
{
}

CDialogBase::~CDialogBase()
{
}


LRESULT CALLBACK CDialogBase::StaticDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LPDIALOGBASEPARAM lpdbp;
	CDialogBase *pDialog = NULL;

	if (msg == WM_INITDIALOG || msg == WM_CREATE)
	{
		lpdbp = (LPDIALOGBASEPARAM)lParam;
		lpdbp->pDialogBase->m_hDlg = hDlg;

		SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)lpdbp->pDialogBase);

		return lpdbp->pDialogBase->DlgProc(hDlg, msg, wParam, lParam);
	}
	else
	{
		pDialog = (CDialogBase*)GetWindowLongPtr(hDlg, GWLP_USERDATA);

		if (pDialog)
			return pDialog->DlgProc(hDlg, msg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK CDialogBase::DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}


INT_PTR CDialogBase::DoModal(HINSTANCE hInstance, HWND hwndOwner, LPARAM lParam)
{
	DIALOGBASEPARAM dbp;

	m_hInstance = hInstance;

	dbp.pDialogBase = this;
	dbp.lParam = lParam;

	return DialogBoxParam(hInstance, MAKEINTRESOURCE(m_nID), hwndOwner, (DLGPROC)StaticDlgProc, (LPARAM)&dbp);
}


HWND CDialogBase::Create(HINSTANCE hInstance, HWND hwndOwner, BOOL bShow, LPARAM lParam)
{
	DIALOGBASEPARAM dbp;

	m_hInstance = hInstance;

	dbp.pDialogBase = this;
	dbp.lParam = lParam;

	m_hDlg = CreateDialogParam(hInstance, MAKEINTRESOURCE(m_nID), hwndOwner, (DLGPROC)StaticDlgProc, (LPARAM)&dbp);

	if (m_hDlg == NULL)
		return NULL;

	if (bShow)
		ShowWindow(m_hDlg, SW_SHOW);

	return m_hDlg;
}
