/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:12:43 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/26 03:03:14 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include <iostream>
# include "../utils.hpp"

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
		allocator_type _alloc;
		key_compare comp;
		size_type size;

	public:
		tree(const key_compare &compare = key_compare(), const allocator_type &alloc = allocator_type())
			: root(nullptr), _alloc(alloc), comp(compare), size(0)
		{
			this->_end = _alloc.allocate(1);
			root = this->_end;
		}
		~tree(){};

	public:
		nodePointer base() const { return (root); }
		nodePointer end() const { return (_end); }

	public:
		nodePointer createNode(value_type data)
		{
			nodePointer newNode = _alloc.allocate(1);

			_alloc.construct(newNode, data);
			return (newNode);
		}

		ft::pair<nodePointer, bool> insert(value_type data)
		{
			ft::pair<nodePointer, bool> insertedNode;

			if (root == _end)
			{
				root = createNode(data);
				_end->left = root;
				root->parent = _end;
				insertedNode.first = root;
				insertedNode.second = true;
				size++;
				return (insertedNode);
			}
			root->parent = NULL;
			insertedNode = insert(root, data);
			_end->left = root;
			root->parent = _end;
			if (insertedNode.second == true)
				size++;
			return (insertedNode);
		}

		ft::pair<nodePointer, bool> insert(nodePointer root, value_type newData)
		{
			nodePointer currNode = root;
			nodePointer parent = NULL;
			ft::pair<nodePointer, bool> insertedNode;

			while (currNode != NULL)
			{
				parent = currNode;
				if (currNode->data.first == newData.first)
					break ;
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

		nodePointer find(nodePointer root, T data) const
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

		nodePointer search(T data) const
		{
			return (find(root, data));
		}

		void deleteLeafNode(nodePointer nodeToDelete)
		{
			nodePointer parent = nodeToDelete->parent;
			dir path;

			if (nodeToDelete == root)
				root = _end;
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
				root->parent = NULL;
				updateBalanceFactorAfterDelete(parent, path);
				root->parent = _end;
				_end->left = root;
			}
			_alloc.deallocate(nodeToDelete, 1);
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
				child->parent = parent;
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
				root->parent = NULL;
				updateBalanceFactorAfterDelete(parent, path);
				root->parent = _end;
				_end->left = root;
			}
			_alloc.deallocate(nodeToDelete, 1);
		}

		void deleteNodeWithTwoChilds(nodePointer nodeToDelete)
		{
			nodePointer successorNode = findInorderSuccessor(nodeToDelete);
			T successorData = successorNode->data;
			deleteNode(successorData);

			nodePointer parent = nodeToDelete->parent;
			nodePointer right = nodeToDelete->right;
			nodePointer left = nodeToDelete->left;
			int bf = nodeToDelete->bf;
			_alloc.construct(nodeToDelete, successorData);
			nodeToDelete->bf = bf;
			nodeToDelete->left = left;
			nodeToDelete->right = right;
			nodeToDelete->parent = parent;
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

			if (currNode->bf < -1 || currNode->bf > 1)
			{
				rebalance(currNode);
				return;
			}
			if (parent == NULL)
				return;

			if (currNode == parent->left)
				parent->bf += 1;
			else if (currNode == parent->right)
				parent->bf -= 1;

			if (parent->bf != 0)
				updateBalanceFactorAfterInsert(parent);
		}

		void updateBalanceFactorAfterDelete(nodePointer currNode, dir path)
		{
			root->parent = NULL;
			nodePointer parent = currNode->parent;
			// if (parent == NULL) // I wonder if I shall leave it, but within insert just leave it
			// 	return;
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
			root->parent = _end;
		}

		nodePointer findMinimumNode(nodePointer currNode) const
		{
			if (currNode == _end)
				return (_end);
			while (currNode->left)
				currNode = currNode->left;
			return (currNode);
		}

		nodePointer findMaximumNode(nodePointer currNode) const
		{
			if (currNode == _end)
				return (_end);
			while (currNode->right)
				currNode = currNode->right;
			return (currNode);
		}

		nodePointer findInorderSuccessor(nodePointer currNode) const
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

		nodePointer findInorderPredecessor(nodePointer currNode) const
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

		size_type getSize() const { return (size); }

		size_type getMaxSize() const { return (std::min<size_type>(_alloc.max_size(), std::numeric_limits<difference_type >::max()) ); }

		void clear()
		{
			clear(root);
			root = NULL;
			size = 0;
			if (_end != NULL)
			{
				_alloc.deallocate(_end, 1);
				_end = NULL;
			}
		}

		void clear(nodePointer root)
		{
			if (root == NULL || root == _end)
				return;
			clear(root->left);
			clear(root->right);
			_alloc.deallocate(root, 1);
		}

		void swap(tree &anotherTree)
		{
			int sizeTmp = size;
			key_compare cmpTmp = comp;
			nodePointer endTmp = _end;
			nodePointer rootTmp = root;
			allocator_type allocTmp = _alloc;

			this->size = anotherTree.size;
			this->comp = anotherTree.comp;
			this->_end = anotherTree._end;
			this->root = anotherTree.root;
			this->_alloc = anotherTree._alloc;

			anotherTree.size = sizeTmp;
			anotherTree.comp = cmpTmp;
			anotherTree._end = endTmp;
			anotherTree.root = rootTmp;
			anotherTree._alloc = allocTmp;
		}

		nodePointer lowerBound(const value_type &val) const	//this on need to be checked does it return end or not
		{
			nodePointer currNode = findMinimumNode(root);

			while (currNode && comp(currNode->data, val))
			{
				if (currNode->data.first == val.first)
					return (currNode);
				currNode = findInorderSuccessor(currNode);
			}
			return (currNode);
		}

		nodePointer upperBound(const value_type &val) const
		{
			nodePointer currNode = findMinimumNode(root);

			while (!comp(val, currNode->data))
			{
				currNode = findInorderSuccessor(currNode);
				if (currNode == _end)	//I wonder if findinorderSuccessor will return NULL
					return (_end);
			}
			return (currNode);
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
}

#endif
