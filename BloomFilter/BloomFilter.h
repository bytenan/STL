#pragma once
#include <iostream>
#include <bitset>

namespace wyn
{
    template <class T>
    class BKDRHash
    {
    public:
        size_t operator()(const T &str)
        {
            register size_t hash = 0;
            for (const auto &ch : str)
            {
                hash = hash * 131 + ch;
            }
            return hash;
        }
    };

    template <class T>
    class SDBMHash
    {
    public:
        size_t operator()(const T &str)
        {
            register size_t hash = 0;
            for (const auto &ch : str)
            {
                hash = 65599 * hash + ch;
            }
            return hash;
        }
    };

    template <class T>
    class RSHash
    {
    public:
        size_t operator()(const T &str)
        {
            register size_t hash = 0;
            size_t magic = 63689;
            for (const auto &ch : str)
            {
                hash = hash * magic + ch;
                magic *= 378551;
            }
            return hash;
        }
    };

    /**
     * k 为哈希函数个数
     * m 为布隆过滤器长度
     * n 为插入的元素个数
     * 选择合适的k和m值的公式：k = (m/n) * ln2    ln2 ≈ 0.693
     */
    template <size_t N, class T, class HashFcn1 = BKDRHash<T>, class HashFcn2 = SDBMHash<T>, class HashFcn3 = RSHash<T> >
    class BloomFilte
    {
    public:
        void set(const T &val)
        {
            size_t pos1 = HashFcn1()(val) % (N * 5);
            size_t pos2 = HashFcn2()(val) % (N * 5);
            size_t pos3 = HashFcn3()(val) % (N * 5);
            bs_.set(pos1);
            bs_.set(pos2);
            bs_.set(pos3);
        }
        bool test(const T &val) const
        {
            size_t pos1 = HashFcn1()(val) % (N * 5);
            size_t pos2 = HashFcn2()(val) % (N * 5);
            size_t pos3 = HashFcn3()(val) % (N * 5);
            if (!bs_.test(pos1) || !bs_.test(pos2) || !bs_.test(pos3)) // 当有任意一个为0时，即val一定不存在
            {
                return false;
            }
            return true; // 即使三个都为1，但val是可能存在
        }

    private:
        std::bitset<N * 5> bs_; // 这里测试时：假设k = 3，近似认为m = 5n， 所以当插入元素个数为N时，开辟5N个bit位
    };
}