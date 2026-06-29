#include "Contact.h"

#include <iostream>
#include <cctype>    // std::isdigit

// ==============================================================
// Menampilkan seluruh field satu kontak secara detail
// ==============================================================
void printKontak(const Contact& c) {
    std::cout << "  ID     : " << c.id     << "\n";
    std::cout << "  Nama   : " << c.nama   << "\n";
    std::cout << "  No. HP : " << c.no_tlp << "\n";
    std::cout << "  Email  : " << c.email  << "\n";
    std::cout << "  Alamat : " << c.alamat << "\n";
}

// ==============================================================
// Validasi nomor HP
// Aturan: tidak boleh kosong, hanya boleh mengandung digit,
//         tanda '-', '+', dan spasi.
// Contoh valid : "0812-3456-7890", "+62 812 345 6789"
// Contoh tidak : "abc", "08123x"
// ==============================================================
bool validatePhone(const std::string& phone) {
    if (phone.empty()) return false;
    for (char c : phone) {
        bool isDigit = std::isdigit(static_cast<unsigned char>(c));
        bool isAllowed = (c == '-' || c == '+' || c == ' ');
        if (!isDigit && !isAllowed) {
            return false;
        }
    }
    return true;
}

// ==============================================================
// Validasi email
// Aturan: tidak boleh kosong, harus mengandung '@',
//         dan '@' tidak boleh di posisi pertama atau terakhir.
// Contoh valid : "user@email.com", "a@b"
// Contoh tidak : "@email.com", "useremail.com", ""
// ==============================================================
bool validateEmail(const std::string& email) {
    if (email.empty()) return false;
    size_t atPos = email.find('@');
    // '@' harus ada, tidak di awal, dan tidak di akhir
    return (atPos != std::string::npos &&
            atPos > 0 &&
            atPos < email.size() - 1);
}