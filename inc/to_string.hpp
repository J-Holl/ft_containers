/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:31:58 by jholl             #+#    #+#             */
/*   Updated: 2022/10/01 00:42:05 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TO_STRING_HPP
# define TO_STRING_HPP

# include <sstream>

namespace ft
{
	template <typename T>
	std::string to_string(T n)
	{
		std::ostringstream ss;
		ss << n;
		return (ss.str());
	}	
}

#endif
