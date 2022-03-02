/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 22:41:56 by iltafah           #+#    #+#             */
/*   Updated: 2022/03/01 22:31:56 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iostream>
#include "../utils.hpp"

namespace ft
{

	template <typename T, typename nodePointer>
	class treeIter
	{
	public:
		typedef T iterator_type;
		typedef typename iterator_traits<iterator_type>::pointer pointer;
		typedef typename std::bidirectional_iterator_tag iterator_category;
		typedef typename iterator_traits<iterator_type>::reference reference;
		typedef typename iterator_traits<iterator_type>::value_type value_type;
		typedef typename iterator_traits<iterator_type>::difference_type difference_type;

	private:
		nodePointer _nodePtr;

	public:
		treeIter() : _nodePtr(NULL){};
		explicit treeIter(nodePointer it) : _nodePtr(it){};
		template <typename U, typename V>
		treeIter(const treeIter<U, V> &treeIterObj) : _nodePtr(treeIterObj.base()){};

	public:
		nodePointer base() const { return (_nodePtr); };
		reference operator*() const { return (_nodePtr->data); };
		pointer operator->() const { return &(operator*()); };
		treeIter &operator++()
		{
			_nodePtr = findInorderSuccessor(_nodePtr);
			return (*this);
		};
		treeIter operator++(int)
		{
			treeIter tempObj = *this;
			++(*this);
			return (tempObj);
		};
		treeIter &operator--()
		{
			_nodePtr = findInorderPredecessor(_nodePtr);
			return (*this);
		};
		treeIter operator--(int)
		{
			treeIter tempObj = *this;
			--(*this);
			return (tempObj);
		};

	private:
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
	};

	template <class T, class nodePointer>
	bool operator==(const treeIter<T, nodePointer> &lhs, const treeIter<T, nodePointer> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class T, class nodePointer>
	bool operator!=(const treeIter<T, nodePointer> &lhs, const treeIter<T, nodePointer> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

}

#endif
