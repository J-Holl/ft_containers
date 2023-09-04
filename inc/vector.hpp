/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:39:09 by jholl             #+#    #+#             */
/*   Updated: 2022/09/30 15:27:56 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "to_string.hpp"
# include "random_access_iterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include "lexicographical_compare.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			//Member type
			typedef T value_type; 
			typedef Alloc allocator_type;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename allocator_type::const_reference const_reference;
			typedef ptrdiff_t difference_type;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::reference reference;
			typedef ft::random_access_iterator<value_type> iterator;
			typedef ft::random_access_iterator<const value_type> const_iterator;
			/*
			 * A copy of the original iterator (the base iterator) is kept internally
			 * and used to reflect the operations performed on the reverse_iterator:
			 * whenever the reverse_iterator is incremented, its base iterator is decreased, 
			 * and vice versa. A copy of the base iterator with the current state 
			 * can be obtained at any time by calling member base.
			*/
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef size_t size_type;
			
			//constructor default
			explicit vector(const allocator_type& alloc = allocator_type()):
			_size(0), _capacity(0), _data(NULL), _alloc(alloc)
			{
			}

			//constructor fill
			explicit vector(size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type()):
			_size(n), _capacity(n), _data(NULL), _alloc(alloc)
			{
				if (n > 0)
				{
					_data = _alloc.allocate(_capacity);
					for (size_type i = 0 ; i < n ; i++)
						_alloc.construct(_data + i, val);
				}
			}
	
			//constructor range
			template <class InputIterator>
			vector(InputIterator first, 
			InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true, 
			const allocator_type& alloc = allocator_type()):
			_size(0), _capacity(0), _data(NULL),  _alloc(alloc)
			{
				size_type size = 0;
				for (InputIterator it = first ; it != last ; it++)
					size++;
				_size = size;
				_capacity = size;
				if (size > 0)
				{
					_data = _alloc.allocate(_capacity);
					pointer it2 = _data;
					for ( ; first != last ; first++)
					{
						_alloc.construct(it2, *first);
						it2++;
					}
				}
			}

			//constructor copy - take x allocator
			vector (const vector& x):
			_size(0), _capacity(0), _data(NULL)
			{
				*this = x;
			}
			
			//destructor - clear(destroy the object) then deallocate memory
			~vector(void)
			{
				clear();
				if (_capacity != 0)
					_alloc.deallocate(_data, _capacity);
			}

			//operator = - preserve his own alloc
			vector& operator=(const vector& x)
			{
				if (this != &x)
				{
					clear();
					if (_capacity < x._size)
					{
						_alloc.deallocate(_data, _capacity);
						_capacity = x._size;
						if (_capacity > 0)
							_data = _alloc.allocate(_capacity);
						else
							return (*this);
					}
					_size = x._size;
					for(size_type i = 0 ; i < x._size ; i++)
						_alloc.construct(_data + i, x._data[i]);
				}
				return (*this);
			}
			
			//Iterators
			//begin
			iterator begin(void)
			{
				return (iterator(_data));
			}
			
			//begin const
			const_iterator begin(void) const
			{
				return (const_iterator(_data));
			}

			//end
			iterator end(void)
			{
				return (iterator(_data + _size));
			}
			
			//end const
			const_iterator end(void) const
			{
				return (const_iterator(_data + _size));
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
			//size (!= capacity)
			size_type size(void) const
			{
				return (_size);
			}

			//max size
			size_type max_size(void) const
			{
				return (_alloc.max_size());
			}

			//resize
			void resize(size_type n, value_type val = value_type())
			{
				if (n < _size)
				{
					while (n < _size)
						pop_back();
				}
				else if (n > _size)
					insert(end(), n - _size, val);
			}
			
			//capacity
			size_type capacity(void) const
			{
				return (_capacity);
			}
		
			//empty
			bool empty(void) const
			{
				if (_size == 0)
					return (true);
				return (false);
			}

			//reserve - request a change in capacity - if change realloacte the storage
			// construct object in good area -> destroy old object -> deallocate old capa
			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (n >= _capacity && n > 0)
				{
					pointer new_ptr = _alloc.allocate(n);
					if (_capacity > 0)
					{
						for (size_t i = 0 ; i < _size ; i++)
						{
							_alloc.construct(new_ptr + i, _data[i]);
							_alloc.destroy(&_data[i]);
						}
						_alloc.deallocate(_data, _capacity);
					}
					_data = new_ptr;
					_capacity = n;
				}
			}

			//Elements access
			//[] - dont throw out of range
			reference operator[](size_type n)
			{
				return (_data[n]);
			}

			// const
			const reference operator[](size_type n) const
			{
				return (_data[n]);
			}

			//at - like [] with exception
			reference at(size_type n)
			{
				if (n < 0 || n >= _size)
				{
					std::string out("vector::_M_range_check: __n (which is ");
					out += ft::to_string<size_type>(n);
					out += ") >= this->size() (which is ";
					out += ft::to_string<size_type>(this->size());
					out += ")";
					throw std::out_of_range(out);
				}
				return (_data[n]);
			}

			//at const
			const_reference at(size_type n) const
			{
				if (n < 0 || n >= _size)
				{
					std::string out("vector::_M_range_check: __n (which is ");
					out += ft::to_string<size_type>(n);
					out += ") >= this->size() (which is ";
					out += ft::to_string<size_type>(this->size());
					out += ")";
					throw std::out_of_range(out);
				}
				return (_data[n]);
			}

			//front - first elem
			reference front(void)
			{
				return (_data[0]);
			}
			
			//front const
			const_reference front(void) const
			{
				return (_data[0]);
			}
			
			//back - last elem
			reference back(void)
			{
				if (_size == 0)
					return (_data[0]);
				else
					return (_data[_size - 1]);
			}
			
			//back const
			const_reference back(void) const
			{
				if (_size == 0)
					return (_data[0]);
				else
					return (_data[_size - 1]);
			}

			//Modifiers
			//assign range - elements before call are destroyed and replaced by newly constructed elements
			//enable_if protect integral to enter and crash with *
			template<class InputIterator>
			void assign(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
			{
				clear();
				size_type size = 0;
				for (InputIterator it = first ; it != last ; it++)
					size++;
				_size = size;
				if (_capacity < size)
				{
					_alloc.deallocate(_data, _capacity);
					_capacity = size;
					if (size > 0)
						_data = _alloc.allocate(_capacity);
					else
						return ;
				}
				pointer tmp_data = _data;
				while (first != last)
				{
					_alloc.construct(tmp_data, *first);
					first++;
					tmp_data++;
				}
			}

			//assign fill
			void assign(size_type n, const value_type& val)
			{
				clear();
				_size = n;
				if (_capacity < n)
				{
					_alloc.deallocate(_data, _capacity);
					_capacity = n;
					if (n > 0)
						_data = _alloc.allocate(_capacity);
					else
						return ;
				}
				for (size_type i = 0 ; i < n ; i++)
					_alloc.construct(_data + i, val);
			}
	
			//push back
			void push_back(const value_type& val)
			{
				if (_size >= _capacity)
				{
					if (_capacity <= 0)	
						reserve(1);
					else
						reserve(_capacity *= 2);
				}
				_alloc.construct(&_data[_size++], val);
			}

			//pop_back
			void pop_back(void)
			{
				_size--;
				_alloc.destroy(_data + _size);
			}

			//insert single element - vector extended, relocate old elem moved
			iterator insert(iterator position, const value_type& val)
			{
				difference_type pos = position - _data;
				insert(position, 1, val);
				return (iterator(begin() + pos));
			}

			//insert fill
			void insert(iterator position, size_type n, const value_type& val)
			{
				difference_type pos = position - _data;
				if (n <= 0)
					return ;
				if (_size + n > _capacity)
				{
					if (_size * 2 > _size + n)
						reserve(_size * 2);
					else
						reserve(_size + n);
				}
				pointer tmp_reconstructed = _data + _size + n - 1;
				pointer stop = _data + pos + n - 1;
				for (; tmp_reconstructed != stop ; --tmp_reconstructed)
				{
					_alloc.construct(tmp_reconstructed, *(tmp_reconstructed - n));
					_alloc.destroy(tmp_reconstructed - n);
				}
				_size += n;
				while (n > 0)
				{
					_alloc.construct(_data + pos - 1 + n, val);
					n--;
				}
			}

			//insert range
			template <class InputIterator>
			void insert(iterator position,
			InputIterator first, InputIterator last, 
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
			{
				if (first == last)
					return ;
				difference_type pos = position - _data;
				size_type n = 0;
				for (InputIterator it = first ; it != last ; it++)
					n++;
				if (_size + n > _size * 2)
					reserve(_size + n);
				else if (_size + n > _capacity)
					reserve(_size * 2);
				pointer tmp_reconstructed = _data + _size + n - 1;
			   	pointer stop = _data + pos + n - 1; 
				for (;tmp_reconstructed != stop ; tmp_reconstructed--)
				{
					_alloc.construct(tmp_reconstructed, *(tmp_reconstructed - n));
					_alloc.destroy(tmp_reconstructed - n);
				}
				_size += n;
				while (n > 0)
				{
					last--;
					_alloc.construct(_data + pos + n - 1, *last);
					n--;
				}
			}

			//erase single
			iterator erase(iterator position)
			{
				return (erase(position, position + 1));
			}
	
			//erase range - erasing elements in positions other than the vector 
			//end causes container to relocate all the elements after the pos
			iterator erase(iterator first, iterator last)
			{
				size_type i = last - first;
				size_type j = first - _data;
				if (i > 0)
				{
					for ( ; j < _size - i ; j++)
					{
						_alloc.destroy(_data + j);
						_alloc.construct (_data + j, _data[j + i]);
					}
					for ( ; j < _size ; j++)
						_alloc.destroy(_data + j);
					_size -= i;
				}
				return (iterator(first));
			}
			
			//swap - overload after to use him with diff syntax
			void swap (vector& x)
			{
				size_type tmp_cap = x._capacity;
				pointer tmp_arr = x._data;
				allocator_type tmp_all = x._alloc;
				size_type tmp_size = x._size;
				x._alloc = _alloc;
				x._size = _size;
				x._capacity = _capacity;
				x._data = _data;
				_alloc = tmp_all;
				_size = tmp_size;
				_capacity = tmp_cap;
				_data = tmp_arr;
			}

			//clear - destroy
			void clear(void)
			{
				if (empty())
					return ;
				for (size_type i = 0 ; i < _size ; i++)
					_alloc.destroy(_data + i);
				_size = 0;
			}
			
			//get_allocator
			allocator_type get_allocator(void) const
			{
				return (_alloc);
			}

		private:
			size_type _size;
			size_type _capacity;
			pointer _data;
			allocator_type _alloc;	
			
	};
	
	//Non member overloads
	//Relational operator
	// == equivalent to use equal
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			for (size_t i = 0 ; i < lhs.size() ; i++)
			{
				if (lhs[i] != rhs[i])
					return (false);
			}
			return (true);
		}
		return (false);
	}
	
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	// < use lexico, then all other use == and <
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}
	
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	//swap overload to swap(vec, vec) use
	template <class T, class Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
