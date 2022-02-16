/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:55:21 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/16 21:21:59 by iltafah          ###   ########.fr       */
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
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

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
        typedef node *node_ptr;
    
    public:
        // typedef tree_iterator<pointer, node_ptr> iterator;
        // typedef tree_iterator<const_pointer, node_ptr> const_iterator;
        // typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        // typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        //ft::tree<value_type, value_compare, allocator_type> _tree;
        tree _tree;
        allocator_type _alloc;
        key_compare _compare;

    public:
        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
            : _tree(value_compare(comp), alloc), _alloc(alloc), _compare(comp)
        {
        }
        /// range
        // template <class InputIterator>
        // map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
        //     : _tree(value_compare(comp), alloc), _alloc(alloc), _compare(comp)
        // {
        //     this->insert(first, last);
        // }
        ////// copy
        // map(const map &x) : _tree(value_compare(x._compare), x._alloc), _alloc(x._alloc), _compare(x._compare)
        // {
        //     *this = x;
        // }

        // map &operator=(const map &obj)
        // {
        //     // this need to fix
        //     if (this != &obj)
        //     {
        //         insert(obj.begin(), obj.end());
        //     }
        //     return (*this);
        // }

        // ~map()
        // {
        //     this->clear();
        // }

		public:
		void /* pair<iterator,bool>*/ insert(const value_type &val)
		{
			_tree.insert(val);
		}

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

// 	private:
// 		Tree _tree;
// 		allocator_type _alloc;
// 		size_type _size;

// 	public:
// 		void print()
// 		{
// 			_tree.print();
// 		}

// 		explicit map(const key_compare &comp = key_compare(),
// 					 const allocator_type &alloc = allocator_type()) : _tree(value_compare(comp), alloc), _alloc(alloc), _size(0)
// 		{
// 		}

// 		template <class InputIterator>
// 		map(InputIterator first, InputIterator last,
// 			const key_compare &comp = key_compare(),
// 			const allocator_type &alloc = allocator_type())
// 		{
// 		}

// 		map(const map &x)
// 		{
// 		}

// 		~map()
// 		{
// 		}

		// public:
		// 	map& operator= (const map& x)
		// 	{

		// 	}

		// 	mapped_type& operator[] (const key_type& k)
		// 	{

		// 	}

		// public:
		// 	iterator begin()
		// 	{

		// 	}

		// 	const_iterator begin() const
		// 	{

		// 	}

		// 	iterator end()
		// 	{

		// 	}

		// 	const_iterator end() const
		// 	{

		// 	}

		// 	reverse_iterator rbegin()
		// 	{

		// 	}

		// 	const_reverse_iterator rbegin() const
		// 	{

		// 	}

		// 	reverse_iterator rend()
		// 	{

		// 	}

		// 	const_reverse_iterator rend() const
		// 	{

		// 	}

		// public:
		// 	bool empty() const
		// 	{

		// 	}

		// 	size_type size() const
		// 	{

		// 	}

		// 	size_type max_size() const
		// 	{

		// 	}

	// public:
	// 	void /* pair<iterator,bool>*/ insert(const value_type &val)
	// 	{
	// 		_tree.insert(val);
	// 	}

		// 	iterator insert (iterator position, const value_type& val)
		// 	{

		// 	}

		// 	template <class InputIterator>
		// 	void insert (InputIterator first, InputIterator last)
		// 	{

		// 	}

		// 	void erase (iterator position)
		// 	{

		// 	}

		// 	size_type erase (const key_type& k)
		// 	{

		// 	}

		// 	void erase (iterator first, iterator last)
		// 	{

		// 	}

		// 	void swap (map& x)
		// 	{

		// 	}

		// 	void clear()
		// 	{

		// 	}

		// public:
		// 	key_compare key_comp() const
		// 	{

		// 	}

		// 	value_compare value_comp() const
		// 	{

		// 	}

		// public:
		// 	iterator find (const key_type& k)
		// 	{

		// 	}

		// 	const_iterator find (const key_type& k) const
		// 	{

		// 	}

		// 	size_type count (const key_type& k) const
		// 	{

		// 	}

		// 	iterator lower_bound (const key_type& k)
		// 	{

		// 	}

		// 	const_iterator lower_bound (const key_type& k) const
		// 	{

		// 	}

		// 	iterator upper_bound (const key_type& k)
		// 	{

		// 	}

		// 	const_iterator upper_bound (const key_type& k) const
		// 	{

		// 	}

		// 	std::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const
		// 	{

		// 	}

		// 	std::pair<iterator,iterator>	equal_range (const key_type& k)
		// 	{

		// 	}

		// public:
		// 	allocator_type get_allocator() const
		// 	{

		// 	}
// 	};
// }

// #endif
