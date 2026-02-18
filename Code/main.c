#include <stdlib.h>
#include <unistd.h>
#include "../Headers/game.h"

#define TAILLE_X 15
#define TAILLE_Y 15

int main()
{
    struct Plateau plateform;
    Multiplayer(plateform.plateau, plateform.matrice);
    return (0);
}