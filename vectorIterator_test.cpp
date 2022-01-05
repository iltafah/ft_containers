/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator_test.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:52:07 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/05 14:42:48 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <vector>

#include "./iterator.hpp"

int main()
{
	std::vector<int> vec(10, 1337);
	
	// ft::vecIter<int> it =;

	std::vector<int>::iterator it = vec.begin();
	
	
	return (0);
}