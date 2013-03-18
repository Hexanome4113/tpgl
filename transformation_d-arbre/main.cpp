/* 3.5.2 Traitement des templates
/*
/**/

/* --- Includes --- */
#include <iostream>




int main(){
   /* Algorithme :
   /*
   /* Partir de la racine de l'arbre XML
   /* Pour chaque élément :
   /* - Parcourir le XSLT à la recherche d'un template à utiliser
   /* # Si on en trouve un :
   /*   - Ecrire le texte se trouvant AVANT la balise <apply-templates/>
   /*   - Faire la récursivité (voir ci-dessous)
   /*   - Ecrire le texte se trouvant APRES la balise <apply-templates/>
   /* # Si on en trouve pas :
   /*   - Faire seulement la récursivité
   /*
   /* Pour la récursivité, on parcourt le noeud. Pour chaque enfant :
   /* # Si c'est un texte, on l'écrit
   /* # Si c'est un noeud non-textuel, on répète les étapes précédentes
   /**/

}
