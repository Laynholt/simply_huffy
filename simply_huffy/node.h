#ifndef _NODE_H_
#define _NODE_H_

#include <stdint.h>
#include <malloc.h>
#include <string.h>

typedef struct Node
{
	char* symbol;
	int16_t count;

	// ”казатель дл€ списка
	struct Node* next;

	// ”казатели дл€ дерева
	struct Node* left;
	struct Node* right;

}Node;

extern Node* node_create(int16_t number_of_symbols);
extern void node_destroy(Node* node);


#endif // !_NODE_H_