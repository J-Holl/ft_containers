/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 22:55:42 by jholl             #+#    #+#             */
/*   Updated: 2022/09/30 16:16:16 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft
{
	//we take this struct to respect the std structure but in our case
	//we juste use integral constant value
	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator T()
		{
			return (v);
		}
	};

	//If all types bellow are identify then is_integral construct with true
	//so is_integral::v will be set on true, we then use this on enable_if
	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <typename T>
	struct is_integral:
	public false_type
	{
	};

	template <>
	struct is_integral<bool>:
	public true_type
	{
	};

	template <>
	struct is_integral<char>:
	public true_type
	{
	};

	template <>
	struct is_integral<wchar_t>:
	public true_type
	{
	};

	template <>
	struct is_integral<signed char>:
	public true_type
	{
	};

	template <>
	struct is_integral<short int>:
	public true_type
	{
	};

	template <>
	struct is_integral<int>:
	public true_type
	{
	};

	template <>
	struct is_integral<long int>:
	public true_type
	{
	};

	template <>
	struct is_integral<long long int>:
	public true_type
	{
	};

	template <>
	struct is_integral<unsigned char>:
	public true_type
	{
	};

	template <>
	struct is_integral<unsigned short int>:
	public true_type
	{
	};

	template <>
	struct is_integral<unsigned int>:
	public true_type
	{
	};

	template <>
	struct is_integral<unsigned long int>:
	public true_type
	{
	};

	template <>
	struct is_integral<unsigned long long int>:
	public true_type
	{
	};

}

#endif
