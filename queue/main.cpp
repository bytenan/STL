#include <iostream>
#include <string>
#include "Queue.h"

using namespace wyn;

void print(queue<std::string> & qe)
{
    std::cout << "qe.front(): " << qe.front() << std::endl;
    std::cout << "qe.back(): " << qe.back() << std::endl;
    std::cout << "qe.size(): " << qe.size() << std::endl;
    if (qe.empty())
    {
        std::cout << "qe.empty(): " << "true" << std::endl;
    }
    else
    {
        std::cout << "qe.empty(): " << "false" << std::endl;
    }
}

int main()
{
    queue<std::string> qe1;
    qe1.push("a");
    qe1.push("b");
    qe1.push("c");
    qe1.push("d");
    qe1.push("e");
    print(qe1);
    print(qe1);
    return 0;
}