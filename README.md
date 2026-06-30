# Contact Manager CLI — UAS Struktur Data

Aplikasi **Contact Manager CLI** adalah proyek sistem manajemen kontak berbasis terminal (Command Line Interface) yang dibangun menggunakan bahasa pemrograman C++17 dan CMake. Proyek ini dibuat untuk memenuhi tugas akhir/ujian akhir semester (UAS) mata kuliah **Struktur Data**, dengan menerapkan konsep struktur data dinamis **Singly Linked List** secara manual.

---

## 🚀 Fitur Utama

Aplikasi ini menyediakan manajemen kontak yang lengkap (*Create, Read, Update, Delete*) serta dilengkapi dengan validasi data dan pengurutan:

1. **Tambah Kontak baru**:
   - Menghasilkan ID unik secara otomatis.
   - Validasi nama (tidak boleh kosong).
   - Validasi format nomor telepon (hanya menerima angka, spasi, tanda `-`, dan `+`).
   - Validasi format email sederhana (wajib memiliki karakter `@`).
2. **Lihat Semua Kontak**:
   - Menampilkan data dalam format tabel yang rapi di terminal.
3. **Cari Kontak**:
   - Pencarian berdasarkan **ID** (pencarian instan).
   - Pencarian berdasarkan **Nama** (*exact match, case-sensitive*).
4. **Edit Detail Kontak**:
   - Mengubah nama, nomor telepon, email, atau alamat kontak yang sudah terdaftar berdasarkan ID.
5. **Hapus Kontak**:
   - Menghapus kontak tertentu berdasarkan ID dengan fitur konfirmasi (`y/n`) terlebih dahulu untuk mencegah penghapusan yang tidak sengaja.
6. **Urutkan Kontak**:
   - Mengurutkan kontak secara alfabetis dari **A-Z** atau **Z-A** berdasarkan nama menggunakan algoritma **Bubble Sort**.
   - *Catatan: Proses pengurutan ini dilakukan pada buffer visual sehingga tidak mengubah urutan asli pada struktur data Linked List utama.*

---

## 📁 Struktur Proyek

Proyek ini terorganisasi dengan struktur modular sebagai berikut:

```text
UASStrukturData/
│
├── CMakeLists.txt         # Konfigurasi CMake untuk mem-build proyek
├── main.cpp               # Alur utama program CLI (Menu, Input, Loop Utama)
├── README.md              # Dokumentasi proyek
│
├── include/               # Header Files (.h)
│   ├── Contact.h          # Struktur data Contact dan fungsi utilitas/validasi
│   └── LinkedList.h       # Definisi struktur Node dan operasi dasar Linked List
│
└── src/                   # Source Files (.cpp)
    ├── Contact.cpp        # Implementasi fungsi utilitas & validasi input kontak
    └── LinkedList.cpp     # Implementasi logika operasi Singly Linked List
```

---

## 🛠️ Persyaratan Sistem & Kompilasi

Untuk membangun dan menjalankan proyek ini, pastikan sistem Anda telah terpasang:
- **C++ Compiler** (GCC / MinGW dengan dukungan C++17, MSVC, atau Clang)
- **CMake** versi 3.16 atau yang lebih baru

### Cara Build & Run (Terminal / Command Prompt)

1. **Kloning atau Unduh Repositori** ke komputer Anda.
2. Buka terminal di dalam direktori proyek, lalu jalankan perintah-perintah berikut:

```bash
# 1. Buat direktori build dan masuk ke dalamnya
mkdir build
cd build

# 2. Generate file konfigurasi build menggunakan CMake
cmake ..

# 3. Compile/Build program
cmake --build . --config Release
```

3. **Menjalankan Program**:
   - **Windows**: Jalankan executable yang terbentuk di folder `build` atau `build/Release`:
     ```cmd
     .\Release\contact_manager.exe
     ```
   - **Linux / macOS**: Jalankan binary hasil kompilasi:
     ```bash
     ./contact_manager
     ```

---

## 💻 Contoh Penggunaan Program

Saat aplikasi dijalankan, Anda akan disajikan menu utama sebagai berikut:

```text
  ==============================
        CONTACT MANAGER
  ==============================
  1. Tambah Kontak
  2. Lihat Semua Kontak
  3. Cari Kontak
  4. Edit Kontak
  5. Hapus Kontak
  6. Urutkan Kontak
  7. Keluar
  ==============================
  Pilih menu [1-7]: 
```

---

## 🧠 Konsep Struktur Data yang Diterapkan

- **Singly Linked List**: Digunakan untuk menyimpan daftar kontak secara dinamis di dalam memori tanpa alokasi ukuran tetap di awal. Setiap elemen disimpan sebagai `Node` yang memiliki pointer `next` yang menunjuk ke `Node` berikutnya.
- **Dynamic Memory Allocation**: Penggunaan operator `new` dan `delete` pada C++ untuk mengalokasikan dan membebaskan memori kontak secara dinamis guna menghindari kebocoran memori (*memory leak*).
- **Bubble Sort**: Digunakan untuk mengurutkan salinan kontak demi kebutuhan visualisasi tampilan yang terurut tanpa mengganggu struktur link pointer data asli.