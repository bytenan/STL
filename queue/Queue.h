#pragma once

#include <iostream>
#include <deque>
#include <cassert>

namespace wyn
{
    template <class T, class Container = std::deque<T>>
    class queue
    {
    public:
        explicit queue(const Container &con = Container())
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
        T &front()
        {
            assert(!empty());
            return con_.front();
        }
        T &back()
        {
            assert(!empty());
            return con_.back();
        }
        void push(const T &val)
        {
            con_.push_back(val);
        }
        template <class... Args>
        void emplace(Args&&... args)
        {
            con_.emplace_back(args...);
        }
        void pop()
        {
            assert(!empty());
            con_.pop_front();
        }
        void swap(queue<T> &x)
        {
            con_.swap(x.con_);
        }

    private:
        Container con_;
    };
}