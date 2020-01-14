#include<cstdio>
#include<cstring>
#include <map>
#include <iostream>
#include <string>

using namespace std;

int main() {
    map<string,string> dictionary;
    char str[22];
    string s1,s2,s;
    while(gets(str)&&strlen(str)){
        for(int i = 0;;i++){
            if(str[i] == ' '){
                str[i] = '\0';
                s1 = str;
                s2 = str+i+1;
                break;
            }
        }
        dictionary[s2] = s1;
    }
    while(cin >> s){
        if(dictionary.find(s) != dictionary.end()){
            printf("%s\n",dictionary[s].c_str());
        }else
            printf("eh\n");
    }
    return 0;
}