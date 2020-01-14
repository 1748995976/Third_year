//
// Created by wzc-1748995976 on 2019/10/9.
//
#include <malloc.h>
#include <cstdio>
#include "stack.h"
//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, int m){
    p -> elems = (int *)malloc(m * sizeof(int));
    p -> max = m;
    p -> pos = 0;
}

//用栈s初始化p指向的栈
void initSTACK(STACK *const p, const STACK&s){
    p -> elems = (int*)malloc(s.max * sizeof(int));
    p -> max = s.max;
    p -> pos = s.pos;
    for(int i = 0;i < p -> pos;i++)
        (p -> elems)[i] = (s.elems)[i];
}

//返回p指向的栈的最大元素个数max
int  size (const STACK *const p){
    return p -> max;
}

//返回p指向的栈的实际元素个数pos
int  howMany (const STACK *const p){
    return p -> pos;
}

//取下标x处的栈元素
int  getelem (const STACK *const p, int x){
    return (p -> elems)[x];
}

//将e入栈，并返回p
STACK *const push(STACK *const p, int e){
    if(p -> pos == p -> max)//栈已满
        return nullptr;
    (p -> elems)[p -> pos] = e;
    (p -> pos)+= 1;
    return  p;
}

//出栈到e，并返回p
STACK *const pop(STACK *const p, int &e){
    if(p->pos == 0)//栈为空
        return nullptr;
    (p -> pos) -= 1;
    e = (p -> elems)[p -> pos];
    return p;
}

//赋s给p指的栈,并返回p
STACK *const assign(STACK*const p, const STACK&s){
    free(p-> elems);
    p -> elems = (int *)malloc(s.max * sizeof(int));
    p -> max = s.max;
    p -> pos = s.pos;
    for(int i = 0;i < p -> pos;i++)
        (p -> elems)[i] = (s.elems)[i];
    return p;
}

//打印p指向的栈
void print(const STACK*const p){
    for(int i = 0;i < p -> pos;i++)
        printf("%d  ",(p->elems)[i]);
}

//销毁p指向的栈
void destroySTACK(STACK*const p){
    free(p->elems);
    free(p);
}




