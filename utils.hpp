/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 04:44:50 by iltafah           #+#    #+#             */
/*   Updated: 2022/02/25 23:06:59 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>
#include <limits>
#include <algorithm>

namespace ft
{

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

	////////////////??????????????????????////////////////////????????????????????//////////////////////

	template <typename T>
	class reverse_iterator
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
			iterator_type copy = --base();
			return (*copy);
		};
		reverse_iterator operator+(difference_type n) const { return (reverse_iterator(_it - n)); };
		reverse_iterator operator-(difference_type n) const { return (reverse_iterator(_it + n)); };
		reverse_iterator &operator++()
		{
			_it = --_it;
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
			_it = ++_it;
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

	////////////////??????????????????????////////////////////????????????????????//////////////////////

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return (false);
			first1++;
			first2++;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	////////////////??????????????????????////////////////////????????????????????//////////////////////

	template <bool B, class T = void>
	struct enable_if
	{
	};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	////////////////??????????????????????////////////////////????????????????????//////////////////////

	template <class T>
	struct is_integral
	{
		static const bool value = false;
	};

	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char16_t>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char32_t>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<wchar_t>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<signed char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<short int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long long int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned short int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long long int>
	{
		static const bool value = true;
	};

	////////////////??????????????????????////////////////////????????????????????//////////////////////

	template <class T1, class T2>
	struct pair
	{
	public:
		typedef T1 first_type;
		typedef T2 second_type;

	public:
		first_type first;
		second_type second;

	public:
		pair() : first(), second(){};

		template <class U, class V>
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second){};

		pair(const first_type &a, const second_type &b) : first(a), second(b){};

	public:
		pair &operator=(const pair &pr)
		{
			if (this != &pr)
			{
				this->first = pr.first;
				this->second = pr.second;
			}
			return (*this);
		}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	////////////////??????????????????????////////////////////????????????????????//////////////////////

}

#endif
