/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:40:17 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/06 20:20:02 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef vecIter<pointer> iterator;
		typedef vecIter<const_pointer> const_iterator; // const pointer is not const_pointer :3
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

	private:
		pointer _arr;
		size_type _size;
		size_type _capacity;
		allocator_type _alloc;

	public:
		explicit vector(const allocator_type &alloc = allocator_type())
			: _arr(nullptr), _size(0), _capacity(0), _alloc(alloc){};
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: _arr(nullptr), _size(0), _capacity(0), _alloc(alloc)
		{
			assign(n, val);
		};
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type &alloc = allocator_type(), typename std::enable_if<!std::is_integral<InputIterator>::value >::type *ptr = nullptr)
		{
			assign(first, last);
		};
		vector(const vector &x);

	public:
		iterator begin() { return (iterator(_arr)); };
		const_iterator begin() const { return (const_iterator(_arr)); };
		iterator end() { return (iterator(_arr + _size)); };
		const_iterator end() const { return (iterator(_arr + _size)); };

	public:
		size_type size() const { return (_size); };

	public:
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename std::enable_if<!std::is_integral<InputIterator>::value >::type *ptr = nullptr)
		{
			size_type newSize = last - first; // 13
			if (newSize > _capacity) //13 > 5
			{
				pointer newArr = _alloc.allocate(newSize); //allocate a new memory in a temp
				for (size_type i = 0; i < newSize; i++)	//copy the old content in the new memory
				{
					_alloc.construct(newArr + i, *first);
					first++;
				}
				for (size_type i = 0; i < newSize; i++) //destroy the old pointer
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _capacity);	//deallocate it and free the old memory
				_arr = newArr;						//assign our pointer the new filled memory
				_size = newSize;
				_capacity = newSize;
			}
			else
			{
				for (size_type i = 0; i < newSize; i++)
				{
					_alloc.construct(_arr + i, *first);
					first++;
				}
				_size = newSize;
			}
		}
		void assign(size_type n, const value_type &val)
		{
			if (n > _capacity)
			{
				pointer newArr = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(newArr + i, val);
				for (size_type i = 0; i < n; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _capacity);
				_arr = newArr;
				_size = n;
				_capacity = n;
			}
			else
			{
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_arr + i, val);
				_size = n;
			}
		}
		void reserve(size_type n)
		{
			if (n > _capacity)
			{
			}
		}
	};
}

#endif
