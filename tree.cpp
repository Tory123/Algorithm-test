//
//  main.cpp
//  tree
//
//  Created by 杨涛睿 on 2020/7/20.
//  Copyright © 2020 杨涛睿. All rights reserved.
//

#include <iostream>
#include "Stack.cpp"
#define BinNodePosi BinNode*
#define stature(p) ((p)?(p)->height:-1)
using namespace std;



class BinNode{
public :
    BinNodePosi parent;BinNodePosi lchild;BinNodePosi rchild;
    int data, height;
    BinNodePosi insertAsLC(int n){
        return lchild = new BinNode(n,this);
    }
    BinNodePosi insertAsLR(int n){
        return rchild = new BinNode(n,this);
    }
    int size(){
        int s = 1;
        if(lchild) s+=lchild->size();
        if(rchild) s+=rchild->size();
        return s;
    }
    void travLevel();
    void travPre();
    void travIn();
    void travPost();
    BinNode(int e,BinNodePosi p=NULL,BinNodePosi lc=NULL,BinNodePosi lr=NULL,int h=0) : data(e),parent(p),lchild(lc),rchild(lr),height(h) {}
};

class BinTree{
public:
    int _size;   //规模
    BinNodePosi _root; //根结点
    int updateHeight(BinNodePosi x);
    void updateHeightAbove(BinNodePosi x);
public :
    int size() const { return size(); }
    bool empty() const { return !_root; }
    BinNodePosi root(){ return _root; }
    BinNodePosi insertAsLR(BinNodePosi p, int e){
        _size++;
        p->insertAsLR(e);
        updateHeightAbove(p);
        return p->rchild;
    }
};
/*
   获取结点的高度
   结点的高度等于左孩子/右孩子中高度最大者 + 1
   空树的高度为-1，只有一个结点的树的高度为1
*/
int BinTree::updateHeight(BinNode *x){
    return x->height = 1 + max(stature(x->rchild),stature(x->lchild));
}
/*
 对全树整体做高度更新
 从某个结点出发，向上追溯
 */
void BinTree::updateHeightAbove(BinNode *x){
    while(x){
        updateHeight(x);x=x->parent;
    }
}
//二叉树递归先序遍历
void travPre(BinNodePosi p){
    if(!p)return ;
    cout << p->data;
    travPre(p->lchild);
    travPre(p->rchild);
}
/*
 二叉树迭代先序遍历
 T(n) = O(1)+T(a)+T(n-a-1),解得T(n)=O(n)
 */

int main(int argc, const char * argv[]) {
    
    BinNode *root = new BinNode(5,NULL);
    root->insertAsLR(3);
    root->insertAsLC(4);
    BinTree * tree = new BinTree();
    tree->updateHeight(root);
    travPre(root);
   // cout << root->height <<endl;
    return 0;
}
