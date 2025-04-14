#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LEN 10
#define MAX_PLAYER_NUM 4
#define MAX_WORD_NUM 20
#define MAX_WORD_LEN 10

void enter_player_num(int *num)
{
    printf("Ender number of players(1-%d): ", MAX_PLAYER_NUM);
    scanf("%d", num); 
    while(getchar() != '\n');

    if( *num < 1 || MAX_PLAYER_NUM < *num )
    {
        printf("Wrong fromat try again\n");
        enter_player_num(num);
    }

    return;
}

void enter_player_name(char **names, int *player_num)
{
    for(int i=0; i<*player_num; i++)
    {
        printf("Enter player %d name: ", i+1);
        scanf("%s", *(names+i));
        while(getchar() != '\n');
    }

    return;
}

void enter_char(char *name, char *ch)
{
    printf("%s's turn, Enter Letter: ", name);
    scanf("%c", ch);
    while(getchar() != '\n');

    if(!( ('a' <= *ch && *ch <= 'z') || ('A' <= *ch && *ch <= 'Z') ))
    {
        printf("Wrong format try again\n");
        enter_char(name, ch);
    }

    if( *ch > 'Z') // changing lowercase to uppercase
    {
        *ch -= 32;
    }
}

const char* generate_word(void)
{
    const char* words[20] = {
            "DOM",
            "KOT",
            "PIES",
            "STOL",
            "KRZESLO",
            "OKNO",
            "DRZWI",
            "LAMPKA",
            "KSIAZKA",
            "TELEFON",
            "ROWER",
            "AUTO",
            "PLAZA",
            "GORY",
            "MORZE",
            "SLONCE",
            "DESZCZ",
            "SNIEG",
            "WIOSNA",
            "LATO"
    };

    int ind = rand() % MAX_WORD_NUM;

    return words[ind];
}

void check_char(const char *word, int *word_len, int *shown_letters, char *ch, int *curr_player, int *score, int *shown_cnt)
{
    for(int i=0; i<*word_len; i++)
    {
        if(!*(shown_letters+i) && *(word+i) == *ch) 
        {
            *(score+*curr_player) += 1;
            *(shown_letters+i) = 1;     
            *shown_cnt += 1;
        }
    }

    return;
}

void print_UI(const char *word, int *word_len, int *shown_letters, int *player_num, char **names, int *score)
{
    for(int i=0; i<*word_len; i++)
    {
        char ch = (*(shown_letters+i) ? *(word+i) : '_');

        printf("%c", ch);
    }
    printf("\n");

    for(int i=0; i<*player_num; i++)
    {
        printf("%s: %d\n", *(names+i), *(score+i));
    }
    
    return;
}

void restart(const char **word, int *word_len, int *score, int *shown_letters, int *shown_cnt)
{
    *shown_cnt = 0;
    *word = generate_word();
    *word_len = strlen(*word);

    for(int i=0; i<MAX_WORD_LEN; i++)
    {
        *(shown_letters+i) = 0;
    }

    for(int i=0; i<MAX_PLAYER_NUM; i++)
    {
        *(score+i) = 0;
    }

    return;
}

void end_game(int *player_num, char **player_names, int *score)
{
    int *processed = malloc(MAX_PLAYER_NUM*sizeof(int));
    int processed_cnt = 0;
    
    for(int i=0; i<*player_num; i++)
    {
        *(processed+i) = 0;
    }

    int max_score = 0;

    printf("Score:\n");

    while(processed_cnt<*player_num)
    {
        max_score = 0;

        for(int i=0; i<*player_num; i++)
        {
            if(!*(processed+i) && *(score+i) > max_score)
            {
                max_score = *(score+i);
            }
        }

        for(int i=0; i<*player_num; i++)
        {
            if(*(score+i) == max_score)
            {
                printf("%d. %s\n", ++processed_cnt, *(player_names+i));
                *(processed+i) = 1;
                break;
            }
        }
    }
    


    free(processed);

    return;
}

void wheel_of_fortune(void)
{
    char **player_names = malloc(MAX_PLAYER_NUM * sizeof(char *)); // names od the players
    const char *word = malloc(MAX_WORD_LEN*sizeof(char)); // word for players to guess
    int player_num; // number of active players
    int word_len; // size of word
    int *score = malloc(MAX_PLAYER_NUM * sizeof(int)); // score of every player
    int *shown_letters = malloc(MAX_WORD_LEN * sizeof(int)); // keeping track on which letters were shown
    int shown_cnt = 0; //keeping track of number of shown letters
    int curr_player = 0; // player making move in round
    char ch; // character inputed by player

    if(!score)
    {
        perror("Memory Error");
        return;
    }

    for(int i=0; i<MAX_PLAYER_NUM; i++)
    {
    }

    if(!player_names)
    {
        perror("Memory Error");
        return;
    }

    for(int i=0; i<MAX_PLAYER_NUM; i++)
    {
        *(player_names+i) = malloc(MAX_NAME_LEN * sizeof(char));

        if(!*(player_names+i))
        {
            perror("Memory Error");
            return;
        }

        /**(score+i) = malloc(sizeof(int));
        if(!*(score+i))
        {
            perror("Memory Error");
            return;
        }*/
    }

    enter_player_num(&player_num);
    enter_player_name(player_names, &player_num);

    restart(&word, &word_len, score, shown_letters, &shown_cnt);

    printf("%s\n", word);

    while(shown_cnt < word_len)
    {
        printf("\n");

        print_UI(word, &word_len, shown_letters, &player_num, player_names, score);
        enter_char(*(player_names+curr_player), &ch);
        check_char(word, &word_len, shown_letters, &ch, &curr_player, score, &shown_cnt);

        curr_player = (curr_player+1) % player_num;
    }

    printf("\n%s\nCongratulations!\n", word);

    end_game(&player_num, player_names, score);


    for(int i=0; i<MAX_PLAYER_NUM; i++)
    {
        free(*(player_names+i));
        //free(*(score+i));
    }

    free(player_names);
    free(score);
    free(shown_letters);

    return;
}

int main(void)
{
    srand(time(NULL));

    wheel_of_fortune();
   
    /*
    char word[] = "WORD";

    printf("%lu\n", strlen(word));
    */    

    return 0;
}
