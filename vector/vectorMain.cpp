/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorMain.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 22:13:40 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/28 00:08:28 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector.hpp"
#include <vector>

class xd
{
	public:
		int _a;
	public:
		xd() : _a(0) {std::cout << "default const has been called" << std::endl;};
		xd(int a) : _a(a) {std::cout << "param const has been called" << std::endl;}; 
		xd(const xd &o) {std::cout << "copy const has been called" << std::endl;}
		~xd() {std::cout << "destructor has been called" << std::endl;}
};


int main()
{
	// {
		// ft::vector<int> vec;

		// vec.push_back(1337);
		// vec.push_back(42);
		// vec.push_back(19);
		// vec.push_back(10);
		// vec.push_back(60);

		// std::cout << vec.size() << std::endl;
		// std::cout << vec.capacity() << std::endl;

		// ft::vector<int> anvec;

		// anvec = vec;
		// std::cout << anvec.size() << std::endl;
		// std::cout << anvec.capacity() << std::endl;
	// }

	{
		xd obj1(1337);
		xd obj2(42);

		ft::vector<xd> vec;

		vec.assign(10, obj1);

		vec.assign(15, obj2);

		std::cout << "capacity :" << vec.capacity() << std::endl; 
		std::cout << "size :" << vec.size() << std::endl; 
		ft::vector<xd>::iterator it = vec.begin();
		while (it != vec.end())
		{
			std::cout << (*it)._a << " ";			
			it++;
		}
		std::cout << std::endl;
	}



	return (0);
}
