/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:00:13 by jholl             #+#    #+#             */
/*   Updated: 2022/09/30 16:19:11 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "rb_tree.hpp"
# include "bidirectional_iterator.hpp"
# include "less.hpp"
# include "pair.hpp"
# include "make_pair.hpp"
# include "equal.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"
# include "lexicographical_compare.hpp"

namespace ft
{

	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			//Member types
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			//Nested function class to compare elements
			class value_compare
			{
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

					value_compare(key_compare c = key_compare()):
					_comp(c)
					{
					}

					bool operator()(const value_type& x, const value_type& y) const
					{
						return (_comp(x.first, y.first));
					}		

				protected:
					key_compare _comp;
			};
			typedef Alloc allocator_type;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::reference reference;
			typedef typename ft::rb_tree<value_type, value_compare>::iterator iterator;
			typedef typename ft::rb_tree<value_type, value_compare>::const_iterator const_iterator;
			typedef typename ft::reverse_iterator<iterator> reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;
			
			//constructor empty
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			_tree(ft::rb_tree<value_type, value_compare>(value_compare(comp))), _key(comp), _alloc(alloc)
			{
			}

			//constructor range
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true):
			_tree(ft::rb_tree<value_type, value_compare>(value_compare(comp))), _key(comp), _alloc(alloc)
			{
				for (; first != last ; first++)
					insert(*first);
			}

			//constructor cpy
			map (const map& x)
			{
				*this = x;
			}

			//destructor
			~map(void)
			{
			}

			//assignement =
			map& operator=(const map& x)
			{
				clear();
				_alloc = x._alloc;
				_key = x._key;
				_val = x._val;
				for (const_iterator it = x.begin() ; it != x.end() ; it++)
					insert(*it);
				return (*this);
			}

			//Iterators:
			//begin
			iterator begin(void)
			{
				return (_tree.begin());
			}

			//begin const
			const_iterator begin(void) const
			{
				return (_tree.begin());
			}

			//end
			iterator end(void)
			{
				return (_tree.end());
			}

			//end const
			const_iterator end(void) const
			{
				return (_tree.end());
			}

			//rbegin
			reverse_iterator rbegin(void)
			{
				return (reverse_iterator(end()));
			}

			//rbegin const
			const_reverse_iterator rbegin(void) const
			{
				return (const_reverse_iterator(end()));
			}

			//rend
			reverse_iterator rend(void)
			{
				return (reverse_iterator(begin()));
			}

			//rend const
			const_reverse_iterator rend(void) const
			{
				return (const_reverse_iterator(begin()));
			}

			//Capacity
			//empty
			bool empty(void) const
			{
				return (_tree.empty());
			}

			//size
			size_type size(void) const
			{
				return (_tree.size());
			}

			//max_size
			size_type max_size(void) const
			{
				return (_tree.max_size());
			}

			//Element access:
			//[] - if key don't exist insert it and return mapped_value associated with it
			mapped_type& operator[](const key_type& k)
			{
				return ((*((insert(ft::make_pair(k, mapped_type()))).first)).second);
			}

			//insert single element - extends containers, if key are equal dont add this keys
			pair<iterator, bool> insert(const value_type& val)
			{
				return (_tree.insert(val));
			}

			//insert with hint position - optional optimisation
			//return element that has already a key or the new elem
			iterator insert(iterator position, const value_type& val)
			{
				(void)position;
				return (_tree.insert(val).first);
			}

			//insert range
			template <class InputIterator>
			void insert(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
			{
				for (; first != last ; first++)
					insert(*first);
			}

			//erase single
			void erase (iterator position)
			{
				_tree.delete_node(*position);
			}

			//erase
			size_type erase (const key_type& k)
			{
				if (_tree.delete_node(value_type(k, mapped_type())))
					return (1);
				return (0);
			}

			//erase range
			void erase(iterator first, iterator last)
			{
				iterator it;
				for (; first != last ; )
				{
					it = first;
					first++;
					_tree.delete_node(*it);
				}
			}

			//swap
			void swap(map& x)
			{
				_tree.swap(x._tree);
				key_compare tmp_key = x._key;
				value_compare tmp_val = x._val;
				allocator_type tmp_alloc = x._alloc;
				x._key = _key;
				x._val = _val;
				x._alloc = _alloc;
				_key = tmp_key;
				_val = tmp_val;
				_alloc = tmp_alloc;
			}

			//clear
			void clear(void)
			{
				_tree.clear();
			}

			//key_comp - return the comp we use for key, by default less
			key_compare key_comp(void) const
			{
				return (_key);
			}

			//value_comp - return nested class use to comp
			value_compare value_comp(void) const
			{
				return (_val);
			}

			//find - if found the iterator on the object else on end()
			iterator find(const key_type& k)
			{
				return (iterator(_tree.search_tree(value_type(k, mapped_type()))));
			}

			//find const
			const_iterator find(const key_type& k) const
			{
				return (const_iterator(_tree.search_tree(value_type(k, mapped_type()))));
			}

			//count - only 1 elem by key, so 1 or 0
			size_type count(const key_type& k) const
			{
				if (_tree.count(value_type(k, mapped_type())))
					return (1);
				return (0);
			}

			//lower_bound - return ite on a key not considered to go before k 
			//so if k exist return k
			iterator lower_bound(const key_type& k)
			{
				iterator it = begin();
				for (; it != end() ; it++)
				{
					if (!_key(it->first, k))
						break ;
				}
				return (it);
			}

			//lower_bound_
			const_iterator lower_bound(const key_type& k) const
			{
				const_iterator it = begin();
				for ( ; it != end() ; it++)
				{
					if (!_key(it->first, k))
						break ;
				}
				return (it);
			}
			//upper_bound - return it on a key who go after k
			iterator upper_bound(const key_type& k)
			{
				iterator it = begin();
				for (; it != end() ; it++)
				{
					if (_key(k, it->first))
						break ;
				}
				return (it);
			}

			//upper_bound const
			const_iterator upper_bound(const key_type& k) const
			{
				const_iterator it = begin();
				for (; it != end() ; it++)
				{
					if (_key(k, it->first))
						break ;
				}
				return (it);
			}

			//equal range const - The function returns a pair, whose member pair::first
			//is the lower bound of the range (the same as lower_bound), 
			//and pair::second is the upper bound (the same as upper_bound).
			pair<const_iterator, const_iterator> equal_range(const key_type& k) const
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			//equal range
			pair<iterator, iterator> equal_range(const key_type& k)
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			//get_allocator
			allocator_type get_allocator(void) const
			{
				return (_alloc);
			}

		private:
			ft::rb_tree<value_type, value_compare> _tree;
			key_compare _key;
			value_compare _val;
			allocator_type _alloc;
	};
	//Non member overloads
	//Relational operators
	//== with equal et < with lexicographical_compare, all other with this
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		return (false);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(rhs > lhs));
	}

	//swap overload
	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
