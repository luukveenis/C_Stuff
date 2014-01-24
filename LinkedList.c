#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DataNode
{
	char* info;
} d_node;

typedef struct Node
{
	struct Node* next;
	struct Node* prev;
	d_node* data;
} node;

/* Global references to head and tail to
 * avoid having to pass them around in functions */
node* head = NULL;
node* tail = NULL;

/* Creates a new node
 * Both back and prev pointers will be NULL
 * Creates a data node with the specified data and sets the reference */
node* create_node(char* new_data)
{
	/* Create the node */
	node* new_node = malloc(sizeof(node));
	new_node->next = NULL;
	new_node->prev = NULL;
	/* Create the data struct */
	d_node* data_node = malloc(sizeof(d_node));
	data_node->info = new_data;
	/* Set the reference */
	new_node->data = data_node;
	return new_node;
}

/* Destroys the given node, freeing the memory 
 * All pointers are set to NULL */
void deallocate_node(node* node)
{
	node->data->info = NULL;
	free(node->data);
	node->data = NULL;
	node->next = NULL;
	node->prev = NULL;
	free(node);
}

/* Deletes the given node */
void delete_node(node* node)
{
	/* Case 1: It is the only node in the list */
	if (NULL == node->prev && NULL == node->next)
	{
		head = NULL;
		tail = NULL;
		deallocate_node(node);
	}
	/* Case 2: It is the head of the list */
	else if (NULL == node->prev && NULL != node->next)
	{
		head = node->next;
		node->next->prev = NULL;
		deallocate_node(node);
	}
	/* Case 3: It is the tail of the list */
	else if (NULL != node->prev && NULL == node->next)
	{
		tail = node->prev;
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
}

/* Searches for and returns a node that constains the specified string */
node* search(char *data)
{
	node* current = head;
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
void insert_at_head(char* new_data)
{
	node* new_node = create_node(new_data);
	if (NULL == head)
	{
		head = new_node;
	}
	else
	{
		head->prev = new_node;
		new_node->next = head;
		head = new_node;
	}
}

/* Inserts a new node after the provided node */
node* insert_after(node *node, char *data)
{
	/* Case 1: Inserting in middle of list */
	if (NULL != node && NULL != node->next)
	{
		node *new_node = create_node(data);
		new_node->prev = node;
		new_node->next = node->next;
		new_node->next->prev = new_node;
		new_node->prev->next = new_node;
	}
	/* Case 2: Inserting at the end of the list */
	else if (NULL != node && NULL == node->next)
	{
		node *new_node = create_node(data);
		new_node->prev = node;
		node->next = new_node;
	}
	else
	{
		printf("Invalid node: is NULL");
		return NULL;
	}
	/* You should never be inserting at the beginning using this function */
	return new_node;
}

/* Returns the node at the given index (indexing from 0)
 * Returns NULL if the index doesn't exist */
node* find_node_at(node *head, int index)
{
	node *current = head;
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
void print_list()
{
	int counter = 1;
	node* current = head;
	while(NULL != current)
	{
		printf("Node %d: %s\n", counter, current->data->info);
		counter++;
		current = current->next;
	}
}

/* Returns the size of the list */
int size(node* head)
{
	int count= 0;
	node* current = head;
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
	printf("Hello, and welcome to my linked list program!\n\n");
	printf("Inserting some data...\n");
	insert_at_head("Luuk");
	insert_at_head("Ozzy");
	insert_at_head("Andria");
	insert_at_head("Linux");
	print_list();
	printf("\nDeleting the first node...\n");
	delete_node(head);
	print_list();
	printf("\nDeleting another node...\n");
	delete_node(head);
	print_list();
	printf("\nSearching for 'Luuk'\n");
	node* result = search("Luuk");
	printf("Result was: %s\n", result->data->info);
	printf("Size is: %d\n", size(head));
}
