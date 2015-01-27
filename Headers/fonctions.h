#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#define DECALAGE 5
#define TAILLE_POLYNOME 1024
#define DEBUG

typedef struct monome{
    float coeff;
    int exposant;
}monome;

char menu(void);
void printChoice(void);
int valideMenu(char p);

void exercice1(void);
void crypt(char* p);

void question1(void);
void saisie(monome* p, int* taille);
monome saisieMonome(void);
void saisiePolynome(monome* Polynome, int* i);

void question2(void);
void suppressionDoublons(monome* polynome, int* taillePolynome);

void question3(void);
void triPolynome(monome* P, int start, int stop);
int estPresentDans(monome toTest, monome* polynome, int taillePolynome);
int estTrie(monome* P, int start, int stop);
int placerPivot(monome* P, int start, int stop);

void question4(void);
void displayMonome(monome m);
void displayFirstMonome(monome m);
void displayPolynome(monome * P, int tailleP);

void question5(void);
void ajouterTaillePolynome(monome* P, int i);
double eval(monome* polynome, double x);

void concatenerPolynome(char* chaine, char* out);
monome premierMonome(char* chaine, int* length);
void entrezPolynome(void);
int estUnMonomeValide(char* chaine);
int nbrOccChar(char* chaine, char c);
monome extraitMonome(char* chaine);
/*void estUnExposant(char* string, int* degres);
int estUnNombre(char c);
int estUnSep(char c);*/

#endif // FONCTIONS_H_INCLUDED
