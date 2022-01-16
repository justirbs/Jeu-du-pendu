/*!
* \file pendu.c
*
* \brief le code des fonctions relatives au jeu du pendu
*
* \author Justine Ribas <ribasjusti@cy-tech.fr>
* \version 0.1
* 
* \date 11 janvier 2022
*/

/*inclusion des entêtes de librairie*/
#include "pendu.h"


/*code des fonctions*/

// fonction qui permet de tirer un mot au hasard dans le fichier
char* motAleatoire(char *nomFichier)
{
    FILE* pfil_fic;  // Descripteur de fichier
	int int_retour;  // Valeur de retour des fonctions
	size_t uint_nb; // Nombre pour le getline
    char *str_ligne; // Ligne lue
    int int_nbMots; // Nombre de mots dans le fichier
    char** pstr_mots; // Tableau de mots
    int int_i; // Iterateur de boucle
    char* str_res; // Mot tiré au hasard
	
	// Ouverture du fichier et test de l'ouverture
	pfil_fic = fopen (nomFichier, "r");
	if (pfil_fic == NULL) {
		// Si pb alors on affiche un message
		fprintf (stderr, "Problème d'ouverture du fichier : %s\n", strerror (errno));
		// et on quitte
		exit (EXIT_FAILURE);
	}

    // On lit le fichier ligne par ligne
    // On récupère d'abord le nombre de mots dans le fichier
    getline(&str_ligne, &uint_nb, pfil_fic);
    int_nbMots = atoi(str_ligne);
    
    pstr_mots = creerTab(int_nbMots);

    for(int_i = 0; int_i < int_nbMots; int_i ++){
        getline(&str_ligne, &uint_nb, pfil_fic);
        pstr_mots[int_i] = malloc(sizeof(char)*(strlen(str_ligne)+1));
        strcpy(pstr_mots[int_i], str_ligne);
    }

    // On tire au hasard un mot dans le tableau
    srand(time(NULL));
    str_res = copieChaine(pstr_mots[rand()%int_nbMots], strlen(pstr_mots[rand()%int_nbMots]));

	// Dans tous les cas, ici on ferme le fichier
	int_retour = fclose (pfil_fic);
	if (int_retour == EOF) {
		// Si il y a un pb de fermeture alors on affiche un message 
		fprintf (stderr, "Problème de fermeture du fichier : %s\n", strerror (errno));
		exit (EXIT_FAILURE);
	}

    freeTab2D(pstr_mots, int_nbMots);

    // On retourne le mot tiré au hasard
    return(str_res);
}


// fonction qui permet de lancer une partie de pendu
void jouePendu(char *str_mot)
{
    // Déclaration des variables
    char str_lettre; // Lettre saisie
    int int_nbErreurs = 0; // Nombre d'erreurs
    char* str_motTmp; // Mot temporaire
    int int_aGagne; // Booléen qui indique si on a gagné ou non
    int int_occurences; // le nombre d'occurences de la lettre jouée dans le mot
    int int_nbCoups; // le nombre de coups effectués

    // Initialisation des variables
    int_nbErreurs = 0;
    int_aGagne = 0;
    int_nbCoups = 0;

    // On copie le mot pour l'afficher à l'écran
    str_motTmp = copieChaine(str_mot, strlen(str_mot));
    for(int int_i = 0; int_i < strlen(str_mot)-2; int_i++){
        str_motTmp[int_i] = '_';
    }

    // On lance la partie
    while(int_aGagne == 0){
        // On affiche le mot à trouver
        system("clear");
        affichagePendu(int_nbErreurs);
        printf("\n\nMot : %s\n", str_motTmp);
        // On demande une lettre
        printf("Nombre de coups : %d\nIl vous reste %d essais\n", int_nbCoups, 11 - int_nbErreurs);
        printf("Les lettres du mot sont toutes en majuscules.\nEntrez une lettre : \n");
        str_lettre = saisirCaractere();
        printf("caractere saisi : %c\n", str_lettre);
        // On joue le tour
        int_occurences = joueLettre(str_mot, str_motTmp, str_lettre);
        if(int_occurences == 0){
            int_nbErreurs += 1;
        }
        int_nbCoups += 1;
        // On vérifie si on a gagné ou non
        int_aGagne = aTrouve(str_mot, str_motTmp, int_nbErreurs);
        if(int_aGagne != 0){
            system("clear");
            if(int_aGagne == 1){
                printf("%s\nBravo, vous avez gagné en %d coups !\n", str_motTmp, int_nbCoups);
            }
            else{
                affichagePendu(int_nbErreurs);
                printf("Dommage, vous avez perdu !\nLe mot était : %s\n", str_mot);
            }
        }
    }

    // On libère la mémoire
    free(str_motTmp);
    free(str_mot);

    // On sauvegarde le score
    ecrireScore(11 - int_nbErreurs);
}

// fonction qui permet de jouer une lettre
int joueLettre(char *str_mot, char* str_motTemp, char str_lettre)
{
    // Déclaration des variables
    int int_i; // Iterateur de boucle
    int int_res; // le nombre d'occurences dans le mot

    // Initialisation des variables
    int_res = 0;

    // On parcours le mot
    for(int_i = 0; int_i < strlen(str_mot); int_i++){
        if(str_mot[int_i] == str_lettre){
            str_motTemp[int_i] = str_lettre;
            int_res ++;
        }
    }

    return(int_res);
}

// fonction qui permet savoir si le mot est trouvé
int aTrouve(char *str_mot, char* str_motTemp, int int_nbErreur)
{
    // Déclaration des variables
    int int_i; // Iterateur de boucle
    int int_res; // Booléen pour savoir si le mot est trouvé

    // Initialisation des variables
    int_res = 1;

    // On vérifie si il reste des essais
    if(int_nbErreur < 11){
        // On parcours le mot
        for(int_i = 0; int_i < strlen(str_mot); int_i++){
            if(str_mot[int_i] != str_motTemp[int_i]){
                int_res = 0;
            }
        }
    } else {
        int_res = -1;
    }

    return(int_res);
}

// fonction qui permet de sauvegarder le score
void ecrireScore(int int_essaisRestants)
{
    FILE* pfil_fic;  // Descripteur de fichier
	int int_retour;  // Valeur de retour des fonctions
	char* str_pseudo; //Pseudo du joueur
	size_t uint_nb; // Nombre pour le getline
	
	// Ouverture du fichier et test de l'ouverture
	pfil_fic = fopen ("./files/scores.txt", "a+");
	if (pfil_fic == NULL) {
		// Si pb alors on affiche un message
		fprintf (stderr, "Problème d'ouverture du fichier : %s\n", strerror (errno));
		// et on quitte
		exit(EXIT_FAILURE);
	}

	// Ecriture d'une cha�ne demandée à l'utilisateur dans le fichier
	// Initialisation
	str_pseudo = NULL;
	// Demande de la chaîne à l'utilisateur
	printf ("Quel est votre pseudo ?\n");
	int_retour = getline (&str_pseudo, &uint_nb, stdin);
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
		exit(EXIT_FAILURE);		
	}

    // On regarde si l'utilisateur n'avait pas déjà un score, si c'est le cas on prend le max
    if(int_essaisRestants > recherchePseudo(str_pseudo, int_essaisRestants)){
        // écriture de la chaîne dans le fichier
        int_retour = fprintf (pfil_fic, "%s%d\n", str_pseudo, int_essaisRestants);   
    }

	if (int_retour < 0) {
		// Si pb d'ecriture, on affiche un message
		fprintf (stderr, "Problème d'écriture : %s\n", strerror (errno));
		// et on quitte, mais avant on ferme le fichier
		int_retour = fclose (pfil_fic);
		if (int_retour == EOF) {
			// Si il y a un pb de fermeture alors on affiche un message 
			fprintf (stderr, "Problème de fermeture du fichier : %s\n", strerror (errno));
		}
		exit(EXIT_FAILURE);		
	}

	// Dans tous les cas, ici on ferme le fichier
	int_retour = fclose (pfil_fic);
	if (int_retour == EOF) {
		// Si il y a un pb de fermeture alors on affiche un message 
		fprintf (stderr, "Problème de fermeture du fichier : %s\n", strerror (errno));
		exit(EXIT_FAILURE);	
	}
}

// fonction qui permet chercher le pseudo du joueur
int recherchePseudo(char *str_pseudo, int int_score)
{
    FILE* pfil_fic;  // Descripteur de fichier
	int int_retour;  // Valeur de retour des fonctions
	size_t uint_nb; // Nombre pour le getline
    char *str_ligne; // Ligne lue
    int int_res; // Score maximum de l'utilisateur

    int_res = 0;
	
	// Ouverture du fichier et test de l'ouverture
	pfil_fic = fopen ("./files/scores.txt", "r");
	if (pfil_fic == NULL) {
		// Si pb alors on affiche un message
		fprintf (stderr, "Problème d'ouverture du fichier : %s\n", strerror (errno));
		// et on quitte
		exit (EXIT_FAILURE);
	}

    // On lit le fichier ligne par ligne
    while (getline(&str_ligne, &uint_nb, pfil_fic) != EOF) {
        // On vérifie si le pseudo correspond
        if(strcmp(str_ligne, str_pseudo) == 0){
            // Si oui on récupère le score
            fgets (str_ligne, sizeof (str_ligne), pfil_fic);
            if(int_res < atoi(str_ligne)){
                int_res = atoi(str_ligne);
            }
            int_res = atoi(str_ligne + strlen(str_pseudo) + 1);
        }
    }

	// Dans tous les cas, ici on ferme le fichier
	int_retour = fclose (pfil_fic);
	if (int_retour == EOF) {
		// Si il y a un pb de fermeture alors on affiche un message 
		fprintf (stderr, "Problème de fermeture du fichier : %s\n", strerror (errno));
		exit (EXIT_FAILURE);
	}

    return(int_res);
}

// Fonction qui permet d'afficher le nombre d'erreurs graphiquement
void affichagePendu(int int_nbErreurs)
{
    switch (int_nbErreurs)
    {
    case 1:
        printf("\n\n\n\n\n\n\n\n\n_____\n");
        break;
    case 2:
        printf("\n\n |\n |\n |\n |\n |\n |\n |\n_|___\n");
        break;
    case 3:
        printf("\n  _______\n |\n |\n |\n |\n |\n |\n |\n_|___\n");
        break;
    case 4:
        printf("\n  _______\n |/\n |\n |\n |\n |\n |\n |\n_|___\n");
        break;
    case 5:
        printf("\n  _______\n |/      |\n |\n |\n |\n |\n |\n |\n_|___\n");
        break;
    case 6:
        printf("\n  _______\n |/      |\n |      (_)\n |\n |\n |\n |\n |\n_|___\n");
        break;
    case 7:
        printf("\n  _______\n |/      |\n |      (_)\n |       | \n |       |\n |\n |\n |\n_|___\n");
        break;
    case 8:
        printf("\n  _______\n |/      |\n |      (_)\n |       |/\n |       |\n |\n |\n |\n_|___\n");
        break;
    case 9:
        printf("\n  _______\n |/      |\n |      (_)\n |      \\|/\n |       |\n |\n |\n |\n_|___\n");
        break;
    case 10:
        printf("\n  _______\n |/      |\n |      (_)\n |      \\|/\n |       |\n |        \\\n |\n |\n_|___\n");
        break;
    case 11:
        printf("\n  _______\n |/      |\n |      (_)\n |      \\|/\n |       |\n |      / \\\n |\n |\n_|___\n");
        break;
    default:
        printf("\n\n\n\n\n\n\n\n\n\n");
        break;
    }
}