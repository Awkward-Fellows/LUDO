/**
 * @author Awkward_Fellow
 * @file game.h
 * @brief Core logic and menu management for the game application.
 * @details This header defines the primary game loops, save/load mechanics,
 * and menu interface functions.
 */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include "joueur.h"
#include "mouvement.h"
#include "plateau.h"

/**
 * @brief Restores a previous game state from a file.
 * @param player Array of player structures.
 * @param turn Pointer to store the current turn index.
 * @param score Pointer to the scores array.
 * @param ind_class Pointer to the ranking index (to not lose which index of the classement we are now.)
 * @param gamemode The current game mode (Classic, No Mercy, etc.).
 * @param session Current session identifier.(more accurately the the indetifier of the turn you want to load but there is already
 * a turn parameter and I'm not good at naming things)
 * @param Time Pointer to the string storing the timestamp.
 * @return joueur** Updated array of players.
 */
joueur **loadGame(FILE *saveData, int *nb_player, joueur **player, int *turn, int **score, int **classement, int *ind_class, Gamemode gamemode, int session, char **Time);

/**
 * @brief Saves the current game state to a persistent file.
 * * @param saveFile Pointer to the destination file.
 * @param player Array of player structures.
 * @param nb_player Number of players in the session.
 * @param turn The current turn number.(which player should play(lack of vocabulary) if we loaded the saved game)
 * @param score Current scores.
 * @param classement Current player rankings.
 * @param ind_class Current index in the ranking array.
 * @param gamemode The mode being played.
 */
void saveGame(FILE *saveFile, struct joueur **player, int nb_player, int turn, int *score, int *classement, int ind_class, Gamemode gamemode);

/**
 * @brief Initializes and manages the Multiplayer game loop.
 * * @param plateau The visual representation of the board.
 * @param matrice The underlying logical matrix of the board.
 */
void Multiplayer(char **plateau, int **matrice);

/**
 * @brief Displays and handles the main application menu.
 */
void Main_Menu();

/**
 * @brief Displays and handles the menu for "No Mercy" mode.
 */
void No_Mercy_Menu();

/**
 * @brief Displays and handles the menu for "Classic" mode.
 */
void Classic_Menu();

/**
 * @brief Triggers a visual loading sequence in the console.
 */
void Loading_Animation();

/**
 * @brief Parses a string to extract player scores.
 * * @param string The raw data string from a save file.
 * @param nb_player The number of players to look for.
 * @return int* An allocated array of scores.
 */
int *get_score(char *string, int nb_player);

/**
 * @brief Parses a string to extract player rankings.
 * * @param string The raw data string from a save file.
 * @param nb_player The number of players to look for.
 * @param ind_class Pointer to update with the ranking index.
 * @return int* An allocated array of rankings.
 */
int *get_classement(char *string, int nb_player, int *ind_class);

#endif