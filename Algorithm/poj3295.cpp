#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

int p, q, r, s, t;

bool Push(char ch,stack<int> &variate) {
    switch (ch) {
        case 'p': {
            variate.push(p);
            return true;
        }
        case 'q': {
            variate.push(q);
            return true;
        }
        case 'r': {
            variate.push(r);
            return true;
        }
        case 's': {
            variate.push(s);
            return true;
        }
        case 't': {
            variate.push(t);
            return true;
        }
        default:{
            return false;
        }
    }
}

void Calculate(char ch,stack<int> &variate) {
    int first_va;
    int second_va;
    switch (ch) {
        case 'K': {
            first_va = variate.top();variate.pop();
            second_va = variate.top();variate.pop();
            variate.push(first_va && second_va);
            return;
        }
        case 'A': {
            first_va = variate.top();variate.pop();
            second_va = variate.top();variate.pop();
            variate.push(first_va || second_va);
            return;
        }
        case 'N': {
            first_va = variate.top();variate.pop();
            variate.push(!first_va);
            return;
        }
        case 'C': {
            first_va = variate.top();variate.pop();
            second_va = variate.top();variate.pop();
            variate.push(first_va || (!second_va));
            return;
        }
        case 'E': {
            first_va = variate.top();variate.pop();
            second_va = variate.top();variate.pop();
            variate.push(first_va == second_va);
            return;
        }
    }
}

void Judge(char *str,stack<int> &variate,int size){
    for(p = 0;p < 2;p++)
        for (q = 0;q < 2;q++)
            for(r = 0;r < 2;r++)
                for(s = 0;s < 2;s++)
                    for(t = 0;t < 2;t++){
                        for(int i = size - 1;i >= 0;i--){
                            if(!Push(str[i],variate))
                                Calculate(str[i],variate);
                        }
                        if(variate.top() == 0){
                            cout << "not" << endl;
                            variate.pop();
                            return;
                        }
                    }
    cout << "tautology" << endl;
    variate.pop();
}

int main() {
    stack<int> variate;
    char str[101];
    while (true) {
        scanf("%s",str);
        if (str[0] == '0')
            break;
        Judge(str,variate,strlen(str));
    }
    return 0;
}