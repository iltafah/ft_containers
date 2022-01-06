#include <iterator>
#include <vector>
#include <iostream>
#include "vector.hpp"



template <class iter>
void	dosome(iter f) // int *
{
	// typedef typename  f value_type;
	// typedef typename std::iterator_traits<iter>::value_type value_type;
	// typedef typename std::iterator_traits<iter>::reference  reference;
	
	// value_type var = *(f);
	// reference ref = *(f);
	
	// std::cout << var << std::endl;
	
	// ref = 85;
	
	// std::cout << ref << std::endl;
}

int main()
{
	ft::vector<int> vec(5, 1337);
	ft::vector<int>::iterator it = vec.begin();
std::cout << "vector size is : " << vec.size() << std::endl;
	while (it != vec.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
		// *(it + 2) = 42;
		// it++;
		// std::cout << *it << std::endl;
		// it++;
		// std::cout << *it << std::endl;
		// std::cout << *it << std::endl;
// vec.begin();

	// std::vector<int> vec(3, 1337);
	// std::cout << *vec.begin() << std::endl;
	// int arr[] = {42, 19, 1337};
	// std::vector<int> vec2(arr, arr + 3);
	// dosome(&arr[1]);
	// std::vector<int>::iterator it = vec.begin();
	// dosome(&arr[0]);
	return (0);
}
