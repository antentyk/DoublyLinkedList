#include <gtest/gtest.h>
#include <memory>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

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

TEST(DoublyLinkedList, arrowOperator){
    DoublyLinkedList<std::vector<int>> lst;

    std::vector<int> tmp;
    tmp.push_back(1);
    tmp.push_back(2);
    tmp.push_back(3);

    lst.push_back(tmp);

    ASSERT_EQ(lst.begin()->size(), 3);
    ASSERT_EQ(lst.cbegin()->size(), 3);
    ASSERT_FALSE(lst.begin()->empty());
    ASSERT_FALSE(lst.cbegin()->empty());
}

TEST(DoublyLinkedList, constIterators){
    DoublyLinkedList<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    const DoublyLinkedList<int> &lstAlias = lst;

    int expected = 1;
    for(auto it: lstAlias)
        ASSERT_EQ(expected++, it);
    
    expected = 1;
    for(auto it = lstAlias.cbegin(); it != lstAlias.cend(); ++it)
        ASSERT_EQ(expected++, *it);
}

TEST(DoublyLinkedList, size){
    DoublyLinkedList<int> lst;
    ASSERT_EQ(lst.size(), 0);

    for(size_t i = 1; i <= 1000; ++i){
        if(i % 2 == 0)
            lst.push_front(i);
        else
            lst.push_back(i);
        
        ASSERT_EQ(lst.size(), i);
    }
}

TEST(DoublyLinkedList, popFront){
    DoublyLinkedList<int> lst;
    lst.push_back(1);

    lst.pop_front();
    ASSERT_EQ(lst.size(), 0);

    for(int i = 0; i < 10; i++)
        lst.push_back(i);
    
    for(int i = 0; i < 10; i++){
        ASSERT_EQ(lst.size(), 10 - i);
        ASSERT_EQ(*lst.cbegin(), i);
        ASSERT_EQ(*(--lst.cend()), 9);
        ASSERT_EQ(*(--lst.end()), 9);
        ASSERT_EQ(*lst.begin(), i);
        lst.pop_front();
    }
    ASSERT_EQ(lst.size(), 0);
}

TEST(DoublyLinkedList, popBack){
    DoublyLinkedList<int> lst;
    lst.push_back(1);

    lst.pop_back();
    ASSERT_TRUE(lst.empty());

    for(int i = 0; i < 10; ++i)
        lst.push_back(i);
    
    for(int i = 0; i < 10; ++i){
        ASSERT_EQ(lst.size(), (10 - i));
        ASSERT_EQ(*lst.begin(), 0);
        ASSERT_EQ(*lst.cbegin(), 0);
        ASSERT_EQ(*(--lst.end()), 10 - 1 - i);
        ASSERT_EQ(*(--lst.cend()), 10 - 1 - i);
        lst.pop_back();
    }
    ASSERT_EQ(lst.size(), 0);
}

TEST(DoublyLinkedList, empty){
    DoublyLinkedList<int> lst;
    ASSERT_TRUE(lst.empty());
    lst.push_back(1);
    ASSERT_FALSE(lst.empty());
    lst.push_front(2);
    ASSERT_FALSE(lst.empty());
    lst.pop_front();
    ASSERT_FALSE(lst.empty());
    lst.pop_front();
    ASSERT_TRUE(lst.empty());
}

TEST(DoublyLinkedList, clear){
    DoublyLinkedList<int> lst;
    
    for(int i = 0; i < 10000; ++i)
        lst.push_back(i);
    
    ASSERT_EQ(lst.size(), 10000);
    ASSERT_FALSE(lst.empty());

    lst.clear();
    ASSERT_TRUE(lst.empty());
    ASSERT_EQ(lst.size(), 0);

    lst.clear();
    ASSERT_EQ(lst.size(), 0);
}

TEST(DoublyLinkedList, eraseSingle){
    DoublyLinkedList<int> lst;

    for(int i = 0; i < 5; ++i)
        lst.push_back(i);
    
    auto pos = lst.begin();
    ++pos; ++pos;
    lst.erase(pos);

    ASSERT_EQ(lst.size(), 4);

    std::vector<int> expectedValues{0, 1, 3, 4};

    int expectedIndex = 0;
    for(auto it: lst)
        ASSERT_EQ(it, expectedValues[expectedIndex++]);
}

TEST(DoublyLinkedList, eraseRange){
    DoublyLinkedList<int> lst;

    for(int i = 0; i < 5; ++i)
        lst.push_back(i);
    
    auto first = lst.begin();
    ++first;

    auto last = lst.end();
    --last;

    lst.erase(first, last);

    std::vector<int> expectedValues{0, 4};

    int expectedIndex = 0;
    for(auto it: lst)
        ASSERT_EQ(it, expectedValues[expectedIndex++]);
}

TEST(DoublyLinkedList, removeIf){
    DoublyLinkedList<int> lst;

    for(int i = 0; i < 100; ++i)
        lst.push_back(i);
    
    lst.erase(
        std::remove_if(lst.begin(), lst.end(), [](int i){return (i % 2) == 0;}),
        lst.end()
    );

    ASSERT_EQ(lst.size(), 50);

    int expected = 1;
    for(auto it: lst){
        ASSERT_EQ(it, expected);
        expected += 2;
    }
}

int main(int argc, char ** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}