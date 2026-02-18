#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "../Headers/game.h"

void saveGame(FILE *saveFile, struct joueur **player, int nb_player, int turn, int *score, int *classement, int ind_class, Gamemode gamemode)
{
    mkdir("./SaveData", 0777);
    switch (gamemode)
    {
    case NO_MERCY:
        saveFile = fopen("./SaveData/no_mercy.txt", "a+");
        break;
    default:
        saveFile = fopen("./SaveData/classic.txt", "a+");
        break;
    }
    if (saveFile != NULL)
    {
        fprintf(saveFile, "\n%d %d\n", nb_player, turn);
        for (int i = 0; i < nb_player; i++)
        {
            if (i == nb_player - 1)
            {
                fprintf(saveFile, "%d\n", score[i]);
            }
            else
            {
                fprintf(saveFile, "%d ", score[i]);
            }
        }
        for (int i = 0; i < nb_player; i++)
        {
            if (i == nb_player - 1)
            {
                fprintf(saveFile, "%d %d\n", classement[i], ind_class);
            }
            else
            {
                fprintf(saveFile, "%d ", classement[i]);
            }
        }
        for (int i = 0; i < nb_player; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                fprintf(saveFile, "%d ", player[i][j].x);
                if (i == nb_player - 1 && j == 3)
                {
                    fprintf(saveFile, "%d", player[i][j].y);
                }
                else
                {
                    fprintf(saveFile, "%d\n", player[i][j].y);
                }
            }
        }
    }
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    fprintf(saveFile, "\nTime: %s, %02d:%02d:%02d", __DATE__, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
    fclose(saveFile);
}

joueur **loadGame(FILE *saveData, int *nb_player, joueur **player, int *turn, int **score, int **classement, int *ind_class, Gamemode gamemode, int session, char **Time)
{
    int index_player = 0;
    if (saveData == NULL)
    {
        switch (gamemode)
        {
        case NO_MERCY:
            saveData = fopen("./SaveData/no_mercy.txt", "r");
            break;
        default:
            saveData = fopen("./SaveData/classic.txt", "r");
            break;
        }
    }
    int **data = malloc(18 * sizeof(int *));
    char *actual_line = malloc(256 * sizeof(char));
    for (int i = 0; i < 18; i++)
    {
        *(data + i) = malloc(5 * sizeof(int));
    }
    int lgn = 0, psession = 0;
    actual_line = fgets(actual_line, 255, saveData);
    if (actual_line == NULL)
    {
        printf("Votre sauvegarde a été corrompue, impossible de procéder\n");
        exit(-1);
    }
    do
    {
        actual_line = fgets(actual_line, 255, saveData);
        if (strstr(actual_line, "Time:") != NULL)
        {
            *Time = actual_line;
            psession++;
            if (psession == session)
            {
                break;
            }
            else
            {
                actual_line = fgets(actual_line, 255, saveData);
                if (actual_line == NULL)
                {
                    break;
                }
                else
                {
                    lgn = 0;
                }
            }
        }
        switch (lgn)
        {
        case 0:
            sscanf(actual_line, "%d %d", &data[0][0], turn);
            break;
        case 1:
            *score = get_score(actual_line, data[0][0]);
            break;
        case 2:
            *classement = get_classement(actual_line, data[0][0], ind_class);
            break;
        default:
            sscanf(actual_line, "%d %d", &data[lgn - 2][0], &data[lgn - 2][1]);
            break;
        }
        lgn++;
    } while (!feof(saveData));
    fclose(saveData);
    if (data[0][0] > 4 || data[0][0] < 2)
    {
        printf("\nVotre sauvegarde a été corrompue, impossible de procéder\n");
        exit(-1);
    }
    for (int i = 3; i < lgn - 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (data[i][j] < 0 || data[i][j] > 15)
            {
                printf("Votre sauvegarde a été corrompue, impossible de procéder\n");
                exit(-1);
            }
        }
    }
    *nb_player = data[0][0];
    player = malloc((*nb_player + 1) * sizeof(joueur *));
    for (int i = 0; i < *nb_player; i++)
    {
        *(player + i) = malloc(4 * sizeof(joueur));
    }
    for (int i = 1; i < lgn - 2; i++)
    {
        player[index_player][(i - 1) % 4].x = data[i][0];
        player[index_player][(i - 1) % 4].y = data[i][1];
        if (i % 4 == 0)
        {
            index_player++;
        }
    }
    return player;
}

void Multiplayer(char **plateau, int **matrice)
{
    Gamemode gamemode;
    int in;
    FILE *saves = NULL;
    int indClass = 0;
    int nb_player, jauge = 0;
    int rNumber, index, input, turn = 0;
    bool on_move, start_game = true;
    bool restart_turn = false, end_game = false;
    struct joueur **player = NULL;
    int **actualState = (int **)malloc(4 * sizeof(int *));
    int *class;
    int *score;
    matrice = (int **)malloc(TAILLE_X * sizeof(int *));
    for (int i = 0; i < TAILLE_X; i++)
    {
        *(matrice + i) = (int *)malloc(TAILLE_Y * sizeof(int));
    }
    for (int i = 0; i < 4; i++)
    {
        *(actualState + i) = (int *)malloc(4 * sizeof(int));
    }
    Main_Menu();
    char *time_actual = malloc(256 * sizeof(char));
    int mode_choice;
    in = scanf("%d", &mode_choice);
    if (in == 0)
    {
        getchar();
    }
    if (mode_choice == 1)
    {
    no_mercy:
        gamemode = NO_MERCY;
        nb_player = 4;
        No_Mercy_Menu();
        int choice2;
        in = scanf("%d", &choice2);
        if (in == 0)
        {
            getchar();
        }
        if (choice2 == 1)
        {
            init_player_no_mercy(&player);
            score = malloc(4 * sizeof(int));
            class = malloc(4 * sizeof(int));
            for (int i = 0; i < nb_player; i++)
            {
                class[i] = nb_player;
                score[i] = 0;
            }
            saves = fopen("./SaveData/no_mercy.txt", "w");
            fclose(saves);
        }
        else if (choice2 == 2)
        {
            saves = fopen("./SaveData/no_mercy.txt", "r");
            if (saves == NULL)
            {
                printf("Vous n'avez pas de partie sauvegardée...");
                getchar();
                goto multiplayer;
            }
            player = loadGame(saves, &nb_player, player, &turn, &score, &class, &indClass, gamemode, 0, &time_actual);
            player = initialisation_load(player, nb_player, gamemode);
            player = get_mvt_count(player, nb_player);
        }
        else
        {
            Multiplayer(plateau, matrice);
        }
    }
    else if (mode_choice == 2)
    {
    multiplayer:
        gamemode = CLASSIC;
        Classic_Menu();
        int choice2;
        in = scanf("%d", &choice2);
        if (in == 0)
        {
            getchar();
        }
        if (choice2 == 2)
        {
            saves = fopen("./SaveData/classic.txt", "r");
            if (saves == NULL)
            {
                printf("Vous n'avez pas de partie sauvegardée...");
                getchar();
                goto multiplayer;
            }
            player = loadGame(saves, &nb_player, player, &turn, &score, &class, &indClass, gamemode, 0, &time_actual);
            player = initialisation_load(player, nb_player, gamemode);
            player = get_mvt_count(player, nb_player);
        }
        else if (choice2 == 1)
        {
            do
            {
                printf("         < New Game >\n");
                printf("Entrer le nombre de joueur(2-4): ");
                input = scanf("%d", &nb_player);
                if (input == 0 || nb_player > 4 || nb_player < 2)
                {
                    printf("Le nombre de joueur en Multiplayer doit être superieur ou égale à 2 et inferieur ou égale à 4!\n");
                    if (input == 0)
                    {
                        char *buffer = (char *)malloc(256 * sizeof(char));
                        fgets(buffer, 255, stdin);
                        free(buffer);
                    }
                }
            } while (input == 0 || nb_player > 4 || nb_player < 2);
            saves = fopen("./SaveData/classic.txt", "w");
            fclose(saves);
            player = (joueur **)malloc((nb_player + 1) * sizeof(joueur *));
            for (int i = 0; i < nb_player; i++)
            {
                *(player + i) = (joueur *)malloc(4 * sizeof(joueur));
            }
            player = initialisation(player, nb_player);
            score = malloc(nb_player * sizeof(int));
            class = malloc(nb_player * sizeof(int));
            for (int i = 0; i < nb_player; i++)
            {
                class[i] = nb_player;
                score[i] = 0;
            }
        }
        else
        {
            Multiplayer(plateau, matrice);
        }
    }
    else
    {
        printf("\033c");
        Multiplayer(plateau, matrice);
    }
    getchar();
    plateau = init(plateau, TAILLE_X, TAILLE_Y, player, nb_player);
    update_matrice(&matrice, plateau);
    get_state(&actualState, player, nb_player, 0);
    Loading_Animation();
    afficher(plateau, TAILLE_X, TAILLE_Y, 0, player, 0, actualState, nb_player);

    while (!end_game)
    {
        srand(time(NULL));
        for (int i = 0; i < nb_player; i++)
        {

            saveGame(saves, player, nb_player, i, score, class, indClass, gamemode);
            get_state(&actualState, player, nb_player, i);
            afficher(plateau, TAILLE_X, TAILLE_Y, rNumber, player, i, actualState, nb_player);
            if (start_game == true)
            {
                i = turn;
                start_game = false;
                printf("%s\n\n", time_actual);
            }
            rollDice(player, i);
            getchar();
            rNumber = diceRoll(gamemode);
            if (rNumber == 0)
            {
                printf("Dice: %d\n", rNumber);
                pressEnter(player, i);
                getchar();
                restart_turn = false;
            }
            int dice = rNumber;
            while (rNumber > 0)
            {
                plateau = Move(plateau, matrice, player, &i, &rNumber, &on_move, &index, nb_player, dice, &restart_turn, actualState, &end_game, class, &indClass, score, gamemode);
                get_state(&actualState, player, nb_player, i);
                afficher(plateau, TAILLE_X, TAILLE_Y, rNumber, player, i, actualState, nb_player);
                usleep(400000);
            }
            if (restart_turn == true)
            {
                --i;
            }
            if (end_game)
            {
                saveGame(saves, player, nb_player, i, score, class, indClass, gamemode);
                break;
            }
        }
    }
    printf("Game Over\n");
    display_classement(player, class, score, nb_player);
}

void Main_Menu()
{
    printf("\033c");
    printf("" BLU "+-----------------+\n");
    printf("" BLU "|    Multiplayer  |\n");
    printf("" BLU "+-----------------+\n");
    printf("" GRN "+-----------------+\n");
    printf("" GRN "|    1-No_Mercy   |\n");
    printf("" GRN "+-----------------+\n");
    printf("" YEL "+-----------------+\n");
    printf("" YEL "|    2-Classic    |\n");
    printf("" YEL "+-----------------+\n");
    printf("" MAG "> " WHT "");
}

void Classic_Menu()
{
    printf("\033c");
    printf("" BLU "+-----------------+\n");
    printf("" BLU "|     Classic     |\n");
    printf("" BLU "+-----------------+\n");
    printf("" GRN "+-----------------+\n");
    printf("" GRN "|    1-NewGame    |\n");
    printf("" GRN "+-----------------+\n");
    printf("" YEL "+-----------------+\n");
    printf("" YEL "|   2-Load Game   |\n");
    printf("" YEL "+-----------------+\n");
    printf("" RED "+-----------------+\n");
    printf("" RED "|      Back       |\n");
    printf("" RED "+-----------------+\n");
    printf("" MAG "> " WHT "");
}

void No_Mercy_Menu()
{
    printf("\033c");
    printf("" BLU "+-----------------+\n");
    printf("" BLU "|     No_Mercy    |\n");
    printf("" BLU "+-----------------+\n");
    printf("" GRN "+-----------------+\n");
    printf("" GRN "|    1-NewGame    |\n");
    printf("" GRN "+-----------------+\n");
    printf("" YEL "+-----------------+\n");
    printf("" YEL "|   2-Load Game   |\n");
    printf("" YEL "+-----------------+\n");
    printf("" RED "+-----------------+\n");
    printf("" RED "|      Back       |\n");
    printf("" RED "+-----------------+\n");
    printf("" MAG "> " WHT "");
}

void Loading_Animation()
{
    printf("\033c");
    printf("" WHT "#####################################################################################################\n");
    printf("#                                                                                                   #\n");
    printf("#                                        LOADING YOUR GAME...                                       #\n");
    printf("#                                                                                                   #\n");
    printf("#####################################################################################################\n");
    for (int i = 0; i < 100; i++)
    {
        printf("" MAG "#");
        fflush(stdout);
        if (i < 30)
            usleep(25000);
        else if (i >= 30 && i < 70)
            usleep(10000);
        else
            usleep(1000);
    }
}

int *get_score(char *string, int nb_player)
{
    int *score = malloc((nb_player + 1) * sizeof(int));
    if (nb_player == 2)
    {
        sscanf(string, "%d %d", &score[0], &score[1]);
    }
    else if (nb_player == 3)
    {
        sscanf(string, "%d %d %d", &score[0], &score[1], &score[2]);
    }
    else if (nb_player == 4)
    {
        sscanf(string, "%d %d %d %d", &score[0], &score[1], &score[2], &score[3]);
    }
    return score;
}

int *get_classement(char *string, int nb_player, int *ind_class)
{
    int *classement = malloc((nb_player + 1) * sizeof(int));
    if (nb_player == 2)
    {
        sscanf(string, "%d %d %d", &classement[0], &classement[1], ind_class);
    }
    else if (nb_player == 3)
    {
        sscanf(string, "%d %d %d %d", &classement[0], &classement[1], &classement[2], ind_class);
    }
    else if (nb_player == 4)
    {
        sscanf(string, "%d %d %d %d %d", &classement[0], &classement[1], &classement[2], &classement[3], ind_class);
    }
    return classement;
}