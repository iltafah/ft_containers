/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:12:43 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/12 19:36:32 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include <iostream>

template <typename T>
struct Node
{
	T		data;
	Node	*parent;
	Node	*left;
	Node	*right;
	int		bf;
	Node(T givenData) : data(givenData), parent(0), left(0), right(0), bf(0) {};
};

template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<Node<T> > >
class AVL
{
	public:
		typedef Node<T>* nodePointer;
		typedef Alloc allocator_type;

	private:
		// nodePointer root;
		Compare value_compare;
		allocator_type alloc;

	public:
		AVL() : root(NULL) {};
		~AVL(){};

	public:
		nodePointer root;
		nodePointer createNode(T data)
		{
			nodePointer newNode = alloc.allocate(1);
			alloc.construct(newNode, data);
			return (newNode);
		}

		void insert(T data)
		{
			nodePointer newNode = createNode(data);
			if (root == NULL)
			{
				root = newNode;
				root->data = data;
			}
			else
				insert(root, newNode);
		}

		void insert(nodePointer root, nodePointer newNode)
		{
			nodePointer	currNode = root;
			nodePointer	parent = NULL;

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
			//Time for balancing
			updateBalanceFactor(newNode);
		}

		void	leftRotate(nodePointer currNode)
		{
			nodePointer oldRoot;
			nodePointer newRoot;

			oldRoot = currNode;
			newRoot = currNode->right;
			if (newRoot->left != NULL)
			{
				oldRoot->right = newRoot->left;
				newRoot->left->parent = oldRoot;
			}
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
			oldRoot.balanceFactor = oldRoot.balanceFactor + 1 - std::min(newRoot.balanceFactor, 0);
    		newRoot.balanceFactor = newRoot.balanceFactor + 1 + std::max(oldRoot.balanceFactor, 0);
		}

		void	rightRotate(nodePointer currNode)
		{
			nodePointer oldRoot;
			nodePointer newRoot;

			oldRoot = currNode;
			newRoot = currNode->left;
			if (newRoot->right != NULL)
			{
				oldRoot->left = newRoot->right;
				newRoot->right->parent = oldRoot;
			}
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
			oldRoot.balanceFactor = oldRoot.balanceFactor + 1 - std::min(newRoot.balanceFactor, 0);
    		newRoot.balanceFactor = newRoot.balanceFactor + 1 + std::max(oldRoot.balanceFactor, 0);
		}

		void	rebalance(nodePointer currNode)
		{
			if (currNode->bf < 0)
			{
				nodePointer rightChild = currNode->right;
				if (rightChild->bf > 0)
				{

				}
				else
			}
			else if (currNode->bf > 0)
			{
				nodePointer leftChild = currNode->left;
				if (leftChild->bf < 0)
				{

				}
				else
			}
		}

		void	updateBalanceFactor(nodePointer currNode)
		{
			nodePointer parent = currNode->parent;

			if (currNode->bf < -1 || currNode->bf > 1)
				rebalance(currNode);

			if (parent != NULL)
			{
				if (currNode == parent->left)
					parent->bf += 1;
				else if (currNode == parent->right)
					parent->bf -= 1;
			}

			if (parent.bf != 0)
				updateBalanceFactor(parent);
		}

		nodePointer	find(nodePointer root, T data)
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

		void	deleteLeafNode(nodePointer nodeToDelete)
		{
			nodePointer parent = nodeToDelete->parent;
			if (nodeToDelete == root)
				root = NULL;
			else
			{
				if (parent->left == nodeToDelete)
					parent->left = NULL;
				else if (parent->right == nodeToDelete)
					parent->right = NULL;
			}
			alloc.deallocate(nodeToDelete, 1);
		}

		void deleteNodeWithOneChild(nodePointer nodeToDelete)
		{
			nodePointer parent = nodeToDelete->parent;
			nodePointer child = nodeToDelete->left != NULL ? nodeToDelete->left : nodeToDelete->right;

			if (nodeToDelete == root)
				root = child;
			else
			{
				if (parent->left == nodeToDelete)
					parent->left = child;
				else if (parent->right == nodeToDelete)
					parent->right = child;
			}
			alloc.deallocate(nodeToDelete, 1);
		}

		void	deleteNode(T data)
		{
			nodePointer nodeToDelete = find(root, data);
			if (nodeToDelete == NULL)
				return ;
			if (!nodeToDelete->left && !nodeToDelete->right)
				deleteLeafNode(nodeToDelete);
			else if (!nodeToDelete->left || !nodeToDelete->right)
				deleteNodeWithOneChild(nodeToDelete);
			// else
			// 	deleteNodeWithTwoChilds();
		}

		void print(nodePointer root)
		{
			if (root == NULL)
				return ;
			std::cout << root->data << std::endl;
			print(root->left);
			print(root->right);
		}
};

#endif
