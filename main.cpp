#include "Contact.h"
#include "LinkedList.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>

#ifdef _WIN32
    #define CLEAR_CMD "cls"
#else
    #define CLEAR_CMD "clear"
#endif

void clearScreen() {
    system(CLEAR_CMD);
}

void pause() {
    std::cout << "\n  Tekan Enter untuk melanjutkan...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

std::string inputString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int inputPilihan() {
    int pilihan;
    std::cin >> pilihan;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return pilihan;
}

void printHeader() {
    std::cout << "\n";
    std::cout << "  ==============================\n";
    std::cout << "        CONTACT MANAGER\n";
    std::cout << "  ==============================\n";
}

void showMenu() {
    printHeader();
    std::cout << "  1. Tambah Kontak\n";
    std::cout << "  2. Lihat Semua Kontak\n";
    std::cout << "  3. Cari Kontak\n";
    std::cout << "  4. Edit Kontak\n";
    std::cout << "  5. Hapus Kontak\n";
    std::cout << "  6. Urutkan Kontak\n";
    std::cout << "  7. Keluar\n";
    std::cout << "  ==============================\n";
    std::cout << "  Pilih menu [1-7]: ";
}

void printTableHeader() {
    const std::string garis(90, '-');
    std::cout << "  " << garis << "\n";
    std::cout << "  | "
              << std::left << std::setw(4)  << "ID"
              << " | " << std::setw(20) << "Nama"
              << " | " << std::setw(15) << "No. HP"
              << " | " << std::setw(25) << "Email"
              << " | " << "Alamat"
              << "\n";
    std::cout << "  " << garis << "\n";
}

void printTableRow(const Contact& c) {
    std::cout << "  | "
              << std::left << std::setw(4)  << c.id
              << " | " << std::setw(20) << c.nama
              << " | " << std::setw(15) << c.no_tlp
              << " | " << std::setw(25) << c.email
              << " | " << c.alamat
              << "\n";
}

void displayContacts(Node* head) {
    printHeader();
    std::cout << "  DAFTAR SEMUA KONTAK\n";

    int total = listCount(head);
    if (total == 0) {
        std::cout << "\n  [INFO] Belum ada kontak yang tersimpan.\n";
        return;
    }

    printTableHeader();
    Node* temp = head;
    while (temp != nullptr) {
        printTableRow(temp->data);
        temp = temp->next;
    }
    std::cout << "  " << std::string(90, '-') << "\n";
    std::cout << "  Total kontak: " << total << "\n";
}

int generateId(Node* head) {
    if (head == nullptr) return 1;
    int maxId = 0;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.id > maxId) maxId = temp->data.id;
        temp = temp->next;
    }
    return maxId + 1;
}

void addContact(Node*& head) {
    printHeader();
    std::cout << "  TAMBAH KONTAK BARU\n";
    std::cout << "  " << std::string(30, '-') << "\n\n";

    Contact c;
    c.id = generateId(head);

    do {
        c.nama = inputString("  Nama       : ");
        if (c.nama.empty()) {
            std::cout << "  [ERROR] Nama tidak boleh kosong. Coba lagi.\n";
        }
    } while (c.nama.empty());

    do {
        c.no_tlp = inputString("  No. HP     : ");
        if (!validatePhone(c.no_tlp)) {
            std::cout << "  [ERROR] Nomor HP tidak valid.\n";
            std::cout << "          (hanya angka, tanda '-', '+', dan spasi)\n";
        }
    } while (!validatePhone(c.no_tlp));

    do {
        c.email = inputString("  Email      : ");
        if (!validateEmail(c.email)) {
            std::cout << "  [ERROR] Format email tidak valid.\n";
            std::cout << "          (harus mengandung karakter '@')\n";
        }
    } while (!validateEmail(c.email));

    c.alamat = inputString("  Alamat     : ");

    listInsert(head, c);
    std::cout << "\n  [OK] Kontak \"" << c.nama
              << "\" berhasil ditambahkan (ID: " << c.id << ").\n";
}

void searchContact(Node* head) {
    printHeader();
    std::cout << "  CARI KONTAK\n";
    std::cout << "  " << std::string(30, '-') << "\n\n";

    if (listCount(head) == 0) {
        std::cout << "  [INFO] Belum ada kontak yang tersimpan.\n";
        return;
    }

    std::cout << "  Cari berdasarkan:\n";
    std::cout << "  1. ID\n";
    std::cout << "  2. Nama\n";
    std::cout << "  Pilih [1-2]: ";
    int pilihan = inputPilihan();

    if (pilihan == 1) {
        std::cout << "  Masukkan ID: ";
        int id = inputPilihan();

        if (id <= 0) {
            std::cout << "  [ERROR] ID harus berupa angka positif.\n";
            return;
        }

        Node* result = listSearchById(head, id);
        if (result == nullptr) {
            std::cout << "\n  [INFO] Kontak dengan ID " << id << " tidak ditemukan.\n";
        } else {
            std::cout << "\n  [OK] Kontak ditemukan:\n";
            std::cout << "  " << std::string(30, '-') << "\n";
            printKontak(result->data);
        }

    } else if (pilihan == 2) {
        std::string keyword = inputString("  Masukkan nama yang dicari: ");
        if (keyword.empty()) {
            std::cout << "  [ERROR] Keyword tidak boleh kosong.\n";
            return;
        }

        std::string kwLower = keyword;
        std::transform(kwLower.begin(), kwLower.end(), kwLower.begin(), ::tolower);

        std::cout << "\n  Hasil pencarian untuk \"" << keyword << "\":\n";
        bool found = false;
        Node* temp = head;

        while (temp != nullptr) {
            std::string namaLower = temp->data.nama;
            std::transform(namaLower.begin(), namaLower.end(), namaLower.begin(), ::tolower);

            if (namaLower.find(kwLower) != std::string::npos) {
                if (!found) {
                    printTableHeader();
                    found = true;
                }
                printTableRow(temp->data);
            }
            temp = temp->next;
        }

        if (!found) {
            std::cout << "  [INFO] Tidak ada kontak yang mengandung nama \""
                      << keyword << "\".\n";
        } else {
            std::cout << "  " << std::string(90, '-') << "\n";
        }

    } else {
        std::cout << "  [ERROR] Pilihan tidak valid.\n";
    }
}

void updateContact(Node*& head) {
    printHeader();
    std::cout << "  EDIT KONTAK\n";
    std::cout << "  " << std::string(30, '-') << "\n\n";

    if (listCount(head) == 0) {
        std::cout << "  [INFO] Belum ada kontak yang tersimpan.\n";
        return;
    }

    displayContacts(head);
    std::cout << "\n  Masukkan ID kontak yang ingin diedit: ";
    int id = inputPilihan();

    if (id <= 0) {
        std::cout << "  [ERROR] ID harus berupa angka positif.\n";
        return;
    }

    Node* target = listSearchById(head, id);
    if (target == nullptr) {
        std::cout << "  [INFO] Kontak dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    std::cout << "\n  Data kontak saat ini:\n";
    std::cout << "  " << std::string(30, '-') << "\n";
    printKontak(target->data);
    std::cout << "  " << std::string(30, '-') << "\n";
    std::cout << "  (Tekan Enter tanpa mengetik untuk mempertahankan data lama)\n\n";

    Contact updated = target->data;
    std::string input;

    input = inputString("  Nama   [" + updated.nama + "]: ");
    if (!input.empty()) {
        updated.nama = input;
    }

    while (true) {
        input = inputString("  No. HP [" + updated.no_tlp + "]: ");
        if (input.empty()) break;
        if (validatePhone(input)) {
            updated.no_tlp = input;
            break;
        }
        std::cout << "  [ERROR] Nomor HP tidak valid. Coba lagi.\n";
    }

    while (true) {
        input = inputString("  Email  [" + updated.email + "]: ");
        if (input.empty()) break;
        if (validateEmail(input)) {
            updated.email = input;
            break;
        }
        std::cout << "  [ERROR] Format email tidak valid. Coba lagi.\n";
    }

    input = inputString("  Alamat [" + updated.alamat + "]: ");
    if (!input.empty()) {
        updated.alamat = input;
    }

    listUpdateById(head, id, updated);
    std::cout << "\n  [OK] Kontak berhasil diperbarui.\n";
}

void deleteContact(Node*& head) {
    printHeader();
    std::cout << "  HAPUS KONTAK\n";
    std::cout << "  " << std::string(30, '-') << "\n\n";

    if (listCount(head) == 0) {
        std::cout << "  [INFO] Belum ada kontak yang tersimpan.\n";
        return;
    }

    displayContacts(head);
    std::cout << "\n  Masukkan ID kontak yang ingin dihapus: ";
    int id = inputPilihan();

    if (id <= 0) {
        std::cout << "  [ERROR] ID harus berupa angka positif.\n";
        return;
    }

    Node* target = listSearchById(head, id);
    if (target == nullptr) {
        std::cout << "  [INFO] Kontak dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    std::cout << "\n  Kontak yang akan dihapus:\n";
    std::cout << "  " << std::string(30, '-') << "\n";
    printKontak(target->data);
    std::cout << "  " << std::string(30, '-') << "\n";

    std::string konfirmasi = inputString("\n  Yakin ingin menghapus? (y/n): ");
    if (konfirmasi == "y" || konfirmasi == "Y") {
        listRemoveById(head, id);
        std::cout << "  [OK] Kontak berhasil dihapus.\n";
    } else {
        std::cout << "  [INFO] Penghapusan dibatalkan.\n";
    }
}

void bubbleSort(std::vector<Contact>& vec, bool ascending) {
    int n = static_cast<int>(vec.size());
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool perluTukar;
            if (ascending) {
                perluTukar = (vec[j].nama > vec[j + 1].nama);
            } else {
                perluTukar = (vec[j].nama < vec[j + 1].nama);
            }
            if (perluTukar) {
                Contact temp  = vec[j];
                vec[j]        = vec[j + 1];
                vec[j + 1]    = temp;
            }
        }
    }
}

void sortContacts(Node* head) {
    printHeader();
    std::cout << "  URUTKAN KONTAK\n";
    std::cout << "  " << std::string(30, '-') << "\n\n";

    if (listCount(head) == 0) {
        std::cout << "  [INFO] Belum ada kontak yang tersimpan.\n";
        return;
    }

    std::cout << "  Urutkan berdasarkan:\n";
    std::cout << "  1. Nama A-Z\n";
    std::cout << "  2. Nama Z-A\n";
    std::cout << "  Pilih [1-2]: ";
    int pilihan = inputPilihan();

    if (pilihan != 1 && pilihan != 2) {
        std::cout << "  [ERROR] Pilihan tidak valid.\n";
        return;
    }

    std::vector<Contact> buffer;
    Node* temp = head;
    while (temp != nullptr) {
        buffer.push_back(temp->data);
        temp = temp->next;
    }

    bool ascending = (pilihan == 1);
    bubbleSort(buffer, ascending);

    std::string label = ascending ? "Nama A-Z" : "Nama Z-A";
    std::cout << "\n  Kontak diurutkan berdasarkan " << label << ":\n";
    printTableHeader();
    for (const Contact& c : buffer) {
        printTableRow(c);
    }
    std::cout << "  " << std::string(90, '-') << "\n";
    std::cout << "  Total: " << static_cast<int>(buffer.size()) << " kontak\n";
    std::cout << "  (Catatan: urutan di daftar asli tidak berubah)\n";
}

int main() {
    Node* head = nullptr;

    Contact sample1 = {1, "Ahmad Fauzi",  "0821-4567-8901", "ahmad@gmail.com",  "Jl. Thamrin No. 10"};
    Contact sample2 = {2, "Budi Santoso", "0812-3456-7890", "budi@gmail.com",   "Jl. Merdeka No. 1"};
    Contact sample3 = {3, "Siti Rahayu",  "0856-9012-3456", "siti@gmail.com",   "Jl. Sudirman No. 5"};
    listInsert(head, sample1);
    listInsert(head, sample2);
    listInsert(head, sample3);

    bool running = true;
    while (running) {
        clearScreen();
        showMenu();

        int pilihan = inputPilihan();
        switch (pilihan) {
            case 1:
                clearScreen();
                addContact(head);
                pause();
                break;
            case 2:
                clearScreen();
                displayContacts(head);
                pause();
                break;
            case 3:
                clearScreen();
                searchContact(head);
                pause();
                break;
            case 4:
                clearScreen();
                updateContact(head);
                pause();
                break;
            case 5:
                clearScreen();
                deleteContact(head);
                pause();
                break;
            case 6:
                clearScreen();
                sortContacts(head);
                pause();
                break;
            case 7:
                clearScreen();
                printHeader();
                std::cout << "\n  Terima kasih telah menggunakan Contact Manager!\n";
                std::cout << "  Program selesai.\n\n";
                running = false;
                break;
            default:
                std::cout << "\n  [ERROR] Pilihan tidak valid! Masukkan angka 1-7.\n";
                pause();
                break;
        }
    }

    listFree(head);
    return 0;
}