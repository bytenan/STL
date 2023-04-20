#include <iostream>
#include "HashTable.h"

int main()
{
    closed::hash<int, int> h;
    h.insert(std::pair<int, int>(1, 10));
    h.insert(std::pair<int, int>(2, 20));
    h.insert(std::pair<int, int>(3, 30));
    h.insert(std::pair<int, int>(13, 70));
    h.insert(std::pair<int, int>(12, 90));
    h.insert(std::pair<int, int>(4, 40));

    return 0;
}