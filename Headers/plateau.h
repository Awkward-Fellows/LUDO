#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdbool.h>
#include "joueur.h"
#define NBPCS 4
#define TAILLE_X 15
#define TAILLE_Y 15
#define RED "\e[1;31m"
#define GRN "\e[1;32m"
#define YEL "\e[1;33m"
#define BLU "\e[1;34m"
#define WHT "\e[1;37m"
#define MAG "\e[1;35m"
#define CYN "\e[1;36m"
#define A 10
#define B 11
#define C 12
#define D 13
#define E 14

enum Gamemode
{
    NO_MERCY,
    CLASSIC
};

typedef enum Gamemode Gamemode;

char **init(char **plateau, int taille_x, int taille_y, struct joueur **player, int nb_player);

struct Plateau
{
    char **plateau;
    int **matrice;
};

void afficher(char **plateau, int taille_x, int taille_y, int dice, struct joueur **player, int actual, int **gameState, int nb_player);

void clear_screen();

void menu();

void pauseMenu();

int verifPost(char **plateau, struct joueur player);

void update_plateau(char ***plateau, struct joueur **player, int nb_player, int **gameState);

void display_pos(struct joueur ***player, int *actual, int nb_player, char ***plateau, int dice, int **gameState);

void update_matrice(int ***matrice, char **plateau);

void display_state(struct joueur **player, int actual, int **gameState, int nb_player);

void display_classement(struct joueur **player, int *classement, int *score, int nb_player);

#endif