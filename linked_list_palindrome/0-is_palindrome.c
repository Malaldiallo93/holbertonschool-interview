#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * is_palindrome - test if a linked list is a palindrome
 * @head: pointer to pointer of first node in linked list
 * Return: 0 if not, 1 if it is a palindrome
 */
int is_palindrome(listint_t **head)
{
	listint_t *slow = *head;
	listint_t *fast = *head;
	listint_t *stack = NULL;

	if (*head == NULL || (*head)->next == NULL)
	{
		return (1);
	}

	while (fast != NULL && fast->next != NULL)
	{
		push(&stack, slow->n);
		slow = slow->next;
		fast = fast->next->next;
	}

	/* if linked list is odd */
	if (fast != NULL)
	{

		slow = slow->next;
	}

	while (slow != NULL)
	{
		if (pop(&stack) != slow->n)
		{
			free(stack);
			return (0);
		}
		slow = slow->next;
	}
	free(stack);
	return (1);
}

/**
 * push - pushes an element on top of stack
 * @stack: pointer to pointer to the top of the stack
 * @n: data to be pushed onto the stack
 */
void push(listint_t **stack, int n)
{
	listint_t *new_node = malloc(sizeof(listint_t));

	if (new_node == NULL)
	{
		exit(EXIT_FAILURE);
	}

	new_node->n = n;
	new_node->next = *stack;
	*stack = new_node;
}
/**
 * pop - pops an element from the top of the stack
 * @stack: pointer to pointer to the top of the stack
 * Return: data of the popped element
 */
int pop(listint_t **stack)
{
listint_t *temp;
int n;

if (*stack == NULL)
{
exit(EXIT_FAILURE);
}

temp = *stack;
n = temp->n;

*stack = (*stack)->next;
free(temp);

return (n);
}

