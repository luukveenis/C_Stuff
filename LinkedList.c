#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DataNode* d_node_ptr;
typedef struct DataNode
{
	char* info;
} d_node;

typedef struct Node* node_ptr;
typedef struct Node
{
	node_ptr next;
	node_ptr prev;
	d_node_ptr data;
} node;

typedef struct LinkedList* llist_ref;
typedef struct LinkedList
{
	node_ptr head;
	node_ptr tail;
	int size;
} LList;

/* Global references to head and tail to
 * avoid having to pass them around in functions */
node_ptr head = NULL;
node_ptr tail = NULL;

/* Creates a new node
 * Both back and prev pointers will be NULL
 * Creates a data node with the specified data and sets the reference */
node_ptr create_node(char* new_data)
{
	/* Create the node */
	node_ptr new_node = malloc(sizeof(node));
	new_node->next = NULL;
	new_node->prev = NULL;
	/* Create the data struct */
	d_node_ptr data_node = malloc(sizeof(d_node));
	data_node->info = new_data;
	/* Set the reference */
	new_node->data = data_node;
	return new_node;
}

/* Destroys the given node, freeing the memory 
 * All pointers are set to NULL */
void deallocate_node(node_ptr node)
{
	node->data->info = NULL;
	free(node->data);
	node->data = NULL;
	node->next = NULL;
	node->prev = NULL;
	free(node);
}

/* Deletes the given node */
void delete_node(llist_ref list, node_ptr node)
{
	/* Case 1: It is the only node in the list */
	if (NULL == node->prev && NULL == node->next)
	{
		list->head = NULL;
		list->tail = NULL;
		deallocate_node(node);
	}
	/* Case 2: It is the head of the list */
	else if (NULL == node->prev && NULL != node->next)
	{
		list->head = node->next;
		node->next->prev = NULL;
		deallocate_node(node);
	}
	/* Case 3: It is the tail of the list */
	else if (NULL != node->prev && NULL == node->next)
	{
		list->tail = node->prev;
		node->prev->next = NULL;
		deallocate_node(node);
	}
	/* Case 4: It is in the middle of the list */
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		deallocate_node(node);
	}
	list->size--;
}

/* Searches for and returns a node that constains the specified string */
node_ptr search(llist_ref list, char *data)
{
	node_ptr current = list->head;
	while (NULL != current)
	{
		if (0 == strcmp(data, current->data->info))
		{
			return current;
		}
		current = current->next;
	}
	return current;
}

/* Inserts a node that contains the given information
 * at the head of the list */
void insert_at_head(llist_ref list, char* new_data)
{
	node_ptr new_node = create_node(new_data);
	if (NULL == list->head)
	{
		list->head = new_node;
		if (NULL == list->tail)
		{
			list->tail = new_node;
		}
	}
	else
	{
		list->head->prev = new_node;
		new_node->next = list->head;
		list->head = new_node;
	}
	list->size++;
}

/* Inserts a new node after the provided node */
node_ptr insert_after(llist_ref list, node *node, char *data)
{
	/* Case 1: Inserting in middle of list */
	if (NULL != node && NULL != node->next)
	{
		node_ptr new_node = create_node(data);
		new_node->prev = node;
		new_node->next = node->next;
		new_node->next->prev = new_node;
		new_node->prev->next = new_node;
		list->size++;
		return new_node;
	}
	/* Case 2: Inserting at the end of the list */
	else if (NULL != node && NULL == node->next)
	{
		node_ptr new_node = create_node(data);
		new_node->prev = node;
		node->next = new_node;
		list->size++;
		return new_node;
	}
	else
	{
		printf("Invalid node: is NULL");
		return NULL;
	}
}

/* Returns the node at the given index (indexing from 0)
 * Returns NULL if the index doesn't exist */
node_ptr find_node_at(llist_ref list, node *head, int index)
{
	node *current = list->head;
	int count = 0;
	while (NULL != current)
	{
		if (count == index)
		{
			return current;
		}
		count++;
	}
	return NULL;	
}

/* Simply prints all the elements currently in the list pointed to by head */
void print_list(llist_ref list)
{
	int counter = 1;
	node_ptr current = list->head;
	while(NULL != current)
	{
		printf("Node %d: %s\n", counter, current->data->info);
		counter++;
		current = current->next;
	}
}

/* Returns the size of the list */
int size(llist_ref list)
{
	int count= 0;
	node_ptr current = list->head;
	while (NULL != current)
	{
		count++;
		current = current->next;
	}
	return count;
}

/* Just some testing code */
int main(void)
{
	LList list = {NULL, NULL, 0};

	printf("******************************\n");
	printf("* Simple linked list program *\n");
	printf("******************************\n\n");
	printf("Inserting some data...\n");
	insert_at_head(&list, "Luuk");
	insert_at_head(&list, "Ozzy");
	insert_at_head(&list, "Andria");
	insert_at_head(&list, "Linux");
	print_list(&list);
	printf("\nDeleting the first node...\n");
	delete_node(&list, list.head);
	print_list(&list);
	printf("\nDeleting another node...\n");
	delete_node(&list, list.head);
	print_list(&list);
	printf("\nSearching for 'Luuk'\n");
	node_ptr result = search(&list, "Luuk");
	printf("Result was: %s\n", result->data->info);
	printf("Size is: %d\n\n", list.size);
	printf("Inserting two things after Luuk...\n");
	insert_after(&list, search(&list, "Luuk"), "New stuff");
	insert_after(&list, search(&list, "Luuk"), "More stuff");
	print_list(&list);
}
