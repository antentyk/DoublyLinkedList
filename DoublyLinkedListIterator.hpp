#ifndef DOUBLY_LINKED_LIST_ITERATOR_H_
#define DOUBLY_LINKED_LIST_ITERATOR_H_

#include <cstddef>
#include <iterator>

#include "Node.hpp"
#include "DoublyLinkedList.hpp"

template<class T>
template<class ValueType>
class DoublyLinkedList<T>::Iterator{
public:
    friend class DoublyLinkedList<T>;

    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ValueType value_type;
    typedef ptrdiff_t difference_type;
    typedef ValueType* pointer;
    typedef ValueType& reference;

    Iterator(Node<T>* data):
        data(data)
    {}

    Iterator():
        Iterator(nullptr)
    {}

    // Iterator(const Iterator<ValueType>&) = default;
    // Iterator<ValueType> operator=(const Iterator<ValueType>&) = default;

    inline bool operator==(const Iterator<ValueType> &other)const noexcept{ 
        return data == other.data; 
    }
    inline bool operator!=(const Iterator<ValueType> &other)const{
        return !operator==(other);
    }

    inline reference operator*(){
        return *data->getValue();
    }
    inline pointer operator->(){
        return data->getValue();
    }

    Iterator<ValueType>& operator++(){
        if(data->getRight() != nullptr)
            data = data->getRight();
        return *this;
    }
    Iterator<ValueType> operator++(int){
        Iterator<ValueType> tmp(*this);
        if(data->getRight() != nullptr)
            data = data->getRight();
        return tmp;
    }

    Iterator<ValueType>& operator--(){
        if(data->getLeft() != nullptr)
            data = data->getLeft();
        return *this;
    }
    Iterator<ValueType> operator--(int){
        Iterator<ValueType> tmp(*this);
        if(data->getLeft() != nullptr)
            data = data->getLeft();
        return tmp;
    }
private:
    Node<T>* data;
};


#endif