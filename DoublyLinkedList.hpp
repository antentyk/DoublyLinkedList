#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

#include <cstddef>
#include <iterator>
#include <algorithm>
#include <exception>

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

    DoublyLinkedList(const DoublyLinkedList<T> &) = delete;
    DoublyLinkedList(DoublyLinkedList<T>&&) = delete;

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

    void erase(iterator it){
        Node<T> *current = it.data;

        Node<T>
            *left = current->getLeft(),
            *right = current->getRight();

        if(it == begin())
            head = right;

        delete current;

        if(left != nullptr)
            left->setRight(right);
        if(right != nullptr)
            right->setLeft(left);
    }
    void erase(iterator first, iterator last){
        Node<T>
            *left = first.data->getLeft(),
            *right = last.data;
        
        if(first == begin())
            head = right;
        
        Node<T> *current = first.data;
        while(current != right){
            Node<T> *tmp(current);
            current = current->getRight();
            delete tmp;
        }

        if(left != nullptr)
            left->setRight(right);
        
        if(right != nullptr)
            right->setLeft(left);
    }

    inline void pop_front(){ erase(begin()); }
    inline void pop_back(){ erase(--end()); }
    
    inline bool empty() const { return cbegin() == cend(); }
    inline void clear() { erase(begin(), end()); }

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