#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#define MAX 6
#define MIN 1
#define TAILLE_X 15
#define TAILLE_Y 15
#define NBCASE 57

#include "joueur.h"
#include "plateau.h"

int diceRoll(Gamemode gamemode);

char **Move(char **plateau, int **matrice, struct joueur **player, int *actual, int *move, bool *in_mvt, int *index, int nb_player, int dice, bool *decrement, int **gameState, bool *partie_terminee, int *classement, int *ind_class, int *score, Gamemode gamemode);

void check_coordinate(struct joueur **player, int *actual, int *index, int *move);

void last_straight_line(struct joueur **player, int *actual, int *index, int *move);

void restart(char ***plateau, int ***matrice, struct joueur **player, int pi, int pj, int nb_player, int actual, int **gameState);

void get_state(int ***gameState, struct joueur **player, int nb_player, int actual);

void rollDice(struct joueur **p, int ind);

void pressEnter(struct joueur **p, int ind);

void choosePiece(struct joueur **player, int ind);

void replace_case(char **plateau, struct joueur **player, int player_initx, int player_inity, int *actual, int *index, int nb_player);

void check_collision(char **pplateau, int **pmatrice, struct joueur **pplayer, int *pactual, int *pindex, int pnb_player, int *pscore, int **pgameState, bool *pdecrement);

void first_move(struct joueur **pplayer, int *pactual);

void end_turn(int *pmove, bool *in_move);

void leaveBase(struct joueur **player, int *actual, int *index, int *player_initx, int *player_inity);

void clean_buffer();

char **summon(char **plateau, struct joueur **player, int actual, int index, int nb_player);

int get_random_player(int nb_player_out);

struct joueur **verify_safety(int **matrice, struct joueur **player, int actual, int index);

#endif