#include <iostream>
#include <utility>
#include "RBTree.h"

using namespace wyn;

int main()
{
    tree<int> t;
    srand(time(nullptr));
    const size_t N = 100000;
    for (size_t i = 0; i < N; ++i)
    {
        size_t x = rand();
        t.insert(x);
    }
    std::cout << t.IsValidRBTree() << std::endl;
    return 0;
}