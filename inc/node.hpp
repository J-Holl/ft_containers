/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:17:18 by jholl             #+#    #+#             */
/*   Updated: 2022/09/30 00:16:13 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

namespace ft
{
	//Color: [ 0 black ][ 1 red ]
	template <class T>
	struct Node
	{
		T _data;
		Node *_parent;
		Node *_l;
		Node *_r;
		int _color;	

		Node(T data, Node *parent, Node *l, Node *r, int color):
		_data(data), _parent(parent), _l(l), _r(r), _color(color)
		{
		}
	};

	template <class T>
	Node<T> *minimum(Node<T> *node)
	{
		while (node && node->_l != NULL)
			node = node->_l;
		return (node);
	}

	template <class T>
	Node<T> *maximum(Node<T> *node)
	{
		while (node && node->_r != NULL)
			node = node->_r;
		return (node);
	}
}

#endif
