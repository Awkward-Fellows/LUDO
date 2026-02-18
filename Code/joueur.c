#include "../Headers/joueur.h"
#include "../Headers/mouvement.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void init_player(struct joueur *player, int init_x, int init_y, char symb, char couleur)
{
    player[0].x = init_x;
    player[0].y = init_y;
    player[1].x = player[0].x + 3;
    player[1].y = player[0].y;
    player[2].x = player[0].x;
    player[2].y = player[0].y + 3;
    player[3].x = player[0].x + 3;
    player[3].y = player[0].y + 3;
    player[0].bx = init_x;
    player[0].by = init_y;
    player[1].bx = player[0].bx + 3;
    player[1].by = player[0].by;
    player[2].bx = player[0].bx;
    player[2].by = player[0].by + 3;
    player[3].bx = player[0].bx + 3;
    player[3].by = player[0].by + 3;
    for (int i = 0; i < NBPCS; i++)
    {
        player[i].symbole = symb;
        player[i].mvt_count = 0;
        player[i].color = couleur;
        player[i].back_symb = symb;
        player[i].won = false;
        player[i].is_safe = false;
        player[i].is_unsafe = false;
    }
}

void init_player_no_mercy(struct joueur ***player)
{
    *player = malloc(4 * sizeof(joueur *));
    for (int i = 0; i < 4; i++)
    {
        (*player)[i] = malloc(4 * sizeof(joueur));
    }
    (*player)[0][0].x = A;
    (*player)[0][0].y = 1;
    (*player)[0][1].x = 1;
    (*player)[0][1].y = 1;
    (*player)[0][2].x = 1;
    (*player)[0][2].y = A;
    (*player)[0][3].x = A;
    (*player)[0][3].y = A;
    for (int i = 0; i < 4; i++)
    {
        (*player)[0][i].bx = (*player)[0][i].x;
        (*player)[0][i].by = (*player)[0][i].y;
        (*player)[0][i].symbole = 'x';
        (*player)[0][i].mvt_count = 0;
        (*player)[0][i].color = 'B';
        (*player)[0][i].back_symb = 'x';
        (*player)[0][i].won = false;
        (*player)[0][i].is_unsafe = false;
        (*player)[0][i].is_safe = false;
    }
    for (int i = 1; i < 4; i++)
    {
        switch (i)
        {
        case 1:
            for (int j = 0; j < 4; j++)
            {
                (*player)[i][j].x = (*player)[0][j].x + 3;
                (*player)[i][j].y = (*player)[0][j].y;
                (*player)[i][j].bx = (*player)[i][j].x;
                (*player)[i][j].by = (*player)[i][j].y;
                (*player)[i][j].symbole = 'c';
                (*player)[i][j].mvt_count = 0;
                (*player)[i][j].color = 'R';
                (*player)[i][j].back_symb = 'c';
                (*player)[i][j].won = false;
                (*player)[i][j].is_unsafe = false;
            }
            break;
        case 2:
            for (int j = 0; j < 4; j++)
            {
                (*player)[i][j].x = (*player)[0][j].x;
                (*player)[i][j].y = (*player)[0][j].y + 3;
                (*player)[i][j].bx = (*player)[i][j].x;
                (*player)[i][j].by = (*player)[i][j].y;
                (*player)[i][j].symbole = 'o';
                (*player)[i][j].mvt_count = 0;
                (*player)[i][j].color = 'G';
                (*player)[i][j].back_symb = 'o';
                (*player)[i][j].won = false;
                (*player)[i][j].is_unsafe = false;
            }
            break;
        case 3:
            for (int j = 0; j < 4; j++)
            {
                (*player)[i][j].x = (*player)[0][j].x + 3;
                (*player)[i][j].y = (*player)[0][j].y + 3;
                (*player)[i][j].bx = (*player)[i][j].x;
                (*player)[i][j].by = (*player)[i][j].y;
                (*player)[i][j].symbole = 'z';
                (*player)[i][j].mvt_count = 0;
                (*player)[i][j].color = 'Y';
                (*player)[i][j].back_symb = 'z';
                (*player)[i][j].won = false;
                (*player)[i][j].is_unsafe = false;
            }
            break;
        }
    }
}

void init_player_load(struct joueur *player, char symb, char couleur, int init_x, int init_y)
{
    player[0].bx = init_x;
    player[0].by = init_y;
    player[1].bx = player[0].bx + 3;
    player[1].by = player[0].by;
    player[2].bx = player[0].bx;
    player[2].by = player[0].by + 3;
    player[3].bx = player[0].bx + 3;
    player[3].by = player[0].by + 3;
    for (int i = 0; i < NBPCS; i++)
    {
        player[i].symbole = symb;
        player[i].color = couleur;
        player[i].back_symb = symb;
        player[i].won = 0;
        player[i].is_unsafe = false;
    }
}

struct joueur **initialisation_load(struct joueur **player, int nb_player, Gamemode gamemode)
{
    switch (gamemode)
    {
    case NO_MERCY:
        player[0][0].bx = A;
        player[0][0].by = 1;
        player[0][1].bx = 1;
        player[0][1].by = 1;
        player[0][2].bx = 1;
        player[0][2].by = A;
        player[0][3].bx = A;
        player[0][3].by = A;
        for (int i = 0; i < 4; i++)
        {
            player[0][i].symbole = 'x';
            player[0][i].mvt_count = 0;
            player[0][i].color = 'B';
            player[0][i].back_symb = 'x';
            player[0][i].won = false;
            player[0][i].is_unsafe = false;
            player[0][i].is_safe = false;
        }
        for (int i = 1; i < 4; i++)
        {
            switch (i)
            {
            case 1:
                for (int j = 0; j < 4; j++)
                {
                    player[i][j].bx = player[0][j].bx + 3;
                    player[i][j].by = player[0][j].by;
                    player[i][j].symbole = 'c';
                    player[i][j].mvt_count = 0;
                    player[i][j].color = 'R';
                    player[i][j].back_symb = 'c';
                    player[i][j].won = false;
                    player[i][j].is_unsafe = false;
                }
                break;
            case 2:
                for (int j = 0; j < 4; j++)
                {
                    player[i][j].bx = player[0][j].bx;
                    player[i][j].by = player[0][j].by + 3;
                    player[i][j].symbole = 'o';
                    player[i][j].mvt_count = 0;
                    player[i][j].color = 'G';
                    player[i][j].back_symb = 'o';
                    player[i][j].won = false;
                    player[i][j].is_unsafe = false;
                }
                break;
            case 3:
                for (int j = 0; j < 4; j++)
                {
                    player[i][j].bx = player[0][j].bx + 3;
                    player[i][j].by = player[0][j].by + 3;
                    player[i][j].symbole = 'z';
                    player[i][j].mvt_count = 0;
                    player[i][j].color = 'Y';
                    player[i][j].back_symb = 'z';
                    player[i][j].won = false;
                    player[i][j].is_unsafe = false;
                }
                break;
            }
        }
        break;
    default:
        if (nb_player == 2)
        {
            init_player_load(player[0], 'x', 'B', 10, 1);
            init_player_load(player[1], 'o', 'G', 1, 10);
        }
        if (nb_player == 3)
        {
            init_player_load(player[0], 'x', 'B', 10, 1);
            init_player_load(player[2], 'o', 'G', 1, 10);
            init_player_load(player[1], 'c', 'R', 1, 1);
        }
        if (nb_player == 4)
        {
            init_player_load(player[0], 'x', 'B', 10, 1);
            init_player_load(player[2], 'o', 'G', 1, 10);
            init_player_load(player[1], 'c', 'R', 1, 1);
            init_player_load(player[3], 'z', 'Y', 10, 10);
        }
        break;
    }
    return player;
}

struct joueur **initialisation(struct joueur **player, int nb_player)
{
    switch (nb_player)
    {
    case 2:
        init_player(player[0], 10, 1, 'x', 'B');
        init_player(player[1], 1, 10, 'o', 'G');
        break;
    case 3:
        init_player(player[0], 10, 1, 'x', 'B');
        init_player(player[2], 1, 10, 'o', 'G');
        init_player(player[1], 1, 1, 'c', 'R');
        break;
    case 4:
        init_player(player[0], 10, 1, 'x', 'B');
        init_player(player[2], 1, 10, 'o', 'G');
        init_player(player[1], 1, 1, 'c', 'R');
        init_player(player[3], 10, 10, 'z', 'Y');
        break;
    }
    return player;
}

struct joueur **get_mvt_count(struct joueur **player, int nb_player)
{
    struct joueur mvt_getter;
    for (int i = 0; i < nb_player; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            mvt_getter.x = player[i][j].bx;
            mvt_getter.y = player[i][j].by;
            mvt_getter.mvt_count = 0;
            mvt_getter.color = player[i][j].color;
            while (mvt_getter.x != player[i][j].x || mvt_getter.y != player[i][j].y)
            {
                if (mvt_getter.mvt_count == 0)
                {
                    if (player[i][j].bx > 8)
                    {
                        if (player[i][j].by < 6)
                        {
                            mvt_getter.x = D;
                            mvt_getter.y = 6;
                            mvt_getter.mvt_count++;
                        }
                        else
                        {
                            mvt_getter.x = 8;
                            mvt_getter.y = D;
                            mvt_getter.mvt_count++;
                        }
                    }
                    else
                    {
                        if (player[i][j].by < 6)
                        {
                            mvt_getter.x = 6;
                            mvt_getter.y = 1;
                            mvt_getter.mvt_count++;
                        }
                        else
                        {
                            mvt_getter.x = 1;
                            mvt_getter.y = 8;
                            mvt_getter.mvt_count++;
                        }
                    }
                }
                else
                {
                    if (mvt_getter.mvt_count > 50)
                    {
                        if (player[i][j].bx > 8)
                        {
                            if (player[i][j].by < 6)
                            {
                                mvt_getter.x--;
                                mvt_getter.mvt_count++;
                            }
                            else
                            {
                                mvt_getter.y--;
                                mvt_getter.mvt_count++;
                            }
                        }
                        else
                        {
                            if (player[i][j].by < 6)
                            {
                                mvt_getter.y++;
                                mvt_getter.mvt_count++;
                            }
                            else
                            {
                                mvt_getter.x++;
                                mvt_getter.mvt_count++;
                            }
                        }
                    }
                    else if (mvt_getter.x < 5 && mvt_getter.y == 8)
                    {
                        mvt_getter.x++;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.x == 5 && mvt_getter.y == 8)
                    {
                        mvt_getter.y++;
                        mvt_getter.x++;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.x == 6 && (mvt_getter.y > 8 && mvt_getter.y != E))
                    {
                        mvt_getter.y++;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.y == E && mvt_getter.x != 8)
                    {
                        mvt_getter.x++;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.x == 8 && mvt_getter.y > 9)
                    {
                        mvt_getter.y--;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.x == 8 && mvt_getter.y == 9)
                    {
                        mvt_getter.x++;
                        mvt_getter.y--;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.y == 8 && (mvt_getter.x > 8 && mvt_getter.x != E))
                    {
                        mvt_getter.x++;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.x == E && mvt_getter.y != 6)
                    {
                        mvt_getter.y--;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.y == 6 && mvt_getter.x > 9)
                    {
                        mvt_getter.x--;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.x == 9 && mvt_getter.y == 6)
                    {
                        mvt_getter.y--;
                        mvt_getter.x--;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.x == 8 && (mvt_getter.y < 6 && mvt_getter.y != 0))
                    {
                        mvt_getter.y--;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.y == 0 && mvt_getter.x != 6)
                    {
                        mvt_getter.x--;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.x == 6 && mvt_getter.y < 5)
                    {
                        mvt_getter.y++;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.x == 6 && mvt_getter.y == 5)
                    {
                        mvt_getter.x--;
                        mvt_getter.y++;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.y == E && mvt_getter.x != 8)
                    {
                        mvt_getter.x++;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.y == 6 && mvt_getter.x < 6 && mvt_getter.x != 0)
                    {
                        mvt_getter.x--;
                        mvt_getter.mvt_count++;
                    }
                    else if (mvt_getter.x == 0 && mvt_getter.y != 8)
                    {
                        mvt_getter.y++;
                        mvt_getter.mvt_count++;
                    }
                }
            }
            player[i][j].mvt_count = mvt_getter.mvt_count;
            if (player[i][j].mvt_count == 57)
            {
                player[i][j].won = 1;
            }
        }
    }
    return player;
}

void class_player(int *classement, int *indClass, int nb_player, int actual_player)
{
    int j;
    for (j = 0; j < nb_player; j++)
    {
        if (classement[j] == actual_player)
        {
            break;
        }
    }
    if (j == nb_player)
    {
        classement[*indClass] = actual_player;
        (*indClass)++;
    }
}