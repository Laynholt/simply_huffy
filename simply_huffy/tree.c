#include "tree.h"

void tree_create(Tree* tree, int16_t number_of_varialbes)
{
	tree->root = NULL;
	tree->depth = 0;

	// Высчитываем ближайшее меньшее значение двойки
	int16_t size = 1;
	while (number_of_varialbes > size)
		size <<= 1;

	tree->buffer = (char*)malloc(size);
	memset(tree->buffer, '\0', size);
	tree->number_of_varialbes = number_of_varialbes;
	tree->current_element = 0;
}

void tree_destroy(Tree* tree)
{
	if (tree->root == NULL)
		return;

	free(tree->buffer);
	tree_destroy_node(tree->root);
}

void tree_destroy_node(Node* node)
{
	if (node->left)
		tree_destroy_node(node->left);

	if (node->right)
		tree_destroy_node(node->right);

	node_destroy(node);
}

void tree_create_table(Tree* tree, Element** elements)
{
	if (tree->root == NULL)
		return;

	*elements = (Element*)malloc(sizeof(Element) * tree->number_of_varialbes);
	tree_create_code(tree, tree->root, *elements);
}

void tree_destroy_table(Tree* tree, Element* elements)
{
	for (int16_t i = 0; i < tree->number_of_varialbes; ++i)
		free(elements[i].code);
	free(elements);
}

void tree_create_code(Tree* tree, Node* node, Element* elements)
{
	uint8_t is_leaf = 1;

	if (tree->number_of_varialbes == 1)
	{
		elements[tree->current_element].symbol = node->symbol[0];
		elements[tree->current_element].code = (char*)malloc(2 * sizeof(char));
		memcpy(elements[tree->current_element].code, "0", 2);
		return;
	}

	if (node->left)
	{
		tree->buffer[tree->depth] = '0';
		tree->depth += 1;
		tree_create_code(tree, node->left, elements);
		tree->depth -= 1;
		tree->buffer[tree->depth] = '\0';
		is_leaf = 0;
	}
	if (node->right)
	{
		tree->buffer[tree->depth] = '1';
		tree->depth += 1;
		tree_create_code(tree, node->right, elements);
		tree->depth -= 1;
		tree->buffer[tree->depth] = '\0';
		is_leaf = 0;
	}

	if (is_leaf)
	{
		elements[tree->current_element].symbol = node->symbol[0];

		int16_t code_length = strlen(tree->buffer) + 1;
		elements[tree->current_element].code = (char*)malloc(code_length);
		memcpy(elements[tree->current_element].code, tree->buffer, code_length);
		tree->current_element += 1;
	}
}

void tree_print(Tree* tree)
{
	tree_print_node(tree->root);
}

void tree_print_node(Node* node)
{
	printf("%s - [%d] [%d / %d]\n", node->symbol, node, node->left, node->right);

	if (node->left)
		tree_print_node(node->left);

	if (node->right)
		tree_print_node(node->right);

//	printf("%s - [%d / %d]\n", node->symbol, node->left, node->right);

}