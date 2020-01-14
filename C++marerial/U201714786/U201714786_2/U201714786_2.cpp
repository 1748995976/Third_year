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


using namespace std;

bool is_error = false;//标志位，用来判断程序是否出错

int main() {
    STACK *p = nullptr,*q = nullptr;
    char command;
    int number;
    cout << "S:设定栈大小"
         << "    I:入栈"<< endl;
    cout << "O:出栈"
         << "    A:深拷贝赋值"<<endl;
    cout << "C:深拷贝构造"
         << "   G:相应位置元素"<< endl;
    cout << "N:栈中剩余元素个数"
         << "    H:栈的大小"<< endl;
    cout << "R:移动构造"
         << "    M:移动复制"<< endl;
    cout << "Q:退出程序"<< endl;
    while (true) {
        scanf("%c",&command);
        switch (command) {
            case 'S': {
                cin >> number;
                p =  new STACK(number);
                cout << "S  " << number << "  ";
                break;
            }
            case 'I': {
                while(scanf("%d",&number)) {
                    (*p) << number;
                    if(is_error)
                        break;
                }
                if(is_error) {
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
                    if(is_error)
                        break;
                }
                if(is_error) {
                    cout << "O  E  ";
                    delete p;
                    return 1;
                }else{
                    cout << "O  " << (int)(*p) <<"  ";
                }
                break;
            }
            case 'C': {
                q = new STACK(*p);
                delete p;
                p = q;
                q = nullptr;
                cout << "C  ";
                p -> print();
                break;
            }
            case 'A': {
                cin >> number;
                q = new STACK(number);
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
                if(is_error) {
                    cout << "G  E  ";
                    delete p;
                    return 1;
                }else
                    cout << "G  " << number << "  ";
                break;
            }
            case 'N': {
                number = (*p);
                cout << "N  " << number << "  ";
                break;
            }
            case 'H':{
                cout << "H  " << p -> size() << "  ";
                break;
            }
            case 'R':{
                q = new STACK(move(*p));
                delete p;
                p = q;
                q = nullptr;
                cout << "R  ";
                p -> print();
                break;
            }
            case 'M':{
                cin >> number;
                q = new STACK(number);
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

STACK::STACK():elems(nullptr),max(0),pos(0){
}//为了实验的方便性，在这里重写默认构造函数
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
    if(elems){//避免重复释放空间
        delete [] elems;
        *(int **)(&elems) = nullptr;
        *(int *)(&max) = 0;
        pos = 0;
    }
}