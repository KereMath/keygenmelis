#pragma once

#include "DialogBase.h"
#include "SeedInput.h"
#include <list>
#include <shellapi.h>
#include <chrono>
extern KGFunctions KeyGeneration_helper[9];

bool RunTestAndLog(int index, const std::vector<bool>& result2, double linComplexity, int outputSize, 
                   std::vector<bool>& acceptanceLog);
typedef struct _kg_RunParam
{
	KG_RUNPARAM2*		parameters;
	SeedInput			seedDlg;
} KG_RUNPARAM;

class CNEDDlg: public CDialogBase
{
	public:
		CNEDDlg();
		virtual ~CNEDDlg();

	protected:
		virtual LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
		
		LRESULT OnInitDialog(WPARAM, LPARAM);
		LRESULT OnRun();
		LRESULT OnSourceChange();
		
		HANDLE	m_hNEThread;
		// SeedInput m_SeedDlg;
};

DWORD WINAPI KGThread(LPVOID lpParam);