/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:01:00 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/13 15:36:31 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

namespace ft
{
	// template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
	// struct iterator
	// {
	// 	typedef T value_type;
	// 	typedef Distance difference_type;
	// 	typedef Pointer pointer;
	// 	typedef Reference reference;
	// 	typedef Category iterator_category;
	// };

	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <typename T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <typename T>
	class vecIter //: public iterator<std::random_access_iterator_tag, T>
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
	template <typename T>
	class reverse_iterator //: public iterator<std::random_access_iterator_tag, T>
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
		reverse_iterator() : _it(nullptr){};
		explicit reverse_iterator(iterator_type it) : _it(it){};
		template <typename vIter>
		reverse_iterator(const reverse_iterator<vIter> &reverse_iteratorObj) : _it(reverse_iteratorObj.base()){};

	public:
		iterator_type base() const { return (_it); };
		reference operator*() const
		{
			iterator_type copy = base() - 1;
			return (*copy);
		};
		reverse_iterator operator+(difference_type n) const { return (reverse_iterator(_it - n)); };
		reverse_iterator operator-(difference_type n) const { return (reverse_iterator(_it + n)); };
		reverse_iterator &operator++()
		{
			*this = *this + 1;
			return (*this);
		};
		reverse_iterator operator++(int)
		{
			reverse_iterator tempObj = *this;
			++(*this);
			return (tempObj);
		};
		reverse_iterator &operator--()
		{
			*this = *this - 1;
			return (*this);
		};
		reverse_iterator operator--(int)
		{
			reverse_iterator tempObj = *this;
			--(*this);
			return (tempObj);
		};
		reverse_iterator &operator+=(difference_type n)
		{
			*this = *this + n;
			return (*this);
		};
		reverse_iterator &operator-=(difference_type n)
		{
			*this = *this - n;
			return (*this);
		};
		pointer operator->() const { return &(operator*()); };
		reference operator[](difference_type n) const
		{
			reverse_iterator temp = *this + n;
			return (*temp);
		};
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator> &lhs,
		const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	// template <class Iterator>
	// reverse_iterator<Iterator> operator+(
	// 	typename reverse_iterator<Iterator>::difference_type n,
	// 	const reverse_iterator<Iterator> &rev_it)
	// {
	// 	return (lhs.base() + rhs.base());
	// }
}

#endif
