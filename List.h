//
//  main.cpp
//  List
//
//  Created by 杨涛睿 on 2020/8/9.
//  Copyright © 2020 杨涛睿. All rights reserved.
//

#include <iostream>
typedef int Rank;
#define Posi(T) ListNode<T>*

using namespace std;
template<typename T>
struct ListNode{
    T data;
    Posi(T) pred; Posi(T) succ; //前驱和后继
    ListNode(){}
    ListNode(T e,Posi(T)p = NULL,Posi(T)s = NULL):data(e),pred(p),succ(s){}
    Posi(T) insertAsPred(T const&e);
    Posi(T) insertAsSucc(T const&e);
};
template<typename T>
Posi(T) ListNode<T>::insertAsPred(const T &e){
  
    Posi(T) p = new ListNode(e,this->pred,this);
    pred->succ = p;
    pred = p;
    return p;
   
   /*
    不能在函数栈中创建结点，会被其他函数定义的变量覆盖！
    ListNode p(e,this->pred,this);
    pred->succ = &p;
    pred = &p;
    return &p;
    */
}
    
template<typename T>
class List{
private:
    int _size;
    Posi(T) header;
    Posi(T) trailer;
protected:
    void init();
    int  clear();
    void copyNodes ( Posi(T), int n);
public:
    T remove(Posi(T) p);
    /*重载下标操作符
     在函数后加const的含义是：该函数不修改对象内数据成员的值
     */
    T& operator[] ( Rank r ) const{
        Posi(T) p = header->succ;
        while(0<r--)p=p->succ;
        return p->data;
    }
    //插入结点
    Posi(T) insertAsBefore(T const&e,Posi(T)p);
    Posi(T) insertNode(T const&e);
    //构造函数
    List(){
        init();
    }
     List ( List<T> const& L ); //列表整体复制
     List ( List<T> const& L, Rank r, int n );//复制列表L自第R项起的第n项
     List ( Posi(T) p, int n ); //复制列表自位置P起的n项
    //析构函数
    ~ List();
    //无序列表唯一化
    int deduplicate();
    //有序列表唯一化
    int uniquify();
    //列表遍历
    void traverse();
    //无序列表查找,与有序列表共同约定d返回不大于e的最后者
    Posi(T) find(T const&e,Posi(T)p,int n);
    //有序列表查找
    Posi(T) search(T const&e,Posi(T)p,int n);
};


template<typename T>
void List<T>::init(){
    _size = 0;
    header = new ListNode<T>(0);
    trailer = new ListNode<T>(0);
    header->succ = trailer;
    trailer->pred = header;
    header->pred = NULL;
    trailer->succ=NULL;
}
template<typename T>
void List<T>::copyNodes(Posi(T) p, int n){
    init();
    while (n--) {
        insertNode(p->data);
        p=p->succ;
    }
}
//析构函数，先删除所有结点，再删除两个哨兵
template<typename T>
 List<T>::~List(){
    clear();
    delete(header);
    delete(trailer);
}
//删除结点
template<typename T>
T List<T>::remove(Posi(T) p){
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete(p);_size--;
    return e;
}
//遍历
template<typename T>
void List<T>::traverse(){
    Posi(T) p= header->succ;
    while(p!=trailer){
        cout << p->data <<endl;
        p = p->succ;
    }
}
//在结点前插入
template<typename T>
Posi(T) List<T>::insertAsBefore(const T &e, Posi(T) p){
    _size++;
    return p->insertAsPred(e);
}
//在列表末尾新增结点
template<typename T>
Posi(T) List<T>::insertNode(const T &e){
    _size++;
    Posi(T) p = new ListNode<T>(e,trailer->pred,trailer);
    trailer->pred->succ = p;
    trailer ->pred = p;
    return p;
    /*
      _size++;
      ListNode<T>node(e);
      node.pred = trailer->pred;
      node.succ = trailer;
      trailer->pred = &node;
      node.pred->succ = &node;
    */
}

//清空结点
template<typename T>
int List<T>::clear(){
    int oldSize = _size;
    while(_size>0)
        remove(header->succ);
    return oldSize;
}
//无序列表唯一化，思想：前缀无重复元素,后缀加入前缀
template <typename T>
int List<T>::deduplicate(){
    if(_size<2)return 0;
    int oldSize = _size;
    Posi(T) p = header->succ;Rank r = 1;
    while(trailer!=(p=p->succ)){
        Posi(T) q = find(p->data, p, r);
        q?remove(q):r++;
    }
    return oldSize - _size;
}
//有序列表唯一化，思想：前缀无重复元素,后缀加入前缀
template<typename T>
int List<T>::uniquify(){
    if(_size<2)return 0;
    int oldSize = _size;
    Posi(T) p = header->succ;
    Posi(T) q  ;
    while(trailer!=(q=p->succ)){
        if(p->data!=q->data)p=q;
        else remove(q);
    }
    return oldSize - _size;
}
//无序列表查找，n在唯一化时起作用
template<typename T>
Posi(T) List<T>::find(T const&e,Posi(T)p,int n){
    while(n-->0){
        if(e==(p=p->pred)->data)return p;
    }
    return NULL;
}
//有序列表查找
template<typename T>
Posi(T) List<T>::search(T const&e,Posi(T)p,int n){
    while(n-->0){
         if(((p=p->pred)->data) <=e)break;
        return p;
    }
   
    return p;
}

