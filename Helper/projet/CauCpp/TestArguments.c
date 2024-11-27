#include  <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
  char nomFichier[100], nom[100], nom1[100];
  int num;
  FILE *fich;

  if (argc != 4)
  {
    fprintf(stderr,"USAGE : TestArguments nomFichier nom num \n");
    exit(0);
  }
#if 0
  strcpy(nom, argv[1]);
  num  = atoi(argv[2]);
#endif
  strcpy(nomFichier, *++argv);
  strcpy(nom, *++argv);
  num  = atoi(*++argv);
  fprintf(stderr,"Recupere : %s %s %d\n",nomFichier, nom, num);

  /* --- Ouverture du Fichier en Ecriture --- */
#if 0
  fich = fopen (nomFichier,"w");
  if (fich == NULL)
  {
    fprintf(stderr,"Erreur d'Ouverture \n");
    exit(0);
  }
#endif
  /* --- Ouverture Fichier en Ecriture --- */
  if ((fich = fopen (nomFichier,"w")) == NULL)
  {
    fprintf(stderr,"Erreur d'Ouverture \n");
    exit(0);
  }
  /* --- Ecriture --- */
  fprintf(fich,"Type de Fichier:\n%s %d", nom, num);
  fclose(fich);

  /* --- Ouverture Fichier en Lecture --- */
  if ((fich = fopen (nomFichier,"r")) == NULL)
  {
    fprintf(stderr,"Erreur d'Ouverture \n");
    exit(0);
  }
  /* --- Lecture --- */
  fgets(nom, 99, fich);
  fprintf (stderr,"Premiere Ligne : |%s| \n", nom);
  
  num = 0;
  fgets(nom, 99, fich);
  sscanf (nom,"%s %d", nom1, &num);
  fprintf (stderr,"Secone Ligne : %s %d \n", nom1, num);
  
  return EXIT_SUCCESS;
}




