#include <stdio.h>
#include <math.h>
int num_ct = 0;
int op_ct = 0;
int priority(int t)
{
    if (t == -1 || t == -2)
        return 1;
    else if (t == -3)
        return 2;
    else if(t == -4)
        return 3;
    else if (t == -5)
        return 4;
    else
        return 0;
}
int power(int a,int b){
  int tmp = 1;
  for(int i = 1;i<=b;i++){
    tmp *= a;
  }
  return tmp;
}
int chkdo(int a, int b, int op)
{
    if (op == -2)
        return a + b;
    else if (op == -1)
        return b - a;
    else if (op == -3)
        return a * b;
    else if (op == -4)
        return b / a;
    else if (op == -5)
        return power(b, a);
}
int main()
{
    int t;
    scanf("%d", &t);
    if (t == 0)
    {
        int n;
        scanf("%d", &n);
        int temp = 0;
        int num_st[n + 1], op_st[n + 1];
        while (n--)
        {
          
            scanf("%d ", &temp);
            if (temp > 0)
            {
                num_st[num_ct] = temp;
                // printf("%d\n",temp);
                num_ct++;
            }
            else
            {
                if (op_ct == 0)
                {
                    op_st[op_ct] = temp;
                    // printf("%d\n",temp);
                    op_ct++;
                }
                else if(temp == -6){
                    op_st[op_ct] = temp;
                    op_ct++;
                }
                else if(temp == -7){
                  while(op_st[op_ct-1] != -6){
                        int a = num_st[num_ct - 1];
                        int b = num_st[num_ct - 2];
                        int res = chkdo(a, b, op_st[op_ct - 1]);
                        // printf("%d %d %d = %d \n",num_st[num_ct - 1],op_st[op_ct - 1],num_st[num_ct - 2],res);
                        num_st[num_ct - 2] = res;
                        num_ct--;
                        op_ct--;
                  }
                  op_ct--;
                }
                else if (priority(temp) > priority(op_st[op_ct - 1]))
                {
                    op_st[op_ct] = temp;
                    op_ct++;
                }
                else if (priority(temp) < priority(op_st[op_ct - 1]))
                {
                    while (priority(temp) < priority(op_st[op_ct - 1]))
                    {
                        
                        int a = num_st[num_ct - 1];
                        int b = num_st[num_ct - 2];
                        int res = chkdo(a, b, op_st[op_ct - 1]);
                        // printf("%d %d %d = %d \n",num_st[num_ct - 1],op_st[op_ct - 1],num_st[num_ct - 2],res);
                        num_st[num_ct - 2] = res;
                        num_ct--;
                        op_ct--;
                    }
                    if (priority(temp) > priority(op_st[op_ct - 1]))
                    {
                        op_st[op_ct] = temp;
                        op_ct++;
                    }
                    else
                    {
                        if (temp != -5)
                        {
                            int a = num_st[num_ct - 1];
                            int b = num_st[num_ct - 2];
                            int res = chkdo(a, b, op_st[op_ct - 1]);
                            // printf("%d %d %d = %d \n",num_st[num_ct - 1],op_st[op_ct - 1],num_st[num_ct - 2],res);
                            num_st[num_ct - 2] = res;
                            num_ct--;
                            op_ct--;
                            op_st[op_ct] = temp;
                            op_ct++;
                        }
                        else
                        {
                            op_st[op_ct] = temp;
                            op_ct++;
                        }
                    }
                }
                else
                {
                    if (temp != -5)
                    {
                        
                        int a = num_st[num_ct - 1];
                        int b = num_st[num_ct - 2];
                        int res = chkdo(a, b, op_st[op_ct - 1]);
                        
                        num_st[num_ct - 2] = res;
                        num_ct--;
                        op_ct--;
                        op_st[op_ct] = temp;
                        op_ct++;
                        
                    }
                    else
                    {
                        op_st[op_ct] = temp;
                        op_ct++;
                    }
                }
            }
        }
        while (num_ct != 1)
        {
            int a = num_st[num_ct - 1];
            int b = num_st[num_ct - 2];
            int res = chkdo(a, b, op_st[op_ct - 1]);
            // printf("%d %d %d = %d \n",num_st[num_ct - 1],op_st[op_ct - 1],num_st[num_ct - 2],res);
            num_st[num_ct - 2] = res;
            num_ct--;
            op_ct--;
        }
        printf("%d",num_st[num_ct-1]);
    }

    else if (t == 1)
    {
        int sz;
        scanf("%d", &sz);
        int n = sz - 1;
        long long int arr[sz];
        for (int i = 0; i < sz; i++)
        {
            scanf("%lld", &arr[i]);
        }
        long long int dp[sz][sz];
        for (int i = 1; i < sz; i++)
            dp[i][i] = 0;
        for (int j = 1; j <= n; j++)
        {
            for (int i = 1; i <= (n - j + 1); i++)
            {
                if ((i + j - 1) == i)
                    dp[i][+j - 1] = 0;
                else
                {

                    dp[i][i + j - 1] = 9223372036854775807;
                    for (int k = i; k < (i + j - 1); k++)
                    {
                        long long int cost = dp[i][k] + dp[k + 1][i + j - 1] + arr[i - 1] * arr[k] * arr[i + j - 1];
                        if (cost < dp[i][i + j - 1])
                            dp[i][i + j - 1] = cost;
                    }
                }
            }
        }
        printf("%lld", dp[1][n]);
    }
    return 0;
}