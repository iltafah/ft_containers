/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 04:44:50 by iltafah           #+#    #+#             */
/*   Updated: 2022/01/12 05:18:52 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
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

	template<bool B, class T = void>
	struct enable_if {};
 
	template<class T>
	struct enable_if<true, T> { typedef T type; };


	template <class T>
	struct is_integral
	{
		static const value = false;
	}

	template <>
	struct is_integral<bool> { static const value = true; };

	template <>
	struct is_integral<char> { static const value = true; };
	
	template <>
	struct is_integral<char16_t> { static const value = true; };

	template <>
	struct is_integral<char32_t> { static const value = true; };

	template <>
	struct is_integral<wchar_t> { static const value = true; };

	template <>
	struct is_integral<signed char> { static const value = true; };

	template <>
	struct is_integral<short int> { static const value = true; };

	template <>
	struct is_integral<int> { static const value = true; };

	template <>
	struct is_integral<long int> { static const value = true; };

	template <>
	struct is_integral<long long int> { static const value = true; };

	template <>
	struct is_integral<unsigned char> { static const value = true; };

	template <>
	struct is_integral<unsigned short int> { static const value = true; };

	template <>
	struct is_integral<unsigned int> { static const value = true; };

	template <>
	struct is_integral<unsigned long int> { static const value = true; };

	template <>
	struct is_integral<unsigned long long int> { static const value = true; };

}

#endif
