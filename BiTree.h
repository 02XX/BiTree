#ifndef BITREE_H_
#define BITREE_H_
#include<iostream>
#include<vector>
#include<queue>
#include"BiTreeExcept.h"
using namespace std;
template<class T>
struct Node
{
    Node * lchild;
    Node * rchild;
    //tag = 1 mean point to its pre or next
    int ltag;
    int rtag;
    T data;
};
template<class T>
class BiTree
{
protected:
    Node<T>* root;
public:
    BiTree(const vector<T> &inOrder, const vector<T> &preOrder);
    ~BiTree();
    void erase(Node<T>* r);
    Node<T>* build(const vector<T> &inOrder, const vector<T> &preOrder, int preLeft, int preRight, int inLeft, int inRight);
    //Traverse 
    void _preOrder(const Node<T>* r) const;
    void _inOrder(const Node<T>* r) const;
    void _postOrder(const Node<T>* r) const;
    void _visit(const Node<T>* r) const;
    void levelOrder() const;
    void preOrder() const {_preOrder(root);}
    void inOrder() const {_inOrder(root);}
    void postOrder() const {_postOrder(root);}
    
    //inThread
    void _inThread(Node<T>*&p, Node<T>*&pre);
    void inThread() 
    {
        Node<T>* p = root;
        Node<T>*pre = nullptr;
        _inThread(p, pre);
        pre->lchild = nullptr;
        pre->rtag = 1;
    }
    void inThreadOrder() const;
    Node<T>* firstNode(Node<T>* p) const;
    Node<T>* nextNode(Node<T>* p) const;
};
template<class T>
BiTree<T>::BiTree(const vector<T> &inOrder, const vector<T> &preOrder)
{
    /**
     * @description: build a binary tree depend on preorder and inorder sequence
     * @param {inorder-inorder sequence of tree, preorder-preorder sequence of tree}
     * @return {null}
     */
    if(inOrder.size() <= 0 || preOrder.size() <= 0 || inOrder.size()!=preOrder.size())
        throw valueError("invalid length");
    else
    {
        int preRight = int(preOrder.size()) - 1;
        int inRight = int(inOrder.size()) - 1;
        root = build(inOrder, preOrder, 0, preRight, 0, inRight);
    }
    
}
template<class T>
Node<T>* BiTree<T>::build(const vector<T> &inOrder, const vector<T> &preOrder, int preLeft, int preRight, int inLeft, int inRight)
{
    if(preLeft > preRight || inLeft > inRight)
    {
        return nullptr;
    }
    //找到根节点,建立根节点
    Node<T>* r = new Node<T>();
    r->data = preOrder[preLeft];
    r->ltag = r->rtag = 0;
    //找到pIndex中序遍历的分界线
    int count = 0;
    int pIndex = inLeft;
    while(inOrder[pIndex] != preOrder[preLeft])
    {
        pIndex++;
        count++;
    }
    //找到左右子树,连接左右子树
    r->lchild = build(inOrder, preOrder, preLeft + 1, preLeft + count, inLeft, pIndex - 1);
    r->rchild = build(inOrder, preOrder, preLeft + count + 1, preRight, inLeft + count + 1, inRight);
    return r;
    
}
template<class T>
BiTree<T>::~BiTree()
{
    erase(root);
}
template<class T>
void BiTree<T>::erase(Node<T>* r)
{
    if(r != nullptr)
    {
        if(r->ltag == 0)
            erase(r ->lchild);
        if(r->rtag == 0)
            erase(r ->rchild);
        delete r;
    }
}
template<class T>
void BiTree<T>::_preOrder(const Node<T>* r) const
{
    if(r != nullptr)
    {
        _visit(r);
        _preOrder(r->lchild);
        _preOrder(r->rchild);
    }
}
template<class T>
void BiTree<T>::_inOrder(const Node<T>* r) const
{
    if(r != nullptr)
    {
        _inOrder(r->lchild);
        _visit(r);
        _inOrder(r->rchild);
    }
}
template<class T>
void BiTree<T>::_postOrder(const Node<T>* r) const
{
    if(r != nullptr)
    {    _postOrder(r->lchild);
        _postOrder(r->rchild);
        _visit(r);
    }
}
template<class T>
void BiTree<T>::_visit(const Node<T>* r) const   
{
    std::cout << r->data << " ";
}
template<class T>
void BiTree<T>::levelOrder() const
{
    queue<Node<T>*> q;
    q.push(root);
    while(!q.empty())
    {
        Node<T>* current = q.front();
        cout << current->data << " ";
        if(current->ltag == 0 && current->lchild != nullptr)
            q.push(current->lchild);
        if(current->rtag == 0 && current->rchild != nullptr)
            q.push(current->rchild);
        q.pop();
    }
}

template<class T>
void BiTree<T>::_inThread(Node<T>*& p, Node<T>*& pre)
{
    /**
     * @description: Threaded Binary Tree 
     * @param {*}
     * @return {*}
     */
    if(p != nullptr)
    {
        _inThread(p->lchild,pre);
        if(p->lchild == nullptr)
        {
            p->lchild = pre;
            p->ltag = 1;
        }
        if(pre != nullptr && pre->rchild == nullptr)
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
        _inThread(p->rchild,pre);
    }
}
template<class T>
void BiTree<T>::inThreadOrder() const
{
    //find start
    for(Node<T>* i = firstNode(root); i != nullptr; i = nextNode(i))
    {
        cout << i->data << " ";
    }
}
template<class T>
Node<T>* BiTree<T>::nextNode(Node<T>* p) const
{
    /**
     * @description: find successor node of current node
     * @param {p:current node}
     * @return {successor node}
     */
    if(p->rtag == 0) return firstNode(p->rchild);
    else return p->rchild;
}
template<class T>
Node<T>* BiTree<T>::firstNode(Node<T>* p) const 
{
    while(p->ltag == 0)
    {
        p = p->lchild;
    }
    return p;
}
#endif
