#include <iostream>
#include "queue.h"

using namespace std;

bool queue_is_error = false;

int main() {
    QUEUE *p = nullptr,*q = nullptr;
    char command;
    int number;
    cout << "S:�趨���д�С"
         << "    I:�����"<< endl;
    cout << "O:������"
         << "    A:�����ֵ"<<endl;
    cout << "C:�������"
         << "   G:��Ӧλ��Ԫ��"<< endl;
    cout << "N:������ʣ��Ԫ�ظ���"
         << "    F:�����Ƿ�����"<< endl;
    cout << "R:�ƶ�����"
         << "    M:�ƶ�����"<< endl;
    cout << "Q:�˳�����"<< endl;
    cout << "V:�������"<< endl;
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
                cout <<"������ʿ������:"<<endl;
                cin >> men;
                int women;
                cout <<"����Ůʿ������:"<<endl;
                cin >> women;
                int whman;
                int whwoman;
                cout << "��������ڼ�λ��ʿ��͵ڼ�λŮʿһ������(���㿪ʼ)" << endl;
                cout <<"��ʿ��";
                cin >> whman;
                cout << "Ůʿ��";
                cin >> whwoman;
                if(whman > men || whwoman > women){
                    cout << "���벻����!������ѡ����Ĳ���!" << endl;
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
                        cout << "��" << i << "֧�����ǿ���һ������" << endl;
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