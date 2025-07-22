import os
import subprocess

def run_tester_for_all_files():
    # KEYS klasör yolu
    keys_folder = r"C:\Users\J.A.R.V.I.S\Desktop\KEYS"
    tester_executable = r".\tester.exe"

    # Linear complexity değerleri
    linear_complexities = [0.01, 0.05]

    # KEYS klasöründeki tüm dosyaları al
    files = os.listdir(keys_folder)
    txt_files = [file for file in files if file.endswith('.txt')]

    if not txt_files:
        print("KEYS klasöründe işlem yapılacak .txt dosyası bulunamadı.")
        return

    for txt_file in txt_files:
        txt_path = os.path.join(keys_folder, txt_file)
        for complexity in linear_complexities:
            try:
                # tester.exe programını çalıştır
                print(f"Çalıştırılıyor: {tester_executable} \"{txt_path}\" {complexity}")
                subprocess.run([tester_executable, txt_path, str(complexity)], check=True)
            except subprocess.CalledProcessError as e:
                print(f"Hata oluştu: {txt_path} için linear complexity {complexity}. Hata: {e}")

if __name__ == "__main__":
    run_tester_for_all_files()
