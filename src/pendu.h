/*!
* \file pendu.h
*
* \brief le fichier en-tête des fonctions relatives au jeu du pendu
*
* \author Justine Ribas <ribasjusti@cy-tech.fr>
* \version 0.1
* 
* \date 11 janvier 2022
*/

#ifndef PENDU_H
#define PENDU_H

/*inclusion des entêtes de librairie*/
#include "tableau.h"
#include "saisie.h"
#include <errno.h>
#include <string.h>


/*Déclaration des fonctions*/

/**
* \fn char* motAleatoire(char *nomFichier)
* \brief permet de tirer un mot au hasard dans un fichier texte
*
* \param nomFichier nom du fichier texte contenant les mots
*
* \return le mot tiré au hasard
* 
* \author Justine Ribas <ribasjusti@cy-tech.fr>
* \version 0.1
* \date 11 janvier 2022
*/
char* motAleatoire(char *nomFichier);

/**
* \fn void jouePendu(char *str_mot)
* \brief permet de lancer une partie de pendu
*
* \param str_mot le mot à faire deviner
* 
* \author Justine Ribas <ribasjusti@cy-tech.fr>
* \version 0.1
* \date 16 janvier 2022
*/
void jouePendu(char *str_mot);

/**
* \fn int joueLettre(char *str_mot, char* str_motTemp, char str_lettre)
* \brief permet de jouer une lettre
*
* \param str_mot le mot à faire deviner
* \param str_motTemp le mot à afficher
* \param str_lettre la lettre à tester
*
* \return le nombre d'occurences de la lettre dans le mot
* 
* \author Justine Ribas <ribasjusti@cy-tech.fr>
* \version 0.1
* \date 16 janvier 2022
*/
int joueLettre(char *str_mot, char* str_motTemp, char str_lettre);

/**
* \fn int aTrouve(char *str_mot, char* str_motTemp, int int_nbErreur)
* \brief permet de vérifier si l'utilisateur a gagné
*
* \param str_mot le mot à faire deviner
* \param str_motTemp le mot à afficher
* \param int_nbErreur le nombre d'erreurs faites
*
* \return 1 si l'utilisateur a gagné, -1 si il a perdu et 0 si il continue à jouer
* 
* \author Justine Ribas <ribasjusti@cy-tech.fr>
* \version 0.1
* \date 16 janvier 2022
*/
int aTrouve(char *str_mot, char* str_motTemp, int int_nbErreur);

/**
* \fn void ecrireScore(int int_essaisRestants)
* \brief permet d'écrire le score dans un fichier texte

* \param int_essaisRestants le nombre d'essais restants
*
* \author Justine Ribas <ribasjusti@cy-tech.fr>
* \version 0.1
* \date 16 janvier 2022
*/
void ecrireScore(int int_essaisRestants);

/**
* \fn int recherchePseudo(char *str_pseudo, int int_score)
* \brief permet de rechercher un pseudo dans un fichier texte

* \param str_pseudo le pseudo à rechercher
* \param int_score le score de l'utilisateur
*
* \return le score max de l'utilisateur
*
* \author Justine Ribas <ribasjusti@cy-tech.fr>
* \version 0.1
* \date 16 janvier 2022
*/
int recherchePseudo(char *str_pseudo, int int_score);

/**
* \fn void affichagePendu(int int_nbErreurs)
* \brief permet d'afficher le nombre d'erreurs graphiquement
*
* \param int_nbErreurs le nombre d'erreurs faites
*
* \author Justine Ribas <ribasjusti@cy-tech.fr>
* \version 0.1
* \date 16 janvier 2022
*/
void affichagePendu(int int_nbErreurs);

#endif