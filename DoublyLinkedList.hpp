#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

#include <cstddef>
#include <iterator>
#include <algorithm>

#include "Node.hpp"

template<class T>
class DoublyLinkedList{
public:
    class BidirectionalIterator;

    typedef BidirectionalIterator iterator;

    DoublyLinkedList(){
        head = new Node<T>(nullptr);
        tail = head;
    }

    inline iterator begin() { return iterator(head); }
    inline iterator end() { return iterator(tail); }

    void insert(iterator it, const T& val){
        Node<T>
            *left = it.data->getLeft(),
            *right = it.data;
        
        Node<T> *current = new Node<T>(new T(val));

        if(left != nullptr)
            left->setRight(current);
        if(right != nullptr)
            right->setLeft(current);
        
        current->setLeft(left);
        current->setRight(right);

        if(it == begin())
            head = current;
    }

    inline void push_back(const T& val){ insert(end(), val); }
    inline void push_front(const T& val){ insert(begin(), val); }

    ~DoublyLinkedList(){
        Node<T> *current = head;
        while(current != nullptr){
            Node<T> *tmp = current;
            current = current->getRight();
            delete tmp;
        }
    }
private:
    Node<T> *head, *tail;
};

#include "BidirectionalIterator.hpp"

#endif