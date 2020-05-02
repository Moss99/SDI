#pragma once
#include <iostream>
#include <cassert>

template <class T>
struct node {
    T data;
    node* next;
};

template <class T>
class linkedList {
private:
    node<T>* head;
    node<T>* tail;
    int length = 0;
public:
    linkedList();
    void addBack(T n);
    void addFront(T n);
    void addAfterNode(node<T>* a, T n);
    void clear();
    T get(unsigned int n);
	node<T>* getNode(unsigned int n);
    int size();
    std::string print();
};



template <class T>
inline linkedList<T>::linkedList() {
    head = nullptr;
    tail = nullptr;
}

template <class T>
inline void linkedList<T>::addBack(T n) {
    node<T>* tmp = new node<T>;
    tmp->data = n;
    tmp->next = nullptr;

    if (head == nullptr)
    {
        head = tmp;
        tail = tmp;
    }
    else
    {
		//tail = tmp;
        tail->next = tmp;
        tail = tail->next;
    }
    length++;
}

template<class T>
inline void linkedList<T>::addFront(T n) {
    node<T>* tmp = new node<T>;
    tmp->data = n;
    tmp->next = head;
    head = tmp;
	if (tail == nullptr)
		tail = head;
    length++;
}

template<class T>
inline void linkedList<T>::addAfterNode(node<T>* a, T n) {
    node<T>* p = new node<T>;
    p->data = n;
    p->next = a->next;
    a->next = p;
    length++;
}

template<class T>
inline void linkedList<T>::clear() {
    
    node<T>* current = head;
    node<T>* next;

    while (current != nullptr)
    {
        next = current->next;
        free(current);
        current = next;
    }

    head = nullptr;
    length = 0;
}  


template<class T>
inline T linkedList<T>::get(unsigned int n) {
    node<T>* current = head;

    int count = 0;
    while (current != nullptr)
    {
        if (count == n)
            return(current->data);
        count++;
        current = current->next;
    }

    assert(0);
}

template<class T>
inline node<T>* linkedList<T>::getNode(unsigned int n) {
	node<T>* current = head;

	int count = 0;
	while (current != nullptr)
	{
		if (count == n)
			return(current);
		count++;
		current = current->next;
	}

	assert(0);
}

template<class T>
inline int linkedList<T>::size() {
    return length;
}

template <class T>
inline std::string linkedList<T>::print() {
    std::string out = "";
    node<T>* tmp;
    tmp = head;
    while (tmp != nullptr)
    {
        //out += tmp->data;

		out += std::to_string(tmp->data);
		//std::cout << out;
        tmp = tmp->next;
    }
	
    return out;
}