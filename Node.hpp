#ifndef NODE_H_
#define NODE_H_

template<class T>
class Node{
public:
    Node(
        T* value,
        Node<T> *left=nullptr,
        Node<T> *right=nullptr
    ):
        value(value),
        left(left),
        right(right)
    {}

    Node(const Node<T>&) = delete;
    Node(Node<T>&&) = delete;

    ~Node(){ delete value; }

    inline T *getValue() noexcept{ return value; }
    inline T const *getValue() const noexcept { return value; }

    inline void setLeft(Node<T> *newLeft) noexcept { left = newLeft; }
    inline void setRight(Node<T> *newRight) noexcept { right = newRight; }

    inline Node<T> const *getLeft() const noexcept { return left; }
    inline Node<T> const *getRight() const noexcept { return right; }

    inline Node<T> *getLeft() noexcept { return left; }
    inline Node<T> *getRight() noexcept { return right; }
private:
    T *value;
    Node<T> *left, *right;
};

#endif