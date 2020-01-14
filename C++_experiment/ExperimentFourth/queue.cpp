//
// Created by wzc-1748995976 on 2019/10/23.
//

#include <iostream>
#include "queue.h"
//本身当做第一个栈，s当作s2

extern bool queue_is_error;

QUEUE::QUEUE(int m):STACK(m),s(m){

}

QUEUE::QUEUE(const QUEUE &q):STACK(q),s(q.s){

}

QUEUE::QUEUE(QUEUE &&q):STACK(std::move(q)),s(std::move(q.s)){

}

QUEUE::operator int() const{
    return STACK::operator int() + (int)s;
}

int QUEUE::full() const{
    if((int)s != 0 && STACK::operator int() == STACK::size())
        return 1;
    else
        return 0;
}

int QUEUE::operator[](int x) const{
    if(x < 0 || x >= (int)s + STACK::operator int()){
        queue_is_error = true;
        return 0;
    }
    if(x <= (int)s)
        return s[(int)s - x];
    else{
        return STACK::operator[](x - (int)s - 1);
    }
}

QUEUE& QUEUE::operator<<(int e){
    if((*this).size() == STACK::operator int() && (int)s != 0) {
        queue_is_error = true;
    }else if((*this).size() == STACK::operator int() && (int)s == 0){
        int temp;
        for(int i = 0;i < (*this).size();i++){
            STACK::operator>>(temp);
            s << temp;
        }
        STACK::operator<<(e);
    }else{
        STACK::operator<<(e);
    }
    return (*this);
}

QUEUE& QUEUE::operator>>(int &e){
    if((int)s != 0){
        s >> e;
    }else if((int)s == 0 && STACK::operator int() != 0){
        int temp;
        int number = STACK::operator int();
        for(int i = 0;i < number - 1;i++){
            STACK::operator>>(temp);
            s << temp;
        }
        STACK::operator>>(e);
        number = (int)s;
        for(int i = 0;i < number;i++){
            s >> temp;
            STACK::operator<<(temp);
        }
    }else{
        queue_is_error = true;
    }
    return (*this);
}

QUEUE& QUEUE::operator=(const QUEUE &q){
    STACK::operator=(q);
    s = q.s;
    return (*this);
}

QUEUE& QUEUE::operator=(QUEUE &&q){
    STACK::operator=(std::move(q));
    s = std::move(q.s);
    return (*this);
}

void QUEUE::print() const{
    for(int i = (int)s - 1;i >= 0;i--)
        std::cout << s[i] << "  ";
    STACK::print();
}

QUEUE::~QUEUE(){

}