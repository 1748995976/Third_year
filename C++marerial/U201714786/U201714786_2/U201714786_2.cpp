#include <cstdio>
#include <iostream>

class STACK{
    int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
    const  int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
    int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
    STACK();            //��дĬ�Ϲ��캯��
    STACK(int m);		//��ʼ��ջ������m��Ԫ��
    STACK(const STACK&s); 			//��ջs������ʼ��ջ
    STACK(STACK &&s);       			//�ƶ�����
    virtual int  size ( ) const;			//����ջ�����Ԫ�ظ���max
    virtual operator int ( ) const;			//����ջ��ʵ��Ԫ�ظ���pos
    virtual int operator[ ] (int x) const;	//ȡ�±�x����ջԪ�أ���1��Ԫ��x=0
    virtual STACK& operator<<(int e); 	//��e��ջ,������ջ
    virtual STACK& operator>>(int &e);	//��ջ��e,������ջ
    virtual STACK& operator=(const STACK&s); //��s��ջ,�����ر���ֵջ
    virtual STACK& operator=(STACK &&s);  //�ƶ���ֵ
    virtual void print( ) const;			//��ӡջ
    virtual ~STACK( );					//����ջ
};


using namespace std;

bool is_error = false;//��־λ�������жϳ����Ƿ����

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

STACK::STACK():elems(nullptr),max(0),pos(0){
}//Ϊ��ʵ��ķ����ԣ���������дĬ�Ϲ��캯��
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
    if(elems){//�����ظ��ͷſռ�
        delete [] elems;
        *(int **)(&elems) = nullptr;
        *(int *)(&max) = 0;
        pos = 0;
    }
}