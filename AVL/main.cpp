#include <iostream>
#include "AVLTree.h"

using namespace wyn;

int main()
{
    tree<int> t;
    t.insert(16);
    t.insert(3);
    t.insert(7);
    t.insert(11);
    t.insert(9);
    t.insert(26);
    t.insert(18);
    t.insert(14);
    t.insert(15);
    std::cout << t.isBlance();

    return 0;
}