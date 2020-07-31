//
//  main.cpp
//  Stack
//
//  Created by 杨涛睿 on 2020/7/27.
//  Copyright © 2020 杨涛睿. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>

using namespace std;
//计算阶乘
int facI ( int n ) { int f = 1; while ( n > 1 ) f *= n--; return f; }
/*
  < : 栈顶运算符优先级更低，运算符进栈
  > : 栈顶运算符优先级更高，执行计算，结果入栈
 */
const char pri[9][9] ={
    
        // +   -   *   /   ^   !   (   )   \0
/*栈顶*/
/* + */   '>','>','<','<','<','<','<','>','>',
/* - */   '>','>','<','<','<','<','<','>','>',
/* * */   '>','>','>','>','<','<','<','>','>',
/* / */   '>','>','>','>','<','<','<','>','>',
/* ^ */   '>','>','>','>','>','<','<','>','>',
/* ! */   '>','>','>','>','>','>',' ','>','>',
/* ( */   '<','<','<','<','<','<','<','=',' ',
/* ) */   ' ',' ',' ',' ',' ',' ',' ',' ',' ',
/* \0 */  '<','<','<','<','<','<','<',' ','=',
};
char orderBetween(char a,char b){
    int c,d;
    
    switch (a) {
        case '+':c= 0;break;
        case '-':c= 1;break;
        case '*':c= 2;break;
        case '/':c= 3;break;
        case '^':c= 4;break;
        case '!':c= 5;break;
        case '(':c= 6;break;
        case ')':c= 7;break;
        case '\0':c= 8;break;
        default:break;
    }
    switch (b) {
        case '+':d= 0;break;
        case '-':d= 1;break;
        case '*':d= 2;break;
        case '/':d= 3;break;
        case '^':d= 4;break;
        case '!':d= 5;break;
        case '(':d= 6;break;
        case ')':d= 7;break;
        case '\0':d = 8;break;
        default: break;
    }
    return pri[c][d];
}
void append ( char*& rpn, float opnd ) { //将操作数接至RPN末尾
   int n = strlen ( rpn );
   if ( opnd != ( float ) ( int ) opnd )
       sprintf ( rpn+n, "%.2f \0", opnd ); //浮点格式
   else
       sprintf ( rpn+n, "%d \0", ( int ) opnd ); //整数格式
   // strcat ( rpn, buf ); //RPN加长
 }
void append ( char*& rpn, char optr ) { //将运算符接至RPN末尾
    int n = strlen ( rpn ); //RPN当前长度（以'\0'结尾，长度n + 1）
    sprintf ( rpn + n, "%c ", optr ); rpn[n + 2] = '\0'; //接入指定的运算符
 }
/*栈模板类
 栈的应用场合主要分为以下四类：
 (1)逆序输出：输出次序与处理过程颠倒——进制转换
 (2)递归嵌套——括号匹配
 (3)延迟缓冲，需要读取一定长度后，才能进行处理 ——中缀表达式求值
 (4)栈式计算
 */
template <typename T>
class Stack{
public:
    T stack[100];
    int size = 0;
    void push(T e){
        size<100?stack[size++]=e: NULL;
    }
    float pop(){
        
        return stack[--size];
    }
    //取顶
    T& top(){
        return stack[size-1];
    }
   
    //进制转换，base是十进制，num是转化的目标进制
    void convert(int base ,int n){
        while(base > 0){
            this->push(base%n);
            base/=n;
        }
        while(size>0){
            cout << this->pop();
        }
        cout << endl;
    }
    /*
     括号匹配
     无括号的表达式是匹配的
     减而治之：减少部分括号，不影响表达式的正确性
     分而治之：两个表达式E和F已经是括号匹配的，则串接起来可以得到一个匹配的表达式
     但是，
     ———— 串接起来匹配的表达式，两个子表达式原先未必匹配
     因此采用减而治之的策略
     ————减去一对紧邻的括号不影响原表达式匹配与否，遇到左括号入栈，遇到右括号出栈
     为什么使用栈而不是计数器？———— 栈可以判断多种括号并存的情况
     */
    bool parel(string s ,int lo,int hi){
        for(int i = 0; i<s.size() ;i++){
            if(s[i]=='(')this->push(s[i]);
            if(s[i]==')')this->pop();
        }
        if(this->size==0)return true;
        return false;
    }
    /*
        栈混洗——借助中转栈C，将栈A中的元素转入栈B
        栈B中的元素序列，可能与栈A不同
        长度为n的序列，可能的栈混洗总数为卡特兰数(2n)!/((n+1)!n!)
        判断一个序列是否满足栈混洗的充要条件 ——> 312情况
        甄别算法：暴力枚举——>O(n^3)
        O(n)复杂度算法 ——>模拟！
        n个括号匹配的本质，就是对n个元素进行栈混洗的一系列push和pop操作
    */
};
void readNumber ( char*& p, Stack<float>& stk ) { //将起始于p的子串解析为数值，并存入操作数栈
   stk.push ( ( float ) ( *p - '0' ) ); //当前数位对应的数值进栈
   while ( isdigit ( * ( ++p ) ) ) //只要后续还有紧邻的数字（即多位整数的情况），则
      stk.push ( stk.pop() * 10 + ( *p - '0' ) ); //弹出原操作数并追加新数位后，新数值重新入栈
   if ( '.' != *p ) return; //此后非小数点，则意味着当前操作数解析完成
   float fraction = 1; //否则，意味着还有小数部分
   while ( isdigit ( * ( ++p ) ) ) //逐位加入
   stk.push ( stk.pop() + ( *p - '0' ) * ( fraction /= 10 ) ); //小数部分
}
 //执行一元运算
float calcu ( char op, float b ) {
    switch ( op ) {
       case '!' : return ( float ) facI ( ( int ) b );
       default  : exit ( -1 );
    }
}
//执行二元运算
float calcu ( float a,char op, float b ) {
    switch ( op ) {
       case '+' : return  ( float ) ( a + b );
       case '-' : return  ( float ) ( a - b );
       case '*' : return  ( float ) ( a * b );
       case '/' : return  ( float ) ( a / b );
       case '^' : return  pow(a, b);
       default  : exit ( -1 );
    }
}
  /*
  中缀表达式求值,顺带完成中缀表达式向后缀表达式(RPN)的转换
  同样采用减而治之的策略，减少运算符数目，并不影响正确性
  采用两个栈——将运算符和运算数分别对待
  */
float evaulate(char*S,char* RPN){
    //操作数栈和运算符栈
    Stack<float>opnd; Stack<char>optr;
    optr.push('\0');
    while(optr.size!=0){
        if(isdigit(*S))
        {readNumber(S,opnd); append(RPN,opnd.top()); }
        else
            //比较当前运算符和栈顶元素优先级高低
            switch(orderBetween(optr.top(),*S) ){
                case '<':
                    optr.push(*S);S++;
                    break;
                case '=':
                    optr.pop();S++;
                    break;
                case '>':
                    char op = optr.pop();
                    append(RPN,op);
                    if(op=='!')opnd.push(calcu(op,opnd.pop()));
                    //除了阶乘都是二元运算符
                    else{
                        float pOpnd2 = opnd.pop(),pOpnd1 = opnd.pop();
                        opnd.push(calcu(pOpnd1,op,pOpnd2));
                    }
                    break;
            }
    }
    return opnd.pop();
}

int main(int argc, const char * argv[]) {
    char RPN[100];
    cout << evaulate("3+2",RPN)<<endl;
    cout << RPN;
    return 0;
}
