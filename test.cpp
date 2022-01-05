/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 09:13:12 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/05 12:31:01 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>


template < typename T >
void	print(T shihaja) // expected as iterator
{
	typename std::iterator_traits< T >::value_type a = 16;
	// typename T::value_type a = 16;
	std::cout << a << std::endl;
}

int main()
{
	std::vector<int> vec(3,100);
	int a[4] = {1, 5, 1337, 42};
	// std::vector<int> vec1(vec.begin(), vec.end());
	// std::vector<int> vec2(a, a + 4);
	print(a);
	// std::__1::vector<int>::iterator iter();
	//  = vec.begin();
	
	return (0);
}
