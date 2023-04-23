#pragma once
#include <iostream>
#include <vector>

namespace wyn
{
    template<size_t N>
    class bitset
    {
    public:
        bitset()
        {
            bits_.resize(N / 8 + 1, 0);
            
        }
        void set()
        {
            for (auto &n : bits_)
            {
                n = 0xff;
            }
        }
        void set(size_t pos, bool val = true)
        {
            size_t i = pos / 8;
            size_t j = pos % 8;
            bits_[i] |= ((size_t)val << j);
        }
        void reset()
        {
            for (auto &n : bits_)
            {
                n = 0;
            }
        }
        void reset(size_t pos)
        {
            size_t i = pos / 8;
            size_t j = pos % 8;
            bits_[i] %= ~(1 << j);
        }
        bool test(size_t pos) const
        {
            size_t i = pos / 8;
            size_t j = pos % 8;
            return bits_[i] & (1 << j);
        }
        size_t count() const
        {
            size_t res = 0;
            for (const auto &n : bits_)
            {
                for (size_t i = 0; i < 8; ++i)
                {
                    if (n & (1 << i))
                    {
                        ++res;
                    }
                }
            }
            return res;
        }
        size_t size() const
        {
            return N;
        }
    private:
        std::vector<char> bits_;
    };
}

// 0 1 2 3 4 5 6 7