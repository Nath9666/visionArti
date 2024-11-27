/* Test de la memoire : Pile, Segment de Donnees, Tas */
#include  <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
  char nom [100];
  int num;
  char *nom1 = "Bonjour";

  sprintf(nom,"Bonjour a tous");
  printf("%s \n",nom);
  strcpy(nom,"Bonsoir a tous");
  printf("%s \n",nom);
  printf("%s \n",nom1);
  nom[8] = '\0';
  printf("%s \n",nom);
  
  sprintf(nom, "fichier.txt");
  printf("%s \n",nom);

  nom[strlen(nom) - 4] = '\0';
  printf("%s \n",nom);

  printf ("Entrer mot entier \n");
  scanf("%s %d",nom,&num);
  printf ("Entree clavier : %s : %d\n", nom, num);

  sprintf(nom, "Toto 30");
  sscanf(nom, "%s %d", nom, &num);
  printf ("Entree nom : %s : %d\n", nom, num);


  return EXIT_SUCCESS;
}




