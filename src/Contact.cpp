#include "Contact.h"
#include <iostream>

void print_kontak(const contact& c) {
    std::cout << "Nama   : " << c.nama << '\n';
    std::cout << "No Tlp : " << c.no_tlp << '\n';
    std::cout << "Alamat : " << c.alamat << '\n';
}