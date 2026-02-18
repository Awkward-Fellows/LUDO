#include <stdio.h>
#include <stdlib.h>
#include "../Headers/plateau.h"
#include "../Headers/mouvement.h"

char **init(char **plateau, int taille_x, int taille_y, struct joueur **player, int nb_player)
{
    plateau = (char **)malloc(taille_x * sizeof(char *));
    for (int i = 0; i < taille_x; i++)
    {
        *(plateau + i) = (char *)malloc(taille_y * sizeof(char));
    }
    for (int i = 0; i < taille_x; i++)
    {
        for (int j = 0; j < taille_y; j++)
        {
            plateau[i][j] = ' ';
        }
    }
    plateau[D][6] = 'S';
    plateau[8][2] = 'U';
    plateau[6][1] = 'S';
    plateau[2][6] = 'U';
    plateau[1][8] = 'S';
    plateau[6][C] = 'U';
    plateau[8][D] = 'S';
    plateau[12][8] = 'U';
    plateau[7][7] = 'X';
    for (int i = 0; i < nb_player; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            plateau[player[i][j].x][player[i][j].y] = player[i][j].symbole;
        }
    }
    return plateau;
}

void update_plateau(char ***plateau, struct joueur **player, int nb_player, int **gamseState)
{
    for (int i = 0; i < TAILLE_X; i++)
    {
        for (int j = 0; j < TAILLE_Y; j++)
        {
            (*plateau)[i][j] = ' ';
        }
    }
    (*plateau)[D][6] = 'S';
    (*plateau)[8][2] = 'U';
    (*plateau)[6][1] = 'S';
    (*plateau)[2][6] = 'U';
    (*plateau)[1][8] = 'S';
    (*plateau)[6][C] = 'U';
    (*plateau)[8][D] = 'S';
    (*plateau)[12][8] = 'U';
    (*plateau)[7][7] = 'X';
    for (int i = 0; i < nb_player; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((*plateau)[player[i][j].x][player[i][j].y] == '0' || (*plateau)[player[i][j].x][player[i][j].y] == '1' || (*plateau)[player[i][j].x][player[i][j].y] == '2' || (*plateau)[player[i][j].x][player[i][j].y] == '3')
            {
                continue;
            }
            else
            {
                (*plateau)[player[i][j].x][player[i][j].y] = player[i][j].symbole;
            }
        }
    }
}

void afficher(char **plateau, int taille_x, int taille_y, int dice, struct joueur **player, int actual, int **gameState, int nb_player)
{
    printf("\033c");

    printf("" MAG "\t  0   1   2   3   4   5   6   7   8   9   A   B   C   D   E\n");
    printf("" RED "\t+---+---+---+---+---+---+" WHT "---+---+---" GRN "+---+---+---+---+---+---+\n");
    for (int i = 0; i < taille_x; i++)
    {
        for (int j = 0; j < taille_y; j++)
        {
            if (j == 0)
            {
                if (i < 10)
                {
                    printf("" MAG "%c\t", i + '0');
                }
                else
                {
                    printf("" MAG "%c\t", i + '7');
                }
            }
            if (i == 7 && j == 7)
            {
                printf("|" MAG " %c ", plateau[i][j]);
            }
            else if ((j > 6 && j < 9) || (i >= 6 && i < 9))
            {
                switch (plateau[i][j])
                {
                case '0':
                case '1':
                case '2':
                case '3':
                    printf("" WHT "|" CYN " %c " WHT "", plateau[i][j]);
                    break;
                case 'x':
                case 'o':
                case 'c':
                case 'z':
                    for (int p = 0; p < nb_player; p++)
                    {
                        if (plateau[i][j] == player[p]->symbole)
                        {
                            switch (player[p]->color)
                            {
                            case 'R':
                                printf("" WHT "|" RED " \u265F " WHT "");
                                break;
                            case 'B':
                                printf("" WHT "|" BLU " \u265F " WHT "");
                                break;
                            case 'Y':
                                printf("" WHT "|" YEL " \u265F " WHT "");
                                break;
                            case 'G':
                                printf("" WHT "|" GRN " \u265F " WHT "");
                                break;
                            }
                        }
                    }
                    break;
                case 'S':
                    printf("|" WHT " \u2605 ");
                    break;
                case 'U':
                    printf("|" MAG " \u2605 ");
                    break;
                default:
                    printf("" WHT "| %c ", plateau[i][j]);
                    break;
                }
            }
            else if (j % 3 == 0 && j <= 6)
            {
                if (i < 6)
                {
                    switch (plateau[i][j])
                    {
                    case 'U':
                        printf("|" MAG " \u2605 ");
                        break;
                    default:
                        switch (plateau[i][j])
                        {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                            printf("" RED "|" CYN " %c " WHT "", plateau[i][j]);
                            break;
                        case 'x':
                        case 'o':
                        case 'c':
                        case 'z':
                            for (int p = 0; p < nb_player; p++)
                            {
                                if (plateau[i][j] == player[p]->symbole)
                                {
                                    switch (player[p]->color)
                                    {
                                    case 'R':
                                        printf("" RED "|" RED " \u265F " WHT "");
                                        break;
                                    case 'B':
                                        printf("" RED "|" BLU " \u265F " WHT "");
                                        break;
                                    case 'G':
                                        printf("" RED "|" GRN " \u265F " WHT "");
                                        break;
                                    case 'Y':
                                        printf("" RED "|" YEL " \u265F " WHT "");
                                        break;
                                    }
                                }
                            }
                            break;
                        default:
                            printf("" RED "| %c ", plateau[i][j]);
                            break;
                        }
                        break;
                    }
                }
                if (i >= 9)
                {
                    switch (plateau[i][j])
                    {
                    case 'S':
                        printf("" BLU "|" WHT " \u2605 ");
                        break;
                    default:
                        switch (plateau[i][j])
                        {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                            printf("" BLU "|" CYN " %c " WHT "", plateau[i][j]);
                            break;
                        case 'x':
                        case 'o':
                        case 'c':
                        case 'z':
                            for (int p = 0; p < nb_player; p++)
                            {
                                if (plateau[i][j] == player[p]->symbole)
                                {
                                    switch (player[p]->color)
                                    {
                                    case 'B':
                                        printf("" BLU "|" BLU " \u265F ");
                                        break;
                                    case 'R':
                                        printf("" BLU "|" RED " \u265F ");
                                        break;
                                    case 'G':
                                        printf("" BLU "|" GRN " \u265F ");
                                        break;
                                    case 'Y':
                                        printf("" BLU "|" YEL " \u265F ");
                                        break;
                                    }
                                }
                            }
                            break;
                        default:
                            printf("" BLU "| %c ", plateau[i][j]);
                            break;
                        }
                        break;
                    }
                }
            }
            else if (j % 3 == 0 && j >= 9)
            {
                if (i < 6)
                {
                    printf("" GRN "| %c ", plateau[i][j]);
                }
                if (i >= 9)
                {
                    printf("" YEL "| %c ", plateau[i][j]);
                }
            }
            else
            {
                if (plateau[i][j] != ' ' && dice != 6)
                {
                    switch (plateau[i][j])
                    {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                        printf("" CYN "  %c ", plateau[i][j]);
                        break;
                    default:
                        for (int p = 0; p < nb_player; p++)
                        {
                            if (plateau[i][j] == player[p]->symbole)
                            {
                                switch (player[p]->color)
                                {
                                case 'R':
                                    printf("" RED "  \u265F ");
                                    break;
                                case 'B':
                                    printf("" BLU "  \u265F ");
                                    break;
                                case 'G':
                                    printf("" GRN "  \u265F ");
                                    break;
                                case 'Y':
                                    printf("" YEL "  \u265F ");
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
                else
                {
                    switch (plateau[i][j])
                    {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                        printf("" CYN "  %c ", plateau[i][j]);
                        break;
                    case ' ':
                        printf("  %c ", plateau[i][j]);
                        break;
                    default:
                        for (int p = 0; p < nb_player; p++)
                        {
                            if (plateau[i][j] == player[p]->symbole)
                            {
                                switch (player[p]->color)
                                {
                                case 'R':
                                    printf("" RED "  \u265F ");
                                    break;
                                case 'B':
                                    printf("" BLU "  \u265F ");
                                    break;
                                case 'G':
                                    printf("" GRN "  \u265F ");
                                    break;
                                case 'Y':
                                    printf("" YEL "  \u265F ");
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        if (i < 6)
        {
            printf("" GRN "|\n");
        }
        else if (i > 8)
        {
            printf("" YEL "|\n");
        }
        else
        {
            printf("" WHT "|\n");
        }
        if (i > 5 && i < 8)
        {
            printf("" WHT "\t+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
        }
        else if (i % 3 == 2)
        {
            if (i <= 5)
            {
                printf("" RED "\t+---+---+---+---+---+---+" WHT "---+---+---" GRN "+---+---+---+---+---+---+\n");
            }
            if (i >= 8)
            {
                printf("" BLU "\t+---+---+---+---+---+---+" WHT "---+---+---" YEL "+---+---+---+---+---+---+\n");
            }
        }
        else
        {
            if (i < 5)
            {
                printf("" RED "\t+           +           +" WHT "---+---+---" GRN "+           +           +\n");
            }
            if (i > 8)
            {
                printf("" BLU "\t+           +           +" WHT "---+---+---" YEL "+           +           +\n");
            }
        }
    }
    if (gameState != NULL)
    {
        display_state(player, actual, gameState, nb_player);
    }
}

void display_pos(struct joueur ***player, int *actual, int nb_player, char ***plateau, int dice, int **gameState)
{
    for (int k = 0; k < 4; k++)
    {
        (*player)[*actual][k].symbole = k + '0';
        (*plateau)[(*player)[*actual][k].x][(*player)[*actual][k].y] = (*player)[*actual][k].symbole;
    }
    update_plateau(plateau, *player, nb_player, gameState);
    printf("\033c");
    afficher(*plateau, TAILLE_X, TAILLE_Y, dice, *player, *actual, gameState, nb_player);
    rollDice(*player, *actual);
    printf("\nDice: %d\n", dice);
}

void update_matrice(int ***matrice, char **plateau)
{
    for (int i = 0; i < TAILLE_X; i++)
    {
        for (int j = 0; j < TAILLE_Y; j++)
        {
            if (plateau[i][j] == ' ')
            {
                (*matrice)[i][j] = 0;
            }
            else if ((i == 13 && j == 6) || (i == 6 && j == 1) || (i == 1 && j == 8) || (i == 8 && j == D))
            {
                (*matrice)[i][j] = 2;
            }
            else if ((i == 8 && j == 2) || (i == 2 && j == 6) || (i == 6 && j == C) || (i == 12 && j == 8))
            {
                (*matrice)[i][j] = 3;
            }
            else
            {
                (*matrice)[i][j] = 1;
            }
        }
    }
}

void display_state(struct joueur **player, int actual, int **gameState, int nb_player)
{
    int R, G;
    R = nb_player == 2 ? 2 : 1;
    G = R == 2 ? 1 : 2;
    printf("" CYN "\t+---+---+---+\t+---+---+---+\t+---+---+---+\t+---+---+---+\n");
    printf("\t|           |\t|           |\t|           |\t|           |\n");
    printf("\t+   " RED "%d   " GRN "%d" CYN "   +\t+   " RED "%d   " GRN "%d" CYN "   +\t+   " RED "%d   " GRN "%d" CYN "   +\t+   " RED "%d   " GRN "%d" CYN "   +\n", gameState[R][0], gameState[G][0],
           gameState[R][1], gameState[G][1], gameState[R][2], gameState[G][2], gameState[R][3], gameState[G][3]);
    printf("\t|           |\t|           |\t|           |\t|           |\n");
    printf("\t+   " BLU "%d   " YEL "%d" CYN "   +\t+   " BLU "%d   " YEL "%d" CYN "   +\t+   " BLU "%d   " YEL "%d" CYN "   +\t+   " BLU "%d   " YEL "%d" CYN "   +\n", gameState[0][0], gameState[3][0],
           gameState[0][1], gameState[3][1], gameState[0][2], gameState[3][2], gameState[0][3], gameState[3][3]);
    printf("\t|           |\t|           |\t|           |\t|           |\n");
    printf("\t+---+---+---+\t+---+---+---+\t+---+---+---+\t+---+---+---+\n\n");
    printf("Pos:\t");
    for (int j = 0; j < 4; j++)
    {
        if (player[actual][j].x < 10)
        {
            printf("    %c", player[actual][j].x + '0');
        }
        else if (player[actual][j].x >= 10)
        {
            printf("    %c", player[actual][j].x + '7');
        }
        if (player[actual][j].y < 10)
        {
            printf("    %c", player[actual][j].y + '0');
        }
        else if (player[actual][j].y >= 10)
        {
            printf("    %c", player[actual][j].y + '7');
        }
        printf("\t");
    }
    printf("\n\n");
}

void display_classement(struct joueur **player, int *classement, int *score, int nb_player)
{
    printf("" WHT "=================================================\n");
    printf("|                    CLASSEMENT                 |\n");
    printf("=================================================\n");
    for (int i = 0; i < nb_player; i++)
    {
        switch (player[classement[i]]->color)
        {
        case 'R':
            printf("" WHT "|" RED "\t%d : Player %d \t|\t Score: %d" WHT "\t|\n", i + 1, classement[i], score[classement[i]]);
            break;
        case 'B':
            printf("" WHT "|" BLU "\t%d : Player %d \t|\t Score: %d" WHT "\t|\n", i + 1, classement[i], score[classement[i]]);
            break;
        case 'G':
            printf("" WHT "|" GRN "\t%d : Player %d \t|\t Score: %d" WHT "\t|\n", i + 1, classement[i], score[classement[i]]);
            break;
        default:
            printf("" WHT "|" YEL "\t%d : Player %d \t|\t Score: %d" WHT "\t|\n", i + 1, classement[i], score[classement[i]]);
            break;
        }
    }
    printf("=================================================\n");
}