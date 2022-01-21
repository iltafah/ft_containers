/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:12:43 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/21 12:58:58 by iltafah          ###   ########.fr       */
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

		void insert(nodePointer root, T &data)
		{
			nodePointer	currNode = root;
			nodePointer parent = NULL;

			while (currNode != NULL)
			{
				parent = currNode;
				if (value_compare(data, currNode->data))
					currNode = currNode->left;
				else
					currNode = currNode->right;
			}
			if (value_compare(data, parent->data))
			{
				parent->left = createNode();
				parent->left->data = data;
			}
			else
			{
				parent->right = createNode();
				parent->right->data = data;
			}
			//Time for balancing
		}
};

#endif
