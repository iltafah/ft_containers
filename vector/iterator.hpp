/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:01:00 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/23 23:29:46 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include "../utils.hpp"

namespace ft
{

	template <typename T>
	class vecIter
	{
	public:
		typedef T iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type value_type;
		typedef typename iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename iterator_traits<iterator_type>::pointer pointer;
		typedef typename iterator_traits<iterator_type>::reference reference;

	private:
		iterator_type _it;

	public:
		vecIter() : _it(nullptr){};
		explicit vecIter(iterator_type it) : _it(it){};
		template <typename vIter>
		vecIter(const vecIter<vIter> &vecIterObj) : _it(vecIterObj.base()){};

	public:
		iterator_type base() const { return (_it); };
		reference operator*() const { return (*base()); };
		vecIter operator+(difference_type n) const { return (vecIter(_it + n)); };
		vecIter operator-(difference_type n) const { return (vecIter(_it - n)); };
		vecIter &operator++()
		{
			*this = *this + 1;
			return (*this);
		};
		vecIter operator++(int)
		{
			vecIter tempObj = *this;
			++(*this);
			return (tempObj);
		};
		vecIter &operator--()
		{
			*this = *this - 1;
			return (*this);
		};
		vecIter operator--(int)
		{
			vecIter tempObj = *this;
			--(*this);
			return (tempObj);
		};
		vecIter &operator+=(difference_type n)
		{
			*this = *this + n;
			return (*this);
		};
		vecIter &operator-=(difference_type n)
		{
			*this = *this - n;
			return (*this);
		};
		pointer operator->() const { return &(operator*()); };
		reference operator[](difference_type n) const
		{
			vecIter temp = *this + n;
			return (*temp);
		};
	};

	template <class Iterator>
	bool operator==(const vecIter<Iterator> &lhs, const vecIter<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const vecIter<Iterator> &lhs, const vecIter<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const vecIter<Iterator> &lhs, const vecIter<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator<=(const vecIter<Iterator> &lhs, const vecIter<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	bool operator>(const vecIter<Iterator> &lhs, const vecIter<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator>=(const vecIter<Iterator> &lhs, const vecIter<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	typename vecIter<Iterator>::difference_type operator-(
		const vecIter<Iterator> &lhs,
		const vecIter<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	// template <class Iterator>
	// vecIter<Iterator> operator+(
	// 	typename vecIter<Iterator>::difference_type n,
	// 	const vecIter<Iterator> &rev_it)
	// {
	// 	return (lhs.base() + rhs.base());
	// }

	//////////////////////////////////////////////
	/*				reverse iterator			*/
	//////////////////////////////////////////////

}

#endif
