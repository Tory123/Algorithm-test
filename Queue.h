//
//  Queue
//
//  Created by 杨涛睿 on 2020/8/2.
//  Copyright © 2020 杨涛睿. All rights reserved.
//

#include <iostream>
#include <stdio.h>
template<typename T>
struct Node{
    T e;
    struct Node* next;
};
template<typename T>
class Queue{
public:
    Node<T>* head = new Node<T>();
    struct Node<T>* rear = head;
    int size = 0;
    T top(){
        if(!head->next)return NULL;
        return head->next->e;
    }
    T tail(){
        if(rear==head)return NULL;
        return rear->e;
    }
    T dequeue(){
        if(!(head->next))return NULL;
        if(--size==0) rear = head;
        struct Node<T> * h = head->next ;
        head->next = h->next;
        T e = h->e;
        delete(h);
        return e;
    }
    void enqueue(T e){
        size++;
        rear->next = new Node<T>();
        rear = rear ->next;
        rear->next = NULL;
        rear -> e = e;
    }
};
