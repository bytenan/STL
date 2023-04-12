#pragma once

#include <iostream>
#include <deque>
#include <cassert>

namespace wyn
{
    template <class T, class Container = std::deque<T>>
    class stack
    {
    public:
        explicit stack(const Container &con = Container())
            : con_(con)
        {
        }
        bool empty() const
        {
            return con_.empty();
        }
        size_t size() const
        {
            return con_.size();
        }
        T &top()
        {
            assert(!empty());
            return con_.back();
        }
        void push(const T &val)
        {
            con_.push_back(val);
        }
        template <class... Args>
        void emplace(Args &&...args)
        {
            con_.emplace(args...);
        }
        void pop()
        {
            assert(!empty());
            con_.pop_back();
        }
        void swap(stack<T> &x)
        {
            con_.swap(x.con_);
        }

    private:
        Container con_;
    };
}