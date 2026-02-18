/**
 * @file joueur.h
 * @brief Player structures and initialization logic.
 * @details Defines the player attributes, including positioning, movement tracking,
 * and status flags, along with functions to manage player lifecycle.
 */

#ifndef JOUEUR_H
#define JOUEUR_H

#include <stdbool.h>

/** @brief Number of pieces per player. */
#define NBPCS 4

/**
 * @struct joueur
 * @brief Represents a single player or piece on the board.
 */
struct joueur
{
    char symbole;  /**< Character representing the player on the board. */
    int back_symb; /**< Backup symbol storage. */
    int x;         /* Current X-coordinate on the board. */
    int y;
    int bx; /*like base-x*/
    int by;
    bool won;       /* Flag indicating if the piece of the player has won. */
    int mvt_count;  /* Total number of moves made by the player. */
    char color;     /* Color attribute for console rendering. */
    bool is_safe;   /* True if the player is in a protected zone. */
    bool is_unsafe; /* True if the player is in a vulnerable position. */
};

/**
 * @struct Player_out
 * @brief Helper structure to track players who have finished or exited.
 */
struct Player_out
{
    int a; /* Generic attribute for player status. */
    int i; /* Index identifier. */
};

/** Type definitions for easier usage throughout the project. */
typedef struct joueur joueur;
typedef struct Player_out Player_out;
typedef enum Gamemode Gamemode;

/**
 * @brief Initializes a player with starting coordinates and visuals.
 * @param player Pointer to the player struct to initialize.
 * @param init_x Initial X-coordinate.
 * @param init_y Initial Y-coordinate.
 * @param symb Character symbol for the player.
 * @param color Color identifier for the player.
 */
void init_player(struct joueur *player, int init_x, int init_y, char symb, char color);

/**
 * @brief Specific initialization for loading a player from a saved state.
 * @param player Pointer to the player struct.
 * @param symb Character symbol.
 * @param couleur Color identifier.
 * @param init_x Loaded X-coordinate.
 * @param init_y Loaded Y-coordinate.
 */
void init_player_load(struct joueur *player, char symb, char couleur, int init_x, int init_y);

/**
 * @brief Memory allocation and setup for players when loading a game.
 * @param player Pointer to the player array.
 * @param nb_player Total number of players.
 * @param gamemode The current mode (Classic/No Mercy).
 * @return struct joueur** The initialized player array.
 */
struct joueur **initialisation_load(struct joueur **player, int nb_player, Gamemode gamemode);

/**
 * @brief Standard memory allocation and setup for a new game.
 * @param player Pointer to the player array.
 * @param nb_player Total number of players.
 * @return struct joueur** The initialized player array.
 */
struct joueur **initialisation(struct joueur **player, int nb_player);

/**
 * @brief Retrieves or calculates movement counts for all players.
 * @param player Array of players.
 * @param nb_player Total number of players.
 * @return struct joueur** Updated player array.
 */
struct joueur **get_mvt_count(struct joueur **player, int nb_player);

/**
 * @brief Updates the ranking/classification of players.
 * @param classement Pointer to the ranking array.
 * @param indClass Current index in the ranking array.
 * @param nb_player Total number of players.
 * @param actual_player The player currently being ranked.
 */
void class_player(int *classement, int *indClass, int nb_player, int actual_player);

/**
 * @brief Specialized initialization for the "No Mercy" game mode.
 * @param player Triple pointer to handle complex allocation for No Mercy rules.
 */
void init_player_no_mercy(struct joueur ***player);

#endif