/*!
 * \file tableau.h
 *
 * \author Justine Ribas <ribasjusti@cy-tech.fr>
 * \version 0.1
 * \date 11 janvier 2022
 *
 * \brief header des fonctions pour créer des tableaux
 *
 *
 */

#ifndef __TABLEAU_H__
#define __TABLEAU_H__

 // Inclusion des entêtes de librairies
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/* Déclaration des fonctions */

/**
 * \fn char** creerTab(int int_nbMots)
 *
 * \author Justine Ribas <ribasjusti@eisti.eu>
 * \version 0.1
 * \date 11 janvier 2022
 *
 * \brief permet de créer un tableau de chaines de caractères
 *
 * \param int_nbMots le nombre de chaines de caractères dans le tableau
 * 
 * \return tab l'adresse de la première case du tableau crée
 *
 */
char** creerTab(int int_nbMots);


/**
 * \fn void freeTab2D(char** pstr_mots, int int_nbMots)
 *
 * \author Justine Ribas <ribasjusti@eisti.eu>
 * \version 0.1
 * \date 11 janvier 2022
 *
 * \brief permet de libérer l'espace mémoire des tableaux à deux dimenssions
 *
 *
 * \param pstr_mots le tableau à supprimer
 * \param int_nbMots la taille du tableau
 */
void freeTab2D(char** pstr_mots, int int_nbMots);

/**
 * \fn char* copieChaine(char* str_mot, int int_n)
 *
 * \author Justine Ribas <ribasjusti@eisti.eu>
 * \version 0.1
 * \date 16 janvier 2022
 *
 * \brief permet de copier une chaine de caractères
 *
 * \param str_mot la chaine de caractères à copier
 * \param int_n la taille de la chaines de caractères à copier
 * 
 * \return la copie de la chaine de caractères
 *
 */
char* copieChaine(char* str_mot, int int_n);


#endif
