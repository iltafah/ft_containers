/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:55:21 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/14 19:27:21 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>

namespace
{
	template <class Key,								   // map::key_type
			  class T,									   // map::mapped_type
			  class Compare = std::less<Key>,				   // map::key_compare
			  class Alloc = std::allocator<std::pair<const Key, T> > // map::allocator_type
			  >
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			typedef value_comp value_compare;
			typedef Alloc allocator_type;
			typedef allocator_type::reference reference;
			typedef allocator_type::const_reference const_reference;
			typedef allocator_type::pointer pointer;
			typedef allocator_type::const_pointer const_pointer;
			typedef	/*??*/ iterator;
			typedef	/*??*/ const_iterator;
			typedef	/*??*/ reverse_iterator;
			typedef	/*??*/ const_reverse_iterator;
			typedef iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;
			

		public:
			template <class Key, class T, class Compare, class Alloc>
				class value_comp
				{
				  	friend class map;
					protected:
						Compare comp;
						value_comp (Compare c) : comp(c) {}

					public:
						typedef bool result_type;
						typedef value_type first_argument_type;
						typedef value_type second_argument_type;
						bool operator() (const value_type& x, const value_type& y) const
						{
							return comp(x.first, y.first);
						}
				}
		
		public:
			explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
			{
				
			}

			template <class InputIterator>
  				map (InputIterator first, InputIterator last,
       				const key_compare& comp = key_compare(),
       					const allocator_type& alloc = allocator_type())
				{
					
				}
			
			map (const map& x)
			{
				
			}

			~map()
			{

			}

		public:
			map& operator= (const map& x)
			{
				
			}

			mapped_type& operator[] (const key_type& k)
			{
				
			}

		public:
			iterator begin()
			{
				
			}
	
			const_iterator begin() const
			{
				
			}
	
			iterator end()
			{
				
			}
	
			const_iterator end() const
			{
				
			}
	
			reverse_iterator rbegin()
			{
				
			}
	
			const_reverse_iterator rbegin() const
			{
				
			}
	
			reverse_iterator rend()
			{

			}
	
			const_reverse_iterator rend() const
			{

			}

		public:
			bool empty() const
			{
				
			}

			size_type size() const
			{
				
			}

			size_type max_size() const
			{
				
			}

		public:
			pair<iterator,bool> insert (const value_type& val)
			{
				
			}

			iterator insert (iterator position, const value_type& val)
			{

			}

			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last)
			{
				
			}

			void erase (iterator position)
			{
				
			}

			size_type erase (const key_type& k)
			{
				
			}

			void erase (iterator first, iterator last)
			{
				
			}

			void swap (map& x)
			{
				
			}

			void clear()
			{
				
			}

		public:
			key_compare key_comp() const
			{
				
			}

			value_compare value_comp() const
			{
				
			}
			
		public:
			iterator find (const key_type& k)
			{
				
			}
			
			const_iterator find (const key_type& k) const
			{
				
			}
			
			size_type count (const key_type& k) const
			{
				
			}

			iterator lower_bound (const key_type& k)
			{
				
			}
			
			const_iterator lower_bound (const key_type& k) const
			{
				
			}
			
			iterator upper_bound (const key_type& k)
			{
				
			}

			const_iterator upper_bound (const key_type& k) const
			{
				
			}

			pair<const_iterator,const_iterator>	equal_range (const key_type& k) const
			{

			}

			pair<iterator,iterator>	equal_range (const key_type& k)
			{
				
			}

		public:
			allocator_type get_allocator() const
			{
				
			}
	};
}

#endif
