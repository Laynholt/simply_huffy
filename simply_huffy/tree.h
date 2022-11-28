#ifndef _TREE_H_
#define _TREE_H_

#include "node.h"
#include "list.h"

#define TABLE_RECURSION_MODE 0
#define TABLE_CYCLE_MODE 1

typedef struct Element
{
	char symbol;
	char* code;

}Element;

typedef struct Tree
{
	struct Node* root;

	char* buffer;
	int16_t depth;
	int16_t current_element;
	int16_t number_of_varialbes;

}Tree;

extern void tree_create(Tree* tree, int16_t number_of_varialbes);
extern void tree_destroy(Tree* tree);
extern void tree_destroy_node(Node* node);
extern void tree_destroy_cycle(Tree* tree);

extern void tree_create_table(Tree* tree, Element** elements, uint8_t table_build_mode);
extern void tree_destroy_table(Tree* tree, Element* elements);

extern void tree_create_code(Tree* tree, Node* node, Element* elements);
extern void tree_create_code_cycle(Tree* tree, Element* elements);

extern void tree_print(Tree* tree);
extern void tree_print_node(Node* node);

#endif // !_TREE_H_
