/*! \file Programmation/2007-2008/Cours/Cours10/ffichier.c
 *  \author Florent Devin <florent.devin@eisti.fr>
 *  \version 0.1
 *  \date Thu Dec 13 16:54:36 2007
 *
 *  \brief Manipulation haut niveau de fichier
 *
 *
 */

/*! \page ""
 */
#define _GNU_SOURCE

// Inclusion des entêtes de librairie
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
// Définition de constantes
/*! \def PROG_OK
 *	Constante pour définir une terminaison correcte
 */
#define PROG_OK 0


/*! \def ERREUR_SYS
 *  Constante pour définir une terminaison par erreur
 *  système
 */
#define ERREUR_SYS -1

/*! \fn int main (int argc, char** argv)
 *  \author Florent Devin <florent.devin@eisti.fr>
 *  \version 0.1
 *  \date Thu Dec 13 16:54:56 2007
 *
 *  \brief Fonction principale
 *
 *
 * \param argc : Nombre d'argument
 * \param argv : Tableau des arguments
 * \return 0 : le programme doit se terminer normalement
 *
 * \remarks 
 */

int main (int argc, char** argv) {
 	FILE* pfil_fic;  // Descripteur de fichier
	int int_retour;  // Valeur de retour des fonctions
	char* str_chaine; //Chaîne à écrire
	size_t uint_nb; // Nombre pour le getline
	
	// Ouverture du fichier et test de l'ouverture
	pfil_fic = fopen ("toto", "w+");
	if (pfil_fic == NULL) {
		// Si pb alors on affiche un message
		fprintf (stderr, "Problème d'ouverture du fichier : %s\n", strerror (errno));
		// et on quitte
		return (ERREUR_SYS);
	}


	// Ecriture d'une chaîne demandée à l'utilisateur dans le fichier
	// Initialisation
	str_chaine = NULL;
	// Demande de la chaîne à l'utilisateur
	printf ("Quelles informations voulez vous sauvegarder : ");
	int_retour = getline (&str_chaine, &uint_nb, stdin);
	// Vérification de l'entrée
	if (int_retour == -1) {
		// Si pb de lecture, on affiche un message
		fprintf (stderr, "Problème de lecture : %s\n", strerror (errno));
		// et on quitte, mais avant on ferme le fichier
		int_retour = fclose (pfil_fic);
		if (int_retour == EOF) {
			// Si il y a un pb de fermeture alors on affiche un message 
			fprintf (stderr, "Problème de fermeture du fichier : %s\n", strerror (errno));
		}
		return (ERREUR_SYS);		
	}

	// Écriture de la chaîne dans le fichier
	int_retour = fwrite(str_chaine, sizeof (char),  strlen(str_chaine), pfil_fic);

	// ATTENTION A LA TAILLE : EXEMPLE
	//int_retour = fwrite(str_chaine, sizeof (char),  strlen(str_chaine)*2, pfil_fic);
    
	//fprintf(pfil_fic, "%s", str_chaine);
	//fprintf(pfil_fic, "%d + %d = %d", 15, 102, 15+102);

	if (int_retour != strlen(str_chaine)) {
		// Si pb d'ecriture, on affiche un message
		fprintf (stderr, "Problème d'écriture : %s\n", strerror (errno));
		// et on quitte, mais avant on ferme le fichier
		int_retour = fclose (pfil_fic);
		if (int_retour == EOF) {
			// Si il y a un pb de fermeture alors on affiche un message 
			fprintf (stderr, "Problème de fermeture du fichier : %s\n", strerror (errno));
		}
		return (ERREUR_SYS);		
	}

	// Dans tous les cas, ici on ferme le fichier
	int_retour = fclose (pfil_fic);
	if (int_retour == EOF) {
		// Si il y a un pb de fermeture alors on affiche un message 
		fprintf (stderr, "Problème de fermeture du fichier : %s\n", strerror (errno));
		return (ERREUR_SYS);
	}

	//Fin du programme, Il se termine normalement, et donc retourne 0
	return (PROG_OK);
}
