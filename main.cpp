#include <iostream>
#include <vector>

using namespace std;
struct node{
    int mint, maxt;
};
vector<node> dp;
vector<int> w, have;
vector<vector<int>> v;


int DP(int x){
    if(v[x].size() == 0){
        dp[x].mint = w[x];
        printf("%d %d\n", x, w[x]);
        return w[x];
    }
    int tempmax = -1;
    for(int i = 0; i < v[x].size(); i++){
        int temp = DP(v[x][i]);
        if(temp > tempmax){
            tempmax = temp;
        }
    }
    dp[x].mint = tempmax + w[x];
    for(int i = 0; i < v[x].size(); i++){
        if(dp[v[x][i]].maxt == 0) dp[v[x][i]].maxt = tempmax;
        else dp[v[x][i]].maxt = min(tempmax, dp[v[x][i]].maxt);
    }
    printf("%d %d %d\n", x, dp[x].mint, tempmax);
    return dp[x].mint;
}

int main()
{
    int n, m, maxt = -1;
    scanf("%d %d", &n, &m);
    dp.resize(n + 1);
    v.resize(n + 1);
    w.resize(n + 1);
    have.resize(n + 1);
    for(int i = 1; i <= n; i++){
        scanf("%d", &w[i]);
    }
    for(int i = 0; i < m; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        have[a] = 1;
        v[b].push_back(a);
    }
    /*
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < v[i].size(); j++){
            if(j != 0) printf(" ");
            printf("%d",v[i][j]);
        }
        printf("\n");
    }
    */
    for(int i = 1; i <= n; i++){
        if(have[i] == 0){
            int temp = DP(i);
            printf("maxt and temp:%d %d %d\n", i, maxt, temp);
            maxt = max(maxt, temp);
        }
    }
    printf("%d\n", maxt);
    for(int i = 1; i <= n; i++){
        printf("%d %d\n", dp[i].maxt, dp[i].mint);
    }
    return 0;
}
