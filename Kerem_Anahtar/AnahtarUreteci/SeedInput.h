#pragma once

#include "DialogBase.h"
#include "KeyGenerator.h"
#include <vector>

typedef struct _kg_RunParam2
{
	HINSTANCE			hInstance;
	HWND				hDlg;
	int					outputSize;
	int					outputCount;
	int					initialMethod;
	int					generationMethod;
	double				linComplexity;
	string				shaSeed;
} KG_RUNPARAM2;

class SeedInput : public CDialogBase
{
	public:
		SeedInput();
		virtual ~SeedInput();

	protected:
		virtual LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
		LRESULT OnInitDialog(WPARAM, LPARAM);
		LRESULT OnAbort();
		
		KG_RUNPARAM2	*m_prp;
		HANDLE		m_hThread;
};