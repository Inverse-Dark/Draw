/**
 * @File: INVDK_Tree.hpp
 * @Author: InverseDark
 * @Email: InverseDark@InverseDark.xyz
 * @Date: 2025/3/30
 * @Description: 数据结构：树
 */
#ifndef INVDK_TREE_HPP
#define INVDK_TREE_HPP

#include "INVDK_Data.h"
#include "INVDK_Utility.hpp"
#include "INVDK_Functional.hpp"
#include "INVDK_Memory.hpp"
//#include "INVDK_Memory_lib.h"

namespace INVDK
{
	/// @brief 颜色类型
	enum Color { RED, BLACK };

    /// @brief 红黑树节点模板
	template <class _Key, class _Ty>
	struct TreeNode
	{
        using ValueType = INVDK::pair<const _Key, _Ty>; // 键为 const 类型

        ValueType data;         // 键值对
        Color color;            // 节点颜色
        TreeNode* parent;       // 父节点指针
        TreeNode* left;         // 左子节点指针
        TreeNode* right;        // 右子节点指针

        /// @brief 构造函数
        /// @param val [IN] 键值对
        /// @param c [IN] 节点颜色
        /// @param p [IN] 父节点指针
        /// @param l [IN] 左子节点指针
        /// @param r [IN] 右子节点指针
        TreeNode(const ValueType& val, Color c, TreeNode* p, TreeNode* l, TreeNode* r)
            : data(val), color(c), parent(p), left(l), right(r)
        {}
	};

    template <class _Key, class _Ty, class _Compare = INVDK::less<_Key>,
        class _Allocator = INVDK::allocator<TreeNode<_Key, _Ty>>>
	class RBTree
	{
        using Node = TreeNode<_Key, _Ty>;
        using ValueType = class Node::ValueType;
	public:
        /// @brief 构造函数
        RBTree() 
            : comp(_Compare()), alloc(_Allocator()), node_count(0)
        {
            sentinel = create_node(ValueType(), Color::BLACK);
            root = sentinel;
            sentinel->left = sentinel;
            sentinel->right = sentinel;
            sentinel->parent = root;
        }
        /// @brief 析构函数
        ~RBTree()
        {
            clear(root);
            destroy_node(sentinel);
        }

        // 插入键值对（核心方法）
        INVDK_VOID insert(const ValueType& val)
        {
            Node* z = create_node(val, Color::RED); // 新节点默认为红色
            Node* y = sentinel;
            Node* x = root;

            // 1. 标准二叉搜索树插入
            while (x != sentinel)
            {
                y = x;
                if (comp(z->data.first, x->data.first))
                {
                    x = x->left;
                }
                else
                {
                    x = x->right;
                }
            }

            z->parent = y;
            if (y == sentinel)
            {
                root = z;
            }
            else if (comp(z->data.first, y->data.first))
            {
                y->left = z;
            }
            else
            {
                y->right = z;
            }

            // 初始化子节点为哨兵
            z->left = sentinel;
            z->right = sentinel;
            node_count++;

            // 2. 修复红黑树性质
            insert_fixup(z);
        }

        // 查找键（返回值的指针）
        _Ty* find(const _Key& key)
        {
            Node* current = root;
            while (current != sentinel)
            {
                if (key == current->data.first)
                {
                    return &current->data.second;
                }
                else if (comp(key, current->data.first))
                {
                    current = current->left;
                }
                else
                {
                    current = current->right;
                }
            }
            return NULL;
        }

        // 迭代器类（支持双向遍历）
        class Iterator
        {
        private:
            Node* current;
            Node* sentinel;

        public:
            Iterator(Node* node, Node* sentinel) : current(node), sentinel(sentinel) {}

            ValueType& operator*() { return current->data; }
            Iterator& operator++()
            {
                if (current->right != sentinel)
                {
                    current = current->right;
                    while (current->left != sentinel)
                    {
                        current = current->left;
                    }
                }
                else
                {
                    Node* p = current->parent;
                    while (p != sentinel && current == p->right)
                    {
                        current = p;
                        p = p->parent;
                    }
                    current = p;
                }
                return *this;
            }
            Iterator& operator--() { /* 对称实现反向操作 */ }
            INVDK_BOOL operator!=(const Iterator& other) const { return current != other.current; }
        };

        Iterator begin() const
        {
            Node* leftmost = root;
            while (leftmost->left != sentinel)
            {
                leftmost = leftmost->left;
            }
            return Iterator(leftmost, sentinel);
        }

        Iterator end() const { return Iterator(sentinel, sentinel); }

    private:
        // 创建节点（使用分配器）
        Node* create_node(const ValueType& val, Color color)
        {
            Node* node = alloc.allocate(1);
            alloc.construct(node, val, color, sentinel, sentinel, sentinel);
            return node;
        }

        // 销毁节点
        INVDK_VOID destroy_node(Node* node)
        {
            alloc.destroy(node);
            alloc.deallocate(node, 1);
        }

        // 清空子树
        INVDK_VOID clear(Node* node)
        {
            if (node != sentinel)
            {
                clear(node->left);
                clear(node->right);
                destroy_node(node);
            }
        }

        // 左旋操作
        void left_rotate(Node* x)
        {
            Node* y = x->right;
            x->right = y->left;
            if (y->left != sentinel)
            {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == sentinel)
            {
                root = y;
            }
            else if (x == x->parent->left)
            {
                x->parent->left = y;
            }
            else
            {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
        }

        // 右旋操作（对称实现）
        void right_rotate(Node* y) { /* 类似左旋反向操作 */ }

        // 插入修复（维护红黑树性质）
        void insert_fixup(Node* z)
        {
            while (z->parent->color == Color::RED)
            {
                if (z->parent == z->parent->parent->left)
                {
                    Node* uncle = z->parent->parent->right;
                    if (uncle->color == Color::RED)
                    {
                        // Case 1: 叔叔是红色
                        z->parent->color = Color::BLACK;
                        uncle->color = Color::BLACK;
                        z->parent->parent->color = Color::RED;
                        z = z->parent->parent;
                    }
                    else
                    {
                        if (z == z->parent->right)
                        {
                            // Case 2: 三角形结构转直线
                            z = z->parent;
                            left_rotate(z);
                        }
                        // Case 3: 直线结构调整
                        z->parent->color = Color::BLACK;
                        z->parent->parent->color = Color::RED;
                        right_rotate(z->parent->parent);
                    }
                }
                else
                {
                    // 对称处理右侧情况
                    Node* uncle = z->parent->parent->left;
                    if (uncle->color == Color::RED)
                    {
                        z->parent->color = Color::BLACK;
                        uncle->color = Color::BLACK;
                        z->parent->parent->color = Color::RED;
                        z = z->parent->parent;
                    }
                    else
                    {
                        if (z == z->parent->left)
                        {
                            z = z->parent;
                            right_rotate(z);
                        }
                        z->parent->color = Color::BLACK;
                        z->parent->parent->color = Color::RED;
                        left_rotate(z->parent->parent);
                    }
                }
            }
            root->color = Color::BLACK; // 根节点必须为黑色
        }

	private:
		Node* root;             // 根节点
		Node* sentinel;         // 哨兵节点（统一空指针处理）
		_Compare comp;          // 键比较器
		_Allocator alloc;       // 内存分配器
		size_t node_count;      // 节点数量

	};

}

#endif // !INVDK_TREE_HPP
