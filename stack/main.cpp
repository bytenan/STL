#include <iostream>
#include <string>
#include "Stack.h"

using namespace wyn;

void print(stack<std::string> & st)
{
    std::cout << "st.top(): " << st.top() << std::endl;
    std::cout << "st.size(): " << st.size() << std::endl;
    if (st.empty())
    {
        std::cout << "st.empty(): " << "true" << std::endl;
    }
    else
    {
        std::cout << "st.empty(): " << "false" << std::endl;
    }
}

int main()
{
    stack<std::string> st1;
    st1.push("a");
    stack<std::string> st2;
    st2.push("b");

    print(st1);
    print(st2);
    st1.swap(st2);
    print(st1);
    print(st2);
    
    return 0;
}