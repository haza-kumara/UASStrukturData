#ifndef CONTACT_H
#define CONTACT_H

#include <string>

// ==============================================================
// Struct Contact
// Menyimpan satu data kontak. Menggunakan struct (bukan class)
// sesuai paradigma pemrograman prosedural.
// ==============================================================
struct Contact {
    int         id;      // ID unik, digenerate otomatis
    std::string nama;
    std::string no_tlp;
    std::string email;
    std::string alamat;
};

// ==============================================================
// Deklarasi fungsi utilitas kontak
// ==============================================================

// Menampilkan satu kontak ke layar secara detail
void printKontak(const Contact& c);

// Validasi nomor HP: hanya boleh angka, '-', '+', dan spasi
bool validatePhone(const std::string& phone);

// Validasi email: minimal harus mengandung karakter '@'
bool validateEmail(const std::string& email);

#endif
