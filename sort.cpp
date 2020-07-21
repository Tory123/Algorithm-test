//
//  main.cpp
//  sort
//
//  Created by 杨涛睿 on 2020/6/25.
//  Copyright © 2020 杨涛睿. All rights reserved.
//

#include <iostream>
using namespace std;
typedef int Rank;
int Array[10000];


Rank partition(Rank lo,Rank hi){
    // 随机选取候选轴点
    
       int seq = rand()%(hi-lo) + lo;
       Rank n = Array[seq];
       Array[seq] = Array[lo];
       Array[lo] = n;
       Rank pivot = Array[lo];
    
    //轴点转化
    while(lo<hi){
        while((lo<hi)&&(pivot<=Array[hi]))hi--;
        Array[lo] = Array[hi] ;
        while((lo<hi)&&(pivot>=Array[lo]))lo++;
        Array[hi] = Array[lo] ;
    }
    Array[lo] = pivot;
    return lo;
}
void quicksort(Rank lo,Rank hi){
    if(hi-lo<2) return ;
    Rank mi = partition(lo,hi);
    quicksort(lo, mi);
    quicksort(mi+1, hi);
}
bool bubble(Rank lo, Rank hi){
    Rank last = lo ;
    while(++lo < hi){
        if(Array[lo-1] > Array[lo]) {
            last = lo;
            int holder = Array[lo-1];
            Array[lo-1] = Array[lo];
            Array[lo] = holder;
        }
    }
    return last;
}
void bubbleSort(Rank lo, Rank hi){
    while(lo< bubble(lo,hi));
}
void merge(Rank lo,Rank mid , Rank hi){
    //A指向区间的起点
    int * A = Array + lo;
    //将向量的前半段复制到新开辟的空间中
    int lb = mid - lo ;int *B = new int[lb];
    for(int i = 0;i<lb;i++)B[i] = A[i];
    //C指向区间的后半段,C并不需要另辟空间缓存
    int lc = hi - mid;
    int * C = Array + mid;
    /*
     每次比较B,C两个子向量当前的首元素，
     取出其中更小的项，放入到A中
     j或k每次其中一个会加1，初始j+k = 0，最终j+k = n。
     因此迭代最多只会进行n次，merge算法时间复杂度为O(n)
     */
    for(Rank i =0,j=0,k=0;(j<lb)||(k<lc);){
        if((j<lb)&&((k>=lc)||(B[j]<=C[k]))) A[i++] = B[j++];
        if((k<lc)&&((j>=lb)||(C[k] < B[j]))) A[i++] = C[k++];
    }
    delete []B;
}
void mergeSort(Rank lo,Rank hi){
    if((hi - lo)<2 )return ;
    int mid = (hi + lo) >> 1 ;
    mergeSort(lo, mid);
    mergeSort(mid, hi);
    merge(lo,mid,hi);
}
void selectionSort(Rank lo,Rank hi){
    Rank i,j,smallest;
    for( i = 0;i<(hi-lo-1);i++){
        smallest = i;
        for(j = i+1;j<hi;j++)
            if(Array[j]<Array[smallest]) smallest = j;
        int swap = Array[smallest];
        Array[smallest] = Array[i];
        Array[i] = swap;
    }
}

int main(int argc, const char * argv[]) {
    for(int i=0;i<10000;i++)Array[i] = rand()%10000;
    selectionSort(0, 10000);
//  quicksort(0, 1000000);
    for(int i=0;i<10000;i++)cout << Array[i]<<endl;
}
