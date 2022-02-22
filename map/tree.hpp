/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:12:43 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/21 21:52:12 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP
#include <memory>
#include <iostream>
#include <algorithm>
#include <utility>
#include "print.hpp"

namespace ft
{
	enum dir
	{
		LEFT,
		RIGHT
	};

    template <class T>
    struct Node
    {
        T data;
        Node<T> *left;
        Node<T> *right;
        Node<T> *parent;
        int bf;
        Node(const T &data) : data(data), left(NULL), right(NULL), parent(NULL), bf(0){};
    };

    template <class T, class Compare, class Alloc>
    class tree
    {
    public:
        typedef T value_type;
        typedef Compare key_compare;
        typedef size_t size_type;
        typedef Node<value_type> node;
        typedef Node<value_type> *nodePointer;
        typedef typename Alloc::template rebind<node>::other allocator_type;
        typedef ptrdiff_t difference_type;

    private:
        nodePointer root;
        nodePointer _end;
        allocator_type alloc;
        key_compare comp;
        size_type size;

    public:
        tree(const key_compare &compare = key_compare(), const allocator_type &alloc = allocator_type())
            : root(nullptr), alloc(alloc), comp(compare), size(0)
        {
            //this->_end = _alloc.allocate(1); // allocate the end node
           // this->_end = NULL;
        }
        ~tree(){};

	public:
		nodePointer base() const { return (root); };

// #ifndef TREE_HPP
// #define TREE_HPP

// #include <iostream>
// #include "print.hpp"

// namespace ft
// {
// 	enum dir
// 	{
// 		LEFT,
// 		RIGHT
// 	};

// 	template <typename T>
// 	struct Node
// 	{
// 		T data;
// 		Node *parent;
// 		Node *left;
// 		Node *right;
// 		int bf;
// 		Node(T givenData) : data(givenData), parent(0), left(0), right(0), bf(0){};
// 	};

// 	template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<Node<T> > >
// 	class AVL
// 	{
// 	public:
// 		typedef T value_type;
// 		typedef Compare key_compare;
// 		typedef Node<value_type> node;
// 		typedef	node* nodePtr;
// 		typedef node* nodePointer;
// 		typedef typename Alloc::template rebind<node >::other allocator_type;
// 		// typedef Alloc allocator_type;

// 	private:
// 		nodePointer root;
// 		Compare value_compare;
// 		allocator_type alloc;

// 	public:
// 		// AVL() : root(NULL){};
// 		AVL(const Compare &cmp = Compare(), const allocator_type &allocator = Alloc()) : value_compare(cmp), alloc(allocator) {};
// 		~AVL(){};

	public:
		nodePointer createNode(value_type data)
		{
			nodePointer newNode = alloc.allocate(1);

			alloc.construct(newNode, data);
			return (newNode);
		}

		std::pair<nodePointer, bool> insert(value_type data)
		{
			std::pair<nodePointer, bool> insertedNode;

			if (root == NULL)
			{
				root = createNode(data);
				insertedNode.first = root;
				insertedNode.second = true;
				return (insertedNode);
			}
			insertedNode = insert(root, data);
			if (insertedNode.second == true)
				size++;
			return (insertedNode);
		}

		std::pair<nodePointer, bool> insert(nodePointer root, value_type newData)
		{
			nodePointer currNode = root;
			nodePointer parent = NULL;
			std::pair<nodePointer, bool> insertedNode;

			while (currNode != NULL)
			{
				parent = currNode;
				if (comp(newData, currNode->data))
					currNode = currNode->left;
				else
					currNode = currNode->right;
			}
			if (parent->data.first == newData.first)
			{
				insertedNode.first = parent;
				insertedNode.second = false;
				return insertedNode;
			}
			insertedNode.first = createNode(newData);
			insertedNode.second = true;
			if (comp(newData, parent->data))
			{
				parent->left = insertedNode.first;
				parent->left->parent = parent;
			}
			else
			{
				parent->right = insertedNode.first;
				parent->right->parent = parent;
			}
			// Time for balancing
			updateBalanceFactorAfterInsert(insertedNode.first);
			return (insertedNode);
		}

		nodePointer find(nodePointer root, T data)
		{
			nodePointer currNode = root;

			if (root == NULL)
				return (NULL);
			while (currNode)
			{
				if (currNode->data.first == data.first)
					return (currNode);
				else if (comp(data, currNode->data))
					currNode = currNode->left;
				else
					currNode = currNode->right;
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
			dir path;

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

			nodePointer right = nodeToDelete->right;
			nodePointer left = nodeToDelete->left;
			alloc.construct(nodeToDelete, successorData);
			nodeToDelete->right = right;
			nodeToDelete->left = left;
			// nodeToDelete->data = successorData;
		}

		bool deleteNode(T data)
		{
			nodePointer nodeToDelete = search(data);

			if (nodeToDelete == NULL)
				return (false);
			if (!nodeToDelete->left && !nodeToDelete->right)
				deleteLeafNode(nodeToDelete);
			else if (!nodeToDelete->left || !nodeToDelete->right)
				deleteNodeWithOneChild(nodeToDelete);
			else
				deleteNodeWithTwoChilds(nodeToDelete);
			size--;
			return (true);
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
				return;
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

			if (parent == NULL) // I wonder if I shall leave it, but within insert just leave it
				return;
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
					break;
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
					break;
				currNode = parent;
				parent = parent->parent;
			}
			return (parent);
		}

		size_type getSize() { return (size); }

		void print()
		{
			print(root);
		}

		void print(nodePointer root)
		{
			print2D(root);
		}
	};
}

#endif
