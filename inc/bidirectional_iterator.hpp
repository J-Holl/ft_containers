/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:15:24 by jholl             #+#    #+#             */
/*   Updated: 2022/10/01 00:17:44 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "random_access_iterator.hpp"
# include "node.hpp"

namespace ft
{
	
	/*
	 * Bidirectional iterators are iterators that can be used to access the 
	 * sequence of elements in a range in both directions 
	 * (towards the end and towards the beginning).
	 */
	template <class T>
	class bidirectional_iterator:
	public iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef bidirectional_iterator iterator_type;
			typedef typename iterator<ft::bidirectional_iterator_tag, T>::value_type value_type;
			typedef typename iterator<ft::bidirectional_iterator_tag, Node<T> >::reference node_reference;
			typedef typename iterator<ft::bidirectional_iterator_tag, Node<T> >::pointer node_ptr;
			typedef typename iterator<ft::bidirectional_iterator_tag, T>::reference reference;
			typedef typename iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
			typedef typename iterator<ft::bidirectional_iterator_tag, Node<T> >::difference_type difference_type;
			typedef typename iterator<ft::bidirectional_iterator_tag, Node<T> >::iterator_category iterator_category;

			bidirectional_iterator(void):
			_ptr(NULL)
			{
			}
		
			bidirectional_iterator(node_ptr const &ptr):
			_ptr(ptr)
			{
			}

			bidirectional_iterator(bidirectional_iterator const &src):
			_ptr(src._ptr)
			{
			}

			~bidirectional_iterator()
			{
			}

			//base
			node_ptr base() const
			{
				return (_ptr);
			}

			//operator *
			reference operator*() const
			{
				return (_ptr->_data);
			}
			
			//operator ->
			pointer operator->() const
			{
				return (&(operator*()));
			}
			
			// ++, case 1. root without child
			// case 2. there is right child so we got at the min left to this subtree
			// case 3. there is no right child, while parent and we are right child we up in tree
			// we return the iterator
			iterator_type &operator++()
			{
				if (_ptr->_r == _ptr->_l && _ptr->_parent->_parent == _ptr)
				{
					if (!_ptr->_r)
						_ptr = _ptr->_parent;
					else
						_ptr = maximum(_ptr->_r);
				}
				else if (_ptr->_r)
				{
					_ptr = _ptr->_r;
					while (_ptr->_l)
						_ptr = _ptr->_l;
				}
				else
				{
					node_ptr y = _ptr->_parent;
					while (y && _ptr == y->_r)
					{
						_ptr = y;
						y = y->_parent;
					}
					if (_ptr->_r != y)
						_ptr = y;
				}
				return (*this);
			}

			//operator ++
			iterator_type operator++(int)
			{
				iterator_type _tmp = *this;
				operator++();
				return (_tmp);
			}
			
			//-- case there is left, we go max right to this subtree
			//or while parent and we are left child we up in tree
			//we return the iterator
			iterator_type &operator--()
			{
				if (_ptr->_l)
				{
					_ptr = _ptr->_l;
					while (_ptr->_r)
						_ptr = _ptr->_r;
				}
				else
				{
					node_ptr y = _ptr->_parent;
					while (_ptr == y->_l)
					{
						_ptr = y;
						y = y->_parent;
					}
					if (_ptr->_l != y)
						_ptr = y;
				}
				return (*this);
			}

			iterator_type operator--(int)
			{
				iterator_type _tmp = *this;
				operator--();
				return (_tmp);
			}

		private:
			node_ptr _ptr;
	};

	template <class T1, class T2>
	bool operator==(const bidirectional_iterator<T1> &rbt1, const bidirectional_iterator<T2> &rbt2)
	{
		return (rbt1.base() == rbt2.base());
	}

	template <class T1, class T2>
	bool operator!=(const bidirectional_iterator<T1> &rbt1, const bidirectional_iterator<T2> &rbt2)
	{
		return (rbt1.base() != rbt2.base());
	}
	
	template <class T>
	class const_bidirectional_iterator:
	public iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef const_bidirectional_iterator iterator_type;
			typedef T value_type;
			typedef typename iterator<ft::bidirectional_iterator_tag, Node<T> >::reference node_reference;
			typedef typename iterator<ft::bidirectional_iterator_tag, Node<T> >::pointer node_ptr;
			typedef const T &reference;
			typedef const T *pointer;
			typedef typename iterator<ft::bidirectional_iterator_tag, Node<T> >::difference_type difference_type;
			typedef typename iterator<ft::bidirectional_iterator_tag, Node<T> >::iterator_category iterator_category;

			const_bidirectional_iterator()
			: _ptr(NULL)
			{
			}
		
			const_bidirectional_iterator(node_ptr const &ptr):
			_ptr(ptr)
			{
			}

			const_bidirectional_iterator(bidirectional_iterator<T> const &src):
			_ptr(src.base())
			{
			}

			const_bidirectional_iterator(const_bidirectional_iterator const &src):
			_ptr(src._ptr)
			{
			}

			~const_bidirectional_iterator()
			{
			}

			//base
			node_ptr base() const
			{
				return (_ptr);
			}

			//operator *
			reference operator*() const
			{
				return (_ptr->_data);
			}

			//operator ->
			pointer operator->() const
			{
				return (&(operator*()));
			}
			
			//operator ++
			iterator_type &operator++()
			{
				if (_ptr->_r == _ptr->_l && _ptr->_parent->_parent == _ptr)
				{
					if (!_ptr->_r)
						_ptr = _ptr->_parent;
					else
						_ptr = maximum(_ptr->_r);
				}
				else if (_ptr->_r)
				{
					_ptr = _ptr->_r;
					while (_ptr->_l)
						_ptr = _ptr->_l;
				}
				else
				{
					node_ptr y = _ptr->_parent;
					while (y && _ptr == y->_r)
					{
						_ptr = y;
						y = y->_parent;
					}
					if (_ptr->_r != y)
						_ptr = y;
				}
				return (*this);
			}

			//operator ++
			iterator_type operator++(int)
			{
				iterator_type _tmp = *this;
				operator++();
				return (_tmp);
			}

			//operator --
			iterator_type &operator--()
			{
				if (_ptr->_l)
				{
					_ptr = _ptr->_l;
					while (_ptr->_r)
						_ptr = _ptr->_r;
				}
				else
				{
					node_ptr y = _ptr->_parent;
					while (_ptr == y->_l)
					{
						_ptr = y;
						y = y->_parent;
					}
					if (_ptr->_l != y)
						_ptr = y;
				}
				return (*this);
			}

			//operator --
			iterator_type operator--(int)
			{
				iterator_type _tmp = *this;
				operator--();
				return (_tmp);
			}

			//operator ==
			bool operator==(const const_bidirectional_iterator rbt2) const
			{
				return (base() == rbt2.base());
			}

			//operator !=
			bool operator!=(const const_bidirectional_iterator rbt2) const
			{
				return (base() != rbt2.base());
			}

		private:
			node_ptr _ptr;
	};

	template <class T1, class T2>
	bool operator==(const bidirectional_iterator<T1> &rbt1, const const_bidirectional_iterator<T2> rbt2)
	{
		return (rbt1.base() == rbt2.base());
	}

	template <class T1, class T2>
	bool operator==(const const_bidirectional_iterator<T1> &rbt1, const bidirectional_iterator<T2> rbt2)
	{
		return (rbt1.base() == rbt2.base());
	}

	template <class T1, class T2>
	bool operator!=(const bidirectional_iterator<T1> &rbt1, const const_bidirectional_iterator<T2> rbt2)
	{
		return (rbt1.base() != rbt2.base());
	}

	template <class T1, class T2>
	bool operator!=(const const_bidirectional_iterator<T1> &rbt1, const bidirectional_iterator<T2> rbt2)
	{
		return (rbt1.base() != rbt2.base());
	}
}

#endif
