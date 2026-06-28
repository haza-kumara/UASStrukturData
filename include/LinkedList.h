#ifndef LinkedList_H
#define LinkedList_H

#include <string>
#include "Contact.h"

struct list_node {
  contact data;
  list_node* next;
};

// komen disini
void list_insert (list_node*& head, const contact& k);
void list_remove (list_node*& head, const std::string& nama);
void list_display (list_node* head);
list_node* search(list_node* head, const std::string& nama);








#endif
