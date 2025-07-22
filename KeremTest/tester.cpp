#include "statFunc.h"
#include "KeyGenerator.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

// Test fonksiyonları dizisi
typedef bool (*TestFunction)(const vector<bool>, const double, const int);

TestFunction tests[] = {
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

const char* testNames[] = {
    "Frequency Test",
    "Run Count Test",
    "Run L1 Test",
    "Template Match 4-1 Test",
    "Template Match 4-2 Test",
    "Template Match 4-3 Test",
    "Template Match 4-4 Test",
    "Linear Complexity Test",
    "Blind Spot Complexity Test"
};

// Dosya adından bit boyutunu çıkarır
int extractBitSize(const string &filePath) {
    regex pattern(R"((\d+)(?=\.txt$))");
    smatch match;

    if (regex_search(filePath, match, pattern)) {
        return stoi(match[1]);
    }

    cerr << "Dosya adında bit boyutu bulunamadı: " << filePath << endl;
    return -1;
}

// Dosyadan bit boyutuna uygun satırları okur
vector<vector<bool>> readFile(const string &filePath, int bitSize) {
    ifstream file(filePath);
    vector<vector<bool>> data;

    if (!file.is_open()) {
        cerr << "Dosya açılamadı: " << filePath << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        if (line.length() != bitSize) {
            cerr << "Satır boyutu beklenenden farklı: " << line.length() << " (beklenen: " << bitSize << ")" << endl;
            continue;
        }
        vector<bool> bitVector;
        for (char c : line) {
            if (c == '0') bitVector.push_back(false);
            else if (c == '1') bitVector.push_back(true);
            else {
                cerr << "Geçersiz karakter bulundu: " << c << endl;
                bitVector.clear();
                break;
            }
        }
        if (!bitVector.empty()) data.push_back(bitVector);
    }

    file.close();
    return data;
}

// CSV formatında sonuçları kaydeder
void saveToCsv(const string &outputFilePath, const vector<vector<string>> &results) {
    ofstream outFile(outputFilePath);

    if (!outFile.is_open()) {
        cerr << "Sonuç dosyası oluşturulamadı: " << outputFilePath << endl;
        return;
    }

    for (const auto &row : results) {
        for (size_t i = 0; i < row.size(); i++) {
            outFile << row[i];
            if (i < row.size() - 1) outFile << ",";
        }
        outFile << endl;
    }

    outFile.close();
}

// Test sonuçlarını işler
void processTests(const vector<vector<bool>> &data, int size, double linComplexity, const string &outputFilePath) {
    vector<vector<string>> results;
    vector<string> header = {"Index"};

    // Test adlarını sütun başlıklarına ekle
    for (const auto &testName : testNames) {
        header.push_back(testName);
    }
    results.push_back(header);

    // Her veri için sonuçları işle
    for (size_t i = 0; i < data.size(); i++) {
        vector<string> row = {to_string(i + 1)};

        for (int t = 0; t < sizeof(tests) / sizeof(TestFunction); t++) {
            bool result = tests[t](data[i], linComplexity, size);
            row.push_back(result ? "Passed" : "Failed");
        }

        results.push_back(row);
    }

    // Sonuçları CSV'ye kaydet
    saveToCsv(outputFilePath, results);

    cout << "Sonuçlar kaydedildi: " << outputFilePath << endl;
}

// Ana fonksiyon
int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Kullanım: " << argv[0] << " <dosya yolu> <linear complexity>" << endl;
        return 1;
    }

    string filePath = argv[1];
    double linComplexity = stod(argv[2]);

    // Dosya adından bit boyutunu ayıkla
    int bitSize = extractBitSize(filePath);
    if (bitSize == -1) {
        return 1;
    }

    cout << "Dosya okunuyor: " << filePath << endl;
    vector<vector<bool>> data = readFile(filePath, bitSize);

    if (data.empty()) {
        cerr << "Veri bulunamadı." << endl;
        return 1;
    }

    // Çıkış dosyası adı
    string outputFilePath = filePath.substr(0, filePath.find_last_of(".")) + 
                            "_LC" + to_string(linComplexity) + ".csv";

    cout << "Testler başlatılıyor..." << endl;
    processTests(data, bitSize, linComplexity, outputFilePath);

    return 0;
}
