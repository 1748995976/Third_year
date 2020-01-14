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

class QUEUE{
    STACK s1, s2;
public:
    QUEUE(int m); //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
    QUEUE(const QUEUE&q); 			//�ö���q������ʼ������
    QUEUE(QUEUE &&q);				//�ƶ�����
    virtual operator int ( ) const;			//���ض��е�ʵ��Ԫ�ظ���
    virtual int full ( ) const;		       //���ض����Ƿ�������������1�����򷵻�0
    virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ��,��1��Ԫ���±�Ϊ0
    virtual QUEUE& operator<<(int e); 	//��e�����,�����ض���
    virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
    virtual QUEUE& operator=(const QUEUE&q); //��q������,�����ر���ֵ�Ķ���
    virtual QUEUE& operator=(QUEUE &&q);	//�ƶ���ֵ
    virtual void print( ) const;			//��ӡ����
    virtual ~QUEUE( );					//���ٶ���
};

using namespace std;

bool queue_is_error = false;//��־λ�������жϳ����Ƿ����

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
    if(elems) {//�����ظ��ͷſռ�
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
