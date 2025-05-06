#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT 100
#define MAX_MATRIX_SIZE 100

typedef struct
{
    int row;
    int col;
    int **data;
}Matrix;

void print_matrix(Matrix *matrix)
{
    if(matrix == NULL || matrix->data == NULL)
    {
        printf("Print error\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<matrix->row; i++)
    {
        for(int j=0; j<matrix->col; j++)
        {
            printf("%d ", *(*(matrix->data+i)+j));
        }

        printf("\n");
    }

    return;
}

Matrix create_matrix()
{
    Matrix matrix;
    char *line = malloc(MAX_INPUT*sizeof(char));
    int row, col;

    printf("Enter matrix size( row col):");
    
    fgets(line, MAX_INPUT, stdin);
    sscanf(line, "%d %d", &row, &col);

    matrix.row = row;
    matrix.col = col;
    
    matrix.data = (int **)malloc(row*sizeof(int *));
    if(matrix.data == NULL)
    {
        printf("Memory error\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<row; i++)
    {
        *(matrix.data+i) = (int *)malloc(col*sizeof(int));
        if(*(matrix.data+i)==NULL)
        {
            printf("Memory error\n");
            exit(EXIT_FAILURE);
        }
    }

    for(int i=0; i<row; i++)
    {

        printf("Podaj %d liczb dla wiersza %d (oddzielone spacjami): ", col, i+1);
        fgets(line, MAX_INPUT, stdin);
        
        char *token = strtok(line, " ");
        for(int j = 0; j < col && token != NULL; j++) 
        {
            matrix.data[i][j] = atoi(token);
            token = strtok(NULL, " ");
        }
    }
    free(line);

    return matrix;
}

void free_data(Matrix *matrix)
{
    if(matrix == NULL || matrix->data == NULL) return;

    for( int i=0; i<matrix->row; i++)
    {
        free(*(matrix->data+i));
    }
    free(matrix->data);

    matrix->data = NULL;
    matrix->row = 0;
    matrix->col = 0;

    return;
}


void set(Matrix *matrix, int val, int i, int j)
{
    if(matrix == NULL || matrix->data == NULL || i < 0 || i >= matrix->row || j < 0 || j >= matrix->col)
    {
        printf("index out of bounds\n");
        return;
    }

    *(*(matrix->data+i)+j) = val;
    
    return;
}   

int get(Matrix *matrix, int i, int j)
{
    if(matrix == NULL || matrix->data == NULL || i < 0 || i >= matrix->row || j < 0 || j >= matrix->col)
    {
        printf("index out of bounds\n");
        return -1;
    }
    
    return *(*(matrix->data+i)+j);
}

void prodmat()
{
    Matrix m1, m2, res;

    m1 = create_matrix();
    m2 = create_matrix();
    res.row = m1.row;
    res.col = m2.col;

    res.data = (int **)malloc((res.row*sizeof(int *)));

    for(int i=0; i<res.row; i++)
    {
        *(res.data+i) = (int *)malloc(res.col * sizeof(int));

        for(int j=0; j<res.col; j++)
        {
            *(*(res.data+i)+j) = 0;

            for(int k=0; k<m1.col; k++)
            {
                *(*(res.data+i)+j) += *(*(m1.data+i)+k) * *(*(m2.data+k)+j);
            }
        } 
    }

    printf("The result of multiplication is:\n");

    print_matrix(&res);

    free_data(&m1);
    free_data(&m2);
    free_data(&res);

    return;
}

int main(void)
{
    prodmat();

    return 0;
}
