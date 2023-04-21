#include <iostream>
#include "HashTable.h"
#include <list>

template <class Value>
class HashFcn
{
public:
    Value operator()(const Value &value) const
    {
        return value;
    }
};

template <class Value>
class ExtractKey
{
public:
    size_t operator()(const Value &value) const
    {
        return (size_t)value;
    }
};

int main()
{
    open::hash<int, int, HashFcn<int>, ExtractKey<int>> h;
    h.insert(1);
    h.insert(2);
    h.insert(3);
    h.insert(4);
    h.insert(11);
    h.insert(13);
    h.insert(12);
    h.insert(111);
    h.insert(333);

    auto it = h.begin();

    std::list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    auto itl = l.begin();
    std::cout << *itl << std::endl;
    std::cout << *(itl.operator->()) << std::endl;
    

    std::cout << it.operator->() << std::endl;
    std::cout << *(it.operator->()) << std::endl;
    std::cout << it.operator*() << std::endl;
    std::cout << *it << std::endl;
    // ++it;
    // std::cout << *it << std::endl;

    // for (auto & e : h)
    // {
    //     std::cout << e << std::endl;
    // }
    

    return 0;
}