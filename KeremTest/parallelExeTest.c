#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>

#define KEYS_FOLDER "C:\\Users\\J.A.R.V.I.S\\Desktop\\KEYS"
#define TESTER_EXECUTABLE "tester.exe"

// Thread parametreleri için yapı
typedef struct {
    char txt_file_path[MAX_PATH];
    double complexity;
} ThreadData;

// Thread fonksiyonu
DWORD WINAPI run_tester(LPVOID param) {
    ThreadData *data = (ThreadData *)param;

    char command[512];
    snprintf(command, sizeof(command), "%s \"%s\" %.2f", TESTER_EXECUTABLE, data->txt_file_path, data->complexity);

    printf("Executing: %s\n", command);

    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Error: Failed to execute %s with complexity %.2f\n", data->txt_file_path, data->complexity);
    }

    free(data); // ThreadData yapısını serbest bırak
    return 0;
}

int main() {
    DIR *dir;
    struct dirent *entry;
    HANDLE threads[256]; // Maksimum 256 thread
    int thread_count = 0;

    // KEYS klasörünü aç
    dir = opendir(KEYS_FOLDER);
    if (!dir) {
        perror("Failed to open KEYS folder");
        return 1;
    }

    // Linear complexity değerleri
    double linear_complexities[] = {0.01, 0.05};
    size_t complexity_count = sizeof(linear_complexities) / sizeof(linear_complexities[0]);

    // Klasördeki tüm dosyaları oku
    while ((entry = readdir(dir)) != NULL) {
        // Sadece .txt dosyalarını işle
        if (strstr(entry->d_name, ".txt")) {
            char txt_file_path[MAX_PATH];
            snprintf(txt_file_path, sizeof(txt_file_path), "%s\\%s", KEYS_FOLDER, entry->d_name);

            // Her linear complexity için bir thread oluştur
            for (size_t i = 0; i < complexity_count; i++) {
                ThreadData *data = malloc(sizeof(ThreadData));
                if (!data) {
                    fprintf(stderr, "Failed to allocate memory for thread data\n");
                    continue;
                }

                strncpy(data->txt_file_path, txt_file_path, MAX_PATH);
                data->complexity = linear_complexities[i];

                threads[thread_count] = CreateThread(
                    NULL,          // Default security attributes
                    0,             // Default stack size
                    run_tester,    // Thread function
                    data,          // Thread parameters
                    0,             // Default creation flags
                    NULL           // Thread ID
                );

                if (!threads[thread_count]) {
                    fprintf(stderr, "Failed to create thread for %s\n", txt_file_path);
                    free(data);
                } else {
                    thread_count++;
                }
            }
        }
    }

    closedir(dir);

    // Tüm thread'lerin tamamlanmasını bekle
    for (int i = 0; i < thread_count; i++) {
        WaitForSingleObject(threads[i], INFINITE);
        CloseHandle(threads[i]);
    }

    printf("All tasks completed.\n");
    return 0;
}
