/*
 -----------------------------------------------------------------------------------
 Nom du fichier : <nom du fichier>.<x> (x = h ou c)
 Auteur(s)      : <pr�nom> <nom>
 Date creation  : <jj.mm.aaaa>

 Description    : <� compl�ter>

 Remarque(s)    : <� compl�ter>

 Compilateur    : Mingw-w64 gcc 11.2.0 
 -----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define MAX_BILLES 30000
#define MIN_BILLES 1000
#define MAX_RANGEE 20
#define MIN_RANGEE 10
#define MAX_SAISIE 6
#define MAX_DISPLAY 5
#define TAILLE_HIST 15
#define ERROR_MSG "Saisie incorrecte. Veuillez SVP recommencer.\n"

#define _STR(x) #x
#define STR(x) _STR(x)

void vider_Buffer(){
	scanf("%*[^\n]");
	getchar();
}


int main(void) {
	
	const uint8_t DECALAGE = (MAX_DISPLAY + 1)/2;
	uint32_t nbr_billes, nbr_rangee;
	do{
		printf("Entrez le nombre de billes [%d - %d] : ",MIN_BILLES, MAX_BILLES);
	}while((!(scanf("%" STR(MAX_SAISIE) "u%*[^\n]",&nbr_billes)) ||
		   nbr_billes > MAX_BILLES || nbr_billes < MIN_BILLES) &&
			(vider_Buffer(),printf( ERROR_MSG),1));
	
	do{
		printf("Entrez le nombre de rangees de compteurs [%d - %d]",MIN_RANGEE,
				 MAX_RANGEE);
	}while((!(scanf("%" STR(MAX_SAISIE)"u%*[^\n]",&nbr_rangee)) ||
	        nbr_rangee > MAX_RANGEE || nbr_rangee < MIN_RANGEE) &&
	       (vider_Buffer(),printf( ERROR_MSG),1));
	
	// Display Array as pyramid
	nbr_rangee = 4;
	uint32_t tab[] = {1000,2000,3000,4000,5000,6000,1799,1800,1100,00};
	for(uint32_t i = 0; i < nbr_rangee; i++){
		for(uint32_t j = 0; j < i+1; j++){
			printf("%*d ",MAX_DISPLAY + (j?0:((nbr_rangee- i)* DECALAGE))  ,tab[i*
			(i+1)/2+j]);
		}
		printf("\n");
	}
	
	// Get max value
	uint32_t* ptr = (tab + (nbr_rangee-1)*(nbr_rangee)/2);
	uint32_t max = 0;
	for(int i = 0;i < nbr_rangee; i++){
		if(*(ptr+i) > max) max = *(ptr +i);
	}
	
	// Affichage Histogramme
	for(uint32_t etage = TAILLE_HIST; etage; etage--){
		for(int i = 0;i < nbr_rangee; i++) printf(" %*c",MAX_DISPLAY ,
			(round(*(ptr+i)/((double)max/ TAILLE_HIST)) >=(etage))?'*':' ');
		printf("\n");
	}
	
	
   return EXIT_SUCCESS;
}