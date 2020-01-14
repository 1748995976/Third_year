#include <iostream>
#include "stack.h"

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
