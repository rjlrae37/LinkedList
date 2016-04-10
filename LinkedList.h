/*
* Author: Vladyslav Dukhin
* Version: 0.1.1 (10.04.2016)
* Copyright (c) Flexare Inc.
*/

#pragma once
#include <iostream>
#include <initializer_list>

template <typename T>
class LinkedList;

template <typename T>
class ListNode {
private:
	T _value;
	ListNode<T> *_next;
	ListNode<T> *_prev;
	friend LinkedList<T>;
public:
	ListNode(T);
	void operator =(T);
	void operator =(ListNode<T>&);
	void operator =(ListNode<T>*);
	template <typename T>
	friend std::ostream& operator <<(std::ostream&, const ListNode<T>&);
};

template <typename T>
class LinkedList {
private:
	ListNode<T> *_head, *_tail;
	size_t _size;
public:
	LinkedList();
	~LinkedList();
	LinkedList(std::initializer_list<T>);
	size_t size();
	bool isEmpty();
	bool contains(T);
	T* toArray(); // TODO : use smart pointers
	void add(T);
	void add(size_t, T);
	void addAll(std::initializer_list<T>);
	bool remove(T); // repair
	T remove(size_t);
	bool removeAll(std::initializer_list<T>);
	void clear();
	T get(size_t);
	T set(size_t, T);
	size_t indexOf(T);
	size_t lastIndexOf(T);
	LinkedList<T>& subList(size_t, size_t); // TODO : use smart pointers
	bool swap(size_t, size_t);
	void sort();
	ListNode<T>& operator [](size_t);
	template <typename T>
	friend std::ostream& operator <<(std::ostream&, const LinkedList<T>&);
};

/*
================================= Realization of class ListNode =================================
*/

template <typename T>
ListNode<T>::ListNode(T value) : _value(value), _next(nullptr), _prev(nullptr) {}

template <typename T>
std::ostream& operator <<(std::ostream &out, const ListNode<T> &element) {
	out << element._value;
	return out;
}

template <typename T>
void ListNode<T>::operator =(T value) { _value = value; }

template <typename T>
void ListNode<T>::operator =(ListNode<T> &element) { _value = element._value; }

template <typename T>
void ListNode<T>::operator =(ListNode<T> *element) { _value = element->_value; }

/*
================================= Realization of class LinkedList =================================
*/

template <typename T>
LinkedList<T>::LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
	clear();
	delete _head;
	delete _tail;
	_head = nullptr;
	_tail = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> elements) {
	for (T element : elements) {
		add(element);
	}
}

template <typename T>
size_t LinkedList<T>::size() { return _size; }

template <typename T>
bool LinkedList<T>::isEmpty() { return (_head == nullptr && _tail == nullptr && _size == 0) ? true : false; }

template <typename T>
bool LinkedList<T>::contains(T element) {
	// TODO : contains()
	return false;
}

template <typename T>
T* LinkedList<T>::toArray() {
	// TODO : toArray() + use smart pointers
	return nullptr;
}

template <typename T>
void LinkedList<T>::add(T value) {
	ListNode<T> *newElement = new ListNode<T>(value);
	if (!isEmpty()) {
		newElement->_prev = _tail;
		_tail->_next = newElement;
		_tail = newElement;
	}
	else {
		_head = _tail = newElement;
	}
	_size++;
}

template <typename T>
void LinkedList<T>::add(size_t index, T value) {
	if (index >= 0 && index < _size) {
		ListNode<T> *node = _head;
		for (size_t i = 0; i < index; ++i) {
			node = node->_next;
		}
		ListNode<T> *newElement = new ListNode<T>(value);
		newElement->_next = node;
		newElement->_prev = node->_prev;
		if (node->_prev != nullptr) node->_prev->_next = newElement;
		node->_prev = newElement;
		if (index == 0) _head = newElement;
		if (index == _size - 1) _tail = newElement->_next;
		_size++;
	}
	else {
		throw std::out_of_range("LinkedList :: add(index, value)");
	}
}

template <typename T>
void LinkedList<T>::addAll(std::initializer_list<T> elements) {
	for (T element : elements) {
		add(element);
	}
}

template <typename T>
bool LinkedList<T>::remove(T value) {
	ListNode<T> *node = _head;
	for (size_t i = 0; i < _size; ++i) {
		if (node->_value != value) {
			node = node->_next;
		}
		else {
			if (node->_prev != nullptr) node->_prev->_next = node->_next;
			if (node->_next != nullptr) node->_next->_prev = node->_prev;
			if (_tail == node && node->_prev != nullptr) _tail = node->_prev;
			if (_head == node && node->_next != nullptr) _head = node->_next;
			if (_head == _tail && _tail == node) _head = _tail = nullptr;
			node->_next = nullptr;
			node->_prev = nullptr;
			_size--;
			return true;
		}
	}
	return false;
}

template <typename T>
T LinkedList<T>::remove(size_t index) {
	if (index >= 0 && index < _size) {
		ListNode<T> *node = _head;
		for (size_t i = 0; i < index; ++i) {
			node = node->_next;
		}
		if (node->_prev != nullptr) node->_prev->_next = node->_next;
		if (node->_next != nullptr) node->_next->_prev = node->_prev;
		if (_tail == node && node->_prev != nullptr) _tail = node->_prev;
		if (_head == node && node->_next != nullptr) _head = node->_next;
		if (_head == _tail && _tail == node) _head = _tail = nullptr;
		node->_next = nullptr;
		node->_prev = nullptr;
		_size--;
		return node->_value;
	}
	else {
		throw std::out_of_range("LinkedList :: remove(index)");
	}
}

template <typename T>
bool LinkedList<T>::removeAll(std::initializer_list<T> elements) {
	// TODO : removeAll()
}

template <typename T>
void LinkedList<T>::clear() {
	if (!isEmpty()) {
		ListNode<T> *node = _tail;
		while (node != nullptr) {
			if (node->_next != nullptr) {
				delete node->_next;
				node->_next = nullptr;
			}
			if (node->_prev != nullptr)
				node = node->_prev;
			else {
				delete node;
				node = nullptr;
			}
		}
		_head = _tail = nullptr;
		_size = 0;
	}
}

template <typename T>
T LinkedList<T>::get(size_t index) {
	if (index >= 0 && index < _size) {
		ListNode<T> *node = _head;
		for (size_t i = 0; i < index; ++i) {
			node = node->_next;
		}
		return node->_value;
	}
	else {
		throw std::out_of_range("LinkedList :: get(index)");
	}
}

template <typename T>
T LinkedList<T>::set(size_t index, T value) {
	if (index >= 0 && index < _size) {
		ListNode<T> *node = _head;
		for (size_t i = 0; i < index; ++i) {
			node = node->_next;
		}
		T tmp = node->_value;
		node->_value = value;
		return tmp;
	}
	else {
		throw std::out_of_range("LinkedList :: set(index, value)");
	}
}

template <typename T>
size_t LinkedList<T>::indexOf(T element) {}

template <typename T>
size_t LinkedList<T>::lastIndexOf(T element) {}

template <typename T>
LinkedList<T>& LinkedList<T>::subList(size_t fromIndex, size_t toIndex) {}

template <typename T>
bool LinkedList<T>::swap(size_t index1, size_t index2) {}

template <typename T>
void LinkedList<T>::sort() {}

template <typename T>
ListNode<T>& LinkedList<T>::operator [](size_t index) {}

template <typename T>
std::ostream& operator <<(std::ostream &out, const LinkedList<T> &list) {}