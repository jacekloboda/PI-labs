#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAB_LEN 100000
#define DATA_FLOOR 0
#define DATA_CEIL 10

int compare_int(const void *a, const void *b)
{
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    return (int_a > int_b) - (int_a < int_b);
}

void generate_data(int *data1, int *data2)
{

    for(int i=0; i<TAB_LEN; i++) 
    {
        int value = rand() % (DATA_CEIL-DATA_FLOOR) + DATA_FLOOR;

        *(data1+i) = value;
        *(data2+i) = value;
    }

    return;
}

void print_tab(int *data)
{
    printf("Printing tab: ");

    for(int i=0; i<TAB_LEN; i++)
    {
        printf("%d ", *(data+i));
    }
    printf("\n");

    return;
}

void compare_time(int *data)
{ 
    printf("Before sorting: \n");
    print_tab(data);

    qsort(data, TAB_LEN, sizeof(int), compare_int);
    print_tab(data);

}

int *search(int *data, int *value)
{
    int *ptr = bsearch(value, data, TAB_LEN, sizeof(int), compare_int);
    return ptr;
}

void bouble_sort(int *data)
{
    int n = TAB_LEN;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-1; j++)
        {
            if(compare_int(data+j, data+j+1)>0)
            {
                int tmp = *(data+j);
                *(data+j) = *(data+j+1);
                *(data+j+1) = tmp;
            }
        }
    }

    return;
}

int *bin_search(int *key, int *data)
{
    int l = 0, r = TAB_LEN-1, mid, last_seen;
    while(l<r)
    {
        mid = l+(r-l)/2;
        int compare_res = (compare_int(data+mid, key));
        if(compare_res==0)
        {
            last_seen = mid;
            r = mid-1;
        }
        else if(compare_res>0)
        {
            r = mid-1;
        }
        else
        {
            l = mid+1;
        }
    }
    if(*(data+mid)!=*(key))
    {
        return NULL;
    } 
    return (int *)data+mid;
}

int cw1(void)
{
    int *data1 = malloc(TAB_LEN*sizeof(int));
    int *data2 = malloc(TAB_LEN * sizeof(int));

    if(data1==NULL || data2==NULL)
    {
        perror("Malloc error\n");
        return 1;
    }

    generate_data(data1, data2);
    //print_tab(data1);
    
    clock_t start = clock();
    bouble_sort(data2);
    clock_t stop = clock();
    double run_time = ((double)stop - (double)start)/CLOCKS_PER_SEC;
    printf("bouble sort time: %lf\n", run_time);
    //print_tab(data2);
    
    
    int rand_val = rand() % (DATA_CEIL-DATA_FLOOR) + DATA_FLOOR;

    printf("rand_val: %d\n", rand_val);
    start = clock();
    int *ptr = bin_search(&rand_val, data2);
    stop = clock();
    run_time = ((double)stop - (double)start)/CLOCKS_PER_SEC;
    printf("bin_search time: %lf\n", run_time);
    if(ptr==NULL)
    {
        printf("cant find value\n");
    }
    else
    {
        printf("value fund on %li index\n", ptr-data2);
    }


    free(data1);
    free(data2);
    return 0;
}


int main(void)
{
    srand(time(NULL));
    
    cw1();

    return 0;
} 
