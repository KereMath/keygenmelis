import os

folder_path = r"C:\Users\J.A.R.V.I.S\Desktop\KEYS"

def remove_first_empty_line_from_files(folder_path):
    try:
        # Belirtilen klasördeki tüm .txt dosyalarını bul
        txt_files = [f for f in os.listdir(folder_path) if f.endswith('.txt')]

        for txt_file in txt_files:
            file_path = os.path.join(folder_path, txt_file)

            # Dosyayı okuyup satırları liste olarak al
            with open(file_path, 'r', encoding='utf-8') as file:
                lines = file.readlines()

            # İlk boş satırı bul ve kaldır
            for i, line in enumerate(lines):
                if line.strip() == "":
                    del lines[i]
                    break

            # Dosyayı yeniden yaz
            with open(file_path, 'w', encoding='utf-8') as file:
                file.writelines(lines)

            print(f"{txt_file}: İlk boş satır başarıyla silindi.")

    except FileNotFoundError:
        print(f"Klasör bulunamadı: {folder_path}")
    except Exception as e:
        print(f"Bir hata oluştu: {e}")

# Fonksiyonu çalıştır
remove_first_empty_line_from_files(folder_path)