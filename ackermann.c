#include <stdio.h>
#include <limits.h>

#define MAXM 10
#define MAXN 60
#define FID 3

unsigned long long int ans[MAXM-FID][MAXN];

unsigned long long int ack(int m, int n){
    if (m == 0) return n+1;
    if (m == 1) return n+2;
    if (m == 2) return (n << 1) + 3;
    if (m == 3 && n > 0){
        if (ans[m-FID][n-1] != 0) ans[m-FID][n] = (ans[m-FID][n-1] << 1) + 3;
        else ans[m-FID][n] = (ack(m, n-1) << 1) + 3;
        return ans[m-FID][n];
    } 
    if (m == 4 && n > 0){
        if (ans[m-FID][n-1] != 0) ans[m-FID][n] = (8 << ans[m-FID][n-1]) - 3;
        else ans[m-FID][n] = (8 << ack(m, n-1)) - 3;
        return ans[m-FID][n];
    }

    if (n > 0 && ans[m-FID][n-1] != 0) ans[m-FID][n] = ack(m-1, ans[m-FID][n-1]);
    else if (n == 0) ans[m-3][n] = ack(m-1, 1);
    else if (n == 1) ans[m-FID][n] = ack(m-1, ack(m-1, 1));
    else ans[m-FID][n] = ack(m-1, ack(m, n-1));
    
    return ans[m-FID][n];

}

int main(){
    for (int i=3; i<MAXM; i++){
        for (int j=0; j<MAXN; j++){
            unsigned long long res = ack(i, j);
            if (res < ULLONG_MAX-2) printf("ackermann (%d, %d): %llu\n", i, j, ack(i, j));
            else j = MAXN;
        }
        printf("\n");
    }
    
    return 0;
}
