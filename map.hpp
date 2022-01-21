/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:55:21 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/18 02:22:37 by iltafah          ###   ########.fr       */
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
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		// typedef ?? value_compare;
		typedef Alloc allocator_type;
		typedef allocator_type::reference reference;
		typedef allocator_type::const_reference const_reference;
		typedef allocator_type::pointer pointer;
		typedef allocator_type::const_pointer const_pointer;
		
	};
}

#endif
