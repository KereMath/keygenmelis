#pragma once

#include "DialogBase.h"
#include "TabControlHelper.h"
#include "NEDDlg.h"


class CMainDlg : public CDialogBase
{
public:
	CMainDlg();
	virtual ~CMainDlg();

protected:

	virtual LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

	static LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

	LRESULT OnInitDialog(WPARAM, LPARAM);
	LRESULT OnOK();

	TABCONTROLHELPER m_tch;
	CNEDDlg	neddlg;
};
