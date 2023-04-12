#include <iostream>
#include "Priority_queue.h"

using namespace wyn;

void print(priority_queue<int> &pq)
{
    while (!pq.empty())
    {
        std::cout << pq.top() << std::endl;
        pq.pop();
    }
    std::cout << "pq.size(): " << pq.size() << std::endl;
    if (pq.empty())
    {
        std::cout << "pq.empty(): " << "true" << std::endl;
    }
    else
    {
        std::cout << "pq.empty(): " << "true" << std::endl;
    }
}

int main()
{
    priority_queue<int> pq1;
    pq1.push(1);
    pq1.push(2);
    pq1.push(5);
    pq1.push(3);
    pq1.push(7);
    pq1.push(9);
    print(pq1);

    return 0;
}