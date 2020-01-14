//
// Created by wzc-1748995976 on 2019/10/23.
//

#ifndef EXPERIMENTTHIRD_QUEUE_H
#define EXPERIMENTTHIRD_QUEUE_H

#include "stack.h"

class QUEUE{
    STACK s1, s2;
public:
    QUEUE(int m); //每个栈最多m个元素，要求实现的队列最多能入2m个元素
    QUEUE(const QUEUE&q); 			//用队列q拷贝初始化队列
    QUEUE(QUEUE &&q);				//移动构造
    virtual operator int ( ) const;			//返回队列的实际元素个数
    virtual int full ( ) const;		       //返回队列是否已满，满返回1，否则返回0
    virtual int operator[ ](int x)const;   //取下标为x的元素,第1个元素下标为0
    virtual QUEUE& operator<<(int e); 	//将e入队列,并返回队列
    virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
    virtual QUEUE& operator=(const QUEUE&q); //赋q给队列,并返回被赋值的队列
    virtual QUEUE& operator=(QUEUE &&q);	//移动赋值
    virtual void print( ) const;			//打印队列
    virtual ~QUEUE( );					//销毁队列
};


#endif //EXPERIMENTTHIRD_QUEUE_H
