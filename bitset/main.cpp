#include <iostream>
#include "Bitset.h"

int main()
{
    wyn::bitset<100> bs;
    std::cout << "bs.count(): " << bs.count() << std::endl;
    std::cout << "bs.size(): " << bs.size() << std::endl;
    bs.set(3);
    bs.set(53);
    bs.set(37);
    bs.set(45);
    bs.set(85);
    std::cout << "bs.count(): " << bs.count() << std::endl;
    std::cout << "bs.size(): " << bs.size() << std::endl;
    std::cout << bs.test(3) << std::endl;
    std::cout << bs.test(53) << std::endl;
    std::cout << bs.test(376) << std::endl;
    std::cout << bs.test(77) << std::endl;
    std::cout << bs.test(47) << std::endl;
    std::cout << bs.test(37) << std::endl;
    std::cout << bs.test(45) << std::endl;
    std::cout << bs.test(85) << std::endl;
    bs.reset();
    std::cout << "bs.count(): " << bs.count() << std::endl;
    std::cout << "bs.size(): " << bs.size() << std::endl;
    return 0;
}