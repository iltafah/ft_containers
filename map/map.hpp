/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:55:21 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/26 00:34:11 by iltafah          ###   ########.fr       */
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

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

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
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		tree _tree;
		allocator_type _alloc;
		key_compare _compare;

	public:
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _tree(value_compare(comp), alloc), _alloc(alloc), _compare(comp){};

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _tree(value_compare(comp), alloc), _alloc(alloc), _compare(comp)
		{
			insert(first, last);
		};

		map(const map &x)
			: _tree(value_compare(x._compare), x._alloc), _alloc(x._alloc), _compare(x._compare)
		{
			*this = x;
		};

		~map()
		{
			clear();
		};

	public:
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			ft::pair<nodePointer, bool> insertedNode = _tree.insert(val);

			return (ft::pair<iterator, bool>(iterator(insertedNode.first), insertedNode.second));
		}
		iterator insert(iterator position, const value_type &val)
		{
			ft::pair<nodePointer, bool> insertedNode = _tree.insert(val);

			return (iterator(insertedNode.first));
		};
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_tree.insert(*first);
				first++;
			}
		};

		void erase(iterator position)
		{
			_tree.deleteNode(ft::make_pair((*position).first, (*position).second));
		};
		size_type erase(const key_type &k)
		{
			if (_tree.deleteNode(ft::make_pair(k, mapped_type())) == true)
				return (1);
			return (0);
		};
		void erase(iterator first, iterator last)
		{
			iterator toDelete;

			while (first != last)
			{
				toDelete = first;
				first++;
				erase(toDelete);
			}
		};

		void swap(map &x)
		{
			_tree.swap(x._tree);
		};

		void clear()
		{
			_tree.clear();
		};

	public:
		iterator begin() { return (iterator(_tree.findMinimumNode(_tree.base()))); }
		const_iterator begin() const { return (const_iterator(_tree.findMinimumNode(_tree.base()))); }
		iterator end() { return (iterator(_tree.end())); }
		const_iterator end() const { return (const_iterator(_tree.end())); }
		reverse_iterator rbegin() { return (reverse_iterator(this->end())); };
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); };
		reverse_iterator rend() { return (reverse_iterator(this->begin())); };
		const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); };

	public:
		bool empty() const { return (_tree.getSize() == 0); };
		size_type size() const { return (_tree.getSize()); };
		size_type max_size() const { return (_tree.getMaxSize()); }; //need to check this one

	public:
		mapped_type &operator[](const key_type &k)
		{
			return ((*((this->insert(ft::make_pair(k, mapped_type()))).first)).second);
		};

		map &operator=(const map &x)	//need to clear the curr tree ?? why didn't do it?!
		{
			if (this != &x)
				insert(x.begin(), x.end());
			return (*this);
		};

	public:
		key_compare key_comp() const { return (_compare); };
		value_compare value_comp() const { return (value_compare(_compare)); };

	public:
		iterator find(const key_type &k)
		{
			nodePointer node = _tree.search(ft::make_pair(k, mapped_type()));
			if (node == NULL)
				return (end());
			return (iterator(node));
		};
		const_iterator find(const key_type &k) const
		{
			nodePointer node = _tree.search(ft::make_pair(k, mapped_type()));
			if (node == NULL)
				return (end());
			return (const_iterator(node));
		};

		size_type count(const key_type &k) const
		{
			return (find(k) != end() ? 1 : 0);
		};

		iterator lower_bound(const key_type &k)
		{
			return (iterator(_tree.lowerBound(ft::make_pair(k, mapped_type()))));
		};
		const_iterator lower_bound(const key_type &k) const
		{
			return (const_iterator(_tree.lowerBound(ft::make_pair(k, mapped_type()))));
		};

		iterator upper_bound(const key_type &k)
		{
			return (iterator(_tree.upperBound(ft::make_pair(k, mapped_type()))));
		};
		const_iterator upper_bound(const key_type &k) const
		{
			return (const_iterator(_tree.upperBound(ft::make_pair(k, mapped_type()))));
		};

		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		};
		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
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
