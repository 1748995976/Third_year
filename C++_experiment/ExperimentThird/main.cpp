#include <iostream>
#include "queue.h"

using namespace std;

bool queue_is_error = false;

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