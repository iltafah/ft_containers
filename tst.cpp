#include <iterator>
#include <vector>
#include <iostream>
#include "vector.hpp"


class tst
{
	public:
		// static int a;
		tst();
		tst(const tst & obj);
		~tst();
};

tst::tst()
{
	std::cout << " I have been constructed" << std::endl;
}

tst::tst(const tst & obj)
{
	std::cout << " I have been copied" << std::endl;
}

tst::~tst()
{
	std::cout << " I have been destructed" << std::endl;
}

int main()
{
	int i = 0;
	ft::vector<int> stdvec;
	stdvec.push_back(1);
	stdvec.push_back(2);
	stdvec.push_back(3);
	stdvec.push_back(4);
	stdvec.push_back(5);

	typedef ft::vector<int>::iterator iter_type;
	ft::reverse_iterator<iter_type> rit(stdvec.end());

	// std::cout << *(rit.base() + 2) << std::endl;
	std::cout << *(rit) << std::endl;
	// std::cout << *(stdvec.end()) << std::endl;
	// std::cout << *(rit - 6) << std::endl;


	// int	arr[5] = {1, 2, 3, 4, 5};
	// ft::vector<int> secvec(5, 42);
	// std::cout << "vector size is : " << stdvec.size() << std::endl;
	// std::cout << "vector capacity is : " << stdvec.capacity() << std::endl << std::endl;

	// ft::vector<int>::iterator it1 = stdvec.begin();
	// while (it1 != stdvec.end())
	// {
	// 	std::cout << *it1 << std::endl;
	// 	it1++;
	// }

	// stdvec.erase(stdvec.begin() + 1, stdvec.begin() + 2);
	// stdvec.assign(0, 2);
	// stdvec.insert(stdvec.begin() + 5, secvec.begin(), secvec.end());




	// std::cout << "vector size is : " << stdvec.size() << std::endl;
	// std::cout << "vector capacity is : " << stdvec.capacity() << std::endl << std::endl;


	// ft::vector<int>::iterator it2 = stdvec.begin();
	// while (it2 != stdvec.end())
	// {
	// 	std::cout << *it2 << std::endl;
	// 	it2++;
	// }


	// std::cout << "value of static int = " << tst::a << std::endl;
	// stdvec.reserve(16);
	// std::cout << "value of static int = " << tst::a << std::endl;


	
	
	// ft::vector<int> vec(5, 1337);

	// ft::vector<int>::iterator it = vec.begin();
	// std::cout << "is vector empty : " << (vec.empty() == true ? "Yes" : "No") << std::endl;
	// std::cout << "vector size is : " << vec.size() << std::endl;
	// std::cout << "vector capacity is : " << vec.capacity() << std::endl;

	// while (it != vec.end())
	// {
	// 	std::cout << *it << std::endl;
	// 	it++;
	// }

	// std::vector<int>::iterator it = stdvec.begin();
	// while (it != stdvec.end())
	// {
	// 	std::cout << *it << std::endl;
	// 	it++;
	// 	i++;
	// }






// it = stdvec.begin();
// while (i--)
// {
// 	std::cout << *it << std::endl;
// 	it++;
// }

// size_t a = -1;
// std::cout << stdvec.max_size() << std::endl;
// std::cout << vec.max_size() << std::endl;
// std::cout << a / 4 << std::endl;
// std::vector<char> cvec;
// ft::vector<char> ftcvec;
// std::cout << cvec.max_size() << std::endl;
// std::cout << ftcvec.max_size() << std::endl;


// std::cout << std::numeric_limits<size_t>::max() << std::endl; //unsigned long int
// std::cout << std::numeric_limits<ptrdiff_t>::max() << std::endl; //long int

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
