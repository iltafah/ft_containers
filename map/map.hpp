/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:55:21 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/20 23:35:13 by iltafah          ###   ########.fr       */
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
// #include "./map_iterator.hpp"
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
       			const allocator_type& alloc = allocator_type()) {};

		map (const map& x) {};

		~map() {};

	public:
		void /* pair<iterator,bool>*/ insert(const value_type &val)
		{
			_tree.insert(val);
		}

		iterator insert (iterator position, const value_type& val)
		{
			
		};

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			
		};

	public:
		iterator begin() { return (iterator(_tree.findMinimumNode(_tree.base()))); };
		const_iterator begin() const { return (iterator(_tree.findMinimumNode(_tree.base()))); };
		// iterator end() { return (iterator(_tree.findMaximumNode(_tree.base()))); };
		// const_iterator end() const { return (iterator(_tree.findMaximumNode(_tree.base()))); };
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;

	public:
		bool empty() const {};
		size_type size() const {};
		size_type max_size() const {};

	public:
		mapped_type& operator[] (const key_type& k) {};
		map& operator= (const map& x) {};

	public:
		key_compare key_comp() const { return (_compare); };
		value_compare value_comp() const { return (value_compare(_compare)); };

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
