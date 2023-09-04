#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
		public :
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

			explicit stack(const container_type& ctnr = container_type())
			{
				_c = ctnr;
			}

			~stack(void)
			{
			}

			bool empty(void) const
			{
				return (_c.empty());
			}

			size_type size(void) const 
			{
				return (_c.size());
			}

			value_type& top(void)
			{
				return (_c.back());
			}

			const value_type& top(void) const
			{
				return (_c.back());
			}

			void push(const value_type& val)
			{
				_c.push_back(val);
			}

			void pop(void)	{
				_c.pop_back();
			}

			//Prototypes non-member functions need access _c
			template <class T2, class Container2>
			friend bool operator==(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs);

			template <class T2, class Container2>
			friend bool operator!=(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs);

			template <class T2, class Container2>
			friend bool operator<(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs);

			template <class T2, class Container2>
			friend bool operator<=(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs);
	
			template <class T2, class Container2>
			friend bool operator>(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs);
	
			template <class T2, class Container2>
			friend bool operator>=(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs);

		protected : 
			container_type _c;
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._c == rhs._c);
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._c != rhs._c);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._c < rhs._c);
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._c <= rhs._c);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._c > rhs._c);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs._c >= rhs._c);
	}
}

#endif
