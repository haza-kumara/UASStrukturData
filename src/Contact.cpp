#include "Contact.h"

#include <iostream>
#include <cctype>    // std::isdigit

void printKontak(const Contact& c) {
    std::cout << "  ID     : " << c.id     << "\n";
    std::cout << "  Nama   : " << c.nama   << "\n";
    std::cout << "  No. HP : " << c.no_tlp << "\n";
    std::cout << "  Email  : " << c.email  << "\n";
    std::cout << "  Alamat : " << c.alamat << "\n";
}


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

bool validateEmail(const std::string& email) {
    if (email.empty()) return false;
    size_t atPos = email.find('@');
    // '@' harus ada, tidak di awal, dan tidak di akhir
    return (atPos != std::string::npos &&
            atPos > 0 &&
            atPos < email.size() - 1);
}