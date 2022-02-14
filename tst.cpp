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

	a.insert(15);
	a.insert(10);
	a.insert(25);
	a.insert(20);
	a.insert(35);
	a.insert(13);
	a.insert(5);

	// a.deleteNode(25);

	// a.print();
	// std::cout << a.findInorderSuccessor(a.search(35))->data << std::endl;


	return (0);
}
