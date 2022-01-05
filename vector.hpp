/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 18:40:17 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/05 22:11:40 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
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
			typedef vecIter<const pointer> const_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;

		private:
			pointer			arr;
			size_type		size;
			size_type		capacity;
			allocator_type	alloc;

		public:
			explicit vector (const allocator_type& alloc = allocator_type()) 
				: arr(nullptr), size(0), capacity(0) {};
			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
				: arr(nullptr), size(0), capcaity(0)
			{
				arr = alloc.allocate(n);
				
			};
			template <class InputIterator>
         		vector (InputIterator first, InputIterator last,
                	const allocator_type& alloc = allocator_type()) {};
			vector (const vector& x);
			
	};
}

#endif
