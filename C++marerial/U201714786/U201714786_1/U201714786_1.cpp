#include <iostream>
#include <malloc.h>
#include <cstdio>

struct STACK{
    int  *elems;	//�����ڴ����ڴ��ջ��Ԫ��
    int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
    int   pos;	//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};
void initSTACK(STACK *const p, int m);	//��ʼ��pָ���ջ�����m��Ԫ��

void initSTACK(STACK *const p, const STACK&s); //��ջs��ʼ��pָ���ջ

int  size (const STACK *const p);		//����pָ���ջ�����Ԫ�ظ���max

int  howMany (const STACK *const p);	//����pָ���ջ��ʵ��Ԫ�ظ���pos

int  getelem (const STACK *const p, int x);	//ȡ�±�x����ջԪ��

STACK *const push(STACK *const p, int e); 	//��e��ջ��������p

STACK *const pop(STACK *const p, int &e); 	//��ջ��e��������p

STACK *const assign(STACK*const p, const STACK&s); //��s��pָ��ջ,������p

void print(const STACK*const p);			//��ӡpָ���ջ

void destroySTACK(STACK*const p);		//����pָ���ջ


using namespace std;

bool Destroy(STACK *m,STACK *q,STACK *n);//�жϸ���ָ��ָ��Ŀռ��Ƿ���ͬ����ֹ�ظ��ͷſռ�
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
    cout << "S:�趨ջ��С"
         << "    I:��ջ"<< endl;
    cout << "O:��ջ"
         << "    A:�����ֵ"<<endl;
    cout << "C:�������"
         << "   G:��Ӧλ��Ԫ��"<< endl;
    cout << "N:ջ��ʣ��Ԫ�ظ���"
         << "    H:ջ�Ĵ�С"<< endl;
    cout << "Q:�˳�����" << endl;
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
                {//��ָ��ָ��Ŀռ�ָ���ԭʼ״̬
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
                {//��ָ��ָ��Ŀռ�ָ���ԭʼ״̬
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
                if(number <= 0 || number > p-> pos){//�ж��±��Ƿ�Ϸ�
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

//��main��ĳЩָ��ָ����ڴ�ͳһ�ͷ�
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

//��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK(STACK *const p, int m){
    p -> elems = (int *)malloc(m * sizeof(int));
    p -> max = m;
    p -> pos = 0;
}

//��ջs��ʼ��pָ���ջ
void initSTACK(STACK *const p, const STACK&s){
    p -> elems = (int*)malloc(s.max * sizeof(int));
    p -> max = s.max;
    p -> pos = s.pos;
    for(int i = 0;i < p -> pos;i++)
        (p -> elems)[i] = (s.elems)[i];
}

//����pָ���ջ�����Ԫ�ظ���max
int  size (const STACK *const p){
    return p -> max;
}

//����pָ���ջ��ʵ��Ԫ�ظ���pos
int  howMany (const STACK *const p){
    return p -> pos;
}

//ȡ�±�x����ջԪ��
int  getelem (const STACK *const p, int x){
    return (p -> elems)[x];
}

//��e��ջ��������p
STACK *const push(STACK *const p, int e){
    if(p -> pos == p -> max)//ջ����
        return nullptr;
    (p -> elems)[p -> pos] = e;
    (p -> pos)+= 1;
    return  p;
}

//��ջ��e��������p�����򷵻ؿ�
STACK *const pop(STACK *const p, int &e){
    if(p->pos == 0)//ջΪ��
        return nullptr;
    (p -> pos) -= 1;
    e = (p -> elems)[p -> pos];
    return p;
}

//��s��pָ��ջ,������p
STACK *const assign(STACK*const p, const STACK&s){
    free(p-> elems);
    p -> elems = (int *)malloc(s.max * sizeof(int));
    p -> max = s.max;
    p -> pos = s.pos;
    for(int i = 0;i < p -> pos;i++)
        (p -> elems)[i] = (s.elems)[i];
    return p;
}

//��ӡpָ���ջ
void print(const STACK*const p){
    for(int i = 0;i < p -> pos;i++)
        printf("%d  ",(p->elems)[i]);
}

//����pָ���ջ
void destroySTACK(STACK*const p){
    if(p-> elems)
        free(p->elems);
    free(p);
}
