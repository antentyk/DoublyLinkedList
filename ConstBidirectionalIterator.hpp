#ifndef CONST_BIDIRECTIONAL_ITERATOR_
#define CONST_BIDIRECTIONAL_ITERATOR_

#include "DoublyLinkedList.hpp"
#include "Node.hpp"

template<class T>
class DoublyLinkedList<T>::ConstBidirectionalIterator{
public:
    friend class DoublyLinkedList<T>;

    typedef ptrdiff_t difference_type;
    typedef const T value_type;
    typedef T const * pointer;
    typedef const T& reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    ConstBidirectionalIterator(Node<T> const *data):
        data(data)
    {}

    inline bool operator==(const ConstBidirectionalIterator &other){
        return &(*data) == &(*other.data);
    }
    inline bool operator!=(const ConstBidirectionalIterator &other){
        return !operator==(other);
    }

    inline const T& operator*(){
        return *(data->getValue());
    }

    inline T const * operator->(){
        return data->getValue();
    }

    ConstBidirectionalIterator& operator++(){
        if(data->getRight() != nullptr)
            data = data->getRight();
        return *this;
    }
    ConstBidirectionalIterator operator++(int){
        ConstBidirectionalIterator tmp(*this);
        if(data->getRight() != nullptr)
            data = data->getRight();
        return tmp;
    }

    ConstBidirectionalIterator& operator--(){
        if(data->getLeft() != nullptr)
            data = data->getLeft();
        return *this;
    }
    ConstBidirectionalIterator operator--(int){
        ConstBidirectionalIterator tmp(*this);
        if(data->getLeft() != nullptr)
            data = data->getLeft();
        return tmp;
    }
private:
    Node<T> const *data;
};

#endif