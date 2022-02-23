/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:55:21 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/22 23:47:22 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP
#include <memory>
#include <algorithm>
#include <iostream>
#include <utility>
#include <functional>
#include <cstddef>
#include "tree.hpp"
#include "tree_iterator.hpp"
// #include "utills.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;
		// typedef	/*??*/ iterator;
		// typedef	/*??*/ const_iterator;
		// typedef	/*??*/ reverse_iterator;
		// typedef	/*??*/ const_reverse_iterator;
		// typedef iterator_traits<iterator>::difference_type difference_type;

	public:
		class value_compare
		{
			friend class map;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

	private:
		typedef typename ft::tree<value_type, value_compare, allocator_type> tree;
		typedef typename ft::Node<value_type> node;
		typedef node *nodePointer;

	public:
		typedef treeIter<pointer, nodePointer> iterator;
		typedef treeIter<const_pointer, nodePointer> const_iterator;
		// typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		// typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		tree _tree;
		allocator_type _alloc;
		key_compare _compare;

	public:
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _tree(value_compare(comp), alloc), _alloc(alloc), _compare(comp) {};

		template <class InputIterator>
  		map (InputIterator first, InputIterator last,
       		const key_compare& comp = key_compare(),
       			const allocator_type& alloc = allocator_type())
		{
			insert(first, last);
		};

		map (const map& x)
			: _tree(value_compare(x._compare), x._alloc), _alloc(x._alloc), _compare(x._compare)
		{
			*this = x;
		};

		~map()
		{
			clear();
		};

	public:
		std::pair<iterator,bool> insert(const value_type &val)
		{
			std::pair<nodePointer, bool> insertedNode = _tree.insert(val);

			return (std::pair<iterator, bool>(iterator(insertedNode.first), insertedNode.second));
		}

		iterator insert (iterator position, const value_type& val)
		{
			std::pair<nodePointer, bool> insertedNode = _tree.insert(val);
			
			return (iterator(insertedNode.first));
		};

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_tree.insert(*first);
				first++;
			}
		};

		void erase (iterator position) 
		{
			_tree.deleteNode(std::make_pair((*position).first, (*position).second));
		};

		size_type erase (const key_type& k)
		{
			if (_tree.deleteNode(std::make_pair(k, mapped_type())) == true)
				return (1);
			return (0);
		};

		void erase (iterator first, iterator last)
		{
			iterator toDelete;

			while (first != last)
			{
				toDelete = first;
				first++;
				erase(toDelete);
			}
		};

		void swap (map& x)
		{
			_tree.swap();
		};

		void clear()
		{
			_tree.clear();
		};

	public:
		iterator begin() { return (iterator(_tree.findMinimumNode(_tree.base()))); }
		const_iterator begin() const { return (iterator(_tree.findMinimumNode(_tree.base()))); }
		iterator end() { return (iterator(_tree.end())); }
		const_iterator end() const { return (iterator(_tree.end())); }
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;

	public:
		bool empty() const { return (_tree.getSize() == 0); };
		size_type size() const { return (_tree.getSize()); };
		size_type max_size() const {};

	public:
		mapped_type& operator[] (const key_type& k)
		{ 
			return ((*((this->insert(std::make_pair(k,mapped_type()))).first)).second); 
		};
		map& operator= (const map& x)
		{
			if (this != &x)
				insert(x.begin(), x.end());
			return (*this);
		};

	public:
		key_compare key_comp() const { return (_compare); };
		value_compare value_comp() const { return (value_compare(_compare)); };

	public:
		iterator find (const key_type& k)
		{
			nodePointer node = _tree.search(std::make_pair(k, mapped_type()));
			if (node == NULL)
				return (end());
			return (iterator(node));
		};
		const_iterator	find (const key_type& k) const
		{
			nodePointer node = _tree.search(std::make_pair(k, mapped_type()));
			if (node == NULL)
				return (end());
			return (const_iterator(node));
		};

		size_type	count (const key_type& k) const
		{
			return ( find(k) != end() ? 1 : 0 );
		};

		iterator	lower_bound (const key_type& k)
		{
			return (iterator(_tree.lowerBound(std::make_pair(k, mapped_type()))));
		};

		const_iterator	lower_bound (const key_type& k) const
		{
			return (const_iterator(_tree.lowerBound(std::make_pair(k, mapped_type()))));
		};

		iterator	upper_bound (const key_type& k)
		{
			iterator(_tree.upperBound(std::make_pair(k, mapped_type())));
		};

		const_iterator	upper_bound (const key_type& k) const
		{
			const_iterator(_tree.upperBound(std::make_pair(k, mapped_type())));
		};

		std::pair<iterator, iterator>	equal_range (const key_type& k)
		{
			return (std::make_pair(lower_bound(k), upper_bound(k)));
		};

		std::pair<const_iterator, const_iterator>	equal_range (const key_type& k) const
		{
			return (std::make_pair(lower_bound(k), upper_bound(k)));
		};

	public:
		allocator_type get_allocator() const { return (_alloc); };

	public:
		void print()
		{
			_tree.print();
		}
	};
}

#endif

// #ifndef MAP_HPP
// #define MAP_HPP

// #include <iostream>
// #include "./tree.hpp"

// namespace ft
// {
// 	template <class Key,											 // map::key_type
// 			  class T,												 // map::mapped_type
// 			  class Compare = std::less<Key>,						 // map::key_compare
// 			  class Alloc = std::allocator<std::pair<const Key, T> > // map::allocator_type
// 			  >
// 	class map
// 	{
// 	public:
// 		typedef Key key_type;
// 		typedef T mapped_type;
// 		typedef std::pair<const key_type, mapped_type> value_type;
// 		typedef Compare key_compare;
// 		typedef Alloc allocator_type;
// 		typedef typename allocator_type::reference reference;
// 		typedef typename allocator_type::const_reference const_reference;
// 		typedef typename allocator_type::pointer pointer;
// 		typedef typename allocator_type::const_pointer const_pointer;
// 		// typedef	/*??*/ iterator;
// 		// typedef	/*??*/ const_iterator;
// 		// typedef	/*??*/ reverse_iterator;
// 		// typedef	/*??*/ const_reverse_iterator;
// 		// typedef iterator_traits<iterator>::difference_type difference_type;
// 		typedef size_t size_type;

// 	public:
// 		class value_compare
// 		{
// 			friend class map;

// 		protected:
// 			Compare comp;
// 			value_compare(Compare c) : comp(c) {}

// 		public:
// 			typedef bool result_type;
// 			typedef value_type first_argument_type;
// 			typedef value_type second_argument_type;
// 			bool operator()(const value_type &x, const value_type &y) const
// 			{
// 				return comp(x.first, y.first);
// 			}
// 		};

// 	private:
// 		typedef typename ft::AVL<value_type, key_compare, allocator_type> Tree;
// 		typedef Node<value_type> node;
// 		typedef Node<value_type> *nodePtr;
