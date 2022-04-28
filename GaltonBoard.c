/*
 -----------------------------------------------------------------------------------
 Nom du fichier : GaltonBoard.c
 Auteur(s)      : Loic Brasey et Bastien Pillonel
 Date creation  : 26.04.2022

 Description    : Le programme demande à l'utilisateur de saisir le nombre de
                  billes (1000 - 30000) ainsi que le nombre de rangées de clous
                  (10 - 20) pour simuler une planche de Galton.
                  
						Plus précisément, le programme comptabilise non seulement
						combien de billes terminent leur trajet dans l'un des récipients
						situés au bas de la planche, mais aussi combien d'entre elles
						sont passées à gauche ou à droite de chacun des clous.
						
						Le programme va ensuite afficher la représentation de la planche à
						l'écran et aussi un histogramme des valeurs de la dernière rangée.

 Remarque(s)    : Aucune.

 Compilateur    : Mingw-w64 gcc 11.2.0 
 -----------------------------------------------------------------------------------
*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// Define de constantes
#define MAX_DIGIT_SAISIE 6
#define ERROR_MSG "Saisie incorrecte. Veuillez SVP recommencer.\n"
#define BILLES_MSG "Entrez le nombre de billes"
#define RANGEE_MSG "Entrez le nombre de rangees de compteurs"

// Macro pour convertir la valeur d'un define en une chaine de caractère.
#define _STR(x) #x
#define STR(x) _STR(x)

// Macro pour définir une fonction de saisie pour un type donnée.
// - la fonction vien afficher la chaine de caractère du parametre question.
// - Puis l'intervale admissible de fini par min et max,
// - Ensuite l'utilisateur va devoir faire une saisie
// - En cas de saisie incorrecte ou hors de l'intervale,
//    la fonction affiche error_msg et recommance depuis le début
#define SAISIE_INTERVALE(type,format_print, format_scan,nom)                     \
void saisie_Interval_##nom (type * retour, type min, type max, char* question,   \
									 char* error_msg){                                    \
	assert(min < max);                                                            \
	do{                                                                           \
      printf("%s [%" format_print " - %" format_print "] : ",question,min, max); \
	}while((!(scanf("%" format_scan "%*[^\n]",retour)) ||                         \
				*retour > max || *retour < min) &&                                   \
				(scanf("%*[^\n]"),printf( error_msg),1));                            \
}                                                                                \

// Alias pour le type principal du programme
#define FORMAT_COMPTEUR PRIu32
typedef uint32_t  type_compteur;

// Fonction de saisie via la macro
SAISIE_INTERVALE(type_compteur , FORMAT_COMPTEUR, STR(MAX_DIGIT_SAISIE) FORMAT_COMPTEUR,
                 billes)
SAISIE_INTERVALE(size_t ,"zu", STR(MAX_DIGIT_SAISIE) "zu", size_t)

// Fonction qui prend un nombre de type type_compteur et retourne le nombre de
// digits de ce nombre.
size_t nbr_digit(type_compteur n){
	size_t nbr = 0;
	for(;n>0;nbr++)n/=10;
	return nbr;
}

// Fonction qui génère une planche de Galton de type type_compteur et affiche une
// représentation si désiré
type_compteur* genererPlancheDeGalton(type_compteur nbr_billes,size_t nbr_rangee,
												  bool imprimer){
	assert(nbr_rangee);
	static bool deja_init = false;
	type_compteur*  tab_clous  = calloc(nbr_rangee*(nbr_rangee+1)/2,
	                                                     sizeof(type_compteur));
	if(tab_clous){
		
		// Init.
		*tab_clous = nbr_billes;
		type_compteur* ptr_rangee = tab_clous;
		size_t nbr_digits = 0;
		size_t decalage  = 0;
		if(!deja_init){
			srand(time(NULL));
			deja_init = true;
		}
		
		// Init de variable d'affichage
		if(imprimer){
			nbr_digits = nbr_digit(nbr_billes);
			nbr_digits |= 1; // pour que un nombre de digit pair s'affiche correctement
			decalage = (nbr_digits+ 1)/2;
		}
		
		// Simulation et affichage de la planche de Galton
		for(size_t n_rangee = 0ull; n_rangee < nbr_rangee; ++n_rangee){
			// Mettre le pointeur au début de la ligne
			ptr_rangee += n_rangee;
			for(size_t n_clou = 0ull ; n_clou <= n_rangee; n_clou++) {
				// Determiner la destination des billes si besoin
				if (n_rangee < nbr_rangee - 1) {
					for (type_compteur bille = 0; bille < ptr_rangee[n_clou]; ++bille) {
						ptr_rangee[n_rangee + 1 + n_clou + rand() % 2 ]++;
					}
				}
				// Afficher le clou actuel
				if(imprimer)printf("%*" FORMAT_COMPTEUR " " ,nbr_digits + (n_clou?0:(
					(nbr_rangee-n_rangee-1)*decalage)), ptr_rangee[n_clou]);
			}
			if(imprimer)printf("\n");
		}
	}
	return tab_clous;
}

// Fonction qui prend un tableau en paramètre et qui génére un histogramme
// des valeurs du tableau.
void histogramme(const type_compteur*  tab, size_t nbr_elements, size_t taille,
					  size_t espacement){
	
	// Trouver la valeur max du tableau
	type_compteur max = 0;
	for(size_t i = 0;i < nbr_elements; i++){
		if(tab[i] > max) max = tab[i];
	}
	
	// Affichage de l'histogramme
	espacement |= 1; // pour qu'un nombre de digit pair s'affiche correctement
	for(size_t etage = taille; etage; etage--){
		for(size_t i = 0;i < nbr_elements; i++)
			printf("%*c ",espacement ,(round(tab[i] / (max /(double) taille)) >=
			(double)(etage)) ? '*' : ' ');
		printf("\n");
	}
}

int main(void) {
	
	// Initialisation et Constante
	const type_compteur  MAX_BILLES  = 30000,
								MIN_BILLES  = 1000;
	const size_t         MAX_RANGEE  = 20,
								MIN_RANGEE  = 10,
								TAILLE_HIST = 15;
	type_compteur        nbr_billes;
	size_t				   nbr_rangee;
	
	// Saisie du nombre de billes
	saisie_Interval_billes(&nbr_billes , MIN_BILLES, MAX_BILLES, BILLES_MSG,
								  ERROR_MSG);
	
	// Saisie du nombre de rangées
	saisie_Interval_size_t(&nbr_rangee, MIN_RANGEE, MAX_RANGEE, RANGEE_MSG,
								  ERROR_MSG);
	
	// Génération et impression de la planche de Galton
	printf("\n");
	type_compteur* galtonBoard = genererPlancheDeGalton(nbr_billes,nbr_rangee,true);
	if(!galtonBoard)return EXIT_FAILURE;
	
	
	// Affichage de l'histogramme de la dernière ligne
	printf("\n");
	histogramme(galtonBoard +(nbr_rangee -1)*nbr_rangee/2,nbr_rangee,TAILLE_HIST,
	            nbr_digit(*galtonBoard));
	
	// Libération de la mémoire et fin de programme
	free(galtonBoard);
   return EXIT_SUCCESS;
}