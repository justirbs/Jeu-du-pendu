/*!
\file saisie.h
\brief le fichier en-tête des fonctions de saisie
\author Justine Ribas <ribasjusti@cy-tech.fr>
\version 0.1
\date 16 janvier 2022
*/

#ifndef SAISIE_H
#define SAISIE_H

/* inclusions des entêtes de librairie */
#include <stdio.h>
#include <stdlib.h>


/* Déclaration des fonctions */

/*! \fn void viderBuffer(void)
 *  \author Justine Ribas <ribasjusti@cy-tech.fr>
 *  \version 0.1
 *  \date 11 décembre 2019
 *
 *  \brief vide le buffer
 * 
 *  \remarks 
 */
void viderBuffer(void);


/*! \fn char saisirCaractere(void)
 *  \author Justine Ribas <ribasjusti@cy-tech.fr>
 *  \version 0.1
 *  \date 11 décembre 2019
 *
 *  \brief vérifie la saisie d'un entier
 * 
 *
 * \return le caractère saisi
 *
 * \remarks 
 */
char saisirCaractere(void);


#endif