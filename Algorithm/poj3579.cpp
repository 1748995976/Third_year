#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

int N;
int CN2 = 0;
int X[100005];
bool C(int x) { // 验证x作为中位数 x = X[j] - X[i] 是否太小
	int cnt = 0;
	for (int i = 0; i<N; ++i) {
		cnt += N - (lower_bound(X + i, X + N, X[i] + x) - X); // 统计差值>=x的个数
	}
	return cnt > CN2 >> 1;
}
void solve() {
	sort(X, X + N);
	CN2 = N*(N - 1) >> 1;
	int lb = 0, ub = 1000000001;
	while (ub - lb > 1) {
		int mid = (ub + lb) >> 1;
		if (C(mid)) lb = mid; // 中位数过小，半闭半开区间[lb, ub)
		else ub = mid;
	}
	printf("%d\n", lb);
}
int main()
{
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; ++i)
            scanf("%d", X + i);
		solve();
	}
	return 0;
}