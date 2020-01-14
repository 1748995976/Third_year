#include <iostream>
#include <malloc.h>
#include <cstdio>

struct STACK{
    int  *elems;	//申请内存用于存放栈的元素
    int   max;	//栈能存放的最大元素个数
    int   pos;	//栈实际已有元素个数，栈空时pos=0;
};
void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素

void initSTACK(STACK *const p, const STACK&s); //用栈s初始化p指向的栈

int  size (const STACK *const p);		//返回p指向的栈的最大元素个数max

int  howMany (const STACK *const p);	//返回p指向的栈的实际元素个数pos

int  getelem (const STACK *const p, int x);	//取下标x处的栈元素

STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p

STACK *const pop(STACK *const p, int &e); 	//出栈到e，并返回p

STACK *const assign(STACK*const p, const STACK&s); //赋s给p指的栈,并返回p

void print(const STACK*const p);			//打印p指向的栈

void destroySTACK(STACK*const p);		//销毁p指向的栈


using namespace std;

bool Destroy(STACK *m,STACK *q,STACK *n);//判断各个指针指向的空间是否相同，防止重复释放空间
int main() {
    STACK *n = (STACK *)malloc(sizeof(STACK));
    STACK *q = (STACK *)malloc(sizeof(STACK));
    STACK *m = (STACK *)malloc(sizeof(STACK));
    n -> elems =  q -> elems = m ->elems = nullptr;
    n -> pos = q -> pos = m -> pos = 0;
    n -> max = q -> max = q -> pos = 0;
    STACK *p = n;
    char command;
    int number;
    bool flag = true;
    cout << "S:设定栈大小"
         << "    I:入栈"<< endl;
    cout << "O:出栈"
         << "    A:深拷贝赋值"<<endl;
    cout << "C:深拷贝构造"
         << "   G:相应位置元素"<< endl;
    cout << "N:栈中剩余元素个数"
         << "    H:栈的大小"<< endl;
    cout << "Q:退出程序" << endl;
    while (true) {
        scanf("%c",&command);
        switch (command) {
            case 'S': {
                cin >> number;
                initSTACK(p, number);
                cout << "S  " << number << "  ";
                break;
            }
            case 'I': {
                while(scanf("%d",&number)) {
                    if(!push(p, number)){
                        flag = false;
                        break;
                    }
                }
                if(!flag) {
                    cout << "I  E  ";
                    Destroy(m,q,n);
                    return 1;
                }else{
                    cout << "I  ";
                    print(p);
                }
                break;
            }
            case 'O': {
                cin >> number;
                int temp;
                for(int i = 0;i < number;i++) {
                    if(!pop(p, temp)){
                        flag = false;
                        break;
                    }
                }
                if(!flag) {
                    cout << "O  E  ";
                    Destroy(m,q,n);
                    return 1;
                }else{
                    cout << "O  " << p ->pos << "  ";
                }
                break;
            }
            case 'C': {
                initSTACK(q,*p);
                STACK *temp = p;
                p = q;
                q = temp;
                {//将指针指向的空间恢复到原始状态
                    free(q->elems);
                    q -> elems = nullptr;
                    q -> max = 0;
                    q -> pos = 0;
                }
                cout << "C  ";
                print(p);
                break;
            }
            case 'A': {
                cin >> number;
                initSTACK(m,number);
                STACK *temp = p;
                p = assign(m,*p);
                m = temp;
                {//将指针指向的空间恢复到原始状态
                    free(m->elems);
                    m -> elems = nullptr;
                    m -> max = 0;
                    m -> pos = 0;
                }
                cout << "A  ";
                print(p);
                break;
            }
            case 'G':{
                cin >> number;
                if(number <= 0 || number > p-> pos){//判断下标是否合法
                    cout << "G  E  ";
                    Destroy(m,q,n);
                    return 1;
                }
                number = getelem(p,number);
                cout << "G  " << number << "  ";
                break;
            }
            case 'N': {
                number = howMany(p);
                cout << "N  " << number << "  ";
                break;
            }
            case 'H':{
                number = size(p);
                cout << "H  " << number << "  ";
                break;
            }
            default:{
                break;
            }
        }
        if(command == 'Q')
            break;
    }
    Destroy(m,q,n);
    return 0;
}

//对main中某些指针指向的内存统一释放
bool Destroy(STACK *m,STACK *q,STACK *n){
    if(m == n){
        destroySTACK(n);
        destroySTACK(q);
    }else if(m == q){
        destroySTACK(n);
        destroySTACK(q);
    }else if(q == n){
        destroySTACK(n);
        destroySTACK(m);
    }else if(q == m && q == n){
        destroySTACK(n);
    }else {
        destroySTACK(n);
        destroySTACK(q);
        destroySTACK(m);
    }
    return true;
}

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

//出栈到e，并返回p；否则返回空
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
    if(p-> elems)
        free(p->elems);
    free(p);
}
