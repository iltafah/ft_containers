#include <iterator>
#include <vector>
#include <iostream>
#include <stack>
#include <map>
// #include "vector.hpp"
// #include "stack.hpp"
// #include "tree.hpp"
#include "map.hpp"

// class tst
// {
// 	public:
// 		tst();
// 		tst(const tst & obj);
// 		~tst();
// 		void print() {std::cout << "hello world" << std::endl;}
// };

// tst::tst()
// {
// 	std::cout << " I have been constructed" << std::endl;
// }

// tst::tst(const tst & obj)
// {
// 	std::cout << " I have been copied" << std::endl;
// }

// tst::~tst()
// {
// 	std::cout << " I have been destructed" << std::endl;
// }


// void	func(Node<int> *node)
// {
// 	if (node == 0)
// 		return ;
	
// 	func(node->left);
// 	std::cout << node->data << std::endl;
// 	func(node->right);
// 	return ;
// }

int main()
{

	// AVL<int> a;

	// a.insert(15);
	// a.insert(10);
	// a.insert(25);
	// a.insert(20);
	// a.insert(35);
	// a.insert(13);
	// a.insert(5);

	std::map<int, int> myMap;

	myMap.insert(std::pair<int, int>(42, 1337));
	myMap.insert(std::pair<int, int>(40, 1337));
	myMap.insert(std::pair<int, int>(48, 19));
	myMap.insert(std::pair<int, int>(49, 21));
	myMap.insert(std::pair<int, int>(50, 42));
	myMap.insert(std::pair<int, int>(50, 55));

	std::map<int, int>::iterator it = myMap.begin();

	std::cout << (*it).first << " " << (*it).second << std::endl;
	it++;
	std::cout << (*it).first << " " << (*it).second << std::endl;
	it++;
	std::cout << (*it).first << " " << (*it).second << std::endl;
	it++;
	std::cout << (*it).first << " " << (*it).second << std::endl;
	it++;
	std::cout << (*it).first << " " << (*it).second << std::endl;

//std::map<int, int> a;
	// myMap.print();


	return (0);
}
