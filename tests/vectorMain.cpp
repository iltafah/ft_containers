/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorMain.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 22:13:40 by iltafah           #+#    #+#             */
/*   Updated: 2022/03/01 22:19:22 by iltafah          ###   ########.fr       */
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
		xd(const xd &o) : _a(o._a) {std::cout << "copy const has been called" << std::endl;}
		~xd() {std::cout << "destructor has been called" << std::endl;}
};


int main()
{
	// {
	// 	ft::vector<int> vec;

	// 	vec.push_back(1337);
	// 	vec.push_back(42);
	// 	vec.push_back(19);
	// 	vec.push_back(10);
	// 	vec.push_back(60);

	// 	std::cout << vec.size() << std::endl;
	// 	std::cout << vec.capacity() << std::endl;

	// 	ft::vector<int> anvec;

	// 	anvec = vec;
	// 	std::cout << anvec.size() << std::endl;
	// 	std::cout << anvec.capacity() << std::endl;
	// }

	// {
	// 	xd obj1(1337);
	// 	xd obj2(42);

	// 	ft::vector<xd> vec;

	// 	vec.assign(10, obj1);

	// 	vec.assign(15, obj2);

	// 	std::cout << "capacity :" << vec.capacity() << std::endl; 
	// 	std::cout << "size :" << vec.size() << std::endl; 
	// 	ft::vector<xd>::iterator it = vec.begin();
	// 	while (it != vec.end())
	// 	{
	// 		std::cout << (*it)._a << " ";			
	// 		it++;
	// 	}
	// 	std::cout << std::endl;
	// }

	{
		std::vector<int> vec;
		std::vector<int>::iterator it;

		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(5);

		std::cout << "before insert() : " << std::endl;
		std::cout << vec.size() << std::endl;
		std::cout << vec.capacity() << std::endl;
		it = vec.begin();
		while (it != vec.end())
		{
			std::cout << *it << " ";
			it++;
		}
		std::cout << std::endl << std::endl;

it = vec.begin() + 1;
vec.insert(it, 1337);

it = vec.begin() + 3;
vec.insert(it, 42);

it = vec.begin() + 5;
vec.insert(it, 19);

it = vec.begin() + 7;
vec.insert(it, 21);

it = vec.begin() + 9;
vec.insert(it, 0);
		
		std::cout << "after insert() : " << std::endl;
		std::cout << vec.size() << std::endl;
		std::cout << vec.capacity() << std::endl;
		it = vec.begin();
		while (it != vec.end())
		{
			std::cout << *it << " ";
			it++;
		}
		std::cout << std::endl;
	}

	return (0);
}
