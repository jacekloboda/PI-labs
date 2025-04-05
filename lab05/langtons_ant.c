#include <complex.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

//board size
#define ROW 51
#define COL 51
//starting point of mouse
#define S_ROW 26
#define S_COL 26
//moves
#define M1 1 //move forward
#define M2 2 //turn right
#define M3 3 //turn left
#define M4 4 //move right
#define M5 5 //move left
#define M6 6 //move back
#define M7 7 //turn back
#define M8 8 //do nothing
//how many moves in symulation
#define MOVE 20

typedef enum
{
    UP, //0
    LEFT, //1
    DOWN, //2
    RIGHT, //3
    END, //4, for iterating
} direction;

typedef struct ant_stats
{
    int x;
    int y;
    direction dir;
} ant_stats;

void clear_screen(void)
{
    printf("\033[H\033[J");

    return;
}

void reset_ant(ant_stats *ant)
{
    ant->x = S_ROW;
    ant->y = S_COL;
    ant->dir = RIGHT;

    return;
}

void rotate_left(direction *dir)
{
    *dir = (*dir + 1) % END;

    return;
}

void rotate_right(direction *dir)
{
    *dir = (END + *dir - 1) % END;

    return;
}

void rotate_180(direction *dir)
{
    *dir = (*dir + 2) % END;

    return;
}

void move_forward(direction dir, ant_stats *ant)
{
    //              {UP, LEFT, DOWN, RIGHT}
    const int dir_x[4] = {-1, 0, 1, 0};
    const int dir_y[4] = {0, -1, 0, 1};

    ant->x = ( ant->x + dir_x[dir] + ROW ) % ROW;
    ant->y = ( ant->y + dir_y[dir] + COL ) % COL;

    return;
}

void tile_rotation(int *tile)
{

    int rotation[9] = {0,7,4,2,6,3,5,8,1};

    *tile = rotation[*tile];

    return;
}

void print_board(int **board, ant_stats ant)
{
    for(int j=0; j<COL; j++)
    {
        printf("- ");
    }
    printf("\n");

    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {

            if(i==ant.x && j==ant.y)
            {
                printf("0 ");
            }
            else
            {
                printf("%d ", *(*(board+i)+j));
            }
        }

        printf("\n");
    }
    
    for(int j=0; j<COL; j++)
    {
        printf("- ");
    }
    printf("\n");

    return;
}

void generate_board(int **board)
{
    for(int i=0; i<ROW; i++)
    {

        for(int j=0; j<COL; j++)
        {
            *(*(board+i)+j) = rand()%8 + 1;// random int from 1-8
        }
    }

    //*(*(board+S_ROW)+S_COL) = 0;//starting point of mouse is in the middle

    return;
}


void action(int **board, ant_stats *ant)
{

    int *tile_val = *(board+ant->x)+ant->y;
     
    const direction dir_tab[4] = {UP, LEFT, DOWN, RIGHT};
    
    int new_x = ant->x;
    int new_y = ant->y;
    direction ghost_dir = ant->dir; //used for movin sideways

    switch(*tile_val)
    {
        case M1:
            move_forward(ghost_dir, ant);
        break;

        case M2:
            rotate_right(&ant->dir);
        break;

        case M3: 
            rotate_left(&ant->dir);
        break;
            
        case M4: 
            rotate_right(&ghost_dir);
            move_forward(ghost_dir, ant);
        break;

        case M5:
            rotate_left(&ghost_dir);
            move_forward(ghost_dir, ant);
        break;

        case M6:
            rotate_180(&ghost_dir);
            move_forward(ghost_dir, ant);
        break;

        case M7:
            rotate_180(&ant->dir);
        break;

        default: break;
    }

    tile_rotation(tile_val);

    return;
}

void langton_ant(void)
{ 
    srand(time(NULL));

    int **tab = (int **)malloc(ROW * sizeof(int *));//allocating memory for pointers to rows
    if( tab == NULL )
    {
        perror("memory error\n");
        return;
    }

    for(int i=0; i<ROW; i++)//allocating memory for elements in tab
    {
        *(tab+i) = (int *)malloc(COL * sizeof(int));
        
        if( *(tab+i) == NULL )
        {
            perror("memory error\n");
            return;
        }
    }

    ant_stats ant_pos;
    reset_ant(&ant_pos);

    generate_board(tab);
    print_board(tab,ant_pos);


    int move_cnt = 0;
    while(move_cnt++<MOVE)
    {
        print_board(tab, ant_pos);
        sleep(1);
        action(tab, &ant_pos);
        clear_screen();
    }

    for(int i=0; i<ROW; i++)//freeing memory reserved for tab
    {
        free(*(tab+i));
    }

    free(tab);

    return;
}

int main(void)
{
    langton_ant();

    return 0;
}
