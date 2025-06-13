#include "binary_trees.h"
#include <stdlib.h>

/**
 * heapify_up - Restores the Max Heap property by bubbling up the node
 * @node: The node to heapify
 * Return: The final position of the node
 */
heap_t *heapify_up(heap_t *node)
{
	int temp;

	while (node->parent && node->n > node->parent->n)
	{
		temp = node->n;
		node->n = node->parent->n;
		node->parent->n = temp;
		node = node->parent;
	}
	return (node);
}

/**
 * find_insert_parent - Finds the parent node where the new node should be inserted
 * @root: The root of the heap
 * Return: Pointer to the parent node
 */
heap_t *find_insert_parent(heap_t *root)
{
	heap_t *queue[1024];  /* Simple BFS queue, assuming < 1024 nodes */
	int front = 0, rear = 0;

	queue[rear++] = root;

	while (front < rear)
	{
		heap_t *current = queue[front++];

		if (!current->left || !current->right)
			return (current);

		queue[rear++] = current->left;
		queue[rear++] = current->right;
	}
	return (NULL);
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 * @value: The value to insert
 * Return: Pointer to the inserted node or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *parent;

	if (!root)
		return (NULL);

	if (*root == NULL)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	parent = find_insert_parent(*root);
	if (!parent)
		return (NULL);

	new_node = binary_tree_node(parent, value);
	if (!new_node)
		return (NULL);

	if (!parent->left)
		parent->left = new_node;
	else
		parent->right = new_node;

	return (heapify_up(new_node));
}
