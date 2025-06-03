#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAB_LEN 1000000
#define DATA_FLOOR 0
#define DATA_CEIL 100

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
    qsort(data2, TAB_LEN, sizeof(int), compare_int);
    clock_t stop = clock();
    double run_time = ((double)stop - (double)start)/CLOCKS_PER_SEC;
    printf("qsort time: %lf\n", run_time);
    //print_tab(data2);
    
    
    int rand_val = rand() % (DATA_CEIL-DATA_FLOOR) + DATA_FLOOR;

    printf("rand_val: %d\n", rand_val);
    start = clock();
    int *ptr = bsearch(&rand_val, data2, TAB_LEN, sizeof(int), compare_int);
    stop = clock();
    run_time = ((double)stop - (double)start)/CLOCKS_PER_SEC;
    printf("sorted bsearch time: %lf\n", run_time);
    if(ptr==NULL)
    {
        printf("cant find value\n");
    }
    else
    {
        printf("value fund on %li index\n", ptr-data2);
    }

    start = clock();
    ptr = bsearch(&rand_val, data1, TAB_LEN, sizeof(int), compare_int);
    stop = clock();
    run_time = ((double)stop - (double)start)/CLOCKS_PER_SEC;
    printf("not sorted bsearch time: %lf\n", run_time);
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
