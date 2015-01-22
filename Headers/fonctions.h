#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#define DECALAGE 5
#define TAILLE_POLYNOME 1024

typedef struct monome{
    float coeff;
    int exposant;
}monome;

int estPresentDans(monome toTest, monome * polynome, int taillePolynome);
int valideMenu(char p);
int estTrie(monome * P, int start, int stop);
int placerPivot(monome * P, int start, int stop);

double eval(monome * polynome, double x);

char menu();

void crypt(char *p);
void exercice1();
void printChoice();
void displayMonome(monome m);
void displayFirstMonome(monome m);
void displayPolynome(monome * P, int tailleP);
void triPolynome(monome * P, int start, int stop);
void ajouterTaillePolynome(monome * P, int i);

monome saisieMonome();
monome * saisiePolynome();
monome * suppressionDoublons(monome * polynome, int * taillePolynome);
monome * entrezPolynome();

#endif // FONCTIONS_H_INCLUDED
