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

class QUEUE : public STACK {
    STACK s;
public:
    QUEUE(int m); //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
    QUEUE(const QUEUE &q);            //�ö���q������ʼ������
    QUEUE(QUEUE &&q);                //�ƶ�����
    virtual operator int() const;            //���ض��е�ʵ��Ԫ�ظ���
    virtual int full() const;               //���ض����Ƿ�������������1������0
    virtual int operator[](int x) const;   //ȡ�±�Ϊx��Ԫ�أ���1��Ԫ���±�Ϊ0
    virtual QUEUE &operator<<(int e);  //��e�����,�����ض���
    virtual QUEUE &operator>>(int &e);    //�����е�e,�����ض���
    virtual QUEUE &operator=(const QUEUE &q); //��q������,�����ر���ֵ����
    virtual QUEUE &operator=(QUEUE &&q);  //�ƶ���ֵ
    virtual void print() const;            //��ӡ����
    virtual ~QUEUE();                    //���ٶ���
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
    if(elems){//�����ظ��ͷſռ�
        delete [] elems;
        *(int **)(&elems) = nullptr;
        *(int *)(&max) = 0;
        pos = 0;
    }
}

QUEUE::QUEUE(int m):STACK(m),s(m){

}

QUEUE::QUEUE(const QUEUE &q):STACK(q),s(q.s){

}

QUEUE::QUEUE(QUEUE &&q):STACK(std::move(q)),s(std::move(q.s)){

}

QUEUE::operator int() const{
    return STACK::operator int() + (int)s;
}

int QUEUE::full() const{
    if((int)s != 0 && STACK::operator int() == STACK::size())
        return 1;
    else
        return 0;
}

int QUEUE::operator[](int x) const{
    if(x < 0 || x >= (int)s + STACK::operator int()){
        queue_is_error = true;
        return 0;
    }
    if(x <= (int)s)
        return s[(int)s - x];
    else{
        return STACK::operator[](x - (int)s - 1);
    }
}

QUEUE& QUEUE::operator<<(int e){
    if((*this).size() == STACK::operator int() && (int)s != 0) {
        queue_is_error = true;
    }else if((*this).size() == STACK::operator int() && (int)s == 0){
        int temp;
        for(int i = 0;i < (*this).size();i++){
            STACK::operator>>(temp);
            s << temp;
        }
        STACK::operator<<(e);
    }else{
        STACK::operator<<(e);
    }
    return (*this);
}

QUEUE& QUEUE::operator>>(int &e){
    if((int)s != 0){
        s >> e;
    }else if((int)s == 0 && STACK::operator int() != 0){
        int temp;
        int number = STACK::operator int();
        for(int i = 0;i < number - 1;i++){
            STACK::operator>>(temp);
            s << temp;
        }
        STACK::operator>>(e);
        number = (int)s;
        for(int i = 0;i < number;i++){
            s >> temp;
            STACK::operator<<(temp);
        }
    }else{
        queue_is_error = true;
    }
    return (*this);
}

QUEUE& QUEUE::operator=(const QUEUE &q){
    STACK::operator=(q);
    s = q.s;
    return (*this);
}

QUEUE& QUEUE::operator=(QUEUE &&q){
    STACK::operator=(std::move(q));
    s = std::move(q.s);
    return (*this);
}

void QUEUE::print() const{
    for(int i = (int)s - 1;i >= 0;i--)
        std::cout << s[i] << "  ";
    STACK::print();
}

QUEUE::~QUEUE(){

}