#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>

#include "list.h"
#include "tree.h"

#define MAX_STRING_SIZE 7

int main(int argc, char** argv)
{
	char input_string[MAX_STRING_SIZE] = { '\0' };
	printf("Enter string: ");
	scanf("%s", input_string);

	// Создаем список для хранения переменных с их частотой
	List list;
	list_create(&list);

	char symbols[MAX_STRING_SIZE] = { '\0' };
	for (int16_t i = 0; i < MAX_STRING_SIZE - 1; ++i)
	{
		memcpy(symbols, &input_string[i], 1);
		list_push_back(&list, symbols);
	}

	list_sort(&list);
	printf("Character frequency:\n");
	list_print(&list);
	printf("\n");

	int16_t number_of_variables = list.size;
	while (list.size != 1)
	{
		list_sort(&list);

		Node* left_node = list_pop_front(&list);
		Node* right_node = list_pop_front(&list);

		memset(symbols, '\0', MAX_STRING_SIZE);
		memcpy(symbols, left_node->symbol, strlen(left_node->symbol));
		memcpy(symbols + strlen(left_node->symbol), right_node->symbol, strlen(right_node->symbol));

		list_push_back(&list, symbols);

		Node* parent_node = list_back(&list);
		parent_node->left = left_node;
		parent_node->right = right_node;
	}
	Tree tree;
	Element* table = NULL;

	tree_create(&tree, number_of_variables);
	tree.root = list_pop_front(&list);
	
	printf("Binary tree:\n");
	tree_print(&tree);
	printf("\n");

	tree_create_table(&tree, &table);
	printf("Huffman codes:\n");
	for (int16_t i = 0; i < number_of_variables; ++i)
	{
		printf("%c - %s\n", table[i].symbol, table[i].code);
	}

	tree_destroy_table(&tree, table);
	tree_destroy(&tree);
	list_destroy(&list);
	
	return 0;
}