#ifndef BST_H
#define BST_H

#include <string>
#include "Contact.h"

struct bst_node {
    contact data;
    bst_node* left;
    bst_node* right;
};

void bst_insert(bst_node*& root, const contact& k);
void bst_remove(bst_node*& root, const std::string& nama);
bst_node* bst_search(bst_node* root, const std::string& nama);
void bst_display(bst_node* root);




#endif
