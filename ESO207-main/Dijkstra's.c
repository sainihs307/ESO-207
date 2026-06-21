#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647
struct edge
{
    int to;
    int wt;
    struct edge *next;
};
struct edge *create(int wt, int to)
{
    struct edge *node = (struct edge *)malloc(sizeof(struct edge));
    node->to = to;
    node->wt = wt;
    node->next = NULL;
    return node;
}
struct dist{
    int node;
    int fd;
};
void min_heapify(struct dist* arr, int i, int heap_ct,int* index)
{
    if (i == heap_ct)
        return;
    else
    {
        int lv = (2 * i <= heap_ct);
        int rv = ((2 * i + 1) <= heap_ct);
        if (lv && rv)
        {
            int min_index = (arr[2 * i].fd < arr[2 * i + 1].fd) ? (2 * i) : (2 * i + 1);
            // printf("%d\n",min_index);
            if (arr[min_index].fd < arr[i].fd)
            {
                
                index[arr[min_index].node] = i;
                index[arr[i].node] = min_index;
                
                struct dist tmp = arr[i];
                arr[i] = arr[min_index];
                arr[min_index] = tmp;
                
                min_heapify(arr, min_index, heap_ct,index);
            }
        }
        else if (lv == 0 && rv != 0)
        {
            if (arr[2 * i + 1].fd < arr[i].fd)
            {
                index[arr[2*i+1].node] = i;
                index[arr[i].node] = 2*i+1;
                struct dist tmp = arr[i];
                arr[i] = arr[2*i+1];
                arr[2*i+1] = tmp;
                min_heapify(arr, 2 * i + 1, heap_ct,index);
            }
        }
        else if (rv == 0 && lv != 0)
        {
            if (arr[2 * i].fd < arr[i].fd)
            {   
                index[arr[2*i].node] = i;
                index[arr[i].node] = 2*i;
                struct dist tmp = arr[i];
                arr[i] = arr[2*i];
                arr[2*i] = tmp;
                min_heapify(arr, 2 * i, heap_ct,index);
            }
        }
    }
    return;
}
void build_heap(struct dist* arr, int heap_ct,int* index)
{
    for (int i = heap_ct; i >= 1; i--)
    {
        min_heapify(arr, i, heap_ct,index);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    struct dist d[n + 1];
    int p[n + 1];
    for (int i = 1; i <= n; i++)
    {
        d[i].node = i-1;
        d[i].fd = INF;
        p[i] = INF;
    }

    struct edge *gf[n + 1];
    for (int i = 1; i <= n; i++)
    {
        gf[i] = create(0, i-1);
    }
    int edge_counter = 0;
    for (int i = 1; i <= n; i++)
    {
        struct edge *current = gf[i];
        while (1)
        {
            int t;
            scanf("%d", &t);
            if (t == -1)
                break;
            int w;
            scanf("%d", &w);

            current->next = create(w, t);
            edge_counter++;
            current = current->next;
        }
    }
    int src;
    scanf("%d", &src);
    d[src + 1].fd = 0;
    p[src+1] = 0;
    int index[n+1];
    for (int i = 1; i <= n; i++) {
        index[d[i].node] = i;
    }
    // build_heap(d, n);
    int count = n;
    build_heap(d,count,index);
    while (count>0)
    {
        
        int tmp1 = d[1].node;
        int tmp2 = d[1].fd;
        printf("%d %d ",tmp1,tmp2);
        d[1] = d[count];
        index[d[1].node] = 1;
        count--;
        min_heapify(d,1,count,index);
        // d[count].fd = tmp2;
        struct edge* current = gf[tmp1 + 1]->next;
        while(current!=NULL){
            int a = current->to;
            int w = current->wt;
            if(d[index[a]].fd > (tmp2 + w)){
                
                d[index[a]].fd = tmp2+w;
                build_heap(d, count,index);
                 
            }
            current = current->next;
        }

    }
    
    return 0;
}