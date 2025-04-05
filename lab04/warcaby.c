#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

void restart_board(int board[10][10])
{
    
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
            {
                board[i][j]=0;                  
            }
    }

    for(int i=0; i<10; i++)
    {
        if(i%2==0)
        {
            board[1][i] = -1;
            board[7][i] = 1;
            board[9][i] = 1;
        }
        else
        {
            board[0][i] = -1;
            board[2][i] = -1;
            board[8][i] = 1;
        }
    }

}

void print_board(int board[10][10])
{
    char cord[11] = " ABCDEFGHIJ";

    for(int i=0; i<11; i++)
    {
        printf("%c ", cord[i]);
    }
    printf("\n");


    for(int i=0; i<10; i++)
    {
        if(i<9){printf("%d ",i+1);}
        else{printf("%d",i+1);}
                                
        for(int j=0; j<10; j++)
        {
            char tile = '#';
            if(board[i][j]==1){tile='O';}
            else if(board[i][j]==-1){tile='0';}

            printf("%c ",tile);
        }
        printf("\n");
    }
    return;
}

int is_legal(int board[10][10], int move[4], int player) //move array: {starting x, starting y, move x, move y}:
{   
    int disx = move[3]-move[1];//distance traversed in x axis
    int disy = move[2]-move[0];//distance traversed in y axis
            
    printf("%d %d %d %d\n", move[0], move[2], move[1], move[3]);
    printf("%d %d\n", disx, disy);
    if(abs(disx) != abs(disy)){printf("1\n"); return 0;}//checking if move is legal
    if(board[move[2]][move[3]]!=0){printf("2\n"); return 0;}//destined tile is occupied

    if(player!=board[move[0]][move[1]]){printf("3\n"); return 0;}//player trying to move not his piece

    if(player==1) //'O'
    {
        if(disy>=0){printf("4\n"); return 0;}//players cant move back
                                
    }
    if(player==-1) //'0'
    {
        if(disy<=0){printf("5\n"); return 0;}//players cant move back
    }


                
    if(disx>2){printf("6\n"); return 0;}//player can perform only one capture per move so moving not farther than 2 tiles
                                                                                                                                
    if(disx>1)//capturing or jumping over your piece
    {
        int midx = (move[0]+move[2])/2;
        int midy = (move[1]+move[3])/2;

        if(board[midx][midy]==0){return 0;}//cant jump over empty tile
        
        //now it its possible to jump and move must be legall

        if(board[midx][midy] != player)
        {
            board[midx][midy] = 0; //capturing a pice, why in is_legal function? idk
        }
    }

    return 1;
}
void action(int board[10][10], int *player)
{
    char move_ch[4]; //move array

    printf("Player %c enter move: ", (*player==1)?'O':'0');
    fflush(stdin);
    scanf("%c %c %c %c",&move_ch[0],&move_ch[1],&move_ch[2],&move_ch[3]);
    while(getchar() != '\n');//clearing bufor

    printf("\n");


    int move[4];
    move[0] = move_ch[0]-'1';
    move[1] = move_ch[1]-'A';
    move[2] = move_ch[2]-'1';
    move[3] = move_ch[3]-'A';
    printf("%d, %d, %d, %d\n",move[0], move[1], move[2], move[3]);
                
    if(!is_legal(board, move, *player))
    {
        printf("illegal move try again!\n");
        return;
    }

    //when move is legal

    board[move[0]][move[1]]=0;
    board[move[2]][move[3]]=*player;
 
    *player = (*player == 1) ? -1 : 1;//changing player before next turn

    return;
}

int main(void)
{
    int tab[10][10];
    
    restart_board(tab);

    int player=1;
    while(1)
    {
        
        print_board(tab);
        action(tab,&player);
    }

    return 0;
}
