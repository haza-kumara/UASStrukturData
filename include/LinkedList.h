#ifndef LinkedList_H
#define LinkedList_H

#include <string>
#include "Contact.h"

struct list_node {
  contact data;
  list_node* next;
};

// komen disini
void ll_insert (list_node*& head, const contact& k);
void ll_remove (list_node*& head, const std::string& nama);
void ll_display (list_node* head);
list_node* search(list_node* head, const std::string& nama);








#endif
