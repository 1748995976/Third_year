#include <iostream>
#include <cstring>

int n;
int m;

int mat[30][30];//A

int mat_sum[30][30];//Ak/2∗s[k/2]+s[k/2]
int mat_rem[30][30];//s[k/2]

int mat_tmp[30][30];

void matmul(const int a[30][30], const int b[30][30],int ulti[30][30]){// mat multiple: ulti = a*b
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ulti[i][j] = 0;
            for (int l = 0; l < n; ++l) {
                ulti[i][j] += (a[i][l] * b[l][j]) % m;
            }
            ulti[i][j] %= m;
        }
    }
    return;
}

void calculate(int a){ // after calc, r=mat^a, rs=mat^1 + ... + mat^a
    if(a == 1){
        memcpy(mat_sum,mat, sizeof(mat));
        memcpy(mat_rem,mat, sizeof(mat));
        return;
    }

    int b = a >>1;
    calculate(b);

    // mat_tmp = mat_rem*mat_sum + mat_sum
    matmul(mat_sum,mat_rem,mat_tmp);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat_tmp[i][j] = (mat_sum[i][j]+mat_tmp[i][j])%m;
        }
    }

    // mat_sum = mat_tmp
    // mat_tmp = mat_rem^2
    memcpy(mat_sum,mat_tmp, sizeof(mat_tmp));
    matmul(mat_rem,mat_rem,mat_tmp);

    if(a%2 == 0){//s[k]=Ak/2∗s[k/2]+s[k/2]，Ak=Ak/2∗Ak/2
        memcpy(mat_rem,mat_tmp, sizeof(mat_tmp));
        return;
    }else{//s[k]=Ak/2∗s[k/2]+s[k/2]+Ak，Ak=Ak/2∗Ak/2∗A
        matmul(mat_tmp,mat,mat_rem);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                mat_sum[i][j] = (mat_sum[i][j] + mat_rem[i][j])%m;
            }
        }
    }

}
int main() {
    int k;
    scanf("%d %d %d", &n, &k, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);
    }
    calculate(k);
    for (int i = 0; i < n; i++) {
        printf("%d", mat_sum[i][0]);
        for (int j = 1; j < n; j++) {
            printf(" %d", mat_sum[i][j]);
        }
        printf("\n");
    }
    return 0;
}
