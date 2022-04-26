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
#include <stdbool.h>
#include <time.h>

//TODO Rechecker les types de données

void Galton(unsigned nbrDeBilles, unsigned nbrDeClou, unsigned* tableauCompteur,
            unsigned* tableauBacBilles);

int main(void) {
   return EXIT_SUCCESS;
}

void Galton(unsigned nbrDeBilles, unsigned nbrDeClou, unsigned* tableauCompteur,
            unsigned* tableauBacBilles){

   static bool estRandomInitialise = false;

   if(!estRandomInitialise){
      estRandomInitialise = true;
      srand(time(NULL));
   }

   const size_t TAILLE_TABLEAU_COMPTEUR   = nbrDeClou * (nbrDeClou - 1) / 2;
   const size_t TAILLE_TABLEAU_BAC_BILLES = nbrDeClou + 1;



   tableauCompteur  = (unsigned*) calloc(TAILLE_TABLEAU_COMPTEUR,
                                                  sizeof(unsigned ));
   tableauBacBilles = (unsigned*) calloc(TAILLE_TABLEAU_BAC_BILLES,
                                                   sizeof(unsigned ));
}