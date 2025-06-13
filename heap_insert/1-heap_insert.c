#include "binary_trees.h"
#include <stdlib.h>

/**
 * heapify_up - Maintains the max-heap property by swapping with parents
 * @node: Pointer to the inserted node
 *
 * Return: Final position of the node after heapifying
 */
heap_t *heapify_up(heap_t *node)
{
	int tmp;

	while (node->parent && node->n > node->parent->n)
	{
		tmp = node->n;
		node->n = node->parent->n;
		node->parent->n = tmp;
		node = node->parent;
	}

	return (node);
}

/**
 * find_insert_parent - Finds the first available parent node in level order
 * @root: Pointer to the root of the heap
 *
 * Return: Pointer to the parent node where the new node should be inserted
 */
heap_t *find_insert_parent(heap_t *root)
{
	heap_t *queue[1024];
	int front = 0, rear = 0;

	queue[rear++] = root;

	while (front < rear)
	{
		heap_t *curr = queue[front++];

		if (!curr->left || !curr->right)
			return (curr);

		queue[rear++] = curr->left;
		queue[rear++] = curr->right;
	}

	return (NULL);
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Double pointer to the root of the heap
 * @value: Value to insert
 *
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
