#include <stdio.h>
#include <stdlib.h>
struct edge{
    long long int from;
    long long int to;
    long long int wt;
};
void mg(struct edge* arr,long long int l,long long int m,long long int r){
    long long int lsize = m-l+1;
    long long int rsize = r-m;
    struct edge lt[lsize],rt[rsize];
    for(int i = 0;i<lsize;i++){
        lt[i] = arr[i+l];
    }
    for(int i = 0;i<rsize;i++){
        rt[i] = arr[m+i+1];
    }
    long long int i = 0,j=0,ct=l;
    while((i<lsize) && (j<rsize)){
        if(lt[i].wt<rt[j].wt){
            arr[ct] = lt[i];
            ct++;
            i++;
        }
        else{
            arr[ct] = rt[j];
            ct++;
            j++;
        }
    }
    while(i<lsize){
        arr[ct] = lt[i];
        ct++;
        i++;
    }
    while(j<rsize){
        arr[ct] = rt[j];
        ct++;
        j++;
    }
}
void ms(struct edge* arr, long long int l, long long int r) {
    if (l < r) {
        long long int m = l + (r - l) / 2;
        ms(arr, l, m);
        ms(arr, m + 1, r);
        mg(arr, l, m, r);
    }
}
long long int find(long long int arr[], long long int n, long long int i)
{
    while (arr[i] != i)
    {
        i = arr[i];
    }
    return i;
}
long long int max(long long int a, long long int b)
{
    return (a > b) ? a : b;
}
void merge(long long int *p, long long int *h, long long int p1, long long int p2)
{
    if (h[p1] < h[p2])
    {
        p[p1] = p2;
        h[p2] = max(h[p2], 1 + h[p1]);
    }
    else     
    {
        p[p2] = p1;
        h[p1] = max(h[p1], 1 + h[p2]);
    }
}
void dsu()
{
    long long int n, q;
    scanf("%lld %lld", &n, &q);
    long long int p[n + 1], h[n + 1];
    for (int i = 1; i <= n; i++)
    {
        p[i] = i;
        h[i] = 0;  
    }
    for (int i = 0; i < q; i++)
    {
        long long int query, a1, a2;
        scanf("%lld %lld %lld", &query, &a1, &a2);
        long long int p1 = find(p, n, a1);
        long long int p2 = find(p, n, a2);
        if (query == 0)
        {
            if (p1 == p2)
                continue;
            else
            {
                merge(p,h,p1,p2);
            }
        }
        else if (query == 1)
        {
            if (p1 == p2)
                printf("1 ");
            else
                printf("0 ");
        }
    }
}

void kruskal()
{
    long long int n;
    long long int ans = 0;
    scanf("%lld", &n);
    long long int sz = (1LL*n*(n-1));
    struct edge* ed = (struct edge*)malloc(sizeof(struct edge)*sz);
    long long int ct = 0;
    long long int p[n+1],h[n+1];   
    for(int i = 1;i<=n;i++){
        p[i] = i;
        h[i] = 0;
    }
    for(int i = 1;i<=n;i++){
      while(1){
        long long int a;
        scanf("%lld",&a);
        if(a==-1) break;
        long long int b;
        scanf("%lld",&b);
        ed[ct].from = i;
        ed[ct].to = a;
        ed[ct].wt = b;
        ct++;
      }
    }
    
    ms(ed,0,ct-1);
    long long int count = 0;
    long long int ind = 0;
    while(count != (n-1)){  
        long long int from = ed[ind].from;
        long long int to = ed[ind].to;
        long long int pf = find(p,n,from);
        long long int pt = find(p,n,to);
        if(pf==pt){
            ind++;
            continue;
        }
        else{
            merge(p,h,pf,pt);
            ans += ed[ind].wt;
            ind++;
            count++;
        }
    }
    printf("%lld ",ans);
}
int main()
{
    long long int flag;
    scanf("%lld", &flag);
    if (flag == 0)
    {
        dsu();
    }
    else if (flag == 1)
    {
        kruskal();
    }
    return 0;
}
