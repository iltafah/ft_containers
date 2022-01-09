/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator_test.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:52:07 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/08 17:41:50 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <vector>

#include "./iterator.hpp"

// template <class iter>
// void	dosome(iter f) // int *
// {
	// typedef typename  f value_type;
	// typedef typename std::iterator_traits<iter>::value_type value_type;
	// typedef typename std::iterator_traits<iter>::reference  reference;
	
	// value_type var = *(f);
	// reference ref = *(f);
	
	// std::cout << var << std::endl;
	
	// ref = 85;
	
	// std::cout << ref << std::endl;
// }


int main()
{
	std::vector<int> vec(10, 1337);
	
	// ft::vecIter<int> it =;

	std::vector<int>::iterator it = vec.begin();
	
	
	return (0);
}