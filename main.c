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
#include <math.h>

//TODO Rechecker les types de données

void Galton(unsigned nbrDeBilles, unsigned nbrDeClou, unsigned* tableauCompteur,
            unsigned* tableauBacBilles);

void afficherTab(const unsigned* tab, size_t taille);

int main(void) {

   unsigned nbrDeClou = 10,
            nbrDeBilles = 1000;

   const size_t TAILLE_TABLEAU_COMPTEUR   = nbrDeClou * (nbrDeClou - 1) / 2;
   const size_t TAILLE_TABLEAU_BAC_BILLES = nbrDeClou + 1;

   unsigned* tableauCompteur  = (unsigned*) calloc(TAILLE_TABLEAU_COMPTEUR,
                                         sizeof(unsigned));
   unsigned* tableauBacBilles = (unsigned*) calloc(TAILLE_TABLEAU_BAC_BILLES,
                                         sizeof(unsigned));

   Galton(nbrDeBilles,nbrDeClou,tableauCompteur, tableauBacBilles);

   afficherTab(tableauBacBilles, nbrDeClou + 1);

   free(tableauBacBilles);
   free(tableauCompteur);

   return EXIT_SUCCESS;
}

void Galton(unsigned nbrDeBilles, unsigned nbrDeClou, unsigned* tableauCompteur,
            unsigned* tableauBacBilles){

   static bool estRandomInitialise = false;

   if(!estRandomInitialise){
      estRandomInitialise = true;
      srand(time(NULL));
   }

   // Boucle faisant tomber les billes
   for(unsigned i = 0u; i < nbrDeBilles; ++i){

      // Boucle faisant tomber une bille
      size_t emplacementBille = 0;
      for(unsigned j = 0u; j < nbrDeClou; ++j){
         emplacementBille += (size_t) (rand() % 2);
      }

      // Sécurité en cas d'overflow on arrête d'augmenter le nbr de bille
      if(tableauBacBilles[emplacementBille] < UINT_MAX)
         ++tableauBacBilles[emplacementBille];
   }
}

void afficherTab(const unsigned* tab, size_t taille){
   printf("[");
   for(size_t i = 0; i < taille; ++i){
      if(i > 0)
         printf(",");
      printf("%u", tab[i]);
   }
   printf("]");
}