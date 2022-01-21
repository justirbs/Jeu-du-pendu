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
        printf("Nombre de coups : %d\nIl vous reste %d erreurs possibles\n", int_nbCoups, 11 - int_nbErreurs);
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

    /*
    J'ai codé toutes les fonctions relatives à la sauvegarde du score.
    Cependant, je n'arrive pas à résoudre un "segmentation fault" apparement dû à mon utilisation de la fonction getline().
    */ 
    //score(11 - int_nbErreurs);

    /* A la place j'ai codé un fonction qui me permet d'écrire le score dans un fichier sans le comparer au meilleur score */
    score2(11 - int_nbErreurs);
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
void score(int int_essaisRestants)
{
    char ** pstr_lignes; // Tableau de tableau de caractères
    char* str_pseudo; // Pseudo saisi
    int int_retour; // Retour de fonction
    size_t uint_nb; // Taille du fichier
    int int_nbLignes; // Nombre de lignes du fichier

    // On demande le pseudo à l'utilisateur
	// Initialisation
	str_pseudo = NULL;
	// Demande de la chaîne à l'utilisateur
	printf ("Quel est votre pseudo ?\n");
	int_retour = getline (&str_pseudo, &uint_nb, stdin);
	// Vérification de l'entrée
	if (int_retour == -1) {
		// Si pb de lecture, on affiche un message
		fprintf (stderr, "Problème de lecture : %s\n", strerror (errno));
		exit(EXIT_FAILURE);		
	}

    // On récupère les scores
    pstr_lignes = lireScores();

    // On modifiert le score
    int_nbLignes = modifierScore(str_pseudo, int_essaisRestants, pstr_lignes);

    // On écrit les nouveaux scores dans le fichier
    ecrireScores(pstr_lignes, int_nbLignes);
}

// fonction qui permet de rechercher lire et stocker les scores
char ** lireScores(void){
    FILE* pfil_fic;  // Descripteur de fichier
	int int_retour;  // Valeur de retour des fonctions
	char* str_ligne; // Chaîne de caractères pour la lecture
	size_t uint_nb; // Nombre pour le getline
    int int_nbLignes; // Nombre de lignes dans le fichier
    char ** pstr_lignes; // Tableau de chaînes de caractères
    int int_i; // Iterateur de boucle

	// Ouverture du fichier et test de l'ouverture
	pfil_fic = fopen ("./files/scores.txt", "r");
	if (pfil_fic == NULL) {
		// Si pb alors on affiche un message
		fprintf (stderr, "Problème d'ouverture du fichier : %s\n", strerror (errno));
		// et on quitte
		exit(EXIT_FAILURE);
	}

    // On lit le fichier ligne par ligne
    // On récupère d'abord le nombre de mots dans le fichier
    getline(&str_ligne, &uint_nb, pfil_fic);
    printf("ok lecture nb lignes\n");
    int_nbLignes = atoi(str_ligne);
    
    // on prévoie deux cases supplémentaire pour éventuellement ajouter le pseudo et son score
    pstr_lignes = creerTab(int_nbLignes + 2);

    for(int_i = 0; int_i < int_nbLignes; int_i ++){
        getline(&str_ligne, &uint_nb, pfil_fic);
        printf("%s\n", str_ligne);
        pstr_lignes[int_i] = malloc(sizeof(char)*(strlen(str_ligne)+1));
        strcpy(pstr_lignes[int_i], str_ligne);
    }

    // On remplit les deux dernières cases du tableau
    pstr_lignes[int_nbLignes] = malloc(sizeof(char)*(strlen("\0")+1));
    strcpy(pstr_lignes[int_nbLignes], "\0");
    pstr_lignes[int_nbLignes+1] = malloc(sizeof(char)*(strlen("\0")+1));
    strcpy(pstr_lignes[int_nbLignes+1], "\0");

	// Dans tous les cas, ici on ferme le fichier
	int_retour = fclose (pfil_fic);
	if (int_retour == EOF) {
		// Si il y a un pb de fermeture alors on affiche un message 
		fprintf (stderr, "Problème de fermeture du fichier : %s\n", strerror (errno));
		exit(EXIT_FAILURE);	
	}

    return(pstr_lignes);
}

void ecrireScores(char** tab_scores, int int_nbLignes){
    // Déclaration des variables
    FILE* pfil_fic;  // Descripteur de fichier
    int int_retour;  // Valeur de retour des fonctions
    int int_i; // Iterateur de boucle

    // Ouverture du fichier et test de l'ouverture
	pfil_fic = fopen ("./files/scores.txt", "w");
	if (pfil_fic == NULL) {
		// Si pb alors on affiche un message
		fprintf (stderr, "Problème d'ouverture du fichier : %s\n", strerror (errno));
		// et on quitte
		exit(EXIT_FAILURE);
	}

	// On écrit le nombre de lignes dans le fichier
    int_retour = fprintf (pfil_fic, "%d\n", int_nbLignes); 

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

    // On écrit les scores dans le fichier
    for(int_i = 0; int_i < int_nbLignes; int_i ++){
        int_retour = fprintf (pfil_fic, "%s", tab_scores[int_i]);
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
    }

	// Dans tous les cas, ici on ferme le fichier
	int_retour = fclose (pfil_fic);
	if (int_retour == EOF) {
		// Si il y a un pb de fermeture alors on affiche un message 
		fprintf (stderr, "Problème de fermeture du fichier : %s\n", strerror (errno));
		exit(EXIT_FAILURE);	
	}

    freeTab2D(tab_scores, int_nbLignes);
}

// fonction qui lit le nombre de lignes dans le fichier scores.txt
int nbLignesScores(void)
{
    FILE* pfil_fic;  // Descripteur de fichier
	int int_retour;  // Valeur de retour des fonctions
	char* str_ligne; // Chaîne de caractères pour la lecture
	size_t uint_nb; // Nombre pour le getline
    int int_nbLignes; // Nombre de lignes dans le fichier
	
	// Ouverture du fichier et test de l'ouverture
	pfil_fic = fopen ("./files/scores.txt", "r");
	if (pfil_fic == NULL) {
		// Si pb alors on affiche un message
		fprintf (stderr, "Problème d'ouverture du fichier : %s\n", strerror (errno));
		// et on quitte
		exit(EXIT_FAILURE);
	}

    // On lit le fichier ligne par ligne
    // On récupère d'abord le nombre de mots dans le fichier
    getline(&str_ligne, &uint_nb, pfil_fic);
    int_nbLignes = atoi(str_ligne);

	// Dans tous les cas, ici on ferme le fichier
	int_retour = fclose (pfil_fic);
	if (int_retour == EOF) {
		// Si il y a un pb de fermeture alors on affiche un message 
		fprintf (stderr, "Problème de fermeture du fichier : %s\n", strerror (errno));
		exit(EXIT_FAILURE);	
	}

    return(int_nbLignes);
}

// fonction qui permet chercher le pseudo du joueur
int modifierScore(char *str_pseudo, int int_score, char** tab_score)
{
    // Déclaration des variables
    int int_i; // Iterateur de boucle
    int int_aRemplacer; // booléen qui permet de savoir si on doit remplacer le score ou non
    int int_nbLignes; // Nombre de lignes dans le fichier
    char* str_score; // Chaîne de caractères pour le score

    // Initialisation des variables
    int_aRemplacer = 0;

    // On récupère le nombre de lignes dans le fichier
    int_nbLignes = nbLignesScores();

    // On convertit le score en chaîne de caractères
    str_score = malloc(sizeof(char) * 10);
    sprintf(str_score, "%d", int_score);

    // On parcours le tableau de scores
    for(int_i = 0; int_i < int_nbLignes; int_i ++){
        // Si le pseudo correspond à celui du joueur et que le score est supérieur au score du joueur
        if(strcmp(str_pseudo, tab_score[int_i]) == 0){
            if(int_score > atoi(tab_score[int_i + 1])){
                // On remplace le score
                tab_score[int_i + 1] = str_score;
            }
            // On indique qu'on a trouvé le score
            int_aRemplacer = 1;
        }
    }

    if(!int_aRemplacer){
        // Si on n'a pas trouvé le score, on ajoute le score à la fin du tableau
        tab_score[int_nbLignes] = str_pseudo;
        tab_score[int_nbLignes + 1] = str_score;
        int_nbLignes += 2;
    }

    return(int_nbLignes);
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

// Fonction qui sauvegarde le score dans le fichier
void score2(int int_score){
    // Déclaration des variables
    FILE* pfil_fic;  // Descripteur de fichier
    char* str_pseudo; // Pseudo saisi
    int int_retour; // Retour de fonction
    size_t uint_nb; // Taille du fichier

    // Ouverture du fichier et test de l'ouverture
	pfil_fic = fopen ("./files/scores.txt", "a+");
	if (pfil_fic == NULL) {
		// Si pb alors on affiche un message
		fprintf (stderr, "Problème d'ouverture du fichier : %s\n", strerror (errno));
		// et on quitte
		exit(EXIT_FAILURE);
	}

    // On demande le pseudo à l'utilisateur
	// Initialisation
	str_pseudo = NULL;
	// Demande de la chaîne à l'utilisateur
	printf ("Quel est votre pseudo ?\n");
	int_retour = getline (&str_pseudo, &uint_nb, stdin);
	// Vérification de l'entrée
	if (int_retour == -1) {
		// Si pb de lecture, on affiche un message
		fprintf (stderr, "Problème de lecture : %s\n", strerror (errno));
		exit(EXIT_FAILURE);		
	}

    int_retour = fprintf (pfil_fic, "%s%d", str_pseudo, int_score);

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

    free(str_pseudo);
}

