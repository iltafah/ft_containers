/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 09:13:12 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/06 12:24:24 by iltafah          ###   ########.fr       */
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
	std::vector<int> vec(10, 1);
	for(int i = 0; i <= 6; i++)
		vec.erase(vec.begin());
	
std::cout << "vec capacity : " << vec.capacity() << "\nvec size : " << vec.size() << "\n";
vec.assign(5, 1337);
std::cout << "vec capacity : " << vec.capacity() << "\nvec size : " << vec.size() << "\n";
	
	std::vector<int>::iterator it = vec.begin();
	// int i = 0;
	// while (i++ < vec.capacity())
	while (it != vec.end())
	{
		std::cout << *it << std::endl;
		it++;
	}

	// int xd[3][3] = {
	// 	{1, 2 ,3},
	// 	{0, 5, 9}
	// };
	// std::vector<int*> vec(xd, xd + 1);
	// int a[4] = {1, 5, 1337, 42};
	// std::vector<int> vec1(vec.begin(), vec.end());
	// std::vector<int> vec2(a, a + 4);
	// print(a);
	// std::__1::vector<int>::iterator iter();
	//  = vec.begin();
	
	return (0);
}
