#include "../include/BST.h"
#include <iostream>

//untuk menambahkan kontak ke dalam BST (rekursif)
void bst_insert(bst_node*& root, const contact& k) {
    if (root == nullptr) {
        root = new bst_node{k, nullptr, nullptr};
    } else if (k.nama < root->data.nama) {
        bst_insert(root->left, k);
    } else if (k.nama > root->data.nama) {
        bst_insert(root->right, k);
    }
}

//helper untuk mencari nilai minimum
bst_node* find_min(bst_node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

//delete kontak dengan nama
void bst_remove(bst_node*& root, const std::string& nama) {
    if (root == nullptr) return;

    if (nama < root->data.nama) {
        bst_remove(root->left, nama);
    } else if (nama > root->data.nama) {
        bst_remove(root->right, nama);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->left == nullptr) {
            bst_node* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == nullptr) {
            bst_node* temp = root;
            root = root->left;
            delete temp;
        } else {
            //node dengan 2 anak
            bst_node* temp = find_min(root->right);
            root->data = temp->data; //timpa dengan data suksesor
            bst_remove(root->right, temp->data.nama); //hapus suksesor
        }
    }
}

//mencari kontak berdasarkan nama
bst_node* bst_search(bst_node* root, const std::string& nama) {
    if (root == nullptr || root->data.nama == nama) {
        return root;
    }
    if (nama < root->data.nama) {
        return bst_search(root->left, nama);
    }
    return bst_search(root->right, nama);
}

//menampilkan kontak (In-Order Traversal agar sesuai alfabet A-Z)
void bst_display(bst_node* root) {
    if (root != nullptr) {
        bst_display(root->left);
        print_kontak(root->data);
        bst_display(root->right);
    }
}