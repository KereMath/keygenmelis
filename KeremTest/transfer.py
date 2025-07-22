import os
import shutil

def copy_xlsx_files():
    # KEYS ve hedef klasör yolları
    keys_folder = r"C:\Users\J.A.R.V.I.S\Desktop\KEYS"
    target_folder = r"C:\Users\J.A.R.V.I.S\Desktop\testExcel"

    # Hedef klasörün mevcut olup olmadığını kontrol et, yoksa oluştur
    if not os.path.exists(target_folder):
        os.makedirs(target_folder)

    # KEYS klasöründeki tüm dosyaları al
    files = os.listdir(keys_folder)

    # .xlsx dosyalarını filtrele ve kopyala
    for file in files:
        if file.endswith('.xlsx'):
            source_path = os.path.join(keys_folder, file)
            target_path = os.path.join(target_folder, file)

            try:
                shutil.copy(source_path, target_path)
                print(f"'{file}' başarıyla '{target_folder}' klasörüne kopyalandı.")
            except Exception as e:
                print(f"'{file}' kopyalanırken bir hata oluştu: {e}")

if __name__ == "__main__":
    copy_xlsx_files()
