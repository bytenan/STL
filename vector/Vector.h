#pragma once

#include <iostream>
#include <cassert>

namespace wyn
{
    template <class T>
    class vector
    {
    public:
        typedef T *iterator;
        typedef const T *const_iterator;
        iterator begin()
        {
            return start;
        }
        const_iterator begin() const
        {
            return start;
        }
        iterator end()
        {
            return finish;
        }
        const_iterator end() const
        {
            return finish;
        }
        vector()
            : start(nullptr), finish(nullptr), end_of_storage(nullptr)
        {
            std::cout << "vector()" << std::endl;
        }
        vector(size_t n, const T &val = T())
            : start(nullptr), finish(nullptr), end_of_storage(nullptr)
        {
            std::cout << "vector(size_t n, const T &val = T())" << std::endl;
            start = new T[n];
            finish = start;
            while (n--)
            {
                *finish++ = val;
            }
            end_of_storage = finish;
        }
        vector(const vector<T> &x)
            : start(nullptr), finish(nullptr), end_of_storage(nullptr)
        {
            std::cout << "vector(const vector<T> &x)" << std::endl;
            start = new T[x.size()];
            finish = start;
            for (const auto &val : x)
            {
                *finish++ = val;
            }
            end_of_storage = finish;
        }
        vector<T> &operator=(vector<T> x)
        {
            std::cout << "vector<T> &operator=(vector<T> x)" << std::endl;
            swap(x);
            return *this;
        }
        ~vector()
        {
            delete[] start;
            start = nullptr;
            finish = 0;
            end_of_storage = 0;
            std::cout << "~vector()" << std::endl;
        }
        size_t size() const
        {
            return finish - start;
        }
        size_t max_size() const
        {
            return (unsigned int)-1 / sizeof(T);
        }
        size_t capacity() const
        {
            return end_of_storage - start;
        }
        bool empty() const
        {
            return start == finish;
        }
        void resize(size_t n, const T &val = T())
        {
            if (n <= size())
            {
                finish = start + n;
            }
            else
            {
                reserve(n);
                n -= size();
                while (n--)
                {
                    *finish++ = val;
                }
            }
        }
        void reserve(size_t n)
        {
            if (n > capacity())
            {
                iterator start_ = new T[n];
                iterator finish_ = start_;
                for (const T &val : *this)
                {
                    *finish_++ = val;
                }
                delete[] start;
                start = start_;
                finish = finish_;
                end_of_storage = start + n;
            }
        }
        T &operator[](size_t pos)
        {
            return *(start + pos);
        }
        const T &operator[](size_t pos) const
        {
            return *(start + pos);
        }
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            clear();
            reserve(last - first);
            while (first != last)
            {
                *finish++ = *first++;
            }
        }
        void assign(size_t n, const T &val)
        {
            clear();
            reserve(n);
            while (n--)
            {
                *finish++ = val;
            }
        }
        void push_back(const T &val)
        {
            if (size() == capacity())
            {
                reserve(capacity() == 0 ? 1 : capacity() * 2);
            }
            *finish++ = val;
        }
        void pop_back()
        {
            assert(!empty());
            --finish;
        }
        iterator insert(iterator pos, const T &val)
        {
            assert(pos >= begin() && pos <= end());
            if (size() == capacity())
            {
                size_t offset = pos - start;
                reserve(capacity() == 0 ? 1 : capacity() * 2);
                pos = start + offset;
            }
            iterator end = finish - 1;
            while (end >= pos)
            {
                *(end + 1) = *end;
                --end;
            }
            finish += 1;
            *pos = val;
            return pos;
        }
        void insert(iterator pos, size_t n, const T &val)
        {
            assert(pos >= begin() && pos <= end());
            size_t offset = pos - start;
            reserve(capacity() + n);
            pos = start + offset;
            iterator end = finish - 1;
            while (end >= pos)
            {
                *(end + n) = *end;
                --end;
            }
            finish += n;
            while (n--)
            {
                *pos++ = val;
            }
        }
        template <class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last)
        {
            assert(pos >= begin() && pos <= end());
            size_t offset = pos - start;
            reserve(capacity() + (last - first));
            pos = start + offset;
            size_t n = last - first;
            iterator end = finish - 1;
            while (end >= pos)
            {
                *(end + n) = *end;
                --end;
            }
            finish += n;
            while (first != last)
            {
                *pos++ = *first++;
            }
        }
        iterator erase(iterator pos)
        {
            assert(pos >= begin() && pos < end());
            iterator first = pos + 1;
            while (first != end())
            {
                *(first - 1) = *first;
                ++first;
            }
            --finish;
            return pos;
        }
        iterator erase(iterator first, iterator last)
        {
            assert(first < last);
            assert(first >= begin() && first < end());
            assert(last > begin() && last <= end());
            iterator ret = first;
            size_t n = last - first;
            while (n--)
            {
                *first++ = *last++;
                --finish;
            }
            return ret;
        }
        void swap(vector<T> &x)
        {
            std::swap(start, x.start);
            std::swap(finish, x.finish);
            std::swap(end_of_storage, x.end_of_storage);
        }
        void clear()
        {
            finish = start;
        }

    private:
        iterator start;
        iterator finish;
        iterator end_of_storage;
    };
}