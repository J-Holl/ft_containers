/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:57:19 by jholl             #+#    #+#             */
/*   Updated: 2022/09/30 18:39:50 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ostream>
#include <typeinfo>

#ifndef STD 
	#include "vector.hpp"
	#include "stack.hpp"
	#include "map.hpp"
	#include "make_pair.hpp"
	#define STD 1
#else
	namespace ft = std;
	#include <vector>
	#include <stack>
	#include <map>
#endif

template <class Key, class T>
void show_map_details(ft::map<Key, T> & map)
{
	size_t size = map.size(); 
	std::cout << "|Size:" << size << "|" << std::endl;
	std::cout << "Contained inside:" << std::endl;
	for (typename ft::map<Key, T>::iterator it = map.begin() ; it != map.end() ; it++)
		std::cout << "Key: | " << it->first << " | Value: | " << it->second << " |" << std::endl;
	std::cout << "End of container." << std::endl << std::endl;
}

template < typename T >
void show_vec_details(ft::vector<T> const & vect)
{
	size_t size = vect.size(); 
	std::cout << "|Size:" << size << "| |Capacity: " << vect.capacity() << "|" 
	<< std::endl;
	std::cout << "Contained inside:" << std::endl;
	for (size_t i = 0 ; i < size; i++)
		std::cout << "Index: " << i << " | " << vect[i] << " |" << std::endl;
	std::cout << "End of container." << std::endl << std::endl;
}

int main()
{
	//VECTOR PART
	{
	std::cout << "Try to respect CPLUSPLUS vector order to simplify correction." << std::endl << std::endl;
	std::cout << "0. CONSTRUCTION:" << std::endl << std::endl;
	std::cout << "Empty vector constructor." << std::endl;
	ft::vector<int> vec_int0;
	show_vec_details(vec_int0);
	std::cout << "Fill vector constructor." << std::endl;
	ft::vector<char> vec_char0(5, 'c');
	show_vec_details(vec_char0);
	std::cout << "Range vector constructor." << std::endl;
	ft::vector<char> vec_char1(vec_char0.begin() + 1, vec_char0.end() - 1);
	show_vec_details(vec_char1);
	std::cout << "Copy vector constructor." << std::endl;
	//insert to see if the order is respected in the cpy
	vec_char0.insert(vec_char0.begin() ,'a');
	vec_char0.insert(vec_char0.end() ,'z');
	ft::vector<char> vec_char2(vec_char0);
	show_vec_details(vec_char0);
	show_vec_details(vec_char2);

	std::cout << "1. DESTRUCTION:" << std::endl << std::endl;
	std::cout << "Ensure with valgind all the allocated memory allocate with"<<
	"the given allocator is desallocate." << std::endl << std::endl;

	std::cout << "2. ASSIGN CONTENT:" << std::endl << std::endl;
	vec_char2 = vec_char1;
	show_vec_details(vec_char2);

	vec_int0.push_back(1);
	vec_int0.push_back(2);
	vec_int0.push_back(3);
	vec_int0.push_back(4);
	vec_int0.push_back(5);
	vec_int0.push_back(6);

	vec_char0.push_back('c');
	vec_char0.push_back('h');
	vec_char0.push_back('a');
	vec_char0.push_back('r');

	std::cout << "3. ITERATORS:" << std::endl << std::endl;
	ft::vector<int>::iterator it = vec_int0.begin();
	std::cout << "begin() Iterator create with begin() | " << *it <<  " |" <<std::endl;
	it = vec_int0.end();
	std::cout << "end() Overwrite with end() and prompt *--it | " << *--it <<  " |" <<std::endl;
	ft::vector<int>::reverse_iterator r_it = vec_int0.rbegin();
	std::cout << "rbegin() Iterator create with rbegin() | " << *r_it << " |" << std::endl;
	r_it = vec_int0.rend();
	std::cout << "rend() Overwrite with rend() and prompt *--it | " << *--r_it << " |" << std::endl << std::endl;

	std::cout << "Iterator property:" << std::endl << std::endl;
	it = vec_int0.begin();
	std::cout << "it[3] | " << it[3] << " |" << std::endl;
	std::cout << "++it | " << *++it << " |" << std::endl;
	std::cout << "++it | " << *++it << " |" << std::endl;
	std::cout << "--it | " << *--it << " |" << std::endl;
	std::cout << "(it + 3) = " << *(it + 3) << " |" << std::endl;
	std::cout << "(it + 3) = " << *(3 + it) << " |" << std::endl;
	std::cout << "(it - 1) = " << *(it - 1) << " |" << std::endl;
	std::cout << "it-- | " << *(it--) << " |" << std::endl;
	std::cout << "it | " << *it << " |" << std::endl;
	std::cout << "it - it| " << it - it << " |" << std::endl;
	it += 1;
	std::cout << "it += 1 before | " << *it << " |" << std::endl;
	it -= 1;
	std::cout << "it -= 1 before | " << *it << " |" << std::endl;
	std::cout << "(it < (it + 1)) | " << (it < (it + 1)) << " |" << std::endl;
	std::cout << "(it > (it + 1)) | " << (it > (it + 1)) << " |" << std::endl;
	std::cout << "(it >= (it + 1)) | " << (it >= (it + 1)) << " |" << std::endl;
	std::cout << "(it <= (it + 1)) | " << (it <= (it + 1)) << " |" << std::endl;
	std::cout << "(it == (it + 1)) | " << (it == (it + 1)) << " |" << std::endl;
	std::cout << "(it != (it + 1)) | " << (it != (it + 1)) << " |" << std::endl << std::endl;

	std::cout << "Basic reverse iterator property:" << std::endl << std::endl;
	ft::vector<int>::reverse_iterator rit = vec_int0.rbegin();
	std::cout << "rit | " << *rit << std::endl;
	std::cout << "++rit | " << *++rit << std::endl;
	std::cout << "--rit | " << *--rit << std::endl;
	std::cout << "(rit + 2) = " << *(rit + 2) << std::endl << std::endl;

	std::cout << "4. ELEMENT ACCESS:" << std::endl << std::endl;
	std::cout << "vec_int0[0] | " << vec_int0[0] << " |" << std::endl;
	vec_int0[0] = 99;
	std::cout << "vec_int0[0] after vec_int0[0] = 99 | " << vec_int0[0] << " |" << std::endl;
	show_vec_details(vec_int0);
	const ft::vector<int> const_vec_int0(vec_int0);
	show_vec_details(const_vec_int0);
	std::cout << "const_vec_int0[0] | " << const_vec_int0[0] << " |" << std::endl << std::endl;
	std::cout << "vec_int0.at(0) | " << vec_int0.at(0) << " |" << std::endl;
	try
	{
		std::cout << "vec_int0.at(100) | " << vec_int0.at(100) << " |" << std::endl;
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << "front () vec_int0.front() | " << vec_int0.front() << " |" << std::endl;
	std::cout << "back() vec_int0.back() | " << vec_int0.back() << " |" << std::endl;

	std::cout << std::endl;
	std::cout << "5. CAPACITY:" << std::endl << std::endl;
	std::cout << "size() vec_int0.size() | " << vec_int0.size() << " |" << std::endl;
	std::cout << "max_size() vec_int0.max_size() | " << vec_int0.max_size() << " |" << std::endl;
	std::cout << "resize() vec_int0.resize(10, 100)" << std::endl;
	vec_int0.resize(10, 100);
	show_vec_details(vec_int0);
	std::cout << "resize() vec_int0.resize(5, 100)" << std::endl;
	vec_int0.resize(5, 100);
	show_vec_details(vec_int0);
	std::cout << "capacity() vec_int0.capacity() | " << vec_int0.capacity() << " |" << std::endl;
	std::cout << "empty() vec_int0.empty) | " << vec_int0.empty() << " |" << std::endl;
	vec_int0.reserve(20);
	std::cout << "reserve(20) then prompt vec_int0.capacity() | " << vec_int0.capacity() << " |" << std::endl << std::endl;

	std::cout << "6. MODIFIERS:" << std::endl << std::endl;

	ft::vector<int> vec_int1(10, 111); 
	vec_int0.assign(vec_int1.begin(), vec_int1.begin() + 2);
	std::cout << "assign(vec_int1.begin(), vec_int1.begin() + 2)" << std::endl;
	show_vec_details(vec_int0);
	std::cout << "push_back(999)" << std::endl;
	vec_int0.push_back(999);
	show_vec_details(vec_int0);
	std::cout << "pop_back(999)" << std::endl;
	vec_int0.pop_back();
	show_vec_details(vec_int0);
	vec_int0.insert(vec_int0.begin(), 1);
	std::cout << "insert() single element insert(vec_int0.begin(), 1)" << std::endl;
	show_vec_details(vec_int0);
	ft::vector<int> vec_int2_speed(10000, 1);
	vec_int2_speed.insert(vec_int2_speed.begin() + 1 , 10000, 2);
	vec_int0.insert(vec_int0.begin() + 1 , 5, 2);
	std::cout << "insert() fill insert(vec_int0.begin() + 1, 5, 2)" << std::endl;
	show_vec_details(vec_int0);
	vec_int0.insert(vec_int0.begin(), vec_int0.begin(), vec_int0.end());
	std::cout << "insert() range insert(vec_int0.begin(), vec_int0.begin(), vec_int0.begin())" << std::endl;
	show_vec_details(vec_int0);
	std::cout << "erase() position erase(vec_int0.end() - 2)" << std::endl;
	vec_int0.erase(vec_int0.end() -2);
	show_vec_details(vec_int0);
	std::cout << "erase() range erase(vec_int0.begin() + 1, vec_int0.begin() + 6)" << std::endl;
	vec_int0.erase(vec_int0.begin() + 1, vec_int0.begin() + 6);
	show_vec_details(vec_int0);

	std::cout << "swap(vec_int1) first prompt vec_int0 then vec_int1" << std::endl;
	vec_int0.swap(vec_int1);
	show_vec_details(vec_int0);
	show_vec_details(vec_int1);
	std::cout << "clear()" << std::endl;
	vec_int0.clear();
	show_vec_details(vec_int0);
	

	std::cout << "6. ALLOCATOR:" << std::endl << std::endl;
	if (typeid(vec_int0.get_allocator()) == typeid(std::allocator<int>))
		std::cout << "vec_int0.get_allocator() worked"<< std::endl;
	else
		std::cout << "vec_int0.get_allocator() not working"<< std::endl;

	std::cout << "7. NON MEMBER OVERLOADS:" << std::endl << std::endl;

	vec_char1.pop_back();
	vec_char1.push_back('e');
	show_vec_details(vec_char2);
	show_vec_details(vec_char1);

	if (vec_char2 == vec_char1)
		std::cout << "yes ==" << std::endl;
	else
		std::cout << "no ==" << std::endl;
	if (vec_char2 != vec_char1)
		std::cout << "yes !=" << std::endl;
	else
		std::cout << "no !=" << std::endl;
	if (vec_char2 < vec_char1)
		std::cout << "yes <" << std::endl;
	else
		std::cout << "no <" << std::endl;
	if (vec_char2 <= vec_char1)
		std::cout << "yes <=" << std::endl;
	else
		std::cout << "no <=" << std::endl;
	if (vec_char2 > vec_char1)
		std::cout << "yes >" << std::endl;
	else
		std::cout << "no >" << std::endl;
	if (vec_char2 >= vec_char1)
		std::cout << "yes >=" << std::endl;
	else
		std::cout << "no >=" << std::endl << std::endl;

	swap(vec_char2, vec_char1);
	show_vec_details(vec_char2);
	show_vec_details(vec_char1);
	}



	//STACK PART
	{
		//constructor
	std::cout << "Excplicit stack constructor." << std::endl;
	ft::stack<int> sta_int0;
	ft::stack<int> sta_int1;

	//empty
	std::cout << "empty() sta_int0.empty) | " << sta_int0.empty() << " |" << std::endl;
	//size
	std::cout << "size() sta_int0.size() | " << sta_int0.size() << " |" << std::endl;
	sta_int0.push(999);
	sta_int1.push(999);
	//top
	std::cout << "top() : " << sta_int0.top() <<std::endl;
	//push
	std::cout << "push(888)" << std::endl;
	sta_int0.push(888);
	//pop
	std::cout << "pop()" << std::endl;
	sta_int0.pop();
	std::cout << "after pop top() : " << sta_int0.top() <<std::endl;

	if (sta_int0 == sta_int1)
		std::cout << "yes ==" << std::endl;
	else
		std::cout << "no ==" << std::endl;
	if (sta_int0 != sta_int1)
		std::cout << "yes !=" << std::endl;
	else
		std::cout << "no !=" << std::endl;
	if (sta_int0 < sta_int1)
		std::cout << "yes <" << std::endl;
	else
		std::cout << "no <" << std::endl;
	if (sta_int0 <= sta_int1)
		std::cout << "yes <=" << std::endl;
	else
		std::cout << "no <=" << std::endl;
	if (sta_int0 > sta_int1)
		std::cout << "yes >" << std::endl;
	else
		std::cout << "no >" << std::endl;
	if (sta_int0 >= sta_int1)
		std::cout << "yes >=" << std::endl;
	else
		std::cout << "no >=" << std::endl << std::endl;
	}


	//MAP PART
	{
		std::cout << "Try to respect CPLUSPLUS vector order to simplify correction." << std::endl << std::endl;
		std::cout << "0. CONSTRUCTION:" << std::endl << std::endl;
		std::cout << "Empty map constructor." << std::endl;
		ft::map<int, char> map_intchar0;
		show_map_details(map_intchar0);
		map_intchar0.insert(ft::pair<int, char>(1, 'a'));
		map_intchar0.insert(ft::make_pair(2, 'b'));
		map_intchar0.insert(ft::make_pair(3, 'c'));
		map_intchar0.insert(ft::make_pair(0, 'd'));
		ft::map<int, char> map_intchartest;
		map_intchartest.insert(ft::make_pair(13, 'b'));
		map_intchartest.insert(ft::make_pair(8, 'c'));
		show_map_details(map_intchartest);
		ft::map<int, char>::iterator itit = map_intchartest.end();
		itit--;
		std::cout << (*itit).first << std::endl;
		itit--;
		std::cout << (*itit).first << std::endl;
		show_map_details(map_intchar0);
		std::cout << "Range map constructor." << std::endl;
		ft::map<int, char>::iterator it = map_intchar0.begin();
		it++;
		ft::map<int, char> map_intchar1(it, map_intchar0.end()--);
		show_map_details(map_intchar1);
		std::cout << "Map cpy constructor." << std::endl;
		ft::map<int, char> map_intchar2(map_intchar0);
		show_map_details(map_intchar2);

		std::cout << "1. DESTRUCTION:" << std::endl << std::endl;
		std::cout << "Ensure with valgind all the allocated memory allocate with"<<
		"the given allocator is desallocate." << std::endl << std::endl;
		
		std::cout << "2. ASSIGN CONTENT:" << std::endl << std::endl;
		map_intchar0 = map_intchar1;
		show_map_details(map_intchar0);

		std::cout << "3. ITERATORS:" << std::endl << std::endl;
		it = map_intchar0.begin();
		std::cout << "begin() Iterator create with begin() Key: | " << it->first <<
		" | Value: | " << it->second <<  " |" <<std::endl;
		it = map_intchar0.end();
		it--;
		std::cout << "end() Overwrite with end() and prompt after it-- Key: | " << it->first <<
		" | Value: | " << it->second << " |" <<std::endl;
		show_map_details(map_intchar0);
		ft::map<int, char>::reverse_iterator r_it = map_intchar0.rbegin();
		std::cout << "rbegin() Iterator create with rbegin() Key: | " << r_it->first << 
		" | Value: | " << r_it->second << " |" << std::endl;
		r_it = map_intchar0.rend();
		r_it--;
		std::cout << "rend() Overwrite with rend() and prompt after r_it-- Key: | " << r_it->first << 
		" | Value: | " << r_it->second << " |" << std::endl;

		std::cout << "Iterator property:" << std::endl << std::endl;
		it = map_intchar0.begin();
		std::cout << "++it | " << (*++it).first << " |" << std::endl;
		std::cout << "++it | " << (*++it).first << " |" << std::endl;
		std::cout << "--it | " << (*--it).first << " |" << std::endl;
		std::cout << "it-- | " << (*it--).first << " |" << std::endl;
		std::cout << "it | " << (*it).first << " |" << std::endl << std::endl;
		std::cout << "Basic reverse iterator property:" << std::endl << std::endl;
		ft::map<int, char>::reverse_iterator rit = map_intchar0.rbegin();
		std::cout << "rit | " << (*rit).first << std::endl;
		std::cout << "++rit | " << (*++rit).first << std::endl;
		std::cout << "--rit | " << (*--rit).first << std::endl << std::endl;

		std::cout << "4. ELEMENT ACCESS:" << std::endl << std::endl;
		std::cout << "map_intchar0[1] | " << map_intchar0[1] << " |" << std::endl;
		map_intchar0[0] = 'A';
		std::cout << "map_intchar[0] after map_intchar0[0] = 'A' | " << map_intchar0[0] << " |" << std::endl;
		std::cout << std::endl;

		std::cout << "5. MODIFIERS:" << std::endl << std::endl;

		map_intchar0.insert(ft::pair<int, char>(9, 't'));

		std::cout << "insert() single element map_intchar0.insert(ft::pair<int, char>(9, 't'))"
		<< std::endl;
		show_map_details(map_intchar0);
		map_intchar0.insert(ft::make_pair(10, 'o'));
		map_intchar0.insert(ft::make_pair(11, 't'));
		show_map_details(map_intchar0);
		std::cout << "insert() single element with hint map_intchar0.insert(it, ft::make_pair(8, 'j')"
		<< std::endl;
		map_intchar0.insert(it, ft::make_pair(8, 'j'));
		show_map_details(map_intchar0);
		std::cout << "insert() single element with range" << std::endl;
		show_map_details(map_intchar1);
		map_intchar1.insert(map_intchar0.begin(), map_intchar0.end()--);
		show_map_details(map_intchar1);
		std::cout << "erase() position erase(map_intchar1.begin())" << std::endl;
		map_intchar1.erase(map_intchar1.begin());
		show_map_details(map_intchar1);
		std::cout << "erase() key erase(9)" << std::endl;
		map_intchar1.erase(9);
		show_map_details(map_intchar1);
		std::cout << "erase() position range(map_intchar1.begin(), map_intchar1.end()--)" << std::endl;
		map_intchar1.erase(map_intchar1.begin(), map_intchar1.end());
		show_map_details(map_intchar1);

		std::cout << "swap(map_intchar0) first prompt map_intchar0 then map_intchar1" << std::endl;
		map_intchar1.swap(map_intchar0);
		show_map_details(map_intchar0);
		show_map_details(map_intchar1);
		std::cout << "clear()" << std::endl;
		map_intchar1.clear();
		show_map_details(map_intchar1);


		std::cout << "6. OBSERVERS:" << std::endl << std::endl;
		ft::map<int, char>::key_compare compare = map_intchar0.key_comp();
		if (typeid(compare) == typeid(ft::map<int, char>::key_compare))
			std::cout << "key_comp() worked"<< std::endl;
		else
			std::cout << "key_comp() not worked"<< std::endl;
		std::cout <<" map_intchar1.value_comp()(ft::make_pair(4, 'v'), ft::make_pair(5, 'j')): " <<
		map_intchar1.value_comp()(ft::make_pair(4, 'v'), ft::make_pair(5, 'j')) << std::endl;	
		std::cout <<" map_intchar1.value_comp()(ft::make_pair(4, 'v'), ft::make_pair(4, 'j')): " <<
		map_intchar1.value_comp()(ft::make_pair(4, 'v'), ft::make_pair(4, 'j')) << std::endl;	

		std::cout << "7. OPERATIONS:" << std::endl << std::endl;
		show_map_details(map_intchar2);
		map_intchar0 = map_intchar2;
		std::cout << "(map_intchar2.find(2))->second: " << (map_intchar2.find(2))->second << std::endl;
		std::cout << "(map_intchar2.count(2)): " << (map_intchar2.count(2)) << std::endl;
		std::cout << "(map_intchar2.count(6)): " << (map_intchar2.count(6)) << std::endl;

		map_intchar2.insert(ft::make_pair(10, 'o'));
		map_intchar2.insert(ft::make_pair(11, 't'));
		map_intchar2.insert(ft::make_pair(7, 'r'));
		show_map_details(map_intchar2);
		std::cout << "(map_intchar2.lower_bound(6)->first): " << (map_intchar2.lower_bound(6))->first	<< std::endl;
		std::cout << "(map_intchar2.lower_bound(7)->first): " << (map_intchar2.lower_bound(7))->first	<< std::endl;
		std::cout << "(map_intchar2.upper_bound(6)->first): " << (map_intchar2.upper_bound(6))->first	<< std::endl;
		std::cout << "(map_intchar2.upper_bound(7)->first): " << (map_intchar2.upper_bound(7))->first	<< std::endl << std::endl;

		std::cout << "8. ALLOCATOR:" << std::endl << std::endl;
		if (typeid(map_intchar2.get_allocator()) == typeid(std::allocator< ft::pair<const int, char> >))
			std::cout << "map_intchar2.get_allocator() worked"<< std::endl << std::endl;
		else
			std::cout << "map_intchar2.get_allocator() not working"<< std::endl << std::endl;

		std::cout << "9. NON MEMBER OVERLOADS:" << std::endl << std::endl;

		show_map_details(map_intchar0);
		show_map_details(map_intchar2);

		if (map_intchar0 == map_intchar2)
			std::cout << "yes ==" << std::endl;
		else
			std::cout << "no ==" << std::endl;
		if (map_intchar0 != map_intchar2)
			std::cout << "yes !=" << std::endl;
		else
			std::cout << "no !=" << std::endl;
		if (map_intchar0 < map_intchar2)
			std::cout << "yes <" << std::endl;
		else
			std::cout << "no <" << std::endl;
		if (map_intchar0 <= map_intchar2)
			std::cout << "yes <=" << std::endl;
		else
			std::cout << "no <=" << std::endl;
		if (map_intchar0 > map_intchar2)
			std::cout << "yes >" << std::endl;
		else
			std::cout << "no >" << std::endl;
		if (map_intchar0 >= map_intchar2)
			std::cout << "yes >=" << std::endl;
		else
			std::cout << "no >=" << std::endl << std::endl;

		swap(map_intchar0, map_intchar2);
		show_map_details(map_intchar0);
		show_map_details(map_intchar2);
	}
}
