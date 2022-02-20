/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 22:41:56 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/20 22:37:58 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iostream>

template <typename Iterator>
struct iterator_traits
{
	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template <typename T>
struct iterator_traits<T *>
{
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;
	typedef std::bidirectional_iterator_tag iterator_category;
};

template <typename T>
struct iterator_traits<const T *>
{
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef const T *pointer;
	typedef const T &reference;
	typedef std::bidirectional_iterator_tag iterator_category;
};

template <typename T, typename nodePointer>
class treeIter
{
public:
	typedef T iterator_type;
	typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type value_type;
	typedef typename iterator_traits<iterator_type>::difference_type difference_type;
	typedef typename iterator_traits<iterator_type>::pointer pointer;
	typedef typename iterator_traits<iterator_type>::reference reference;

private:
	nodePointer _nodePtr;

public:
	treeIter() : _nodePtr(NULL){};
	explicit treeIter(nodePointer it) : _nodePtr(it){};
	template <typename U, typename V>
		treeIter(const treeIter<U, V> &treeIterObj) : _nodePtr(treeIterObj._nodePtr){};

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

// template <class Iterator>
// bool operator==(const treeIter<Iterator> &lhs, const treeIter<Iterator> &rhs)
// {
// 	return (lhs.base() == rhs.base());
// }

// template <class Iterator>
// bool operator!=(const treeIter<Iterator> &lhs, const treeIter<Iterator> &rhs)
// {
// 	return (lhs.base() != rhs.base());
// }

// template <class Iterator>
// bool operator<(const treeIter<Iterator> &lhs, const treeIter<Iterator> &rhs)
// {
// 	return (lhs.base() < rhs.base());
// }

// template <class Iterator>
// bool operator<=(const treeIter<Iterator> &lhs, const treeIter<Iterator> &rhs)
// {
// 	return (lhs.base() <= rhs.base());
// }

// template <class Iterator>
// bool operator>(const treeIter<Iterator> &lhs, const treeIter<Iterator> &rhs)
// {
// 	return (lhs.base() > rhs.base());
// }

// template <class Iterator>
// bool operator>=(const treeIter<Iterator> &lhs, const treeIter<Iterator> &rhs)
// {
// 	return (lhs.base() >= rhs.base());
// }

// template <class Iterator>
// typename treeIter<Iterator>::difference_type operator-(
// 	const treeIter<Iterator> &lhs,
// 	const treeIter<Iterator> &rhs)
// {
// 	return (lhs.base() - rhs.base());
// }

// template <class Iterator>
// treeIter<Iterator> operator+(
// 	typename treeIter<Iterator>::difference_type n,
// 	const treeIter<Iterator> &rev_it)
// {
// 	return (lhs.base() + rhs.base());
// }

#endif
