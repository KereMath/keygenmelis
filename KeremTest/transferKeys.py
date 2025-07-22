import os
import shutil

def copy_specific_txt_files():
    # Kaynak ve hedef klasör yolları
    source_folder = r"C:\Users\J.A.R.V.I.S\Desktop\Kerem_Anahtar\x64\Release"
    target_folder = r"C:\Users\J.A.R.V.I.S\Desktop\KEYS"

    # Hedef klasörü temizle
    if os.path.exists(target_folder):
        for file in os.listdir(target_folder):
            file_path = os.path.join(target_folder, file)
            try:
                if os.path.isfile(file_path):
                    os.unlink(file_path)
                    print(f"'{file}' silindi.")
                elif os.path.isdir(file_path):
                    shutil.rmtree(file_path)
            except Exception as e:
                print(f"Hata: '{file}' silinemedi. {e}")
    else:
        os.makedirs(target_folder)

    # Kaynak klasöründeki dosyaları al
    files = os.listdir(source_folder)

    # Belirtilen dosyaları filtrele ve kopyala
    for file in files:
        if file.endswith(('128.txt', '256.txt', '512.txt', '1024.txt', '2048.txt', '4096.txt')):
            source_path = os.path.join(source_folder, file)
            target_path = os.path.join(target_folder, file)

            try:
                shutil.copy(source_path, target_path)
                print(f"'{file}' başarıyla '{target_folder}' klasörüne kopyalandı.")
            except Exception as e:
                print(f"'{file}' kopyalanırken bir hata oluştu: {e}")

if __name__ == "__main__":
    copy_specific_txt_files()
