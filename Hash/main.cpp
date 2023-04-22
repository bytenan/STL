#include <iostream>
#include "Unordered_set.h"
#include "Unordered_map.h"

void func(const wyn_map::unordered_map<int, int> &m)
{
    // for (auto &e : m)
    // {
    //     e.first = 10;
    //     e.second = 20;
    // }
    for (auto &e : m)
    {
        std::cout << e.first << " : " << e.second << std::endl;
    }
}

int main()
{
    wyn_set::unordered_set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(11);
    s.insert(22);
    s.insert(111);
    s.insert(45);
    for (auto &e : s)
    {
        std::cout << e << std::endl;
    }

    // wyn_map::unordered_map<int, int> m;
    // m.insert(std::pair<int, int>(1, 10));
    // m.insert(std::pair<int, int>(2, 20));
    // m.insert(std::pair<int, int>(3, 30));
    // m.insert(std::pair<int, int>(4, 40));
    // m.insert(std::pair<int, int>(11, 110));
    // m.insert(std::pair<int, int>(22, 220));
    // m.insert(std::pair<int, int>(111, 1110));
    // // func(m);
    // for (auto &e : m)
    // {
    //     // e.first = 10;
    //     e.second = 20;
    // }
    // for (auto &e : m)
    // {
    //     std::cout << e.first << " : " << e.second << std::endl;
    // }

    return 0;
}