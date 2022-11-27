#include "list.h"

void list_create(List* list)
{
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

void list_destroy(List* list)
{
	list_clear(list);

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

void list_push_back(List* list, char* symbol)
{
	int16_t number_of_symbols = strlen(symbol) + 1;

	if (list->size == 0)
	{
		list->head = node_create(number_of_symbols);
		list->tail = list->head;
		memcpy(list->head->symbol, symbol, number_of_symbols);
		list->head->count += 1;
		list->size += 1;
	}
	else
	{
		Node* current = list->head;
		uint8_t symbol_exists = 0;

		while (current != NULL)
		{
			if (strcmp(current->symbol, symbol) == 0)
			{
				symbol_exists = 1;
				current->count += 1;
				break;
			}
			current = current->next;
		}

		if (symbol_exists)
			return;

		list->tail->next = node_create(number_of_symbols);
		list->tail = list->tail->next;
		memcpy(list->tail->symbol, symbol, number_of_symbols);
		list->tail->count += 1;
		list->size += 1;
	}
}

Node* list_front(List* list)
{
	return list->head;
}

Node* list_pop_front(List* list)
{
	if (list->size == 0)
		return NULL;

	Node* old_head = list->head;
	list->head = list->head->next;
	list->size -= 1;
	old_head->next = NULL;

	return old_head;
}

Node* list_back(List* list)
{
	return list->tail;
}

void list_clear(List* list)
{
	if (list->size == 0)
		return;

	Node* current = list->head;
	Node* next = NULL;
	while (current != NULL)
	{
		next = current->next;
		node_destroy(current);
		current = next;
	}
}

void list_sort(List* list)
{
	if (list->size < 2)
		return;

	Node* current = list->head;
	Node* next = NULL;

	do
	{
		next = current->next;
		do
		{
			if (current->count > next->count)
			{
				char* symbol = current->symbol;
				int16_t count = current->count;
				Node* left = current->left;
				Node* right = current->right;

				current->symbol = next->symbol;
				current->count = next->count;
				current->left = next->left;
				current->right = next->right;

				next->symbol = symbol;
				next->count = count;
				next->left = left;
				next->right = right;

			}
			next = next->next;

		} while (next != NULL);

		current = current->next;
	} while (current->next != NULL);
}

void list_print(List* list)
{
	Node* current = list->head;
	while (current != NULL)
	{
		printf("%s - %d\n", current->symbol, current->count);
		current = current->next;
	}
}
