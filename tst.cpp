#include <iterator>
#include <vector>
#include <iostream>
#include <stack>
#include <map>
// #include "vector.hpp"
// #include "stack.hpp"
#include "tree.hpp"

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


void	func(Node<int> *node)
{
	if (node == 0)
		return ;
	
	func(node->left);
	std::cout << node->data << std::endl;
	func(node->right);
	return ;
}

int main()
{
	// std::allocator<Node<int> > alloc;

	// Node<int>	*node1 = alloc.allocate(1);
	// Node<int>	*node2 = alloc.allocate(1);

	// alloc.construct(node1);
	// alloc.construct(node2);

	// node1->data = 42;
	// node2->data = 1337;

	// node1->left = node2;
	// func(node1);

	AVL<int> a;

	a.insert(5);
	a.insert(22);
	a.insert(42);
	a.insert(1337);
	a.insert(21);
	a.insert(1);

	a.print(a.root);



	return (0);
}
