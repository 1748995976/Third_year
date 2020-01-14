#include <string.h>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

#define maxn 101
#define inf 0x7fffffff

int metrix[maxn][maxn];
int f[maxn][maxn];

int main() {
    int n;
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d",&metrix[i][j]);
        }
    }
    memset(f, 0, sizeof(f));
    int ans = -inf;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int sum = 0;
            for (int k = j; k <= n; k++) {
                sum += metrix[i][k];
                // i是指行，j是起始列，k是终结列，f存的值为在ijk范围内的元素和最大值
                f[j][k] = max(f[j][k] + sum, sum);
                ans = max(ans, f[j][k]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}