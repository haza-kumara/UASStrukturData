#include "LinkedList.h"

#include <iostream>

// ==============================================================
// listInsert — Sisipkan node baru di akhir list (append)
// Kompleksitas: O(n) karena harus traversal ke ujung list
// ==============================================================
void listInsert(Node*& head, const Contact& c) {
    Node* newNode = new Node{c, nullptr};

    // Kasus 1: list kosong — node baru langsung menjadi head
    if (head == nullptr) {
        head = newNode;
        return;
    }

    // Kasus 2: traversal ke node terakhir, lalu sambungkan
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// ==============================================================
// listRemoveById — Hapus node dengan ID tertentu
// Kompleksitas: O(n)
// ==============================================================
void listRemoveById(Node*& head, int id) {
    if (head == nullptr) return;

    // Kasus 1: node yang dihapus adalah head
    if (head->data.id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // Kasus 2: cari node sebelum target, lalu lewati
    Node* current = head;
    while (current->next != nullptr && current->next->data.id != id) {
        current = current->next;
    }

    // Jika ditemukan, hapus node
    if (current->next != nullptr) {
        Node* temp       = current->next;
        current->next    = current->next->next;
        delete temp;
    }
}

// ==============================================================
// listUpdateById — Perbarui data kontak berdasarkan ID
// Mengembalikan true jika ID ditemukan dan berhasil diperbarui,
// false jika ID tidak ditemukan.
// Kompleksitas: O(n)
// ==============================================================
bool listUpdateById(Node*& head, int id, const Contact& updated) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.id == id) {
            temp->data = updated;   // timpa data lama dengan data baru
            return true;
        }
        temp = temp->next;
    }
    return false;   // ID tidak ditemukan
}

// ==============================================================
// listSearchByName — Cari node dengan nama tertentu (exact match)
// Mengembalikan pointer ke Node jika ditemukan, nullptr jika tidak.
// Algoritma: Linear Search — O(n)
// ==============================================================
Node* listSearchByName(Node* head, const std::string& nama) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.nama == nama) {
            return temp;    // ditemukan
        }
        temp = temp->next;
    }
    return nullptr;         // tidak ditemukan
}

// ==============================================================
// listSearchById — Cari node dengan ID tertentu
// Mengembalikan pointer ke Node jika ditemukan, nullptr jika tidak.
// Algoritma: Linear Search — O(n)
// ==============================================================
Node* listSearchById(Node* head, int id) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.id == id) {
            return temp;    // ditemukan
        }
        temp = temp->next;
    }
    return nullptr;         // tidak ditemukan
}

// ==============================================================
// listCount — Hitung jumlah node dalam list
// Kompleksitas: O(n)
// ==============================================================
int listCount(Node* head) {
    int count = 0;
    while (head != nullptr) {
        count++;
        head = head->next;
    }
    return count;
}

// ==============================================================
// listFree — Bebaskan seluruh memori Linked List
// Panggil fungsi ini sebelum program berakhir untuk menghindari
// memory leak.
// Kompleksitas: O(n)
// ==============================================================
void listFree(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head       = head->next;
        delete temp;
    }
}