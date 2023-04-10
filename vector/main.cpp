#include <iostream>
#include <string>
#include "Vector.h"

using namespace wyn;

void print(const vector<std::string> &v)
{
    std::cout << "v.size(): " << v.size() << std::endl;
    std::cout << "v.capacity: " << v.capacity() << std::endl;
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout<< std::endl << "-----------------------------------------------------------------------------------" << std::endl;
}

int main()
{
    vector<std::string> v1;
    v1.push_back("a");
    v1.push_back("b");
    v1.push_back("c");
    v1.push_back("d");
    v1.push_back("e");
    v1.push_back("f");
    v1.push_back("g");
    v1.push_back("h");
    v1.push_back("i");
    v1.push_back("h");
    print(v1);
    v1.erase(v1.begin(), v1.end());
    print(v1);
    return 0;
}