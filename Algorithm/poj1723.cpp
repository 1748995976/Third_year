#include <stdio.h>
#include <math.h>

void QuickSort(int buf[],int left,int right);

void Switch(int &l,int &right);

# define N 10000

int main(){
    int n;
    int sum = 0;
    scanf("%d",&n);
    int X[N],Y[N];
    for (int i = 0; i < N; i++)
        scanf("%d %d",&X[i],&Y[i]);
    QuickSort(X,0,n-1);
    QuickSort(Y,0,n-1);
    int midY=Y[(n+1)/2-1];
    for(int i=0;i<n;i++)
        X[i]-=i;
    QuickSort(X,0,n-1);
    int midX=X[(n+1)/2-1];
    for(int i=0;i<n;i++)
    sum = sum + abs(Y[i]-midY)+abs(X[i]-midX);
    printf("%d\n",sum);
    return 0;
}

void QuickSort(int *buf,int left,int right){
    int al = left,ar = right,temp = buf[left];
    if(left >= right)
        return;
    while(al != ar){
        while(buf[ar] >= temp && al < ar)
            ar--;
        while(buf[al] <= temp && al < ar)
            al++;
        if(al < ar)
            Switch(buf[al],buf[ar]);
    }
    if(al != left)
        Switch(buf[al],buf[left]);
    QuickSort(buf,left,al-1);
    QuickSort(buf,al+1,right);
}

void Switch(int &l,int &right){
    int temp = l;
    l = right;
    right = temp;
}