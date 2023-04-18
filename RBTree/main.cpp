#include <iostream>
#include <utility>
#include "RBTree.h"
#include "Set.h"
#include "Map.h"

void func(const wyn:: map<int, int> &m)
{
	auto it = m.begin();
	// it->second = 1000;
}

int main()
{
    wyn::map<int, int> m;
    for (int i = 0; i < 10; ++i)
    {
    	m[i] = i + 10;
    }

    for (auto e : m)
    {
    	std::cout << e.first << " : " << e.second << std::endl;
    }

    func(m);

    return 0;
}