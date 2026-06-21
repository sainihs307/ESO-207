#include <stdio.h>
void min_heapify(int *arr, int i, int heap_ct)
{
    if (i == heap_ct)
        return;
    else
    {
        int lv = (2 * i <= heap_ct);
        int rv = ((2 * i + 1) <= heap_ct);
        if (lv & rv)
        {
            int min_index = (arr[2 * i] < arr[2 * i + 1]) ? (2 * i) : (2 * i + 1);
            // printf("%d\n",min_index);
            if (arr[min_index] < arr[i])
            {
                int tmp = arr[min_index];
                arr[min_index] = arr[i];
                arr[i] = tmp;
                // min_index = i;
                min_heapify(arr, min_index, heap_ct);
            }
        }
        else if (lv == 0 && rv!=0)
        {
            if (arr[2 * i + 1] < arr[i])
            {
                int tmp = arr[2 * i + 1];
                arr[2 * i + 1] = arr[i];
                arr[i] = tmp;
                min_heapify(arr, 2 * i + 1, heap_ct);
            }
        }
        else if (rv == 0 && lv!=0)
        {
            if (arr[2 * i] < arr[i])
            {
                int tmp = arr[2 * i];
                arr[2 * i] = arr[i];
                arr[i] = tmp;
                min_heapify(arr, 2 * i, heap_ct);
            }
        }
    }
    return;
}
void build_heap(int *arr, int heap_ct)
{
    for(int i = heap_ct;i>=1;i--)
    {
        min_heapify(arr,i,heap_ct);
    }
}
int main()
{
    int o, max_;
    scanf("%d %d", &o, &max_);
    int stack[max_];
    int queue[max_];
    int heap[max_ + 1];
    int st_counter = 0;
    int heap_ct = 0;
    int node = 1, leaf = 1;
    int qhead = 0, qtail = 0, qblock = 0;
    if (o == 0)
    {
        while (1)
        {
            int a;
            scanf("%d", &a);
            if (a == 0)
            {
                for (int i = 0; i < st_counter; i++)
                {
                    printf("%d ", stack[i]);
                }
                printf("\n");
            }
            else if (a == 1)
            {
                int b;
                scanf("%d", &b);
                if (st_counter == max_)
                {
                    printf("-1\n");
                    return 0;
                }
                else
                {
                    stack[st_counter] = b;
                    st_counter++;
                }
            }
            else if (a == 2)
            {
                if (st_counter == 0)
                {
                    printf("-1\n");
                    return 0;
                }
                else
                {

                    printf("%d\n", stack[st_counter - 1]);
                    st_counter--;
                }
            }
            else if (a == 3)
                return 0;
        }
    }
    else if (o == 1)
    {
        while (1)
        {
            int a;
            scanf("%d", &a);
            if (a == 0)
            {   
                if(qhead == qtail && qtail == qblock)printf("\n");
                else if (qtail >= qhead)
                {
                    
                    for (int i = qhead; i <= qtail; i++)
                    {
                        printf("%d ", queue[i]);
                    }
                    printf("\n");
                }
                else if (qtail < qhead)
                {
                    for (int i = qhead; i < max_; i++)
                    {
                        printf("%d ", queue[i]);
                    }
                    for (int i = 0; i <= qtail; i++)
                    {
                        printf("%d ", queue[i]);
                    }
                    printf("\n");
                }
            }
            else if (a == 1)
            {
                if (((qhead == 0) && (qblock == (max_ - 1))) || (qhead == (qblock + 1)))
                {
                    printf("-1\n");
                    return 0;
                }
                else
                {
                    int b;
                    scanf("%d", &b);
                    if (qblock == (max_ - 1))
                    {
                        queue[qblock] = b;
                        qtail = qblock;
                        qblock = 0;
                    }
                    else
                    {
                        queue[qblock] = b;
                        qtail = qblock;
                        qblock++;
                    }
                }
            }
            else if (a == 2)
            {
                if (qhead == qtail && qtail == qblock)
                {
                    printf("-1\n");
                    return 0;
                }
                else if(qhead==qtail)
                {
                    printf("%d\n",queue[qhead]);
                    qhead = qblock;
                    qtail = qblock;
                }
                else{
                    printf("%d\n", queue[qhead]);
                    if (qhead == max_ - 1)
                    {
                        qhead = 0;
                    }
                    else
                    {
                        qhead++;
                    }
                    }
                }
            
            else if (a == 3)
            {
                return 0;
            }
        }
    }
    else if (o == 2)
    {   
        while(1)
        {
        int a1;
        scanf("%d", &a1);
        if (a1 == 4)
        {
            return 0;
        }
        else if (a1 == 3)
        {
            if (heap_ct == 0)
            {
                printf("-1\n");
                return 0;
            }
            else
            {
                printf("%d\n", heap[1]);
                int tmp1 = heap[1];
                int tmp2 = heap[heap_ct];
                heap[1] = tmp2;
                heap[heap_ct] = tmp1;
                heap_ct--;
                build_heap(heap,heap_ct);
            }
        }
        else if(a1 == 2)
        {
            int a2,a3;
            scanf("%d %d",&a2,&a3);
            if(!(a2>max_) && !(heap[a2]<a3))
            {
                heap[a2] = a3;
                if(!(heap[a2/2] <= heap[a2]))
                {
                    for(int i = a2;i>=1;i--)
                    {
                        min_heapify(heap,i,heap_ct);
                    }
                }
            }
        }
        else if(a1==1)
        {
            int a2;
            scanf("%d",&a2);
            int tmp;
            if((a2+heap_ct)>max_)
            {
                printf("-1\n");
                return 0;
            }
            else
            {
                int j = heap_ct;
                for(int i = 1;i<=a2;i++)
                {
                    scanf("%d",&heap[j+1]);
                    heap_ct++;
                    j++;
                }
                build_heap(heap,heap_ct);
            }
        }
        else if(a1==0)
        {
            for(int i = 1;i<=heap_ct;i++)
            {
                printf("%d ",heap[i]);
            }
            printf("\n");
        }
        }
    }
    return 0;
}
