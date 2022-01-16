/*!
 * \file tableau.c
 *
 * \author Justine Ribas <ribasjusti@cy-tech.fr>
 * \version 0.1
 * \date 11 janvier 2022
 *
 * \brief fonctions pour créer des tableau
 *
 *
 */

//Inclusion des entêtes de librairies
#include"tableau.h"


// Codes des fonctions

// Fonction qui créer un tableau de chaînes de caractères
char** creerTab(int int_nbMots)
{
  // Déclaration des variables
  char** pstr_mots; //tableau de chaînes de caractères

  // On alloue la mémoire pour le tableau
  pstr_mots = malloc(int_nbMots*sizeof(char*));
  if(pstr_mots==NULL){
    fprintf(stderr, "problème d'alloc\n");
    exit(1);
  }

  return(pstr_mots);
}

// Fonction qui libère l'espace mémoire alloué pour un tableau de cases à deux dimensions
void freeTab2D(char** pstr_mots, int int_nbMots)
{
  // Déclaration des variables
  int int_i; //iterrateur de boucle

  // On libère la mémoire allouée pour chaque sous tableau
  for(int_i = 0; int_i < int_nbMots; int_i ++){
    free(pstr_mots[int_i]);
  }
  free(pstr_mots);
}

// Fonction qui copie une chaîne de caractères
char* copieChaine(char* str_mot, int int_n)
{
  // Déclaration des variables
  char* str_res; //chaîne de caractères

  // On alloue la mémoire pour la chaîne
  str_res = malloc(sizeof(char)*(int_n+1));
  if(str_res==NULL){
    fprintf(stderr, "problème d'alloc\n");
    exit(1);
  }

  // On copie la chaîne
  strcpy(str_res, str_mot);

  return(str_res);
}

