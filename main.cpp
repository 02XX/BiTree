#include<iostream>
#include<string>
#include<vector>
#include"BiTree.h"
using namespace std;

int main()
{
    vector<string> preOrder {"a","b","d","e","c","f","g"};
    vector<string> inOrder {"d","b","e","a","f","c","g"};
    // BiTree<string> tree(inOrder, preOrder);
    BiTree<string> Tree(inOrder, preOrder);
    Tree.levelOrder();
    // Tree.inThread();
    // Tree.inThreadOrder();
    // Tree.inThread();
    // Tree.inThreadOrder();


    
    

    return 0;
}
