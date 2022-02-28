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

int main()
{
	ft::vector<int> vec;

	vec.push_back(1337);
	vec.push_back(42);
	vec.push_back(19);
	vec.push_back(10);
	vec.push_back(60);
	
	std::cout << vec.size() << std::endl;
	std::cout << vec.capacity() << std::endl;
	
	ft::vector<int> anvec;
	
	anvec = vec;
	std::cout << anvec.size() << std::endl;
	std::cout << anvec.capacity() << std::endl;
	
	return (0);
}
