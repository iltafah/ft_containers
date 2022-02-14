/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:12:43 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/14 17:24:43 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include "print.hpp"

enum dir
{
	LEFT,
	RIGHT
};

template <typename T>
struct Node
{
	T data;
	Node *parent;
	Node *left;
	Node *right;
	int bf;
	Node(T givenData) : data(givenData), parent(0), left(0), right(0), bf(0){};
};

template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<Node<T> > >
class AVL
{
public:
	typedef Node<T> *nodePointer;
	typedef Alloc allocator_type;

private:
	// nodePointer root;
	Compare value_compare;
	allocator_type alloc;

public:
	AVL() : root(NULL){};
	~AVL(){};

public:
	nodePointer root;

	nodePointer createNode(T data)
	{
		nodePointer newNode = alloc.allocate(1);

		alloc.construct(newNode, data);
		return (newNode);
	}

	nodePointer insert(T data)
	{
		nodePointer newNode = createNode(data);

		if (root == NULL)
		{
			root = newNode;
			root->data = data;
		}
		else
			insert(root, newNode);
		return (newNode);
	}

	void insert(nodePointer root, nodePointer newNode)
	{
		nodePointer currNode = root;
		nodePointer parent = NULL;

		while (currNode != NULL)
		{
			parent = currNode;
			if (value_compare(newNode->data, currNode->data))
				currNode = currNode->left;
			else
				currNode = currNode->right;
		}
		if (value_compare(newNode->data, parent->data))
		{
			parent->left = newNode;
			parent->left->parent = parent;
		}
		else
		{
			parent->right = newNode;
			parent->right->parent = parent;
		}
		// Time for balancing
		updateBalanceFactorAfterInsert(newNode);
	}

	nodePointer find(nodePointer root, T data)
	{
		nodePointer found;

		if (root == NULL)
			return (NULL);
		while (root)
		{
			found = root;
			if (root->data == data)
				return (found);
			else if (value_compare(data, root->data))
				root = root->left;
			else
				root = root->right;
		}
		return (NULL);
	}

	nodePointer search(T data)
	{
		return (find(root, data));
	}

	void deleteLeafNode(nodePointer nodeToDelete)
	{
		nodePointer parent = nodeToDelete->parent;
		dir	path;

		if (nodeToDelete == root)
			root = NULL;
		else
		{
			if (parent->left == nodeToDelete)
			{
				path = LEFT;
				parent->left = NULL;
			}
			else if (parent->right == nodeToDelete)
			{
				path = RIGHT;
				parent->right = NULL;
			}
		}
		updateBalanceFactorAfterDelete(parent, path);
		alloc.deallocate(nodeToDelete, 1);
	}

	void deleteNodeWithOneChild(nodePointer nodeToDelete)
	{
		nodePointer parent = nodeToDelete->parent;
		nodePointer child = nodeToDelete->left != NULL ? nodeToDelete->left : nodeToDelete->right;
		dir path;

		if (nodeToDelete == root)
			root = child;
		else
		{
			if (parent->left == nodeToDelete)
			{
				path = LEFT;
				parent->left = child;
			}
			else if (parent->right == nodeToDelete)
			{
				path = RIGHT;
				parent->right = child;
			}
		}
		updateBalanceFactorAfterDelete(parent, path);
		alloc.deallocate(nodeToDelete, 1);
	}

	void deleteNodeWithTwoChilds(nodePointer nodeToDelete)
	{
		nodePointer successorNode = findInorderSuccessor(nodeToDelete);

		T successorData = successorNode->data;
		deleteNode(successorData);
		nodeToDelete->data = successorData;
	}

	void deleteNode(T data)
	{
		nodePointer nodeToDelete = search(data);

		if (nodeToDelete == NULL)
			return;
		if (!nodeToDelete->left && !nodeToDelete->right)
			deleteLeafNode(nodeToDelete);
		else if (!nodeToDelete->left || !nodeToDelete->right)
			deleteNodeWithOneChild(nodeToDelete);
		else
			deleteNodeWithTwoChilds(nodeToDelete);
	}

	void leftRotate(nodePointer currNode)
	{
		nodePointer oldRoot;
		nodePointer newRoot;

		oldRoot = currNode;
		newRoot = currNode->right;
		oldRoot->right = newRoot->left;
		if (newRoot->left != NULL)
			newRoot->left->parent = oldRoot;
		newRoot->parent = oldRoot->parent;
		if (oldRoot->parent == NULL)
			root = newRoot;
		else
		{
			if (oldRoot == oldRoot->parent->right)
				oldRoot->parent->right = newRoot;
			else if (oldRoot == oldRoot->parent->left)
				oldRoot->parent->left = newRoot;
		}
		newRoot->left = oldRoot;
		oldRoot->parent = newRoot;
		oldRoot->bf = oldRoot->bf + 1 - std::min(newRoot->bf, 0);
		newRoot->bf = newRoot->bf + 1 + std::max(oldRoot->bf, 0);
	}

	void rightRotate(nodePointer currNode)
	{
		nodePointer oldRoot;
		nodePointer newRoot;

		oldRoot = currNode;
		newRoot = currNode->left;
		oldRoot->left = newRoot->right;
		if (newRoot->right != NULL)
			newRoot->right->parent = oldRoot;
		newRoot->parent = oldRoot->parent;
		if (oldRoot->parent == NULL)
			root = newRoot;
		else
		{
			if (oldRoot == oldRoot->parent->right)
				oldRoot->parent->right = newRoot;
			else if (oldRoot == oldRoot->parent->left)
				oldRoot->parent->left = newRoot;
		}
		newRoot->right = oldRoot;
		oldRoot->parent = newRoot;
		oldRoot->bf = oldRoot->bf - 1 - std::max(newRoot->bf, 0);
		newRoot->bf = newRoot->bf - 1 + std::min(oldRoot->bf, 0);
	}

	void rebalance(nodePointer currNode)
	{
		if (currNode->bf < 0)
		{
			nodePointer rightChild = currNode->right;
			if (rightChild->bf > 0)
			{
				rightRotate(rightChild);
				leftRotate(currNode);
			}
			else
				leftRotate(currNode);
		}
		else if (currNode->bf > 0)
		{
			nodePointer leftChild = currNode->left;
			if (leftChild->bf < 0)
			{
				leftRotate(leftChild);
				rightRotate(currNode);
			}
			else
				rightRotate(currNode);
		}
	}

	void updateBalanceFactorAfterInsert(nodePointer currNode)
	{
		nodePointer parent = currNode->parent;

		if (parent == NULL)
			return ;
		if (currNode->bf < -1 || currNode->bf > 1)
		{
			rebalance(currNode);
			return;
		}
		if (parent != NULL)
		{
			if (currNode == parent->left)
				parent->bf += 1;
			else if (currNode == parent->right)
				parent->bf -= 1;
		}
		if (parent->bf != 0)
			updateBalanceFactorAfterInsert(parent);
	}

	void updateBalanceFactorAfterDelete(nodePointer currNode, dir path)
	{
		nodePointer parent = currNode->parent;
		
		if (parent == NULL)//I wonder if I shall leave it, but within insert just leave it
			return ;
		if (currNode != NULL)
		{
			if (path == RIGHT)
				currNode->bf += 1;
			else if (path == LEFT)
				currNode->bf -= 1;
		}
		if (currNode->bf < -1 || currNode->bf > 1)
		{
			rebalance(currNode);
			return;
		}
		if (parent != NULL)
		{
			if (parent->bf == 0)
			{
				if (parent->left == currNode)
					updateBalanceFactorAfterDelete(parent, LEFT);
				else if (parent->right == currNode)
					updateBalanceFactorAfterDelete(parent, RIGHT);
			}
		}
	}

	nodePointer findMinimumNode(nodePointer currNode)
	{
		while (currNode->left)
			currNode = currNode->left;
		return (currNode);
	}

	nodePointer findMaximumNode(nodePointer currNode)
	{
		while (currNode->right)
			currNode = currNode->right;
		return (currNode);
	}

	nodePointer findInorderSuccessor(nodePointer currNode)
	{
		nodePointer rightChild = currNode->right;

		if (rightChild != NULL)
			return (findMinimumNode(rightChild));

		nodePointer parent = currNode->parent;
		while (parent != NULL)
		{
			if (currNode == parent->left)
				break ;
			currNode = parent;
			parent = parent->parent;
		}
		return (parent);
	}

	nodePointer findInorderPredecessor(nodePointer currNode)
	{
		nodePointer leftChild = currNode->left;

		if (leftChild != NULL)
			return (findMaximumNode(leftChild));

		nodePointer parent = currNode->parent;
		while (parent != NULL)
		{
			if (currNode == parent->right)
				break ;
			currNode = parent;
			parent = parent->parent;
		}
		return (parent);
	}

	void print()
	{
		print(root);
	}

	void print(nodePointer root)
	{
		print2D(root);
	}

};

#endif
