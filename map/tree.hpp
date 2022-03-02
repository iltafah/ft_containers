/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:12:43 by iltafah           #+#    #+#             */
/*   Updated: 2022/03/01 23:14:04 by iltafah          ###   ########.fr       */
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
		nodePointer _root;
		nodePointer _end;
		allocator_type _alloc;
		key_compare _comp;
		size_type _size;

	public:
		tree(const key_compare &compare = key_compare(), const allocator_type &alloc = allocator_type())
			: _root(nullptr), _alloc(alloc), _comp(compare), _size(0)
		{
			this->_end = _alloc.allocate(1);
			_root = this->_end;
		}
		~tree()
		{
			_alloc.deallocate(_end, 1);
			_end = NULL;
		};

	public:
		nodePointer base() const { return (_root); }
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

			if (_root == _end)
			{
				_root = createNode(data);
				_end->left = _root;
				_root->parent = _end;
				insertedNode.first = _root;
				insertedNode.second = true;
				_size++;
				return (insertedNode);
			}
			_root->parent = NULL;
			insertedNode = insert(_root, data);
			_end->left = _root;
			_root->parent = _end;
			if (insertedNode.second == true)
				_size++;
			return (insertedNode);
		}

		ft::pair<nodePointer, bool> insert(nodePointer givenRoot, value_type newData)
		{
			nodePointer currNode = givenRoot;
			nodePointer parent = NULL;
			ft::pair<nodePointer, bool> insertedNode;

			while (currNode != NULL)
			{
				parent = currNode;
				if (currNode->data.first == newData.first)
					break ;
				if (_comp(newData, currNode->data))
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
			if (_comp(newData, parent->data))
			{
				parent->left = insertedNode.first;
				parent->left->parent = parent;
			}
			else
			{
				parent->right = insertedNode.first;
				parent->right->parent = parent;
			}
			updateBalanceFactorAfterInsert(insertedNode.first);
			return (insertedNode);
		}

		nodePointer find(nodePointer givenRoot, T data) const
		{
			nodePointer currNode = givenRoot;

			if (givenRoot == NULL)
				return (NULL);
			while (currNode)
			{
				if (currNode->data.first == data.first)
					return (currNode);
				else if (_comp(data, currNode->data))
					currNode = currNode->left;
				else
					currNode = currNode->right;
			}
			return (NULL);
		}

		nodePointer search(T data) const
		{
			return (find(_root, data));
		}

		void deleteLeafNode(nodePointer nodeToDelete)
		{
			nodePointer parent = nodeToDelete->parent;
			dir path;

			if (nodeToDelete == _root)
				_root = _end;
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
				_root->parent = NULL;
				updateBalanceFactorAfterDelete(parent, path);
				_root->parent = _end;
				_end->left = _root;
			}
			_alloc.deallocate(nodeToDelete, 1);
		}

		void deleteNodeWithOneChild(nodePointer nodeToDelete)
		{
			nodePointer parent = nodeToDelete->parent;
			nodePointer child = nodeToDelete->left != NULL ? nodeToDelete->left : nodeToDelete->right;
			dir path;

			if (nodeToDelete == _root)
				_root = child;
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
				_root->parent = NULL;
				updateBalanceFactorAfterDelete(parent, path);
				_root->parent = _end;
				_end->left = _root;
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
			_size--;
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
				_root = newRoot;
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
				_root = newRoot;
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
			_root->parent = NULL;
			nodePointer parent = currNode->parent;

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
			_root->parent = _end;
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

		size_type getSize() const { return (_size); }

		size_type getMaxSize() const { return (std::min<size_type>(_alloc.max_size(), std::numeric_limits<difference_type >::max()) ); }

		void clear()
		{
			clear(_root);
			_root = _end;
			_size = 0;
		}

		void clear(nodePointer node)
		{
			if (node == NULL || node == _end)
				return ;
			clear(node->left);
			clear(node->right);
			_alloc.deallocate(node, 1);
		}

		void swap(tree &anotherTree)
		{
			int sizeTmp = _size;
			key_compare cmpTmp = _comp;
			nodePointer endTmp = _end;
			nodePointer rootTmp = _root;
			allocator_type allocTmp = _alloc;

			this->_size = anotherTree._size;
			this->_comp = anotherTree._comp;
			this->_end = anotherTree._end;
			this->_root = anotherTree._root;
			this->_alloc = anotherTree._alloc;

			anotherTree._size = sizeTmp;
			anotherTree._comp = cmpTmp;
			anotherTree._end = endTmp;
			anotherTree._root = rootTmp;
			anotherTree._alloc = allocTmp;
		}

		nodePointer lowerBound(const value_type &val) const
		{
			nodePointer currNode = findMinimumNode(_root);

			while (currNode && _comp(currNode->data, val))
			{
				if (currNode->data.first == val.first)
					return (currNode);
				currNode = findInorderSuccessor(currNode);
			}
			return (currNode);
		}

		nodePointer upperBound(const value_type &val) const
		{
			nodePointer currNode = findMinimumNode(_root);

			while (!_comp(val, currNode->data))
			{
				currNode = findInorderSuccessor(currNode);
				if (currNode == _end)
					return (_end);
			}
			return (currNode);
		}

		/////////////////////Must be removed
		void print()
		{
			print(_root);
		}

		void print(nodePointer node)
		{
			print2D(node);
		}
	};
}

#endif
