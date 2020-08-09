//
//  Vector
//
//  Created by 杨涛睿 on 2020/8/3.
//  Copyright © 2020 杨涛睿. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#define DEFAULT_CAPACITY  3
typedef int Rank;
using namespace std;
template<typename T>
class Vector{
private:
    Rank _size; int Capacity; T* _elem; //_size为有效数据
protected:
    void copyFrom ( T const* A, Rank lo, Rank hi ){  //复制数组区间A[lo, hi)
      int n  = hi - lo;
      _elem = new T[_Capacity= 2*(hi - lo)];
      for(_size = 0;_size<n;_elem[_size++]=A[lo++]);
    }
    void expand(){  //空间不足时扩容
        /*  容量加倍策略
            分摊分析——假设每次插入固定大小的容量，每次扩容I个单位：
            则每插入I个元素就需要进行一次扩容，
            每次扩容时间成本线性增长，I，2I，3I...,(m-1)I...。m和n看成是等阶的
            总体时间成本：O(n^2),每次分摊的时间成本为O(n)
            如果每次扩增一倍，则每次经过加倍的时间才会进行一次扩容，每次的时间成本依次为：
            1，2，4，8...2^m,呈现几何级数，与末项同阶，m和n等阶，因此整体复杂度为O(n),
            每次分摊为O(1)。
            倍增策略可理解为是在空间效率上做出牺牲，从而在时间效率上得到改进。
            */
           if(_size<Capacity)return;
           T* oldElem = _elem;
           _elem = new T[Capacity <<= 1];
           for (int i = 0; i< _size;i++) {
               _elem[i] = oldElem[i];
           }
           delete []oldElem;
    }
    
    T remove (Rank lo, Rank hi){ //区间删除,范围[lo,hi)
        while(hi<_size)
            _elem[lo++] = _elem[hi++];
        _size = lo;
             
        return hi - lo;
    }
    T remove (Rank n){ //单元素删除,通过区间删除接口来实现
        T e = _elem[n];
        remove(n,n+1);
        return e;
    }
    //约定：取出向量中元素值为e的最靠后的元素，无序向量查找为”输入敏感“的算法
    Rank find(T const& e,Rank lo,Rank hi){
        while (lo < hi--&&e!=_elem[hi]) ;
        return hi;
    }
public:  //构造函数和析构函数
    Vector ( int c = DEFAULT_CAPACITY, int s = 0, T v = 0 ){
    _elem = new T[Capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v );
    }
    Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); }
    ~Vector() { delete [] _elem; } //释放内部空间
    void traverse(){
          for (int i=0; i<_size; i++) {
              cout << _elem[i]<<endl;
          }
      }
    /*
     无序向量去重
     算法正确性证明：
     （1）不变形：算法运行的任何时刻，前缀的所有元素必然互异
     （2）单调性：后缀越来越短
     */
    int deduplicate(){
        int oldSize = _size;
        for(Rank i = 1;i<_size;){
            if (find(_elem[i],0,i)>-1) remove(i);
            else i++ ;
        }
        /*
        while ( i< _size)
            (find(_elem[i],0,i)<0)?i++:remove(i);
         */
        return oldSize - _size;
    }
    //返回逆序对总数,返回的值是0说明向量有序
    int disordered(){
        int n = 0;
        for (int i = 1; i<_size; i++)
            n+= (_elem[i-1]>_elem[i]);
        return n;
    }
    //有序向量去重，时间复杂度O(n)
    int uniquify(){
        Rank i =0 , j=0;
        while(++j <_size)
            if(_elem[j]!=_elem[i])_elem[++i]=_elem[j];
        _size = ++i;
        return j-i;
        /*
         int oldSize = _size;
         Rank i = 0,j=1;
         while (j<_size) {
            int n = _elem[i];int k = _elem[j];
            if (_elem[j]!=_elem[i]){ _elem[++i] = _elem[j] ; j++ ; }
            else j++;
         }
        _size = i + 1;
        return oldSize - _size;
         */
    }
};
