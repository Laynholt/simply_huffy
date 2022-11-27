#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <string.h>
#include "node.h"

typedef struct List
{
	struct Node* head;
	struct Node* tail;
	int16_t size;

}List;

extern void list_create(List* list);
extern void list_destroy(List* list);

extern void list_push_back(List* list, char* symbol);
extern Node* list_front(List* list);
extern Node* list_pop_front(List* list);
extern Node* list_back(List* list);

extern void list_clear(List* list);

extern void list_sort(List* list);
extern void list_print(List* list);
//extern void* list_find(List* list, void* (*_check_element)(void*));

#endif // !_LIST_H_
