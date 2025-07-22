#pragma once

class CDialogBase;

typedef struct _tagDialogBaseParam
{
	CDialogBase	*pDialogBase;
	LPARAM		lParam;
} DIALOGBASEPARAM, *LPDIALOGBASEPARAM;

class CDialogBase
{
public:
	CDialogBase();
	virtual ~CDialogBase();

	HWND GetHWND() const { return m_hDlg; }

	INT_PTR	DoModal(HINSTANCE, HWND hwndOwner, LPARAM lpParam = NULL);

	INT_PTR	DoModal2(HINSTANCE, HWND hwndOwner, LPARAM lpParam = NULL, LPARAM lpParam2 = NULL);

	HWND	Create(HINSTANCE, HWND hwndOwner, BOOL bShow = TRUE, LPARAM lParam = NULL);

	static LRESULT CALLBACK StaticDlgProc(HWND, UINT, WPARAM, LPARAM);

	void SetHInstance(HINSTANCE hInstance) { m_hInstance = hInstance; }

protected:

	int			m_nID;
	HWND		m_hDlg;
	HINSTANCE	m_hInstance;


	virtual LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
};
