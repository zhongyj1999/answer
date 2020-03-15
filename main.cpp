#include <iostream>
#include <vector>

using namespace std;
vector<int> w, have, maxt, mint;
vector<vector<int>> v;
/*
    w 用来存储每篇论文完成需要的时间
    have 用来确定是否是最后一篇完成的论文或者单独完成的一篇论文
    maxt 用来存储在最早完成情况下每篇的最迟完成时间
    mint 用来存储每篇最早完成时间
    v 用来存储每篇文章的前后关联
*/

int DP(int x){    //利用递归从上往下的计算每篇文章的最早完成时间，利用动态规划思想可以避免重复计算
    if(mint[x] != 0) return mint[x];
    if(v[x].size() == 0){
        mint[x] = w[x];
        //printf("%d %d\n", x, w[x]);
        return w[x];
    }
    int tempmax = -1;
    for(int i = 0; i < v[x].size(); i++){
        int temp = DP(v[x][i]);
        if(temp > tempmax){
            tempmax = temp;
        }
    }
    mint[x] = tempmax + w[x];
    //printf("%d %d %d\n", x, mint[x], tempmax);
    return mint[x];
}

void getmaxt(int x){   //从上往下计算每篇文章最迟开始的完成时间，选择其中最小的最迟开始时间，不然会影响最早完成时间
    if(v[x].size() == 0) return ;
    for(int i = 0; i < v[x].size(); i++){
        if(maxt[v[x][i]] == 0) maxt[v[x][i]] = maxt[x] - w[x];
        else maxt[v[x][i]] = min(maxt[v[x][i]], maxt[x] - w[x]);
        getmaxt(v[x][i]);
    }
}

int main()
{
    int n, m, tempmaxt = -1;
    long long int ans = 1;
    scanf("%d %d", &n, &m);
    v.resize(n + 1);
    w.resize(n + 1);
    have.resize(n + 1);
    maxt.resize(n + 1);
    mint.resize(n + 1);
    for(int i = 1; i <= n; i++){
        scanf("%d", &w[i]);
    }
    for(int i = 0; i < m; i++){ //存储前后文章关系
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
            tempmaxt = max(tempmaxt, temp);
        }
    }
    printf("%d\n", tempmaxt);
    for(int i = 1; i <= n; i++){
        if(have[i] == 0){
            maxt[i] = tempmaxt;
            getmaxt(i);
        }
    }
    /*
    for(int i = 1; i <= n; i++){
        printf("%d %d\n", mint[i], maxt[i]);
    }
    */
    for(int i = 1; i <= n; i++){
        ans = ans * (maxt[i] - mint[i] + 10) % 1000000007;
    }
    printf("%lld", ans);
    return 0;
}
