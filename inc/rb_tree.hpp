/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:38:34 by jholl             #+#    #+#             */
/*   Updated: 2022/09/30 21:25:56 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include "less.hpp"
# include "bidirectional_iterator.hpp"
# include "pair.hpp"
# include "node.hpp"

namespace ft
{
	template <class T, class Compare = ft::less<T> >
	class rb_tree
	{
		public:
			typedef Node<T> *node_ptr;
			typedef Node<T> node;
			typedef bidirectional_iterator<T> iterator;
			typedef const_bidirectional_iterator<T> const_iterator;
			typedef T data_type;
			typedef Compare key_compare;

			//constructor
			rb_tree(const key_compare &comp = key_compare()):
			_root(NULL), _size(0), _comp(comp)
			{
				_nil = malloc_node();
				_nil->_parent = _root;
				_nil->_r = _root;
				_nil->_l = _root;
			}

			//destructor
			~rb_tree()
			{
				clear();
				free_node(_nil);
			}
			
			//assignement =
			rb_tree &operator=(const rb_tree &src)
			{
				_alloc = src._alloc;
				_comp = src._comp;
				clear();
				const_iterator it = src.begin();
				for ( ; it != src.end() ; it++)
					insert(*it);
				return (*this);
			}

			//empty
			bool empty() const
			{
				return (_size == 0);
			}

			//size
			size_t size() const
			{
				return (_size);
			}

			//max_sixe
			size_t max_size() const
			{
				return (_alloc.max_size());
			}
		
			//Iterator
			//begin
			iterator begin()
			{
				if (!_root)
					return (end());
				return (iterator(minimum(_root)));
			}
			//begin const
			const_iterator begin() const
			{
				if (!_root)
					return (end());
				return (const_iterator(minimum(_root)));
			}
			//end
			iterator end()
			{
				return (iterator(_nil));
			}

			//end const
			const_iterator end() const
			{
				return (const_iterator(_nil));
			}
		
			//clear
			void clear()
			{
				clear_helper(_root);
			}

			//malloc_node
			node_ptr malloc_node(data_type data = data_type(), node_ptr parent = NULL,
			node_ptr left = NULL, node_ptr right = NULL, int color = 0)
			{
				node_ptr new_node = _alloc.allocate(1);
				_alloc.construct(new_node, node(data, parent, left, right, color));
				return (new_node);
			}

			//Left_rotation
			void left_rotation(node_ptr nd)
			{
				node_ptr nd_tmp = nd->_r;
				nd->_r = nd_tmp->_l;
				if (nd_tmp->_l)
					nd_tmp->_l->_parent = nd;
				nd_tmp->_parent = nd->_parent;
				if (nd->_parent == _nil)
				{
					_root = nd_tmp;
					_root->_parent = _nil;
					_nil->_r = _root;
					_nil->_l = _root;
					_nil->_parent = _root;
				}
				else if (nd == nd->_parent->_l)
					nd->_parent->_l = nd_tmp;
				else
					nd->_parent->_r = nd_tmp;
				nd_tmp->_l = nd;
				nd->_parent = nd_tmp;
			}

			//Right_rotation
			void right_rotation(node_ptr nd)
			{
				node_ptr nd_tmp = nd->_l;
				nd->_l = nd_tmp->_r;
				if (nd_tmp->_r)
					nd_tmp->_r->_parent = nd;
				nd_tmp->_parent = nd->_parent;
				if (nd->_parent == _nil)
				{
					_root = nd_tmp;
					_root->_parent = _nil;
					_nil->_r = _root;
					_nil->_l = _root;
					_nil->_parent = _root;
				}
				else if (nd == nd->_parent->_r)
					nd->_parent->_r = nd_tmp;
				else
					nd->_parent->_l = nd_tmp;
				nd_tmp->_r = nd;
				nd->_parent = nd_tmp;
			}
			//insert - 
			//First: we locate our new key place, if already exist, we stop.
			//Second: if root==NULL we create root color 0 and we return
			//if key < place_we_locate, we put it left
			//if key > place_we_locate, we put it right
			//except root was NULL and little tree, 2hight we go fix eventually
			//if we broke rbt tree rules.
			pair<iterator, bool> insert(const data_type &key)
			{
				node_ptr node = malloc_node(key, NULL, NULL, NULL, 1);
				node_ptr nd = _root;
				node_ptr nd_tmp = NULL;
				while (nd)
				{
					nd_tmp = nd;
					if (_comp(node->_data, nd->_data))
						nd = nd->_l;
					else if (_comp(nd->_data, node->_data))
						nd = nd->_r;
					else
					{
						free_node(node);
						return (pair<iterator, bool>(iterator(nd), false));
					}
				}
				_size++;
				node->_parent = nd_tmp;
				if (!nd_tmp)
				{
					_root = node;
					_root->_parent = _nil;
					_nil->_r = _root,
					_nil->_l = _root;
					_nil->_parent = _root;
				}
				else if (_comp(node->_data, nd_tmp->_data))
					nd_tmp->_l = node;
				else
					nd_tmp->_r = node;
				if (node->_parent == _nil)
				{
					node->_color = 0;
					return (pair<iterator, bool>(iterator(node), true));
				}
				if (node->_parent->_parent == _nil)
					return (pair<iterator, bool>(iterator(node), true));
				fix_insert(node);
				return (pair<iterator, bool>(iterator(node), true));
			}
			//fix_insert - object retablish rbt rules we may have violated
			// If parent is black dont change color.
			// If parent is red check uncle color, if it's red, put them both black. And continue with grand father.
			// If uncle is black there is 4 cases.
			void fix_insert(node_ptr nd)
			{
				node_ptr actual_uncle;
				while (nd->_parent->_color == 1)
				{
					//Left uncle
					if (nd->_parent == nd->_parent->_parent->_r)
					{
						actual_uncle = nd->_parent->_parent->_l;
						//Uncle is red
						if (actual_uncle && actual_uncle->_color == 1)
						{
							actual_uncle->_color = 0;
							nd->_parent->_color = 0;
							nd->_parent->_parent->_color = 1;
							nd = nd->_parent->_parent;
						}
						else
						{
							//Right-left case - RiRo parent then RRcase
							if (nd == nd->_parent->_l)
							{
								nd = nd->_parent;
								right_rotation(nd);
							}
							//Right-right case - SWAP parent/grand_parent C & LeRo grandfather
							nd->_parent->_color = 0;
							nd->_parent->_parent->_color = 1;
							left_rotation(nd->_parent->_parent);
						}
					}
					else
					{
						//Right uncle
						actual_uncle = nd->_parent->_parent->_r;
						//Uncle is red
						if (actual_uncle && actual_uncle->_color == 1)
						{
							actual_uncle->_color = 0;
							nd->_parent->_color = 0;
							nd->_parent->_parent->_color = 1;
							nd = nd->_parent->_parent;
						}
						else
						{
							//Left-Right case - LiRo parent then LLcase
							if (nd == nd->_parent->_r)
							{
								nd = nd->_parent;
								left_rotation(nd);
							}
							//Left-Left - SWAP parent/grand_parent C & RiRo grandfather
							nd->_parent->_color = 0;
							nd->_parent->_parent->_color = 1;
							right_rotation(nd->_parent->_parent);
						}
					}
					if (nd == _root)
						break ;
				}
				_root->_color = 0;
				_alloc.destroy(_nil);
				_alloc.construct(_nil, node(maximum(_root)->_data, _root, _root, _root, 0));
			}

			//recursive_search
			node_ptr recursive_search(node_ptr node, data_type key) const
			{
				if (!node)
					return (node);
				if (_comp(key, node->_data))
					return (recursive_search(node->_l, key));
				else if (_comp(node->_data, key))
					return (recursive_search(node->_r, key));
				return (node);
			}

			//search_tree
			node_ptr search_tree(data_type key) const
			{
				node_ptr element_found = recursive_search(_root, key);
				if (!element_found)
					return (_nil);
				return (element_found);
			}

			//replace - second replace first
			void replace(node_ptr first, node_ptr second)
			{
				if (first->_parent == _nil)
				{
					_root = second;
					if (_root)
					{
						_root->_parent = _nil;
						_nil->_r = _root;
						_nil->_l = _root;
						_nil->_parent = _root;
					}
				}
				else if (first == first->_parent->_l)
					first->_parent->_l = second;
				else
					first->_parent->_r = second;
				if (second)
					second->_parent = first->_parent;
			}

			//clear_helper
			void clear_helper(node_ptr &to_clear)
			{
				if (!to_clear)
					return ;
				clear_helper(to_clear->_l);
				clear_helper(to_clear->_r);
				free_node(to_clear);
				_size--;
				to_clear = NULL;
			}

			//free_node
			void free_node(node_ptr node)
			{
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}

			//fix_delete, color sibling fix cases
			// a. sibling black, one sibling children red -> 4 rotations cases
			// b. sibling black, 2 black children, recolor sib and continue with parent
			// c. sibling red, rotation old sibling, recolor old sibling and parents
			// d. if we root, we put black and return
			void fix_delete(node_ptr nd)
			{
				node_ptr nd_tmp;

				while (nd != _root && nd->_color == 0)
				{
					if (nd == nd->_parent->_l)
					{
						nd_tmp = nd->_parent->_r;
						if (nd_tmp->_color == 1)
						{
							nd_tmp->_color = 0;
							nd->_parent->_color = 1;
							left_rotation(nd->_parent);
							nd_tmp = nd->_parent->_r;
						}
						if ((nd_tmp->_l->_color == 0 || !nd_tmp->_l) && (nd_tmp->_r->_color == 0 || !nd_tmp->_r))
						{
							nd_tmp->_color = 1;
							nd = nd->_parent;
						}
						else
						{
							if (nd_tmp->_r->_color == 0)
							{
								nd_tmp->_l->_color = 0;
								nd_tmp->_color = 1;
								right_rotation(nd_tmp);
								nd_tmp = nd->_parent->_r;
							}
							nd_tmp->_color = nd->_parent->_color;
							nd->_parent->_color = 0;
							nd_tmp->_r->_color = 0;
							left_rotation(nd->_parent);
							nd = _root;
						}
					}
					else
					{
						nd_tmp = nd->_parent->_l;
						if (nd_tmp->_color == 1)
						{
							nd_tmp->_color = 0;
							nd->_parent->_color = 1;
							right_rotation(nd->_parent);
							nd_tmp = nd->_parent->_l;
						}
						if (!nd_tmp->_r || nd_tmp->_r->_color == 0)
						{
							nd_tmp->_color = 1;
							nd = nd->_parent;
						}
						else
						{
							if (nd_tmp->_l->_color == 0)
							{
								nd_tmp->_r->_color = 0;
								nd_tmp->_color = 1;
								left_rotation(nd_tmp);
								nd_tmp = nd->_parent->_l;
							}
							nd_tmp->_color = nd->_parent->_color;
							nd->_parent->_color = 0;
							nd_tmp->_l->_color = 0;
							right_rotation(nd->_parent);
							nd = _root;
						}
					}
				}
				if (nd)
					nd->_color = 0;
				_alloc.destroy(_nil);
				data_type data = (_root ? maximum(_root)->_data : data_type());
				_alloc.construct(_nil, node(data, _root, _root, _root, 0));
			}

			//delete
			// 1. Search the node to delete. If _nil or NULL return.
			// 2. Is a leaf, juste delete.
			// 3. Only one child, cpy the child to the node and delete child.
			// 4. Two child, find the successor: minimum right side.
			// 5. Replace content, free node and let's fix our tree for double black
			bool delete_node_helper(node_ptr node, data_type key)
			{
				node_ptr nd_to_delete = recursive_search(node, key);
				node_ptr nd, successor;

				if (nd_to_delete == _nil || nd_to_delete == NULL)
					return (false);
				_size--;
				int to_delete_color_save = nd_to_delete->_color;
				if (!nd_to_delete->_l)
				{
					nd = nd_to_delete->_r;
					replace(nd_to_delete, nd_to_delete->_r);
				}
				else if (!nd_to_delete->_r)
				{
					nd = nd_to_delete->_l;
					replace(nd_to_delete, nd_to_delete->_l);
				}
				else
				{
					successor = minimum(nd_to_delete->_r);
					to_delete_color_save = successor->_color;
					nd = successor->_r;
					if (successor->_parent == nd_to_delete)
					{
						if (nd)
							nd->_parent = successor;
					}
					else
					{
						replace(successor, successor->_r);
						successor->_r = nd_to_delete->_r;
						successor->_r->_parent = successor;
					}
					replace(nd_to_delete, successor);
					successor->_l = nd_to_delete->_l;
					successor->_l->_parent = successor;
					successor->_color = nd_to_delete->_color;
				}
				free_node(nd_to_delete);
				if (nd && to_delete_color_save == 0)
					fix_delete(nd);
				return (true);
			}

			//delete_node
			bool delete_node(data_type data)
			{
				return (delete_node_helper(_root, data));
			}

			//count
			node_ptr count(data_type key) const
			{
				node_ptr found = recursive_search(_root, key);
				if (!found)
					return (NULL);
				return (found);
			}

			//swap
			void swap(rb_tree &x)
			{
				node_ptr tmp_root = _root;
				size_t tmp_size = _size;
				node_ptr tmp_nil = _nil;
				_root = x._root;
				_size = x._size;
				_nil = x._nil;
				x._root = tmp_root;
				x._size = tmp_size;
				x._nil = tmp_nil;
			}

			private: 
				node_ptr _root;
				node_ptr _nil;
				size_t _size;
				std::allocator<Node<T> > _alloc;
				key_compare _comp;
	};
}

#endif
