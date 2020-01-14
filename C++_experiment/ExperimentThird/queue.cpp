//
// Created by wzc-1748995976 on 2019/10/23.
//

#include <iostream>
#include "queue.h"

extern bool queue_is_error;

QUEUE::QUEUE(int m):s1(m),s2(m){

}

QUEUE::QUEUE(const QUEUE &q):s1(q.s1),s2(q.s2){

}

QUEUE::QUEUE(QUEUE &&q):s1(std::move(q.s1)),s2(std::move(q.s2)){

}

QUEUE::operator int ( ) const{
    return (int)s1 + (int)s2;
}

int QUEUE::full ( ) const{
    if((int)s2 != 0 && (int)s1 == s1.size())
        return 1;
    else
        return 0;
}

int QUEUE::operator[ ](int x)const{
    if(x < 0 || x >= (int)s2 + (int)s1){
        queue_is_error = true;
        return 0;
    }
    if(x <= (int)s2)
        return s2[(int)s2 - x];
    else{
            return s1[x - (int)s2 - 1];
    }
}

QUEUE& QUEUE::operator<<(int e){
    if(s1.size() == (int)s1 && (int)s2 != 0) {
        queue_is_error = true;
    }else if(s1.size() == (int)s1 && (int)s2 == 0){
        int temp;
        for(int i = 0;i < s1.size();i++){
            s1 >> temp;
            s2 << temp;
        }
        s1 << e;
    }else{
        s1 << e;
    }
    return (*this);
}

QUEUE& QUEUE::operator>>(int &e){
    if((int)s2 != 0){
        s2 >> e;
    }else if((int)s2 == 0 && (int)s1 != 0){
        int temp;
        int number = (int)s1;
        for(int i = 0;i < number - 1;i++){
            s1 >> temp;
            s2 << temp;
        }
        s1 >> e;
        number = (int)s2;
        for(int i = 0;i < number;i++){
            s2 >> temp;
            s1 << temp;
        }
    }else{
        queue_is_error = true;
    }
    return (*this);
}

QUEUE& QUEUE::operator=(const QUEUE &q){
    s1 = q.s1;
    s2 = q.s2;
    return (*this);
}

QUEUE& QUEUE::operator=(QUEUE &&q){
    s1 = std::move(q.s1);
    s2 = std::move(q.s2);
    return (*this);
}

void QUEUE::print( ) const{
    for(int i = (int)s2 - 1;i >= 0;i--) {
        std::cout << (s2)[i] << "  ";
    }
    s1.print();
}

QUEUE::~QUEUE( ){
}

