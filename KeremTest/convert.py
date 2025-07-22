import os
import pandas as pd

def convert_csv_to_excel(folder_path):
    # Klasördeki tüm dosyaları listele
    files = os.listdir(folder_path)
    csv_files = [file for file in files if file.endswith('.csv')]

    if not csv_files:
        print("Klasörde CSV dosyası bulunamadı.")
        return

    for csv_file in csv_files:
        csv_path = os.path.join(folder_path, csv_file)
        excel_path = os.path.join(folder_path, csv_file.replace('.csv', '.xlsx'))
        
        try:
            # CSV dosyasını oku
            df = pd.read_csv(csv_path)
            # Excel olarak kaydet
            df.to_excel(excel_path, index=False, engine='openpyxl')
            print(f"'{csv_file}' başarıyla '{excel_path}' olarak kaydedildi.")
        except Exception as e:
            print(f"Hata: '{csv_file}' dönüştürülemedi. Hata: {e}")

if __name__ == "__main__":
    folder_path = r"C:\Users\J.A.R.V.I.S\Desktop\KEYS"  # KEYS klasör yolu
    if os.path.exists(folder_path):
        convert_csv_to_excel(folder_path)
    else:
        print(f"Klasör yolu bulunamadı: {folder_path}")
