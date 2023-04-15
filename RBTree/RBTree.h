#pragma once

#include <iostream>

namespace wyn
{
    enum Color
    {
        RED,
        BLACK
    };

    template <class T>
    class Node
    {
    public:
        T data_;
        Color color_;
        Node<T> *parent_;
        Node<T> *left_;
        Node<T> *right_;
        Node(const T &data)
            : data_(data), color_(RED), parent_(nullptr), left_(nullptr), right_(nullptr)
        {
        }
    };

    template <class T>
    class tree
    {
    public:
        tree()
            : root_(nullptr)
        {
        }
        bool insert(const T &data)
        {
            if (!root_)
            {
                root_ = new Node<T>(data);
                root_->color_ = BLACK;
                return true;
            }
            Node<T> *parent = nullptr;
            Node<T> *cur = root_;
            while (cur)
            {
                if (cur->data_ < data)
                {
                    parent = cur;
                    cur = cur->right_;
                }
                else if (cur->data_ > data)
                {
                    parent = cur;
                    cur = cur->left_;
                }
                else
                {
                    return false;
                }
            }
            cur = new Node<T>(data);
            if (parent->data_ < data)
            {
                parent->right_ = cur;
            }
            else
            {
                parent->left_ = cur;
            }
            cur->parent_ = parent;
            while (parent && parent->color_ == RED)
            {
                Node<T> *grandparent = parent->parent_;
                if (grandparent->left_ == parent)
                {
                    Node<T> *uncle = grandparent->right_;
                    if (uncle && uncle->color_ == RED)
                    {
                        grandparent->color_ = RED;
                        parent->color_ = uncle->color_ = BLACK;
                        cur = grandparent;
                        parent = cur->parent_;
                    }
                    else
                    {
                        if (parent->left_ == cur)
                        {
                            rotateL(grandparent);
                            parent->color_ = BLACK;
                            grandparent->color_ = RED;
                        }
                        else
                        {
                            rotateR(parent);
                            rotateL(grandparent);
                            cur->color_ = BLACK;
                            grandparent->color_ = RED;
                        }
                        break;
                    }
                }
                else
                {
                    Node<T> *uncle = grandparent->left_;
                    if (uncle && uncle->color_ == RED)
                    {
                        grandparent->color_ = RED;
                        parent->color_ = uncle->color_ = BLACK;
                        cur = grandparent;
                        parent = cur->parent_;
                    }
                    else
                    {
                        if (parent->right_ == cur)
                        {
                            rotateR(grandparent);
                            parent->color_ = BLACK;
                            grandparent->color_ = RED;
                        }
                        else
                        {
                            rotateL(parent);
                            rotateR(grandparent);
                            cur->color_ = BLACK;
                            grandparent->color_ = RED;
                        }
                        break;
                    }
                }
            }
            root_->color_ = BLACK;
            return true;
        }

        bool IsValidRBTree()
        {
            Node<T> *pRoot = root_;
            // 空树也是红黑树
            if (nullptr == pRoot)
                return true;
            // 检测根节点是否满足情况
            if (BLACK != pRoot->color_)
            {
                std::cout << "违反红黑树性质二：根节点必须为黑色" << std::endl;
                return false;
            }
            // 获取任意一条路径中黑色节点的个数
            size_t blackCount = 0;
            Node<T> *pCur = pRoot;
            while (pCur)
            {
                if (BLACK == pCur->color_)
                    blackCount++;
                pCur = pCur->left_;
            }
            // 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
            size_t k = 0;
            return _IsValidRBTree(pRoot, k, blackCount);
        }

        bool _IsValidRBTree(Node<T> *pRoot, size_t k, const size_t blackCount)
        {
            // 走到null之后，判断k和black是否相等
            if (nullptr == pRoot)
            {
                if (k != blackCount)
                {
                    std::cout << "违反性质四：每条路径中黑色节点的个数必须相同" << std::endl;
                    return false;
                }
                return true;
            }
            // 统计黑色节点的个数
            if (BLACK == pRoot->color_)
                k++;
            // 检测当前节点与其双亲是否都为红色
            Node<T> *pParent = pRoot->parent_;
            if (pParent && RED == pParent->color_ && RED == pRoot->color_)
            {
                std::cout << "违反性质三：没有连在一起的红色节点" << std::endl;
                return false;
            }
            return _IsValidRBTree(pRoot->left_, k, blackCount) &&
                   _IsValidRBTree(pRoot->right_, k, blackCount);
        }

    private:
        void rotateR(Node<T> *parent)
        {
            Node<T> *grandparent = parent->parent_;
            Node<T> *childR = parent->right_;
            Node<T> *childRL = childR->left_;
            childR->left_ = parent;
            parent->parent_ = childR;
            parent->right_ = childRL;
            if (childRL)
            {
                childRL->parent_ = parent;
            }
            if (grandparent)
            {
                if (grandparent->right_ == parent)
                {
                    grandparent->right_ = childR;
                }
                else
                {
                    grandparent->left_ = childR;
                }
                childR->parent_ = grandparent;
            }
            else
            {
                childR->parent_ = nullptr;
                root_ = childR;
            }
        }
        void rotateL(Node<T> *parent)
        {
            Node<T> *grandparent = parent->parent_;
            Node<T> *childL = parent->left_;
            Node<T> *childLR = childL->right_;
            childL->right_ = parent;
            parent->parent_ = childL;
            parent->left_ = childLR;
            if (childLR)
            {
                childLR->parent_ = parent;
            }
            if (grandparent)
            {
                if (grandparent->left_ == parent)
                {
                    grandparent->left_ = childL;
                }
                else
                {
                    grandparent->right_ = childL;
                }
                childL->parent_ = grandparent;
            }
            else
            {
                childL->parent_ = nullptr;
                root_ = childL;
            }
        }

    private:
        Node<T> *root_;
    };
}