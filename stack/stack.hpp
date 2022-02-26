/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:47:23 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/25 22:01:29 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	protected:
		container_type c;

	public:
		explicit stack(const container_type &ctnr = container_type()) : c(ctnr){};

	public:
		bool empty() const { return (c.empty()); };
		size_type size() const { return (c.size()); };
		value_type &top() { return (c.back()); };
		const value_type &top() const { return (c.back()); };
		void push(const value_type &val) { c.push_back(val); };
		void pop() { c.pop_back(); };

		template <class U, class Cont>
		friend bool operator==(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);

		template <class U, class Cont>
		friend bool operator!=(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);

		template <class U, class Cont>
		friend bool operator<(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);

		template <class U, class Cont>
		friend bool operator<=(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);

		template <class U, class Cont>
		friend bool operator>(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);

		template <class U, class Cont>
		friend bool operator>=(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c != rhs.c);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs.c >= rhs.c);
	}

}

#endif
