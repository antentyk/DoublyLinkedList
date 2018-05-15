#include <gtest/gtest.h>
#include <memory>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <random>

#include "Node.hpp"
#include "DoublyLinkedList.hpp"

using std::shared_ptr;
using std::make_shared;

template class Node<int>;
template class Node<double>;
template class Node<std::set<std::string>>;
template class Node<std::map<float, size_t>>;
template class Node<std::vector<std::vector<std::string>>>;

TEST(Node, init){
    Node<int> n1(new int(1));
    Node<int> n2(new int(2), &n1);
    Node<int> n3(new int(3), &n1, &n2);
}

TEST(Node, getValue){
    Node<int> n1(new int(1));
    ASSERT_EQ(*n1.getValue(), 1);
    ASSERT_NO_THROW(*n1.getValue() = 2);
    ASSERT_EQ(*n1.getValue(), 2);
}

TEST(Node, left){
    Node<int> n1(new int(1));
    Node<int> n2(new int(2));

    n1.setLeft(&n2);
    ASSERT_EQ(*(n1.getLeft()->getValue()), 2);
}

TEST(Node, right){
    Node<int> n1(new int(1));
    Node<int> n2(new int(2));

    n1.setRight(&n2);
    ASSERT_EQ(*(n1.getRight()->getValue()), 2);
}

TEST(Node, constMethods){
    const Node<int> n1(new int(1));
    Node<int> n2(new int(2));

    ASSERT_EQ(*(n1.getValue()), 1);
    // *(n1.getValue()) = 2;
    // n1.setLeft(&n2);
    // *(n1.getLeft()->getValue()) = 3;
}

template class DoublyLinkedList<int>;
template class DoublyLinkedList<std::string>;
template class DoublyLinkedList<std::map<std::string, int>>;
template class DoublyLinkedList<std::vector<std::vector<std::string>>>;

TEST(DoublyLinkedList, init){
    DoublyLinkedList<int> lst();
}

TEST(DoublyLinkedList, pushBack){
    DoublyLinkedList<int> lst;
    ASSERT_NO_THROW(lst.push_back(1));
    ASSERT_EQ(*(lst.begin()), 1);
    ASSERT_NO_THROW(lst.push_back(2));
    ASSERT_EQ(*(lst.begin()), 1);
    ASSERT_EQ(*(--lst.end()), 2);
}

TEST(DoublyLinkedList, pushBackAndTraverse){
    DoublyLinkedList<int> lst;
    for(int i = 0; i < 10; ++i)
        lst.push_back(i);
    
    int expected = 0;
    for(auto it = lst.begin(); it != lst.end(); ++it)
        ASSERT_EQ(*it, expected++);

    expected = 0;
    for(auto it: lst)
        ASSERT_EQ(it, expected++);
}

TEST(DoublyLinkedList, pushFront){
    DoublyLinkedList<int> lst;
    ASSERT_NO_THROW(lst.push_front(1));
    ASSERT_EQ(*lst.begin(), 1);
    ASSERT_NO_THROW(lst.push_front(2));
    ASSERT_EQ(*lst.begin(), 2);
    ASSERT_EQ(*(--lst.end()), 1);
}

TEST(DoublyLinkedList, pushFrontAndTraverse){
    DoublyLinkedList<int> lst;
    for(int i = 9; i >= 0; --i)
        lst.push_front(i);
    
    int expected = 0;
    for(auto it = lst.begin(); it != lst.end(); ++it)
        ASSERT_EQ(*it, expected++);

    expected = 0;
    for(auto it: lst)
        ASSERT_EQ(it, expected++);
}

TEST(DoublyLinkedList, insert){
    DoublyLinkedList<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    auto it = lst.begin();
    ++it; ++it;

    lst.insert(it, 5);

    std::vector<int> expectedValues{1,2,5,3};
    auto expectedIt = expectedValues.begin();

    for(auto it: lst)
        ASSERT_EQ(it, *(expectedIt++));
}

TEST(DoublyLinkedList, transform){
    DoublyLinkedList<int> lst;
    for(int i = 0; i < 10; ++i)
        lst.push_back(i);

    std::transform(lst.begin(), lst.end(), lst.begin(), [](int x){return x + 1;});
    
    int expected = 1;
    for(auto it: lst)
        ASSERT_EQ(it, expected++);
    
    std::transform(lst.begin(), lst.end(), lst.begin(), [](int x){return x % 2;});

    expected = 1;
    for(auto it: lst){
        ASSERT_EQ(it, expected);
        expected ^= 1;
    }
}

TEST(DoublyLinkedList, find){
    DoublyLinkedList<int> lst;
    for(int i = 0; i < 10; ++i)
        lst.push_back(i);
    
    auto it = std::find(lst.begin(), lst.end(), 0);
    ASSERT_TRUE(it == lst.begin());
}

TEST(DoublyLinkedList, reverse){
    DoublyLinkedList<int> lst;

    for(int i = 0; i < 10; ++i)
        lst.push_back(i);
    
    std::reverse(lst.begin(), lst.end());

    int expected = 9;
    for(auto it: lst)
        ASSERT_EQ(it, expected--);
}

int main(int argc, char ** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}