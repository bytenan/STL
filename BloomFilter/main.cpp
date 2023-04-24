#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include "BloomFilter.h"

int main()
{
    const size_t N = 10000;
    wyn::BloomFilte<N, std::string> bf;
    for (size_t i = 0; i < N; ++i)
    {
        bf.set(std::string("https://cn.bing.com/search?q=ln2&PC=U316&FORM=CHROMN" + std::to_string(i)));
    }
    size_t x = 0, y = 0;
    srand((unsigned int)time(nullptr));
    for (size_t i = 0; i < N; ++i)
    {
        int r = rand();
        if (bf.test(std::string("hps://cn.bing.c&PCMCHROMN" + std::to_string(r))))
        {
            ++x;
        }
        if (bf.test(std::string("https://cn.bing.com/search?q=ln2&PC=U316&FORM=CHROMN" + std::to_string(i))))
        {
            ++y;
        }
    }
    std::cout << "误报率：" << x * 1.0 / y  << std::endl;
    return 0;
}