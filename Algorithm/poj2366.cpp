#include <iostream>

int main() {
    int number_1;
    scanf("%d",&number_1);
    int *buff_1 = new int[number_1];
    for (int i = 0; i < number_1; ++i) {
        scanf("%d",&buff_1[i]);
    }
    int number_2;
    scanf("%d",&number_2);
    int *buff_2 = new int[number_2];
    for (int i = 0; i < number_2; ++i) {
        scanf("%d",&buff_2[i]);
    }
    if(buff_1[0] + buff_2[number_2-1] > 10000 || buff_1[number_1-1] + buff_2[0] < 10000){
        printf("NO\n");
        return 0;
    }
    int low;
    int high;
    int mid;
    for (int i = 0; i < number_1; ++i) {
        low = 0;
        high = number_2 -1;
        int other = 10000 - buff_1[i];
        while(low <= high){
            mid = (low+high)/2;
            if(buff_2[mid] == other) {
                printf("YES\n");
                return 0;
            }
            if(buff_2[mid] < other){
                high = mid -1;
                continue;
            }
            else{
                low = mid +1;
                continue;
            }
        }
    }
    printf("NO\n");
    return 0;
}