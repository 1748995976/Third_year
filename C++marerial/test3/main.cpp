#include <cstdio>
#include <iostream>

class STACK{
    int  *const  elems;	//申请内存用于存放栈的元素
    const  int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
    STACK();            //重写默认构造函数
    STACK(int m);		//初始化栈：最多存m个元素
    STACK(const STACK&s); 			//用栈s拷贝初始化栈
    STACK(STACK &&s);       			//移动构造
    virtual int  size ( ) const;			//返回栈的最大元素个数max
    virtual operator int ( ) const;			//返回栈的实际元素个数pos
    virtual int operator[ ] (int x) const;	//取下标x处的栈元素，第1个元素x=0
    virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
    virtual STACK& operator>>(int &e);	//出栈到e,并返回栈
    virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值栈
    virtual STACK& operator=(STACK &&s);  //移动赋值
    virtual void print( ) const;			//打印栈
    virtual ~STACK( );					//销毁栈
};

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

using namespace std;

bool queue_is_error = false;//标志位，用来判断程序是否出错

int main() {
    QUEUE *p = nullptr,*q = nullptr;
    char command;
    int number;
    cout << "S:设定队列大小"
         << "    I:入队列"<< endl;
    cout << "O:出队列"
         << "    A:深拷贝赋值"<<endl;
    cout << "C:深拷贝构造"
         << "   G:相应位置元素"<< endl;
    cout << "N:队列中剩余元素个数"
         << "    F:队列是否已满"<< endl;
    cout << "R:移动构造"
         << "    M:移动复制"<< endl;
    cout << "Q:退出程序"<< endl;
    while (true) {
        scanf("%c",&command);
        switch (command) {
            case 'S': {
                cin >> number;
                p =  new QUEUE(number);
                cout << "S  " << number << "  ";
                break;
            }
            case 'I': {
                while(scanf("%d",&number)) {
                    (*p) << number;
                    if(queue_is_error)
                        break;
                }
                if(queue_is_error) {
                    cout << "I  E  ";
                    delete p;
                    return 1;
                }else{
                    cout << "I  ";
                    p -> print();
                }
                break;
            }
            case 'O': {
                cin >> number;
                int temp;
                for(int i = 0;i < number;i++) {
                    (*p) >> temp;
                    if(queue_is_error)
                        break;
                }
                if(queue_is_error) {
                    cout << "O  E  ";
                    delete p;
                    return 1;
                }else{
                    cout << "O  " << (int)(*p) <<"  ";
                }
                break;
            }
            case 'C': {
                q = new QUEUE(*p);
                delete p;
                p = q;
                q = nullptr;
                cout << "C  ";
                p -> print();
                break;
            }
            case 'A': {
                cin >> number;
                q = new QUEUE(number);
                (*q) = (*p);
                delete p;
                p = q;
                q = nullptr;
                cout << "A  ";
                p -> print();
                break;
            }
            case 'G':{
                cin >> number;
                number = (*p)[number];
                if(queue_is_error) {
                    cout << "G  E  ";
                    delete p;
                    return 1;
                }else {
                    cout << "G  " << number << "  ";
                }
                break;
            }
            case 'N': {
                number = (*p);
                cout << "N  " << number << "  ";
                break;
            }
            case 'F': {
                cout << "F  " << p -> full() << "  ";
                break;
            }
            case 'R':{
                q = new QUEUE(move(*p));
                delete p;
                p = q;
                q = nullptr;
                cout << "R  ";
                p -> print();
                break;
            }
            case 'M':{
                cin >> number;
                q = new QUEUE(number);
                (*q) = move((*p));
                p = q;
                q = nullptr;
                cout << "M  ";
                p -> print();
                break;
            }
            default:{
                break;
            }
        }
        if(command == 'Q')
            break;
    }
    delete p;
    return 0;
}

STACK::STACK():elems(nullptr),max(0),pos(0) {
}
STACK::STACK(int m):elems(new int[m]),max(m),pos(0) {
}
STACK::STACK(const STACK &s):elems(new int[s.max]),max(s.max),pos(s.pos){
    for(int i = 0;i < s.pos;i++){
        elems[i] = (s.elems)[i];
    }
}

STACK::STACK(STACK&& s):elems(s.elems),max(s.max),pos(s.pos){//not use
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
    return elems[x];
}

STACK& STACK::operator<<(int e){
    if(pos == max) {
        return (*this);
    }
    elems[pos] = e;
    pos += 1;
    return (*this);
}

STACK& STACK::operator>>(int &e){
    if(pos == 0) {
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
    *(int **)(&elems) = s.elems;
    *(int *)(&max) = s.max;
    pos = s.pos;
    *(int **)(&s.elems) = nullptr;
    *(int *)(&s.max) = 0;
    s.pos = 0;
    return (*this);
}

void STACK::print( ) const{
    for(int i = 0;i < pos;i++)
        printf("%d  ",elems[i]);
}

STACK::~STACK( ){
    if(elems) {//避免重复释放空间
        delete[] elems;
        *(int **)(&elems) = nullptr;
        *(int *) (&max) = 0;
        pos = 0;
    }
}

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
