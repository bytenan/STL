#include "String.h"

using namespace wyn;

void print(const string &str)
{
    std::cout << "&str: " << &str << std::endl;
    std::cout << "str.c_str(): " << str.c_str() << std::endl;
    std::cout << "str.size(): " << str.size() << std::endl;
    std::cout << "str.capacity(): " << str.capacity() << std::endl;
}

int main()
{

    string str = "hello world";
    string tmp = "zxcvb";
    print(str);
    str.erase(0, 12);
    print(str);
    

    return 0;
}