//
// Created by wzc-1748995976 on 2019/10/22.
//
#include <cstdio>
#include <iostream>
#include "stack.h"

extern bool is_error;
STACK::STACK():elems(nullptr),max(0),pos(0){
}
STACK::STACK(int m):elems(new int[m]),max(m),pos(0) {
}
STACK::STACK(const STACK &s):elems(new int[s.max]),max(s.max),pos(s.pos){
    for(int i = 0;i < s.pos;i++){
        elems[i] = (s.elems)[i];
    }
}

STACK::STACK(STACK&& s):elems(s.elems),max(s.max),pos(s.pos){
    *(int **)(&s.elems) = nullptr;
    *(int *)(&s.max) = 0;
    s.pos = 0;
}

int  STACK::size ( ) const{
    return max;
}

STACK::operator int ( ) const{
    return pos;
}

int STACK::operator[] (int x) const{
    if(x <0 || x >= pos){
        is_error = true;
        return 0;
    }
    return elems[x];
}

STACK& STACK::operator<<(int e){
    if(pos == max) {
        is_error = true;
        return (*this);
    }
    elems[pos] = e;
    pos += 1;
    return (*this);
}

STACK& STACK::operator>>(int &e){
    if(pos == 0) {
        is_error = true;
        return (*this);
    }
    pos -= 1;
    e = elems[pos];
    return (*this);
}

STACK& STACK::operator=(const STACK &s){
    if(&s == this)
        return (*this);
    delete [] elems;
    *(int **)(&elems) = new int[s.max];
    *(int *)(&max) = s.max;
    pos = s.pos;
    for(int i = 0;i < s.pos;i++){
        elems[i] = (s.elems)[i];
    }
    return (*this);
}

STACK & STACK::operator=(STACK &&s){//not use
    delete [] elems;
    *(int **)(&elems) = s.elems;
    *(int *)(&max) = s.max;
    pos = s.pos;
    *(int **)(&s.elems) = nullptr;
    *(int *)(&s.max) = 0;
    s.pos = 0;
    return  (*this);
}

void STACK::print( ) const{
    for(int i = 0;i < pos;i++)
        printf("%d  ",elems[i]);
}

STACK::~STACK( ){
    if(elems){
        delete [] elems;
        *(int **)(&elems) = nullptr;
        *(int *)(&max) = 0;
        pos = 0;
    }
}
