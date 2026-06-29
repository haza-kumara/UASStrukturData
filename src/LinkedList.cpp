#include "LinkedList.h"

#include <iostream>

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

int listCount(Node* head) {
    int count = 0;
    while (head != nullptr) {
        count++;
        head = head->next;
    }
    return count;
}


void listFree(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head       = head->next;
        delete temp;
    }
}