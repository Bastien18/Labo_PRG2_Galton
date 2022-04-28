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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

// Constantes
#define MAX_BILLES 30000
#define MIN_BILLES 1000
#define MAX_RANGEE 20
#define MIN_RANGEE 10
#define MAX_SAISIE 6
#define MAX_DISPLAY 5
#define TAILLE_HIST 15
#define ERROR_MSG "Saisie incorrecte. Veuillez SVP recommencer.\n"

// Macro pour convertir la valeur d'un define est chaine de caractère.
#define _STR(x) #x
#define STR(x) _STR(x)

// Fonction pour vider le buffer après une saisie.
void vider_Buffer(){
	scanf("%*[^\n]");
	getchar();
}

int main(void) {
	
	// Initialisation et Constante
	const uint8_t DECALAGE = (MAX_DISPLAY + 1)/2;
	uint32_t nbr_billes, nbr_rangee;
	
	// Saisie du nombre de billes
	do{
		printf("Entrez le nombre de billes [%d - %d] : ",MIN_BILLES, MAX_BILLES);
		
		// Verifie que la saisie est correcte et réagit en cas d'erreur
	}while((!(scanf("%" STR(MAX_SAISIE) "u%*[^\n]",&nbr_billes)) ||
		   nbr_billes > MAX_BILLES || nbr_billes < MIN_BILLES) &&
			(vider_Buffer(),printf( ERROR_MSG),1));
	
	// Saisie du nombre de rangées
	do{
		printf("Entrez le nombre de rangees de compteurs [%d - %d]",MIN_RANGEE,
				 MAX_RANGEE);
		// Verifie que la saisie est correcte et réagit en cas d'erreur
	}while((!(scanf("%" STR(MAX_SAISIE)"u%*[^\n]",&nbr_rangee)) ||
	        nbr_rangee > MAX_RANGEE || nbr_rangee < MIN_RANGEE) &&
	       (vider_Buffer(),printf( ERROR_MSG),1));
	
	
	// allocation de notre planche de Galton
	uint32_t* const tab_clous  = (uint32_t* const)calloc(nbr_rangee*(nbr_rangee+1)/2,
	                                                sizeof(uint32_t));
	
	// Préparation pour la simulation
	*tab_clous = nbr_billes;
	uint32_t* ptr_rangee = tab_clous;
	srand(time(NULL));
	printf("\n");
	
	// Simulation et affichage de la planche de Galton
	for(unsigned n_rangee = 0u; n_rangee < nbr_rangee; ++n_rangee){
		// Mettre le pointeur au début de la ligne
		ptr_rangee += n_rangee;
		for(unsigned n_clou = 0 ; n_clou <= n_rangee; n_clou++) {
			// Determiner la destination des billes si besoin
			if (n_rangee < nbr_rangee - 1) {
				for (unsigned bille = 0u; bille < ptr_rangee[n_clou]; ++bille) {
					ptr_rangee[n_rangee + 1 + n_clou + rand() % 2]++;
				}
			}
			// Afficher le clou actuel
			printf("%*d ",MAX_DISPLAY + (n_clou?0:((nbr_rangee- n_rangee-1)*
			DECALAGE)), ptr_rangee[n_clou]);
		}
		printf("\n");
	}
	
	// Trouver la valeur max de la dernière rangée
	uint32_t max = 0;
	for(int i = 0;i < nbr_rangee; i++){
		if(ptr_rangee[i] > max) max = ptr_rangee[i];
	}
	
	// Affichage de l'histogramme
	printf("\n");
	for(uint32_t etage = TAILLE_HIST; etage; etage--){
		for(int i = 0;i < nbr_rangee; i++) printf("%*c ",MAX_DISPLAY ,
		(round(*(ptr_rangee + i) / ((double)max / TAILLE_HIST)) >= (etage)) ? '*' : ' ');
		printf("\n");
	}
	
	// Libération de la mémoire et fin de programme
	free(tab_clous);
   return EXIT_SUCCESS;
}