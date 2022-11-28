#include "node.h"

Node* node_create(int16_t number_of_symbols)
{
	void* raw_memory = malloc(sizeof(Node) + number_of_symbols * sizeof(char));
	Node* node = (Node*)raw_memory;
	node->symbol = (char*)(raw_memory) + sizeof(Node);
	memset(node->symbol, '\0', number_of_symbols);

	node->count = 0;
	node->next = NULL;

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void node_destroy(Node* node)
{
	free(node);
}
