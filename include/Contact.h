#ifndef CONTACT_H
#define CONTACT_H

#include <string>

struct contact {
  std::string nama;
  std::string no_tlp;
  std::string alamat;
};

void print_kontak(const contact& c);






#endif

