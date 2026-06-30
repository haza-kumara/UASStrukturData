#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Contact.h"



struct Node {
    Contact data;   // data kontak yang disimpan
    Node*   next;   // pointer ke node selanjutnya (nullptr jika terakhir)
};


// Menyisipkan kontak baru di akhir list 
void listInsert(Node*& head, const Contact& c);

// Menghapus node dengan ID tertentu
void listRemoveById(Node*& head, int id);

// Memperbarui data kontak berdasarkan ID
// Mengembalikan true jika berhasil, false jika ID tidak ditemukan
bool listUpdateById(Node*& head, int id, const Contact& updated);

// Mencari node berdasarkan nama (exact match, case-sensitive)
// Mengembalikan pointer ke Node, atau nullptr jika tidak ditemukan
Node* listSearchByName(Node* head, const std::string& nama);

// Mencari node berdasarkan ID
// Mengembalikan pointer ke Node, atau nullptr jika tidak ditemukan
Node* listSearchById(Node* head, int id);

// Menghitung jumlah node dalam list — O(n)
int listCount(Node* head);

// Membebaskan seluruh memori Linked List (panggil di akhir program)
void listFree(Node*& head);

#endif
