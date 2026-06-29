#ifndef CONTACT_H
#define CONTACT_H

#include <string>

struct Contact {
    int         id;     
    std::string nama;
    std::string no_tlp;
    std::string email;
    std::string alamat;
};

// Menampilkan satu kontak ke layar secara detail
void printKontak(const Contact& c);

// Validasi nomor HP: hanya boleh angka, '-', '+', dan spasi
bool validatePhone(const std::string& phone);

// Validasi email: minimal harus mengandung karakter '@'
bool validateEmail(const std::string& email);

#endif
