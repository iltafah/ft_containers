/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:12:43 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/18 19:23:33 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include <iostream>

template <typename T>
struct Node
{
	T		data;
	Node	*parent;
	Node	*left;
	Node	*right;
	int		bf;
	Node() : parent(0), left(0), right(0), bf(0) { std::cout << "Node constructer has been called" << "\n"; };
};

template <typename key, typename T, typename Compare = std::less<key>, typename Alloc = std::allocator<std::pair<key, T> > >
class AVL
{
	public:
		typedef Node* nodePointer;
		typedef Alloc allocator_type;
		typedef Compare value_compare;

	private:
		nodePointer root;
		allocator_type alloc;

	public:
		AVL() : root(NULL) {};
		~AVL();

	public:
		nodePointer createNode()
		{
			nodePointer newNode = alloc.allocate(1);
			alloc.construct(newNode);
			return (newNode);
		}

		void insert(T &data)
		{
			if (root == NULL)
			{
				root = createNode();
				root->data = data;
			}
			else
				insert(root, data);
		}

		void insert(nodePointer node, T &data)
		{
			if (value_compare(data, node->data))
			{
				insert(node->left);
			}
			else
			{
				insert(node->right);
			}
		}
}

#endif
