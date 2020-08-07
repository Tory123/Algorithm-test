//
//  Graph
//
//  Created by 杨涛睿 on 2020/8/3.
//  Copyright © 2020 杨涛睿. All rights reserved.
//


#include <iostream>
#include <stdio.h>
#include <string>
#include "tree.h"
#include "Vector.h"
template<typename Tv,typename Te> //顶点和边的模板类型
class Graph{
    
    void reset(){
        //所有顶点，边的辅助信息复位
        for(int i=0;i<n;i++){
            
        }
    }
};
typedef enum{UNDISCOVERED,DISCOVERED,VISITED} VStatus;
template <typename T>
struct vertex{
    T data;
    int inDegree, outDegree;     //入度和出度
    VStatus status;
    int dtime,ftime;  //被发现和访问的时间标签
    int parent;
    int priority; //在遍历树中的优先级
Vertex(T const&e):data(e),inDegree(0),outDegree(0),status(UNDISCOVERED),dtime(-1),ftime(-1),parent(-1),priority(INT_MAX){}
};
typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD} EStatus;
template <typename T>
struct edge{
    T data;
    int weight;  //权重
    EStatus status;
    edge(T const&  e,int w):data(e),weight(w),status(UNDETERMINED){}
};
template<typename T>
class GraphMatrix : public Graph{
    
};
int main()
{
    
}
