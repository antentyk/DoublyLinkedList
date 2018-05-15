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
    class ConstBidirectionalIterator;

    typedef BidirectionalIterator iterator;
    typedef ConstBidirectionalIterator const_iterator;

    DoublyLinkedList(){
        head = new Node<T>(nullptr);
        tail = head;
    }

    inline iterator begin() { return iterator(head); }
    inline iterator end() { return iterator(tail); }

    inline const_iterator begin() const { return const_iterator(head); }
    inline const_iterator end() const { return const_iterator(tail); }

    inline const_iterator cbegin() const { return const_iterator(head); }
    inline const_iterator cend() const { return const_iterator(tail); }

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

    inline size_t size() const { return std::distance(cbegin(), cend()); }

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
#include "ConstBidirectionalIterator.hpp"

#endif