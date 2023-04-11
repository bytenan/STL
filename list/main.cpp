#include <iostream>
#include <string>
#include "List.h"
#include <list>
#include <typeinfo>

using namespace wyn;

void print(const list<int> &l)
{
    
    // for (const auto &data : l)
    // {
    //     std::cout << data << std::endl;
    // }
    std::cout << std::endl;
}

int main()
{
    list<int> l1;
    l1.push_back(1);
    l1.push_back(1);
    l1.push_back(1);
    l1.push_back(1);
    l1.push_back(1);
    l1.push_back(1);
    print(l1);

    return 0;
}