#ifndef BIDIRECTIONAL_ITERATOR_
#define BIDIRECTIONAL_ITERATOR_

#include "DoublyLinkedList.hpp"
#include "Node.hpp"

template<class T>
class DoublyLinkedList<T>::BidirectionalIterator{
public:
    friend class DoublyLinkedList<T>;

    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    BidirectionalIterator(Node<T> *data):
        data(data)
    {}

    inline bool operator==(const BidirectionalIterator &other){
        return &(*data) == &(*other.data);
    }
    inline bool operator!=(const BidirectionalIterator &other){
        return !operator==(other);
    }

    inline T& operator*() {
        return *data->getValue();
    }

    BidirectionalIterator& operator++(){
        if(data->getRight() != nullptr)
            data = data->getRight();
        return *this;
    }
    BidirectionalIterator operator++(int){
        BidirectionalIterator tmp(*this);
        if(data->getRight() != nullptr)
            data = data->getRight();
        return tmp;
    }

    BidirectionalIterator& operator--(){
        if(data->getLeft() != nullptr)
            data = data->getLeft();
        return *this;
    }
    BidirectionalIterator operator--(int){
        BidirectionalIterator tmp(*this);
        if(data->getLeft() != nullptr)
            data = data->getLeft();
        return tmp;
    }
private:
    Node<T> *data;
};

#endif