#include <cmath>
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

typedef struct Point
{// 二维坐标上的点Point
    double x;
    double y;
    int camp;//确定点的类别 1:士兵 2:发电站
}Point;

double Distance(Point a, Point b)
{//平面上任意两点对之间的距离公式计算
    if (a.camp == b.camp)
        return numeric_limits<double>::max();
    else
        return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool CompareX(Point a, Point b)
{//自定义排序规则：依照结构体中的x成员变量升序排序
    return a.x < b.x;
}

bool CompareY(Point a, Point b)
{//自定义排序规则：依照结构体中的x成员变量升序排序
    return a.y < b.y;
}

double FindPair(Point *points, int l,int r)
{// 求出最近点对记录，并将两点记录再a、b中
    double distance;                   //记录集合points中最近两点距离
    if (l == r)
        return numeric_limits<double>::max();    //若子集长度小于2，定义为最大距离，表示不可达
    if (l + 1 == r)
    {//若子集长度等于2，直接返回该两点的距离
        distance = Distance(points[l], points[r]);
        return distance;
    }
    //子集长度大于3，进行分治求解
    Point *rectangle = new Point[r - l + 1];
    int m = (l + r) >> 1;
    distance = min(FindPair(points,l, m), FindPair(points,m + 1, r));
    //merge - 进行子集合解合并
    //求解跨分割线并在δ×2δ区间内的最近点对
    int k = 0;
    for (int i = l; i <= r; i++)//取得中线2δ宽度的所有点对共k个
        if (abs(points[i].x - points[m].x) <= distance)
            rectangle[k++] = points[i];
    sort(rectangle, rectangle + k, CompareY);// 以y排序矩形阵内的点集合


    for (int i = 0; i < k; i++) {
        for (int j = i+1; j < k; j++) {
            if (rectangle[j].y - rectangle[i].y >= distance)
                break;
            if (rectangle[i].camp != rectangle[j].camp)
                distance = min(distance, Distance(rectangle[i], rectangle[j]));
        }
    }
    delete rectangle;
    return distance;
}

int main()
{
    int number;
    int N;
    Point *points;
    scanf("%d", &number);
    while (number--) {
        scanf("%d", &N);
        points = new Point[2 * N];
        for (int i = 0; i < N; ++i) {
            scanf("%lf %lf", &points[i].x, &points[i].y);
            points[i].camp = 0;//电厂
        }
        for (int i = 0; i < N; ++i) {
            scanf("%lf %lf", &points[N + i].x, &points[N + i].y);
            points[i].camp = 1;//士兵
        }
        N *= 2;
        sort(points, points + N , CompareX);    //调用algorithm库中的sort函数对points进行排序，compareX为自定义的排序规则
        printf("%.3lf\n", FindPair(points,0, N-1));
        delete points;
    }
    return 0;
}
