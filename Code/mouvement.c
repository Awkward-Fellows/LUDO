#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "../Headers/mouvement.h"
#include "../Headers/plateau.h"
#include "../Headers/game.h"

int diceRoll(Gamemode gamemode)
{
    srand(time(NULL));
    int rNumber;
    switch (gamemode)
    {
    case NO_MERCY:
        rNumber = (rand() % 7);
        break;
    default:
        rNumber = (rand() % (MAX - MIN + 1)) + MIN;
        break;
    }
    return rNumber;
}

int sdiceRoll()
{
    srand(time(NULL));
    int rNumber = (rand() % 9);
    return rNumber;
}

void check_coordinate(struct joueur **player, int *actual, int *index, int *move)
{
    if (player[*actual][*index].x < 5 && player[*actual][*index].y == 8)
    {
        player[*actual][*index].x++;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].x == 5 && player[*actual][*index].y == 8)
    {
        player[*actual][*index].y++;
        player[*actual][*index].x++;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].x == 6 && (player[*actual][*index].y > 8 && player[*actual][*index].y != E))
    {
        player[*actual][*index].y++;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].y == E && player[*actual][*index].x != 8)
    {
        player[*actual][*index].x++;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].x == 8 && player[*actual][*index].y > 9)
    {
        player[*actual][*index].y--;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].x == 8 && player[*actual][*index].y == 9)
    {
        player[*actual][*index].x++;
        player[*actual][*index].y--;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].y == 8 && (player[*actual][*index].x > 8 && player[*actual][*index].x != E))
    {
        player[*actual][*index].x++;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].x == E && player[*actual][*index].y != 6)
    {
        player[*actual][*index].y--;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].y == 6 && player[*actual][*index].x > 9)
    {
        player[*actual][*index].x--;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].x == 9 && player[*actual][*index].y == 6)
    {
        player[*actual][*index].y--;
        player[*actual][*index].x--;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].x == 8 && (player[*actual][*index].y < 6 && player[*actual][*index].y != 0))
    {
        player[*actual][*index].y--;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].y == 0 && player[*actual][*index].x != 6)
    {
        player[*actual][*index].x--;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].x == 6 && player[*actual][*index].y < 5)
    {
        player[*actual][*index].y++;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].x == 6 && player[*actual][*index].y == 5)
    {
        player[*actual][*index].x--;
        player[*actual][*index].y++;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].y == E && player[*actual][*index].x != 8)
    {
        player[*actual][*index].x++;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].y == 6 && player[*actual][*index].x < 6 && player[*actual][*index].x != 0)
    {
        player[*actual][*index].x--;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else if (player[*actual][*index].x == 0 && player[*actual][*index].y != 8)
    {
        player[*actual][*index].y++;
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
}

void restart(char ***plateau, int ***matrice, struct joueur **player, int pi, int pj, int nb_player, int actual, int **gameState)
{

    while (player[pi][pj].x != player[pi][pj].bx || player[pi][pj].y != player[pi][pj].by)
    {
        if (player[pi][pj].mvt_count == 1)
        {
            player[pi][pj].x = player[pi][pj].bx;
            player[pi][pj].y = player[pi][pj].by;
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].mvt_count > 51)
        {
            if (player[pi][pj].bx < 6)
            {
                if (player[pi][pj].by < 6)
                {
                    player[pi][pj].y--;
                    player[pi][pj].mvt_count--;
                }
                else
                {
                    player[pi][pj].x--;
                    player[pi][pj].mvt_count--;
                }
            }
            else
            {
                if (player[pi][pj].by < 6)
                {
                    player[pi][pj].x++;
                    player[pi][pj].mvt_count--;
                }
                else
                {
                    player[pi][pj].y++;
                    player[pi][pj].mvt_count--;
                }
            }
        }
        else if (player[pi][pj].x == 0 && player[pi][pj].y != 6)
        {
            player[pi][pj].y--;
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].y == 6 && player[pi][pj].x <= 5)
        {
            if (player[pi][pj].x == 5)
            {
                player[pi][pj].y--;
            }
            player[pi][pj].x++;
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].x == 6 && player[pi][pj].y < 6)
        {
            if (player[pi][pj].y == 0)
            {
                player[pi][pj].x++;
            }
            else
            {
                player[pi][pj].y--;
            }
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].y == 0 && player[pi][pj].x != 8)
        {
            player[pi][pj].x++;
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].x == 8 && player[pi][pj].y <= 5)
        {
            if (player[pi][pj].y == 5)
            {
                player[pi][pj].x++;
            }
            player[pi][pj].y++;
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].y == 6 && player[pi][pj].x >= 9)
        {
            if (player[pi][pj].x == E)
            {
                player[pi][pj].y++;
            }
            else
            {
                player[pi][pj].x++;
            }
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].x == E && player[pi][pj].y != 8)
        {
            player[pi][pj].y++;
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].y == 8 && player[pi][pj].x >= 9)
        {
            if (player[pi][pj].x == 9)
            {
                player[pi][pj].y++;
            }
            player[pi][pj].x--;
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].x == 8 && player[pi][pj].y > 8)
        {
            if (player[pi][pj].y == E)
            {
                player[pi][pj].x--;
            }
            else
            {
                player[pi][pj].y++;
            }
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].y == E && player[pi][pj].x != 6)
        {
            player[pi][pj].x--;
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].x == 6 && player[pi][pj].y >= 9)
        {
            if (player[pi][pj].y == 9)
            {
                player[pi][pj].x--;
            }
            player[pi][pj].y--;
            player[pi][pj].mvt_count--;
        }
        else if (player[pi][pj].y == 8 && player[pi][pj].x <= 5)
        {
            player[pi][pj].x--;
            player[pi][pj].mvt_count--;
        }
        update_plateau(plateau, player, nb_player, gameState);
        update_matrice(matrice, *plateau);
        afficher(*plateau, TAILLE_X, TAILLE_Y, 0, player, actual, gameState, nb_player);
        usleep(100000);
    }
}

void last_straight_line(struct joueur **player, int *actual, int *index, int *move)
{
    if (player[*actual][*index].bx > 8)
    {
        if (player[*actual][*index].by < 6)
        {
            player[*actual][*index].x--;
        }
        else
        {
            player[*actual][*index].y--;
        }
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
    else
    {
        if (player[*actual][*index].by < 6)
        {
            player[*actual][*index].y++;
        }
        else
        {
            player[*actual][*index].x++;
        }
        (*move)--;
        player[*actual][*index].mvt_count++;
    }
}

void get_state(int ***gameState, struct joueur **player, int nb_player, int actual)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            (*gameState)[i][j] = 0;
        }
    }
    for (int j = 0; j < 4; j++)
    {
        for (int k = 0; k < nb_player; k++)
        {
            for (int l = 0; l < 4; l++)
            {
                if (player[actual][j].x == player[k][l].x && player[actual][j].y == player[k][l].y)
                {
                    (*gameState)[k][j]++;
                }
            }
        }
    }
}

void rollDice(struct joueur **p, int ind)
{
    if (p[ind]->color == 'R')
    {
        printf("" RED "Player %d: Roll the dice? \n", ind);
    }
    else if (p[ind]->color == 'B')
    {
        printf("" BLU "Player %d: Roll the dice? \n", ind);
    }
    else if (p[ind]->color == 'G')
    {
        printf("" GRN "Player %d: Roll the dice? \n", ind);
    }
    else if (p[ind]->color == 'Y')
    {
        printf("" YEL "Player %d: Roll the dice? \n", ind);
    }
}

void pressEnter(struct joueur **p, int ind)
{
    if (p[ind]->color == 'R')
    {
        printf("" RED "Appuyez sur Entrée: ");
    }
    else if (p[ind]->color == 'B')
    {
        printf("" BLU "Appuyez sur Entrée: ");
    }
    else if (p[ind]->color == 'G')
    {
        printf("" GRN "Appuyez sur Entrée: ");
    }
    else if (p[ind]->color == 'Y')
    {
        printf("" YEL "Appuyez sur Entrée: ");
    }
}

void choosePiece(struct joueur **player, int ind)
{
    if (player[ind]->color == 'R')
    {
        printf("" RED "Quelle piece voulez-vous deplacer: ");
    }
    else if (player[ind]->color == 'B')
    {
        printf("" BLU "Quelle piece voulez-vous deplacer: ");
    }
    else if (player[ind]->color == 'G')
    {
        printf("" GRN "Quelle piece voulez-vous deplacer: ");
    }
    else if (player[ind]->color == 'Y')
    {
        printf("" YEL "Quelle piece voulez-vous deplacer: ");
    }
}

void replace_case(char **plateau, struct joueur **player, int player_initx, int player_inity, int *actual, int *index, int nb_player)
{
    int j, ind;

    for (ind = 0; ind < nb_player; ind++)
    {
        for (j = 0; j < 4; j++)
        {
            if ((player[ind][j].x == player_initx && player[ind][j].y == player_inity) && (ind != *actual || j != *index))
            {
                plateau[player_initx][player_inity] = player[ind][j].symbole;
                break;
            }
        }
        if (j != 4)
        {
            break;
        }
    }

    if (ind == nb_player)
    {
        if ((player_initx == 13 && player_inity == 6) || (player_initx == 6 && player_inity == 1) || (player_initx == 1 && player_inity == 8) || (player_initx == 12 && player_inity == 8))
        {
            plateau[player_initx][player_inity] = 'S';
        }
        else if ((player_initx == 8 && player_inity == 2) || (player_initx == 2 && player_inity == 6) || (player_initx == 6 && player_inity == C) || (player_initx == 8 && player_inity == D))
        {
            plateau[player_initx][player_inity] = 'U';
        }
        else
        {
            plateau[player_initx][player_inity] = ' ';
        }
    }

    plateau[player[*actual][*index].x][player[*actual][*index].y] = player[*actual][*index].symbole;
}

void check_collision(char **pplateau, int **pmatrice, struct joueur **pplayer, int *pactual, int *pindex, int pnb_player, int *pscore, int **pgameState, bool *pdecrement)
{
    int bi, bj;
    int collided = 0;

    if (pmatrice[pplayer[*pactual][*pindex].x][pplayer[*pactual][*pindex].y] == 1)
    {

        for (int i = 0; i < pnb_player; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (pplayer[i][j].x == pplayer[*pactual][*pindex].x && pplayer[i][j].y == pplayer[*pactual][*pindex].y && pplayer[i][j].mvt_count != 57)
                {
                    if (i == *pactual)
                    {
                        collided += 2;
                    }
                    else
                    {
                        collided++;
                        bi = i;
                        bj = j;
                    }
                }
            }
        }
        if (collided == 3)
        {
            pscore[*pactual]++;
            restart(&pplateau, &pmatrice, pplayer, bi, bj, pnb_player, *pactual, pgameState);
            *pdecrement = true;
        }
    }
}

void first_move(struct joueur **pplayer, int *pactual)
{
    int ind;
    for (ind = 0; ind < 4; ind++)
    {
        if (pplayer[*pactual][ind].won == false)
        {
            if (pplayer[*pactual][ind].x < 6)
            {
                if (pplayer[*pactual][ind].y < 6)
                {
                    pplayer[*pactual][ind].x = 6;
                    pplayer[*pactual][ind].y = 1;
                    pplayer[*pactual][ind].mvt_count++;
                }
                else
                {
                    pplayer[*pactual][ind].x = 1;
                    pplayer[*pactual][ind].y = 8;
                    pplayer[*pactual][ind].mvt_count++;
                    break;
                }
            }
            else
            {
                if (pplayer[*pactual][ind].y < 6)
                {
                    pplayer[*pactual][ind].x = D;
                    pplayer[*pactual][ind].y = 6;
                    pplayer[*pactual][ind].mvt_count++;
                }
                else
                {
                    pplayer[*pactual][ind].x = 8;
                    pplayer[*pactual][ind].y = D;
                    pplayer[*pactual][ind].mvt_count++;
                }
            }
            break;
        }
    }
}

void leaveBase(struct joueur **player, int *actual, int *index, int *player_initx, int *player_inity)
{
    if (player[*actual][*index].x < 6)
    {
        if (player[*actual][*index].y < 6)
        {
            *player_initx = player[*actual][*index].x;
            *player_inity = player[*actual][*index].y;
            player[*actual][*index].x = 6;
            player[*actual][*index].y = 1;
            player[*actual][*index].mvt_count++;
        }
        else
        {
            *player_initx = player[*actual][*index].x;
            *player_inity = player[*actual][*index].y;
            player[*actual][*index].x = 1;
            player[*actual][*index].y = 8;
            player[*actual][*index].mvt_count++;
        }
    }
    else
    {
        if (player[*actual][*index].y < 6)
        {
            *player_initx = player[*actual][*index].x;
            *player_inity = player[*actual][*index].y;
            player[*actual][*index].x = D;
            player[*actual][*index].y = 6;
            player[*actual][*index].mvt_count++;
        }
        else
        {
            *player_initx = player[*actual][*index].x;
            *player_inity = player[*actual][*index].y;
            player[*actual][*index].x = 8;
            player[*actual][*index].y = D;
            player[*actual][*index].mvt_count++;
        }
    }
}

void clean_buffer()
{
    char *buffer = malloc(256 * sizeof(char));
    fgets(buffer, 255, stdin);
    free(buffer);
}

void end_turn(int *pmove, bool *in_move)
{
    *pmove = 0;
    *in_move = false;
}

char **Move(char **plateau, int **matrice, struct joueur **player, int *actual, int *move, bool *in_mvt, int *index, int nb_player, int dice, bool *decrement, int **gameState, bool *partie_terminee, int *classement, int *ind_class, int *score, Gamemode gamemode)
{
    int ind, j, player_initx, player_inity;
    int input, leftmove, bindex, inert;
    int pawn_out, player_win = 0;
    int player_left = nb_player;
    int dice_number[9] = {6, 1, 2, 6, 3, 6, 4, 5, 6};
    bool rinput = false;

    if (*move == dice)
    {
        *decrement = false;
        pawn_out = 0;
        inert = 0;
        for (ind = 0; ind < 4; ind++)
        {
            if (player[*actual][ind].won == true)
            {
                player_win++;
            }
            if (player[*actual][ind].mvt_count != 0 && player[*actual][ind].won == false)
            {
                pawn_out++;

                if (NBCASE - player[*actual][ind].mvt_count < dice)
                {
                    inert++;
                }
            }
        }
        switch (player_win)
        {
        case 4:
            goto skip_turn;
            break;
        case 3:
            for (int i = 0; i < 4; i++)
            {
                if (player[*actual][i].won == false)
                {
                    *index = i;
                    if (NBCASE - player[*actual][*index].mvt_count < dice)
                    {
                        printf("Dice: %d\n", dice);
                        pressEnter(player, *actual);
                        getchar();
                        goto skip_turn;
                    }
                }
            }
            break;
        }
        if (inert != 0)
        {

            if (inert == pawn_out)
            {
                if (player_win + pawn_out == 4)
                {
                    printf("Dice: %d\n", dice);
                    pressEnter(player, *actual);
                    getchar();
                    goto skip_turn;
                }
                else
                {
                    if (dice == 6)
                    {
                        printf("Dice: %d\n", dice);
                        goto choose_piece;
                    }
                    else
                    {
                        pawn_out = 0;
                    }
                }
            }
        }
    }
    if (pawn_out == 0 && *in_mvt == false)
    {
        *move = dice_number[sdiceRoll()];
        dice = *move;
        printf("Dice: %d\n", *move);
        *index = 0;
        player_initx = player[*actual][*index].x;
        player_inity = player[*actual][*index].y;
        if (*move == 6)
        {
            *decrement = true;
            *in_mvt = true;
            switch (gamemode)
            {
            case NO_MERCY:
                goto choose_piece;
            default:
                pressEnter(player, *actual);
                getchar();
                break;
            }
            first_move(player, actual);
            end_turn(move, in_mvt);
        }
        else
        {
            pressEnter(player, *actual);
            getchar();
            end_turn(move, in_mvt);
        }
    }
    else
    {
        printf("Dice: %d\n", dice);
        if (*move == 6 && player_win != 3)
        {
        choose_piece:
            *decrement = true;
            display_pos(&player, actual, nb_player, &plateau, dice, gameState);
            choosePiece(player, *actual);
            do
            {
                input = scanf("%d", index);
                getchar();

                if (input == 0 || *index < 0 || *index >= 4 || (player[*actual][*index].mvt_count == 0 && *move != 6))
                {
                    display_pos(&player, actual, nb_player, &plateau, dice, gameState);
                    printf("Index invalide, rééssayez: ");
                    if (input == 0)
                    {
                        clean_buffer();
                    }
                }
            } while (input == 0 || *index < 0 || *index >= 4 || (player[*actual][*index].mvt_count == 0 && *move != 6));

            *in_mvt = true;

            for (int k = 0; k < 4; k++)
            {
                player[*actual][k].symbole = player[*actual][k].back_symb;
            }

            update_plateau(&plateau, player, nb_player, gameState);

            printf("\033c");

            afficher(plateau, TAILLE_X, TAILLE_Y, *move, player, *actual, gameState, nb_player);

            if (player[*actual][*index].mvt_count != 0)
            {
                goto move_piece;
            }

            else
            {
            leave_base:
                leaveBase(player, actual, index, &player_initx, &player_inity);

                end_turn(move, in_mvt);
            }
        }
        else
        {
            if (*in_mvt == false)
            {
                if (pawn_out == 1)
                {
                    pressEnter(player, *actual);
                    getchar();

                    for (int ind = 0; ind < 4; ind++)
                    {
                        if (player[*actual][ind].mvt_count != 0 && player[*actual][ind].won == false)
                        {
                            *index = ind;
                            break;
                        }
                    }
                }
                else
                {
                    display_pos(&player, actual, nb_player, &plateau, dice, gameState);
                    choosePiece(player, *actual);
                    do
                    {
                        input = scanf("%d", index);
                        if (rinput == true && *index != bindex && (input == 0 || *index < 0 || *index >= 4 || ((player[*actual][*index].mvt_count == 0 && *move != 6) || rinput == true)))
                        {
                            rinput = false;
                            if (dice == 6 && player[*actual][*index].mvt_count == 0)
                            {
                                goto leave_base;
                            }
                            else
                            {
                                goto move_piece;
                            }
                        }
                        getchar();
                        if (input == 0 || *index < 0 || *index >= 4 || ((player[*actual][*index].mvt_count == 0 && *move != 6) || rinput == true))
                        {
                        re_input:
                            printf("Index invalide, rééssayez: ");
                            if (input == 0)
                            {
                                clean_buffer();
                            }
                        }
                    } while (input == 0 || *index < 0 || *index >= 4 || (player[*actual][*index].mvt_count == 0 && *move != 6) || rinput == true);

                    for (int k = 0; k < 4; k++)
                    {
                        player[*actual][k].symbole = player[*actual][k].back_symb;
                    }
                    update_plateau(&plateau, player, nb_player, gameState);
                    printf("\033c");
                    afficher(plateau, TAILLE_X, TAILLE_Y, *move, player, *actual, gameState, nb_player);
                }
            }
        move_piece:
            *in_mvt = true;
            player_initx = player[*actual][*index].x;
            player_inity = player[*actual][*index].y;
            leftmove = NBCASE - player[*actual][*index].mvt_count;
            if (player[*actual][*index].mvt_count > 50)
            {
                if (leftmove >= *move)
                {
                    last_straight_line(player, actual, index, move);
                }
                else
                {
                    if (pawn_out == 1 && dice != 6)
                    {
                        goto skip_turn;
                    }
                    else
                    {
                        rinput = true;
                        bindex = *index;
                        goto re_input;
                    }
                }
            }
            else
            {
                check_coordinate(player, actual, index, move);
            }
        }
    }
    replace_case(plateau, player, player_initx, player_inity, actual, index, nb_player);
    if (*move == 0)
    {
        if (dice == 6)
        {
            *decrement = true;
        }
        check_collision(plateau, matrice, player, actual, index, nb_player, score, gameState, decrement);
        if (gamemode == NO_MERCY)
        {
            player = verify_safety(matrice, player, *actual, *index);
            if (player[*actual][*index].is_unsafe == true)
            {
                plateau = summon(plateau, player, *actual, *index, nb_player);
            }
        }
        update_plateau(&plateau, player, nb_player, gameState);
        update_matrice(&matrice, plateau);
    }

    if (player[*actual][*index].mvt_count == NBCASE && player[*actual][*index].won != true)
    {
        player[*actual][*index].won = true;
        score[*actual] += 2;
        *decrement = true;
    }

    for (int i = 0; i < nb_player; i++)
    {
        int winner = 0;
        for (int j = 0; j < 4; j++)
        {
            if (player[i][j].won == true)
            {
                winner++;
            }
        }
        if (winner == 4)
        {
            class_player(classement, ind_class, nb_player, i);
            player_left--;
        }
        if (player_left == 1)
        {
            for (int k = 0; k < nb_player; k++)
            {
                class_player(classement, ind_class, nb_player, k);
            }
            *partie_terminee = true;
        }
    }
    if (*move == 0)
    {
    skip_turn:
        end_turn(move, in_mvt);
    }
    return plateau;
}

char **summon(char **plateau, struct joueur **player, int actual, int index, int nb_player)
{
    int ind = 0, random_index;
    struct Player_out *player_out = malloc((nb_player * 4) * sizeof(Player_out));
    for (int i = 0; i < nb_player; i++)
    {
        if (i != actual)
        {
            for (int j = 0; j < 4; j++)
            {
                if (player[i][j].mvt_count != 0 && player[i][j].mvt_count != 57 && player[i][j].is_safe == false)
                {
                    player_out[ind].a = i;
                    player_out[ind].i = j;
                    ind++;
                }
            }
        }
    }
    if (ind != 0 && player[actual][index].is_unsafe == true)
    {
        random_index = get_random_player(ind);
        switch (player[actual][index].x)
        {
        case C:
            player[player_out[random_index].a][player_out[random_index].i].x = 8;
            player[player_out[random_index].a][player_out[random_index].i].y = 9;
            break;
        case 8:
            if (player[actual][index].y == 2)
            {
                player[player_out[random_index].a][player_out[random_index].i].x = 9;
                player[player_out[random_index].a][player_out[random_index].i].y = 6;
            }
            break;
        case 6:
            if (player[actual][index].y == C)
            {
                player[player_out[random_index].a][player_out[random_index].i].x = 5;
                player[player_out[random_index].a][player_out[random_index].i].y = 8;
            }
            break;
        case 2:
            player[player_out[random_index].a][player_out[random_index].i].x = 6;
            player[player_out[random_index].a][player_out[random_index].i].y = 5;
            break;
        }
        int pa = player_out[random_index].a;
        int pi = player_out[random_index].i;
        player = get_mvt_count(player, nb_player);
        plateau[player[pa][pi].x][player[pa][pi].y] = player[pa][pi].symbole;
    }
    return plateau;
}

int get_random_player(int nb_player_out)
{
    int random_index = rand() % nb_player_out;
    return random_index;
}

struct joueur **verify_safety(int **matrice, struct joueur **player, int actual, int index)
{
    switch (matrice[player[actual][index].x][player[actual][index].y])
    {
    case 2:
        player[actual][index].is_safe = true;
        player[actual][index].is_unsafe = false;
        break;
    case 3:
        player[actual][index].is_safe = false;
        player[actual][index].is_unsafe = true;
        break;
    default:
        player[actual][index].is_safe = false;
        player[actual][index].is_unsafe = false;
        break;
    }
    return player;
}