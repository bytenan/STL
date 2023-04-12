#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include <utility>

namespace wyn
{

    template <class T>
    class less
    {
    public:
        bool operator()(const T &lhs, const T &rhs)
        {
            return lhs < rhs;
        }
    };

    template <class T>
    class greater
    {
    public:
        bool operator()(const T &lhs, const T &rhs)
        {
            return lhs > rhs;
        }
    };

    template <class T, class Container = std::vector<T>, class Compare = less<T>>
    class priority_queue
    {
    public:
        explicit priority_queue(const Container &con = Container())
            : con_(con)
        {
        }
        template<class InputIterator>
        priority_queue(InputIterator first, InputIterator last) 
            : con_(first, last)
        {
            for (int i = (size() - 1 - 1) / 2; i >= 0; --i)
            {
                adjust_down(i);
            }
        }
        bool empty() const
        {
            return con_.empty();
        }
        size_t size() const
        {
            return con_.size();
        }
        const T &top() const 
        {
            assert(!empty());
            return con_.front();
        }
        void push(const T &val)
        {
            con_.push_back(val);
            adjust_up(size() - 1);
        }
        template <class... Args>
        void emplace(Args... args)
        {
            con_.emplace_back(args...);
            adjust_up(size() - 1);
        }
        void pop()
        {
            assert(!empty());
            std::swap(con_[0], con_[size() - 1]);
            con_.pop_back();
            adjust_down(0);
        }
        void swap(priority_queue &x)
        {
            con_.swap(x.con_);
        }

    private:
        void adjust_up(size_t child)
        {
            while (child)
            {
                size_t parent = (child - 1) / 2;
                if (Compare()(con_[parent], con_[child]))
                {
                    std::swap(con_[parent], con_[child]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else
                {
                    break;
                }
            }
        }
        void adjust_down(size_t parent)
        {
            size_t child = parent * 2 + 1;
            while (child < size())
            {
                if (child + 1 < size() && Compare()(con_[child], con_[child + 1]))
                {
                    ++child;
                }
                if (Compare()(con_[parent], con_[child]))
                {
                    std::swap(con_[parent], con_[child]);
                    parent = child;
                    child = parent * 2;
                }
                else
                {
                    break;
                }
            }
        }

    private:
        Container con_;
    };
}