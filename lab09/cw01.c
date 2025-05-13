#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>

int compare_int(const void *a, const void *b)
{
    return(*(int *)a - *(int *)b);
}

int suma(int n, ...)
{
    va_list args;
    va_start(args, n);
    int res = 0;
    
    for(int i=0; i<n; i++)
    {
        int num = va_arg(args, int);
        res += num;
    }

    va_end(args);
    return res;
}

float avg(int n, ...)
{
    float res = 0;
    va_list args;
    va_start (args, n);

    for(int i=0; i<n; i++)
    {
        int num = va_arg(args, int);
        res += num;
    }
    va_end(args);

    return res/n;
}

float median(int n, ...)
{
    int *tab = (int *)malloc(n*sizeof(int));
    va_list args;
    va_start(args, n);

    for(int i=0; i<n; i++)
    {
        int num = va_arg(args, int);
        *(tab+i) = num;
    }
    va_end(args);

    qsort(tab, n, sizeof(int), compare_int);

    float ans;

    if(n%2==1)
    {
        ans = *(tab+n/2);
    }
    else
    {
        ans = *(tab+(n/2-1)) + *(tab+(n/2));
        ans /= 2;
    
    }
    free(tab);
    return ans;
}

int max(int n, ...)
{
    int res = -1e9;
    va_list args;
    va_start(args, n);

    for(int i=0; i<n; i++)
    {
        int num = va_arg(args, int);
        if(res<num){res=num;}
    }
    va_end(args);

    return res;
}

int min(int n, ...)
{
    int res = 1e9;
    va_list args;
    va_start(args, n);

    for(int i=0; i<n; i++)
    {
        int num = va_arg(args, int);
        if(num<res){res=num;}
    }
    va_end(args);

    return res;
}

int main(void)
{
    printf("sum: %d\n", suma(4, 1,2,3,4));
    printf("avg: %.2f\n", avg(4,1,2,3,4));
    printf("median: %.2f\n", median(4, 1,2,3,4));
    printf("max: %d\n", max(4,1,2,3,4));
    printf("min: %d\n", min(4,1,2,3,4));


    return 0;
}
