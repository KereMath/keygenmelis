#include "stdafx.h"
#include "SeedInput.h"
#include "resource.h"
#include <string>

SeedInput::SeedInput()
{
	m_nID = KG_SEED_INPUT;
}

SeedInput::~SeedInput()
{
}

LRESULT CALLBACK SeedInput::DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		return OnInitDialog(wParam, lParam);

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case KG_SEED_OK:
				OnAbort();
				break;
		}
		break;
	}

	return 0;
}



LRESULT SeedInput::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	DIALOGBASEPARAM *dbp = (DIALOGBASEPARAM*)lParam;

	m_prp = (KG_RUNPARAM2*)dbp->lParam;
	return 0;
}




LRESULT SeedInput::OnAbort()
{
	/*
	GetDlgItemText(m_hDlg, KG_YENI_SEED, m_prp->shaSeed, 128);
	EndDialog(m_hDlg, 0);
	*/

	return 0;
}