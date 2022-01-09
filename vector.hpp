/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:40:17 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/09 07:28:34 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <stdlib.h>
#include <iostream>
#include "iterator.hpp"



namespace ft
{
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

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
			_arr = _alloc.allocate(n);
			std::cout << GRN;
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_arr + i, val);
			std::cout << WHT;
			_capacity = n;
			_size = n;
		};
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type &alloc = allocator_type(), typename std::enable_if<!std::is_integral<InputIterator>::value >::type *ptr = nullptr)
		{
			// _arr = _alloc.allocate(n);
			assign(first, last);
		};
		vector(const vector &x) {};

	public:
		iterator begin() { return (iterator(_arr)); };
		const_iterator begin() const { return (const_iterator(_arr)); };
		iterator end() { return (iterator(_arr + _size)); };
		const_iterator end() const { return (iterator(_arr + _size)); };

	public:
		size_type size() const { return (_size); };
		size_type max_size() const { return (std::min<size_type>(std::numeric_limits<size_type>::max() / sizeof(value_type), std::numeric_limits<difference_type>::max()));};
		size_type capacity() const { return (_capacity); };
		bool empty() const { return (_size == 0 ? true : false); };
		void resize (size_type n, value_type val = value_type())
		{
			if (n < _capacity)
			{
				std::cout << RED;
				for (size_type i = n; i < _capacity; i++)
					_alloc.destroy(_arr + i);
				std::cout << WHT;
				_size = n;
			}
			else if (n > _capacity)
			{
				size_type sizeToAlloc;
				if (n > _capacity * 2)
					sizeToAlloc = n;
				else
					sizeToAlloc = _capacity * 2;				
				pointer newArr = _alloc.allocate(sizeToAlloc);
				for (size_type i = 0; i < _size; i++)
					newArr[i] = _arr[i];
				for (size_type i = _size; i < n; i++)
					_alloc.construct(newArr + i, val);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _capacity);
				_arr = newArr;
				_size = n;
				_capacity = sizeToAlloc;
			}
		};
		void reserve(size_type n)
		{
			if (n > max_size())
				throw (std::length_error("vector"));
			if (n > _capacity)
			{
				pointer newArr = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(newArr + i, *(_arr + i));
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr);
				_alloc.deallocate(_arr, _capacity);
				_arr = newArr;
				_capacity = n;
			}
		}

	public:
		reference operator[] (size_type n) { return (_arr[n]); };
		const_reference operator[] (size_type n) const { return (_arr[n]); };
		reference at (size_type n)
		{
			if (n >= _size)
				throw (std::out_of_range("vector"));
			return (_arr[n]);
		};
		const_reference at (size_type n) const 
		{
			if (n >= _size)
				throw (std::out_of_range("vector"));
			return (_arr[n]);
		};
		reference front() { return (_arr[0]); };
		const_reference front() const { return (_arr[0]); };
		reference back() { return (_arr[_size - 1]); };
		const_reference back() const { return (_arr[_size - 1]); };

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
		void push_back (const value_type& val)
		{
			if (_size == _capacity)
			{
				pointer newArr = _alloc.allocate(_capacity * 2);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(newArr + i, *(_arr + i));
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _capacity);
				_arr = newArr;
				_capacity = _capacity * 2;
			}
			_arr[_size] = val;
			_size++;
		}
		void pop_back()
		{
			_alloc.destroy(_arr + _size - 1);
			_size--;
		}
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
			_size = 0;
		}
		void swap (vector& x)
		{
			vector temp = *this;
			*this = x;
			x = temp;
		}

		/// 1 2 3
		/// 1 2 3 _ end
		/// 1 4 2 3
		iterator insert (iterator position, const value_type& val)
		{
			if (_size == _capacity)
			{
				pointer newArr = _alloc.allocate(_capacity * 2);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(newArr + i, *(_arr + i));
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _capacity);
				_arr = newArr;
				_capacity = _capacity * 2;
			}
				iterator it = end();
				iterator previt;
				while (it != position)
				{
					previt = it - 1;
					*it = *previt;
					it--;
				}
			*position = val;
			_size++;
			return (position);
		};
    	void insert (iterator position, size_type n, const value_type& val)
		{
			
		};
		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last)
		{
			
		};
		iterator erase (iterator position)
		{
			
		};
		iterator erase (iterator first, iterator last)
		{
			
		};

	public:
		allocator_type get_allocator() const { return (_alloc); };
	};
}

#endif
