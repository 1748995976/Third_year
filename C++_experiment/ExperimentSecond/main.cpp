#include <iostream>
#include "stack.h"

using namespace std;

bool is_error = false;

int main() {
    STACK *p = nullptr,*q = nullptr;
    char command;
    int number;
    cout << "S:�趨ջ��С"
         << "    I:��ջ"<< endl;
    cout << "O:��ջ"
         << "    A:�����ֵ"<<endl;
    cout << "C:�������"
         << "   G:��Ӧλ��Ԫ��"<< endl;
    cout << "N:ջ��ʣ��Ԫ�ظ���"
         << "    H:ջ�Ĵ�С"<< endl;
    cout << "R:�ƶ�����"
         << "    M:�ƶ�����"<< endl;
    cout << "Q:�˳�����"<< endl;
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