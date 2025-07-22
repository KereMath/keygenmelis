#include "stdafx.h"
#include "NEDDlg.h"
#include "resource.h"
#include <commctrl.h>
#include <CommDlg.h>
#include <math.h>
#include "KeyGenerator.h"
#include <windows.h> // Masaüstü ve klasör işlemleri için


CNEDDlg::CNEDDlg()
{
	m_nID = KG_KEYGENERATION;
}

CNEDDlg::~CNEDDlg()
{
}

LRESULT CALLBACK CNEDDlg::DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_INITDIALOG:
			return OnInitDialog(wParam, lParam);

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case KG_RUN:
					OnRun();
					break;
			}
			break;
	}

	return 0;
}

LRESULT CNEDDlg::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	SendDlgItemMessage(m_hDlg, KG_GENERATION, CB_ADDSTRING, NULL, (LPARAM)(L"SHA256"));
	SendDlgItemMessage(m_hDlg, KG_GENERATION, CB_ADDSTRING, NULL, (LPARAM)(L"RANDOM"));
	SendDlgItemMessage(m_hDlg, KG_GENERATION, CB_SETCURSEL, 0, NULL);

	SendDlgItemMessage(m_hDlg, KG_GENERATOR, CB_ADDSTRING, NULL, (LPARAM)(L"Shrinking"));
	SendDlgItemMessage(m_hDlg, KG_GENERATOR, CB_ADDSTRING, NULL, (LPARAM)(L"Alternating"));
	SendDlgItemMessage(m_hDlg, KG_GENERATOR, CB_ADDSTRING, NULL, (LPARAM)(L"AES"));
	SendDlgItemMessage(m_hDlg, KG_GENERATOR, CB_SETCURSEL, 0, NULL);

	SendDlgItemMessage(m_hDlg, KG_LENGTH, CB_ADDSTRING, NULL, (LPARAM)(L"128"));
	SendDlgItemMessage(m_hDlg, KG_LENGTH, CB_ADDSTRING, NULL, (LPARAM)(L"256"));
	SendDlgItemMessage(m_hDlg, KG_LENGTH, CB_ADDSTRING, NULL, (LPARAM)(L"512"));
	SendDlgItemMessage(m_hDlg, KG_LENGTH, CB_ADDSTRING, NULL, (LPARAM)(L"1024"));
	SendDlgItemMessage(m_hDlg, KG_LENGTH, CB_ADDSTRING, NULL, (LPARAM)(L"2048"));
	SendDlgItemMessage(m_hDlg, KG_LENGTH, CB_ADDSTRING, NULL, (LPARAM)(L"4096"));
	SendDlgItemMessage(m_hDlg, KG_LENGTH, CB_SETCURSEL, 0, NULL);

	SendDlgItemMessage(m_hDlg, KG_LINCOMP, CB_ADDSTRING, NULL, (LPARAM)(L"0.01"));
	SendDlgItemMessage(m_hDlg, KG_LINCOMP, CB_ADDSTRING, NULL, (LPARAM)(L"0.05"));
	SendDlgItemMessage(m_hDlg, KG_LINCOMP, CB_SETCURSEL, 0, NULL);

	SetDlgItemInt(m_hDlg, KG_COUNT, 1, FALSE);
	SetDlgItemText(m_hDlg, KG_SEED, L"keygeneration");

	return 0;
}


LRESULT CNEDDlg::OnRun()
{
	int output[] = { 128, 256, 512, 1024, 2048, 4096 };
	KG_RUNPARAM2 *prp = new KG_RUNPARAM2;

	prp->hInstance = m_hInstance;
	prp->hDlg = m_hDlg;
	prp->outputSize =  output[SendDlgItemMessage(m_hDlg, KG_LENGTH, CB_GETCURSEL, 0, NULL)];
	prp->outputCount = GetDlgItemInt(m_hDlg, KG_COUNT, NULL, FALSE)+1;
	prp->initialMethod = SendDlgItemMessage(m_hDlg, KG_GENERATION, CB_GETCURSEL, 0, 0);
	prp->generationMethod = SendDlgItemMessage(m_hDlg, KG_GENERATOR, CB_GETCURSEL, 0, 0);
	int linComplexityHelper = SendDlgItemMessage(m_hDlg, KG_LINCOMP, CB_GETCURSEL, 0, NULL);
	
	prp->shaSeed = GetDlgItemText(m_hDlg, KG_SEED, NULL, FALSE);

	if (linComplexityHelper == 0)
		prp->linComplexity = 0.01;
	else if (linComplexityHelper == 1)
		prp->linComplexity = 0.05;

	EnableWindow(GetDlgItem(m_hDlg, KG_RUN), FALSE);

	DWORD dwTID;
	m_hNEThread = CreateThread(NULL, NULL, KGThread, (LPVOID)prp, NULL, &dwTID);

	return 0;
}


DWORD WINAPI KGThread(LPVOID lpParam)
{	
	auto start_time = std::chrono::high_resolution_clock::now();

	KGFunctions KeyGeneration_helper[] =
	{
		blk_test_fn__frequency_helper,
		blk_test_fn__run_count_helper,
		blk_test_fn__run_L1_helper,
		blk_test_fn__template_match_4_1_helper,
		blk_test_fn__template_match_4_2_helper,
		blk_test_fn__template_match_4_3_helper,
		blk_test_fn__template_match_4_4_helper,
		blk_test_fn__linear_complexity_helper,
		blk_test_fn__blind_spot_complexity_helper
	};

	KG_RUNPARAM2 *prp = (KG_RUNPARAM2*)lpParam;

	int uOldPercentage = -1, uPercentage, numlength;
	wchar_t szBuffer[1024];
	char szBufferTemp[1024];

	vector<bool> result1;
	vector<bool> result2;
	vector<vector<bool> > outputs;

	string name, type;
	int total_attempts = 0; // Toplam deneme sayısını tutacak bir sayaç
	vector<bool> acceptanceLog; // New vector to track each test's acceptance status

	for (int i = 0; i < (prp->outputCount);) {
		bool accepted = true;
        total_attempts++; 

		// for (int j = 0; j < 9; j++){
		// 	accepted = accepted && KeyGeneration_helper[j](result2, prp->linComplexity, prp->outputSize);
		// 	acceptanceLog.push_back(accepted); // Store the acceptance result (true/false) for this attempt
		// 	}

		if (accepted) {
			outputs.push_back(result2);
			i++;
			uPercentage = (i * 100) / (prp->outputCount);
			wsprintf(szBuffer, L" %d%%", uPercentage);
			SendDlgItemMessage(prp->hDlg, KG_PROGRESS, PBM_SETPOS, uPercentage, 0);

			wsprintf(szBuffer, L" %d%%", uPercentage);
			SetDlgItemText(prp->hDlg, KG_PERCENTAGE, szBuffer);
		}

		if (prp->initialMethod == 1) {
			type = "sha256";
			prp->shaSeed = convert2bin(result2);
			result1 = GenerateSHA256(prp->shaSeed);
		}
		else {
			type = "randomized";
			result1 = urandomized();
		}

		if ((prp->generationMethod) == 0) {
			result2 = aes(result1, prp->outputSize);
			name = "aes";
		}
		else if ((prp->generationMethod) == 1) {
			result2 = alternating(result1, prp->outputSize);
			name = "alternating";
		}
		else if ((prp->generationMethod) == 2) {
			result2 = shrinking(result1, prp->outputSize);
			name = "shrinking";
		}

		

		
	}

	char bufferr[100];
	sprintf(bufferr, "%s-%s-%d.txt", name, type, prp->outputSize);

	ofstream filee;
	filee.open(bufferr);
	for (int i = 0; i < outputs.size(); i++)
		filee << outputs[i] << endl;

	auto end_time = std::chrono::high_resolution_clock::now();
	auto total_time = end_time - start_time;
	
	wchar_t buffer[256];
	wsprintfW(buffer, L"Toplam sure: %d ms", total_time / std::chrono::milliseconds(1));
	MessageBox(prp->hDlg, buffer, L"Bitti", MB_ICONEXCLAMATION);
	EnableWindow(GetDlgItem(prp->hDlg, KG_RUN), TRUE);
	
	uPercentage = 0;
	wsprintf(szBuffer, L" %d%%", uPercentage);
	SendDlgItemMessage(prp->hDlg, KG_PROGRESS, PBM_SETPOS, uPercentage, 0);

	wsprintf(szBuffer, L" %d%%", uPercentage);
	SetDlgItemText(prp->hDlg, KG_PERCENTAGE, szBuffer);
wchar_t buffer2[256];  // Yeni bir isimle değiştirildi
wsprintfW(buffer2, L"Toplam deneme: %d", total_attempts-1);
MessageBox(prp->hDlg, buffer2, L"Deneme Sayisi", MB_ICONEXCLAMATION);

	filee.close();
ofstream logFile;
logFile.open("log.txt", ios::out | ios::trunc); // Create log.txt and clear its contents
if (!logFile.is_open()) {
    MessageBox(NULL, L"Log dosyası açılamadı!", L"Hata", MB_ICONERROR);
    return 0;
}
// const char* testNames[] = {
//     // "blk_test_fn__frequency_helper",
//     // "blk_test_fn__run_count_helper",
//     // "blk_test_fn__run_L1_helper",
//     // "blk_test_fn__template_match_4_1_helper",
//     // "blk_test_fn__template_match_4_2_helper",
//     // "blk_test_fn__template_match_4_3_helper",
//     // "blk_test_fn__template_match_4_4_helper",
//     // "blk_test_fn__linear_complexity_helper",
//     // "blk_test_fn__blind_spot_complexity_helper"
// };
logFile << "Acceptance Log for Each Attempt (1=Accepted, 0=Rejected):" << endl;
     size_t total_tests = acceptanceLog.size();
    size_t tests_per_attempt = 0; // Her deneme 9 testten oluşuyor

    // Her deneme için
    // for (size_t k = 1; k < total_tests / tests_per_attempt; k++) {
    //     // Bu deneme için başlangıç ve bitiş indisi
    //     size_t start_index = k * tests_per_attempt;
    //     size_t end_index = start_index + tests_per_attempt;

    //     // O denemedeki ilk yanlış testi bul
    //     bool found_first_error = false;
    //     for (size_t i = start_index; i < end_index; i++) {
    //         if (acceptanceLog[i] == 0) {
    //             int l = (i % tests_per_attempt); // Testin sırasını bul (0-8 arası)
    //             const char* testName = testNames[l]; // Hatalı testin adını al
    //             logFile << (k + 1) << ". denemede " << testName << " yanlis" << endl;
    //             found_first_error = true;
    //             break; // İlk yanlış testi bulduk, bir sonraki denemeye geç
    //         }
    //     }
    // }

logFile.close();
ifstream logReadFile("log.txt");
if (!logReadFile.is_open()) {
    MessageBox(NULL, L"Log dosyası okunamadı!", L"Hata", MB_ICONERROR);
    return 0;
}

std::wstring logContent;
std::string line;

// Tüm satırları oku ve birleştir
while (getline(logReadFile, line)) {
    logContent += std::wstring(line.begin(), line.end()) + L"\n";
}

logReadFile.close();

// Log içeriğini MessageBox'ta göster
MessageBox(prp->hDlg, logContent.c_str(), L"Log İçeriği", MB_ICONINFORMATION);

	return 0;
}













/*
LRESULT CNEDDlg::OnRun()
{
	int output[] = { 128, 256, 512, 1024, 2048, 3072, 4096 };
	KG_RUNPARAM *prp = new KG_RUNPARAM;
	prp->parameters = new KG_RUNPARAM2;

	prp->parameters->hInstance = m_hInstance;
	prp->parameters->hDlg = m_hDlg;
	prp->parameters->outputSize = output[SendDlgItemMessage(m_hDlg, KG_LENGTH, CB_GETCURSEL, 0, NULL)];
	prp->parameters->outputCount = GetDlgItemInt(m_hDlg, KG_COUNT, NULL, FALSE);
	prp->parameters->initialMethod = SendDlgItemMessage(m_hDlg, KG_GENERATION, CB_GETCURSEL, 0, 0);
	prp->parameters->generationMethod = SendDlgItemMessage(m_hDlg, KG_GENERATOR, CB_GETCURSEL, 0, 0);
	int linComplexityHelper = SendDlgItemMessage(m_hDlg, KG_LINCOMP, CB_GETCURSEL, 0, NULL);

	prp->parameters->shaSeed = (wchar_t*)malloc(sizeof(wchar_t) * 128);

	if (linComplexityHelper == 0)
		prp->parameters->linComplexity = 0.01;
	else if (linComplexityHelper == 1)
		prp->parameters->linComplexity = 0.05;

	EnableWindow(GetDlgItem(m_hDlg, KG_RUN), FALSE);

	DWORD dwTID;
	m_hNEThread = CreateThread(NULL, NULL, KGThread, (LPVOID)prp, NULL, &dwTID);

	return 0;
}


DWORD WINAPI KGThread(LPVOID lpParam)
{
	auto start_time = std::chrono::high_resolution_clock::now();

	KGFunctions KeyGeneration_helper[] =
	{
		blk_test_fn__frequency_helper,
		blk_test_fn__run_count_helper,
		blk_test_fn__run_L1_helper,
		blk_test_fn__template_match_4_1_helper,
		blk_test_fn__template_match_4_2_helper,
		blk_test_fn__template_match_4_3_helper,
		blk_test_fn__template_match_4_4_helper,
		blk_test_fn__linear_complexity_helper,
		blk_test_fn__blind_spot_complexity_helper
	};

	KG_RUNPARAM *prp = (KG_RUNPARAM*)lpParam;

	int uOldPercentage = -1, uPercentage, numlength;
	wchar_t szBuffer[1024];
	char szBufferTemp[1024];

	vector<bool> result1;
	vector<bool> result2;
	vector<vector<bool> > outputs;

	string name, type;
	for (int i = 0; i < (prp->parameters->outputCount);) {
		bool accepted = true;

		if (prp->parameters->initialMethod == 1) {
			type = "sha256";
			// (prp->seedDlg).DoModal(prp->parameters->hInstance, prp->parameters->hDlg, (LPARAM)prp->parameters);
			// wstring ws(prp->parameters->shaSeed);
			// string inp(ws.begin(), ws.end());
			result1 = GenerateSHA256(inp);
		}
		else {
			type = "randomized";
			result1 = urandomized();
		}

		if ((prp->parameters->generationMethod) == 0) {
			result2 = aes(result1, prp->parameters->outputSize);
			name = "aes";
		}
		else if ((prp->parameters->generationMethod) == 1) {
			result2 = alternating(result1, prp->parameters->outputSize);
			name = "alternating";
		}
		else if ((prp->parameters->generationMethod) == 2) {
			result2 = shrinking(result1, prp->parameters->outputSize);
			name = "shrinking";
		}

		for (int j = 0; j < 9; j++)
			accepted = accepted && KeyGeneration_helper[j](result2, prp->parameters->linComplexity, prp->parameters->outputSize);

		if (accepted) {
			outputs.push_back(result2);
			i++;
			uPercentage = (i * 100) / (prp->parameters->outputCount);
			wsprintf(szBuffer, L" %d%%", uPercentage);
			SendDlgItemMessage(prp->parameters->hDlg, KG_PROGRESS, PBM_SETPOS, uPercentage, 0);

			wsprintf(szBuffer, L" %d%%", uPercentage);
			SetDlgItemText(prp->parameters->hDlg, KG_PERCENTAGE, szBuffer);
		}
	}

	char bufferr[100];
	sprintf(bufferr, "%s-%s-%d.txt", name, type, prp->parameters->outputSize);

	ofstream filee;
	filee.open(bufferr);
	for (int i = 0; i < outputs.size(); i++)
		filee << outputs[i] << endl;

	auto end_time = std::chrono::high_resolution_clock::now();
	auto total_time = end_time - start_time;

	wchar_t buffer[256];
	wsprintfW(buffer, L"Toplam s�re: %d ms", total_time / std::chrono::milliseconds(1));
	MessageBox(prp->parameters->hDlg, buffer, L"Bitti", MB_ICONEXCLAMATION);
	EnableWindow(GetDlgItem(prp->parameters->hDlg, KG_RUN), TRUE);

	uPercentage = 0;
	wsprintf(szBuffer, L" %d%%", uPercentage);
	SendDlgItemMessage(prp->parameters->hDlg, KG_PROGRESS, PBM_SETPOS, uPercentage, 0);

	wsprintf(szBuffer, L" %d%%", uPercentage);
	SetDlgItemText(prp->parameters->hDlg, KG_PERCENTAGE, szBuffer);

	filee.close();
	return 0;
}
*/


