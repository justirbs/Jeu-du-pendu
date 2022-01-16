/*!
* \file main.c
*
* \brief le code de la fonction main
*
* \author Justine Ribas <ribasjusti@cy-tech.fr>
* \version 0.1
* 
* \date 10 janvier 2022
*/

/*inclusion des entêtes de librairie*/
#include "main.h"


/*code de la fonction main*/

// fonction principale qui permet
int main(int argc, char *argv[])
{
    // Déclaration des variables
    char* str_mot;

    // On tire un mot au hasard dans le fichier
    str_mot = motAleatoire("./files/mots.txt");

    // On lance le jeu
    jouePendu(str_mot);
    
    // On retourne 0 pour indiquer que le programme s'est bien terminé
    return(0);
}