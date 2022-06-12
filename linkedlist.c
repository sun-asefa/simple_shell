#include "shell.h"

/**
 * add_node_to_front - adds a new node at the beginning of a linked_l list
 * @head: reference to head of linked list
 * @str: string to be added on new node
 * Return: address of new head;
 */
linked_l *add_node_to_front(linked_l **head, char *str)
{
	linked_l *newNode;
	char *new_str;

	if (!str)
		return (NULL);
	newNode = malloc(sizeof(linked_l));
	if (!newNode)
	{
		perror("Malloc failed\n");
		exit(errno);
		free(newNode);
	}
	new_str = _strdup(str);
	if (!new_str)
	{
		perror("Malloc failed\n");
		exit(errno);
	}
	newNode->string = new_str;
	newNode->next = *head;
	*head = newNode;
	/*free(newNode);*/
	return (*head);
}

/**
 * addNodeEnd - adds a new node at the end of a linked_l list;
 * @head: reference to head of list
 * @str: string to be added to linked list
 * Return: address of new node
 */
linked_l *add_node_to_end(linked_l **head, char *str)
{
	linked_l *newNode;
	linked_l *last = *head;
	char *newStr;

	if (!str)
		return (NULL);
	newNode = malloc(sizeof(linked_l));
	if (!newNode)
	{
		perror("Malloc failed\n");
		exit(errno);
		free(newNode);
	}
	newStr = _strdup(str);
	if (!newStr)
	{
		perror("Malloc failed\n");
		exit(errno);
	}
	newNode->string = newStr;
	newNode->next = NULL;
	if (!*head)
	{
		*head = newNode;
		return (newNode);
	}
	while (last->next)
		last = last->next;
	last->next = newNode;
	return (last);
}

/**
 * print_list - prints all elements of a linked_l list
 * @h: pointer to head of list
 * Return: number of elements
 */
size_t print_list(const linked_l *h)
{
	register int count = 0;

	while (h)
	{
		write(STDOUT_FILENO, h->string, _strlen(h->string));
		put_new_line();
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * delete_node_at_index - deletes the node at index
 * index of a linked_l linked list
 * @head: double pointer to head of list
 * @index: index of node to be deleted
 * Return: 1 if success, -1 if fail
 */
int delete_node_at_index(linked_l **head, unsigned int index)
{
	linked_l *current;
	linked_l *next;

	register uint i;

	if (!head || !(*head))
		return (-1);
	current = *head;
	if (!index)
	{
		*head = current->next;
		return (1);
	}
	for (i = 0; current && i < index - 1; i++)
		current = current->next;
	if (!current || !(current->next))
		return (-1);
	next = current->next->next;
	free(current->next->string);
	current->next = next;
	/* free(current->next); */
	return (1);
}

/**
 * list_len - returns the number of elements in a linked list
 * @h: head of linked list
 * Return: number of elements in list_t
 */
size_t list_len(linked_l *h)
{
	register unsigned int count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * search_node - searches linked list for string and returns index
 * @head: pointer to head of list
 * @str: input string
 * Return: index of node with matching string
 */

int search_node(linked_l *head, char *str)
{
	register int len = 0, index = 0, i;
	linked_l *current;
	char *tmp, *ptr;

	current = head;
	while (current)
	{
		ptr = _strchr(current->string, '=');
		len = ptr - current->string;
		tmp = malloc(sizeof(char) * len + 1);
		for (i = 0; i < len; i++)
		{
			tmp[i] = current->string[i];
		}
		tmp[i] = '\0';
		if (_strcmp(str, tmp) == 0)
		{
			return (index);
		}
		index++;
		current = current->next;
		free(tmp);
	}
	return (-1);
}

/**
 * generateLinkedList - generates a linked list of environ
 * variables
 * @array: input array of strings
 * Return: head of linked list
 */
linked_l *generateLinkedList(char **array)
{
	register int i = 0;
	linked_l *head;

	head = NULL;
	while (array[i])
	{
		add_node_to_end(&head, array[i]);
		i++;
	}
	return (head);
}

/**
 * addNodeAtIndex - add node at index with string
 * @head: double pointer to head
 * @index: index to add at
 * @str: string to add
 * Return: address of node added
 */
linked_l *add_node_at_index(linked_l **head, int index, char *str)
{
	register int i = 0;
	linked_l *new_node, *current;
	char *new_str;

	current = *head;
	if (!str)
	{
		return (NULL);
	}
	new_node = malloc(sizeof(linked_l));
	if (!new_node)
	{
		perror("Malloc failed\n");
		exit(errno);
		free(new_node);
	}
	new_str = _strdup(str);
	if (!new_str)
	{
		perror("Malloc failed\n");
		exit(errno);
	}

	new_node->string = new_str;
	new_node->next = NULL;

	while (i < index - 1)
	{
		if (current->next == NULL)
		{
			return (NULL);
		}
		current = current->next;
		i++;
	}
	new_node->next = current->next;
	current->next = new_node;
	return (new_node);
}

/**
 * get_node_at_index - returns the nth node of a listint_t linked list
 * @head: pointer to head of list
 * @index: index of value to be returned
 * Return: address of node at input index
 */
char *get_node_at_index(linked_l *head, unsigned int index)
{
	register uint count = 0;
	linked_l *current;
	char *ptr;

	current = head;
	while (current)
	{
		if (count == index)
		{
			ptr = _strdup(current->string);
			return (ptr);
		}
		count++;
		current = current->next;
	}
	return (NULL);
}
