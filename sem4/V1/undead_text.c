#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define HEIGHT 4 //number of lines
#define WIDTH 4 //number of columns

/**
 * brief function to print the number of end spaces we choose and if is too big to add 2*width end spaces for each lines
 * param n number of end spaces
**/
void print_end_spaces(int n){
    if (WIDTH <= 4){
        for (int i = 0; i < n; i++){
            printf(" ");
        }
    }
    else {
        for (int j = 0; j < (2*WIDTH + n); j++){
            printf(" ");
        }
    }
}

/**
 * brief to print he game board
 * param labels[NB_DIR] labels of the game
 * param board the board of the game we want to print
 * param ghosts number of ghosts in the game
 * param vampires number of vampires in the game
 * param zombies number of zombies in the game
 * param spirits number of spirits in the game
**/
void print_game(int* labels[NB_DIR], content* board, int ghosts, int vampires, int zombies, int spirits){
    for (int i = 0; i < 4 ; i++){
        assert(labels[i]);
    }
    assert(board);
    printf("| Z:%d V:%d G:%d S:%d ", zombies, vampires, ghosts, spirits);
    print_end_spaces(0);                                                    //if width is too big
    printf("|\n|                 ");
    print_end_spaces(0);
    printf("|\n|     ");
    for (int j = 0; j < WIDTH; j++){
        printf("%d ", *(labels[0] + j));                                    //prints the horizontal North labels
    }
    print_end_spaces(12 - (2*WIDTH));                                       //prints the correct number of spaces after horizontal labels
    printf("|\n|                 ");
    print_end_spaces(0);
    printf("|\n|  %d  ", *(labels[3] + (HEIGHT-1)));                        //prints the first vertical West label

    int r_pos = HEIGHT - 1;                                                 //relative position of the first East label to print in the labels array
    for (int i = (HEIGHT*WIDTH) - WIDTH; i >= 0 ; i = i - WIDTH){           //beginning at (0, HEIGHT-1) and finishing at (0,0)
        for (int j = 0; j < WIDTH; j++){                                    //running through each lines
            switch (board[i + j]){
            case MIRROR:
                printf("/ ");
                break;
            case ANTIMIRROR:
                printf("\\ ");
                break;
            case VMIRROR:
                printf("| ");
                break;
            case HMIRROR:
                printf("- ");
                break;
            case VAMPIRE:
                printf("V ");
                break;
            case GHOST:
                printf("G ");
                break;
            case ZOMBIE:
                printf("Z ");
                break;
            case SPIRIT:
                printf("S ");
                break;
            default:
                printf("  ");
                break;
            }
        }
        printf(" %d ", *(labels[2] + r_pos));                           //prints the vertical East labels
        print_end_spaces(9 - (2*WIDTH));                                //prints the correct number of spaces after vertical East labels
        if (i != 0){                                                    //after the last East label, there is no more West label to print
            printf("|\n|  %d  ", *(labels[3] + (r_pos - 1)));           //prints the vertical West labels
            r_pos = r_pos - 1;
        }
    }

    printf("|\n|                 ");
    print_end_spaces(0);
    printf("|\n|     ");
    for (int k = 0; k < WIDTH; k++){
        printf("%d ", *(labels[1] + k));                                //prints the horizontal South labels
    }
    print_end_spaces(12 - (2*WIDTH));
    printf("|\n|                 ");
    print_end_spaces(0);
    printf("|\n");
}

int main (){
    //it is necessary to set the parameters to create the game
    int* labels[NB_DIR];
    int coordinate[(2*HEIGHT) + (2*WIDTH)] = {0,3,3,0,0,3,2,3,0,0,3,2,0,2,3,3};
    int* labelsN = coordinate;
    int* labelsS = coordinate + WIDTH;
    int* labelsE = coordinate + (2*WIDTH);
    int* labelsW = coordinate + (2*WIDTH) + HEIGHT;
    labels[0] = labelsN;
    labels[1] = labelsS;
    labels[2] = labelsE;
    labels[3] = labelsW;
    for (int i = 0; i < 4 ; i++){
        assert(labels[i]);
    }
    content* board = (content*) malloc((HEIGHT*WIDTH)*sizeof(content));
    assert(board);
    board[0] = ANTIMIRROR;
    board[1] = EMPTY;
    board[2] = EMPTY;
    board[3] = ANTIMIRROR;
    board[4] = EMPTY;
    board[5] = EMPTY;
    board[6] = ANTIMIRROR;
    board[7] = MIRROR;
    board[8] = ANTIMIRROR;
    board[9] = EMPTY;
    board[10] = EMPTY;
    board[11] = EMPTY;
    board[12] = ANTIMIRROR;
    board[13] = EMPTY;
    board[14] = EMPTY;
    board[15] = MIRROR;
    int ghosts = 2;
    int vampires = 2;
    int zombies = 5;
    int spirits = 0;
    game g = setup_new_game_ext(WIDTH, HEIGHT, labels, board, ghosts, vampires, zombies, spirits);
    assert(g);

    char* s_game_move = (char*) malloc(1001*sizeof(char));                                          //to store the next game move
    assert(s_game_move);
    char* s_cutting = NULL;                                                                         //to store the game move elements by elements
    long column = -1;                                                                               //coordinates of the next move
    long line = -1;
    content monster = EMPTY;                                                                        //monster to put in the next move

    while (!(is_game_over(g))){
        //this prints the game board and ask which monster to place
        print_game(labels, board, ghosts, vampires, zombies, spirits);
        printf("|     start       ");
        print_end_spaces(0);
        printf("|\n");

        while ((column < 0 || column >= WIDTH) || (line < 0 || line >= HEIGHT) || (monster != GHOST && monster != VAMPIRE && monster != ZOMBIE && monster != SPIRIT) || (s_cutting != NULL)){
            column = -1;
            line = -1;
            monster = EMPTY;
            fgets(s_game_move, 1000, stdin);
            s_cutting = strtok(s_game_move, " ");
            if (s_cutting != NULL){
                column = strtol(s_cutting, NULL, 10);
                if (s_cutting[0] < '0' || s_cutting[0] > '9'){                                       //if the column enterred is not a number, asks again
                    column = -1;
                }
                s_cutting = strtok(NULL, " ");
                if (s_cutting != NULL){
                    line = strtol(s_cutting, NULL, 10);
                    if (s_cutting[0] < '0' || s_cutting[0] > '9'){
                        line = -1;
                    }
                    s_cutting = strtok(NULL, " ");
                    if ((column >= 0 && line >= 0) && (get_content(g,column,line) == MIRROR || get_content(g,column,line) == ANTIMIRROR || get_content(g,column,line) == VMIRROR || get_content(g,column,line) == HMIRROR)){
                        s_cutting = NULL;                                                           //if the user try to place a mirror, asks again
                    }
                    if (s_cutting != NULL){
                        if (strcmp(s_cutting, "G\n") == 0){
                            monster = GHOST;
                        }
                        else {
                            if (strcmp(s_cutting, "V\n") == 0){
                                monster = VAMPIRE;
                            }
                            else {
                                if (strcmp(s_cutting, "Z\n") == 0){
                                    monster = ZOMBIE;
                                }
                                else {
                                    if (strcmp(s_cutting, "S\n") == 0){
                                        monster = SPIRIT;
                                    }
                                    else {                                                          //if the monster enterred is not 'G','V','Z' or 'S', asks again
                                        monster = EMPTY;
                                    }
                                }
                            }
                        }
                        s_cutting = strtok(NULL, " ");
                    }
                }
            }
        }
        board[column + (WIDTH*line)] = monster;                                                     //board is an one dimensioned- array
        add_monster(g, monster, column, line);
        column = -1;                                                                                //it is necessary to reinitialize for the next move
        line = -1;
        monster = EMPTY;
    }

    //to print solution and to free the game
    print_game(labels, board, ghosts, vampires, zombies, spirits);
    printf("|     solution    ");
    print_end_spaces(0);
    printf("|\n");
    free(s_game_move);
    free(board);
    delete_game(g);
    return EXIT_SUCCESS;
}
