/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:40:17 by iltafah           #+#    #+#             */
/*   Updated: 2022/03/01 22:30:57 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <stdlib.h>
#include <iostream>
#include "../utils.hpp"
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
		typedef vecIter<const_pointer> const_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
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
			   const allocator_type &alloc = allocator_type(), typename ft::enable_if<!std::is_integral<InputIterator>::value>::type *ptr = nullptr)
			: _arr(nullptr), _size(0), _capacity(0), _alloc(alloc)
		{
			assign(first, last);
		};

		vector(const vector &x) : _arr(nullptr), _size(x._size), _capacity(x._size), _alloc(x._alloc)
		{
			_arr = _alloc.allocate(_size);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_arr + i, *(x._arr + i));
		};

		~vector()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_arr + i);
			_alloc.deallocate(_arr, _capacity);
		}

	public:
		vector &operator=(const vector &x)
		{
			if (this != &x)
			{
				if (_arr != nullptr)
				{
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_arr + i);
					_alloc.deallocate(_arr, _capacity);
					_arr = nullptr;
				}
				_capacity = x._size;
				_size = x._size;
				_alloc = x._alloc;
				_arr = _alloc.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_arr + i, *(x._arr + i));
			}
			return (*this);
		}

	public:
		iterator begin() { return (iterator(_arr)); };
		const_iterator begin() const { return (const_iterator(_arr)); };
		iterator end() { return (iterator(_arr + _size)); };
		const_iterator end() const { return (iterator(_arr + _size)); };
		reverse_iterator rbegin() { return (reverse_iterator(this->end())); };
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); };
		reverse_iterator rend() { return (reverse_iterator(this->begin())); };
		const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); };

	public:
		size_type size() const { return (_size); };
		// size_type max_size() const { return (std::min<size_type>(std::numeric_limits<size_type>::max() / sizeof(value_type), std::numeric_limits<difference_type>::max())); };
		size_type max_size() const { return (std::min<size_type>(_alloc.max_size(), std::numeric_limits<difference_type>::max())); };
		size_type capacity() const { return (_capacity); };
		bool empty() const { return (_size == 0 ? true : false); };
		void reserve(size_type n)
		{
			if (n > max_size())
				throw(std::length_error("vector"));
			if (n > _capacity)
			{
				pointer newArr = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(newArr + i, *(_arr + i));
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _capacity);
				_arr = newArr;
				_capacity = n;
			}
		};

		void resize(size_type n, value_type val = value_type())
		{
			if (n < _size)
			{
				for (size_type i = n; i < _capacity; i++)
					_alloc.destroy(_arr + i);
			}
			else if (n > _size)
			{
				if (n > _capacity)
				{
					size_type sizeToAlloc;
					if (n > _capacity * 2)
						sizeToAlloc = n;
					else
						sizeToAlloc = _capacity * 2;
					reserve(sizeToAlloc);
				}
				for (size_type i = _size; i < n; i++)
					_alloc.construct(_arr + i, val);
			}
			_size = n;
		};

	public:
		reference operator[](size_type n) { return (_arr[n]); };
		const_reference operator[](size_type n) const { return (_arr[n]); };
		reference front() { return (_arr[0]); };
		const_reference front() const { return (_arr[0]); };
		reference back() { return (_arr[_size - 1]); };
		const_reference back() const { return (_arr[_size - 1]); };
		reference at(size_type n)
		{
			if (n >= _size)
				throw(std::out_of_range("vector"));
			return (_arr[n]);
		};
		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw(std::out_of_range("vector"));
			return (_arr[n]);
		};

	public:
		void assign(size_type n, const value_type &val)
		{
			if (n > _capacity)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _capacity);
				_arr = _alloc.allocate(n);
				_capacity = n;
			}
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_arr + i, val);
			_size = n;
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *ptr = nullptr)
		{
			size_type newSize = last - first;
			if (newSize > _capacity)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, _capacity);
				_arr = _alloc.allocate(newSize);
				_capacity = newSize;
			}
			for (size_type i = 0; i < newSize; i++)
			{
				_alloc.construct(_arr + i, *first);
				first++;
			}
			_size = newSize;
		}

		void push_back(const value_type &val)
		{
			if (_size == 0)
				reserve(1);
			else if (_size == _capacity)
				reserve(_capacity * 2);
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

		void swap(vector &x)
		{
			vector temp = *this;
			*this = x;
			x = temp;
		}

		iterator insert(iterator position, const value_type &val)
		{
			difference_type diff = end() - position;
			if (_size == _capacity)
				reserve(_capacity * 2);
			iterator it = end();
			iterator previt;
			while (diff > 0)
			{
				previt = it - 1;
				*it = *previt;
				it--;
				diff--;
			}
			*it = val;
			_size++;
			return (it);
		};

		void insert(iterator position, size_type n, const value_type &val)
		{
			if (n == 0)
				return;
			difference_type diff = end() - position;
			if (_size + n >= _capacity)
			{
				size_type newSize;
				if (_size + n > _capacity * 2)
					newSize = _size + n;
				else
					newSize = _capacity * 2;
				reserve(newSize);
			}
			iterator it = end() + n - 1;
			iterator toShiftIt;
			while (diff > 0)
			{
				toShiftIt = it - n;
				*it = *toShiftIt;
				it--;
				diff--;
			}
			for (int i = 0; i < n; i++)
			{
				*it = val;
				it--;
			}
			_size += n;
		};

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!std::is_integral<InputIterator>::value>::type *ptr = nullptr)
		{
			difference_type n = last - first;

			if (n == 0)
				return;
			difference_type diff = end() - position;
			if (_size + n >= _capacity)
			{
				size_type newSize;
				if (_size + n > _capacity * 2)
					newSize = _size + n;
				else
					newSize = _capacity * 2;
				reserve(newSize);
			}
			iterator it = end() + n - 1;
			iterator toShiftIt;
			while (diff > 0)
			{
				toShiftIt = it - n;
				*it = *toShiftIt;
				it--;
				diff--;
			}
			for (int i = 0; i < n; i++)
			{
				*it = *(--last);
				it--;
			}
			_size += n;
		};

		iterator erase(iterator position)
		{
			return (erase(position, position + 1));
		};

		iterator erase(iterator first, iterator last)
		{
			difference_type startingDeleteIndex = first - begin();
			difference_type toDelete = last - first;
			difference_type toShift = end() - last;

			for (int i = 0; i < toDelete; i++)
				_alloc.destroy(_arr + startingDeleteIndex + i);
			iterator it = first;
			iterator it2 = last;
			while (toShift--)
			{
				*(it) = *(it2);
				it++;
				it2++;
			}
			_size -= toDelete;
			return (--last);
		};

	public:
		allocator_type get_allocator() const { return (_alloc); };
	};

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (lhs == rhs || lhs < rhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (lhs == rhs || lhs > rhs);
	}
}

#endif
