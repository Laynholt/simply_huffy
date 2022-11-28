#include "tree.h"

void tree_create(Tree* tree, int16_t number_of_varialbes)
{
	tree->root = NULL;
	tree->depth = 0;

	// Высчитываем ближайшее значение двойки
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

void tree_destroy_cycle(Tree* tree)
{
	Node* previous = NULL;
	Node* current = tree->root;
	uint8_t is_left = 0;

	if (current == NULL)
		return;

	free(tree->buffer);

	// Удаляем сначало левое поддерево, а потом правое
	for (int16_t i = 0; i < 2; ++i)
	{
		do
		{
			if (current->left)
			{
				current = current->left;
			}
			else if (current->right)
			{
				current = current->right;
			}
			else if (current != tree->root)
			{
				previous = current->parent;
				is_left = (previous->left == current) ? 1 : 0;

				node_destroy(current);
				current = previous;

				if (is_left) current->left = NULL;
				else current->right = NULL;
			}

		} while (current->parent != NULL);
	}
}

void tree_create_table(Tree* tree, Element** elements, uint8_t table_build_mode)
{
	if (tree->root == NULL)
		return;

	*elements = (Element*)malloc(sizeof(Element) * tree->number_of_varialbes);
	
	if (table_build_mode == TABLE_RECURSION_MODE)
		tree_create_code(tree, tree->root, *elements);
	else if (table_build_mode == TABLE_CYCLE_MODE)
		tree_create_code_cycle(tree, *elements);
}

void tree_destroy_table(Tree* tree, Element* elements)
{
	// Высчитываем ближайшее значение двойки
	int16_t size = 1;
	while (tree->number_of_varialbes > size)
		size <<= 1;
	memset(tree->buffer, '\0', size);
	
	tree->depth = 0;
	tree->current_element = 0;

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

void tree_create_code_cycle(Tree* tree, Element* elements)
{
	if (tree->number_of_varialbes == 1)
	{
		elements[tree->current_element].symbol = tree->root->symbol[0];
		elements[tree->current_element].code = (char*)malloc(2 * sizeof(char));
		memcpy(elements[tree->current_element].code, "0", 2);
		return;
	}

	Node* current = tree->root;

	uint8_t is_leaf = 1;
	uint8_t is_left = 0;
	List left_nodes, right_nodes;

	list_create(&left_nodes);
	list_create(&right_nodes);

	for (int16_t i = 0; i < 2; ++i)
	{
		do
		{
			is_leaf = 1;

			if (current->left || current->right)
				is_leaf = 0;

			if (current->left && !list_is_on_list(&left_nodes, current->left))
			{
				tree->buffer[tree->depth] = '0';
				tree->depth += 1;
				current = current->left;
			}
			else if (current->right && !list_is_on_list(&right_nodes, current->right))
			{
				tree->buffer[tree->depth] = '1';
				tree->depth += 1;
				current = current->right;
			}
			else
			{
				if (is_leaf)
				{
					elements[tree->current_element].symbol = current->symbol[0];

					int16_t code_length = strlen(tree->buffer) + 1;
					elements[tree->current_element].code = (char*)malloc(code_length);
					memcpy(elements[tree->current_element].code, tree->buffer, code_length);
					tree->current_element += 1;
				}

				tree->depth -= (tree->depth > 0) ? 1 : 0;
				tree->buffer[tree->depth] = '\0';

				is_left = (current->parent->left == current) ? 1 : 0;
				current = current->parent;

				if (is_left)  list_push_back_link(&left_nodes, current->left);
				else list_push_back_link(&right_nodes, current->right);
			}

		} while (current->parent != NULL);
	}

	list_destroy_link(&left_nodes);
	list_destroy_link(&right_nodes);
}

void tree_print(Tree* tree)
{
	tree_print_node(tree->root);
}

void tree_print_node(Node* node)
{
	printf("%s - [%d (%d)] -- [%d] -- [%d (%d)]\n", node->symbol, node->left, 
		(node->left) ? node->left->parent : NULL, node, node->right, (node->right) ? node->right->parent: NULL);

	if (node->left)
		tree_print_node(node->left);

	if (node->right)
		tree_print_node(node->right);
}