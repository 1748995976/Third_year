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
    cout << "V:舞伴问题"<< endl;
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
            case 'V':{
                int men;
                cout <<"输入男士的数量:"<<endl;
                cin >> men;
                int women;
                cout <<"输入女士的数量:"<<endl;
                cin >> women;
                int whman;
                int whwoman;
                cout << "依次输入第几位男士想和第几位女士一起跳舞(从零开始)" << endl;
                cout <<"男士：";
                cin >> whman;
                cout << "女士：";
                cin >> whwoman;
                if(whman > men || whwoman > women){
                    cout << "输入不合理!请重新选择你的操作!" << endl;
                    break;
                }
                QUEUE aman(men);
                QUEUE awoman(women);
                for(int i = 1;i <= men;i++)
                    aman << i;
                for (int i = 1; i <= women;i++)
                    awoman << i;
                int a = 0;
                int b = 0;
                for (int i = 1;;i++) {
                    aman >> a;
                    awoman >> b;
                    if(a == whman && b == whwoman){
                        cout << "第" << i << "支舞他们可以一起跳舞" << endl;
                        break;
                    }
                    aman << a;
                    awoman << b;
                }
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