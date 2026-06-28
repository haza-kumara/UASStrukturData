#include "../include/LinkedList.h"
#include <iostream>

//menambahkan kontak di akhir linked list
void list_insert(list_node*& head, const contact& k) {
    list_node* newNode = new list_node{k, nullptr};
    if (head == nullptr) {
        head = newNode;
    } else {
        list_node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

//hapus kontak berdasarkan nama
void list_remove(list_node*& head, const std::string& nama) {
    if (head == nullptr) return;

    //jika node yang akan dihapus ada di head
    if (head->data.nama == nama) {
        list_node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    //mencari node yang akan dihapus
    list_node* current = head;
    while (current->next != nullptr && current->next->data.nama != nama) {
        current = current->next;
    }

    //if node ditemukan
    if (current->next != nullptr) {
        list_node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

//display semua kontak
void list_display(list_node* head) {
    list_node* temp = head;
    while (temp != nullptr) {
        print_kontak(temp->data);
        temp = temp->next;
    }
}

//mencari kontak berdasarkan nama
list_node* search(list_node* head, const std::string& nama) {
    list_node* temp = head;
    while (temp != nullptr) {
        if (temp->data.nama == nama) {
            return temp; // Ditemukan
        }
        temp = temp->next;
    }
    return nullptr;
}