#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

char menu(void)//Appelle les fonctions correspondantes aux questions
{
    char selection = 'a';

    while(!valideMenu(selection))//tant que la selection n'est pas valide
    {
        printf("\n");
        printChoice();//reafficher le menu
        fflush(stdin);
        selection = getchar();
        fflush(stdin);
    };

    switch (selection)//appel des questions
    {
    case '0'://quitter le menu
        system("exit");
        break;
    case '1'://appelle l'exo 1
        exercice1();
        break;
    case '2'://appelle la question 2
        question1();
        break;
    case '3':
        question2();
        break;
    case '4':
        question3();
        break;
    case '5':
        question4();
        break;
    case '6':
        question5();
        break;
    case '7':
        entrezPolynome();
        break;
    default://cas par défaut
        exit(-1);
        break;
    }
    return selection;
}

int valideMenu(char p)//Securise l'entrée du menu
{
    return ((p >= '0') && (p <=     '7'));
}

void printChoice(void)//affiche le menu
{
    printf("****** MENU - DM1 ******\n\n");
    printf("\n1- Exercice 1\n");
    printf("2- Saisie de polynome\n");
    printf("3- Reduction du polynome\n");
    printf("4- Tri par degrès croissant\n");
    printf("5- Affichage d'un polynome\n");
    printf("6- Evaluation\n");
    printf("7- Analyseur syntaxique\n");
    printf("0- Exit\n");
    printf("Entrez un nombre pour choisir la question : ");
}

void exercice1(void)//excercice 1
{
    char message[] = "Test de fonctionnement, AbCdE";//chaine de test

    printf("\n%s\n", message);//affiche la chaine de test

    int i = 0;

    while(message[i] != '\0')//tant qu'on atteint pas la fin de la chaine
    {
        crypt(&message[i]);//on crypte le caratère
        i++;
    }

    printf("%s\n", message);//affiche la chaine cryptée
}

void crypt(char* p)//fonction de cryptage d'un caractère
{
    if (((*p) >= 'A') && ((*p) <= 'Z'))//Mofication d'une majuscule
    {
        *p=(((*p)-'A') + DECALAGE) %26 + 'A';/*on restreint p entre 0 et 25
        puis on y ajoute le décalage, on restreint la valeur entre 0 et 25 puis on
        rajoute 'A' pour le code ASCII*/
    }
    if (((*p) <= 'z') && ((*p) >= 'a'))//miniscule
    {
        *p=(((*p) - 'a') + DECALAGE) %26 + 'a';
    }
}

void question1(void)
{
    printf("\n\nQuestion 1 - Saisie polynome\n");

    monome * p = malloc(0*sizeof(monome));
    int taille = 0;
    saisie(p, &taille);

    displayPolynome(p, taille);//affichage du polynome saisie

    free(p);
}

void saisie(monome* polynome, int* taille)
{
    saisiePolynome(polynome, taille);
}

void question2(void)
{
    monome * p = malloc(0*sizeof(monome));
    int taille = 0;
    saisie(p, &taille);

    suppressionDoublons(p, &taille);//suppression des doublons et des zéros

    printf("\nPolynome reduit:\n");

    displayPolynome(p, taille);//affichage du polynome réduit

    free(p);
}

void question3(void)
{
    monome * p = malloc(0*sizeof(monome));
    int taille = 0;
    saisie(p, &taille);

    suppressionDoublons(p, &taille);

    triPolynome(p, 0, taille);
    printf("\ntableau trié:\n");
    displayPolynome(p, taille);

    free(p);
}

void question4(void)
{
    question3();
}

void question5(void)
{
    monome * p = malloc(0*sizeof(monome));
    int taille = 0;
    double x;
    saisie(p, &taille);

    suppressionDoublons(p, &taille);

    triPolynome(p, 0, taille);
    printf("\n");
    displayPolynome(p, taille);

    ajouterTaillePolynome(p, taille);

    printf("Entrez le nombre a évaluer :");
    scanf("%lf", &x);

    printf("\nP(x)= %.2f\n", eval(p, x));

    free(p);
}

void saisiePolynome(monome* Polynome, int* i)//Saisie d'un polynome
{
    *i=0;

    monome buffer;

    do
    {
        buffer = saisieMonome();//on remplit un monome

        if(buffer.exposant != -1)//on vérifie qu'il ne correspond pas a la condition de sortie
        {
            (*i)++;
            Polynome = (monome*) realloc (Polynome, (*i)*sizeof(monome));//on augmente de 1 la taille du polynome
            Polynome[(*i)-1] = buffer;//qu'on remplit avec le buffer
        }
    }
    while(buffer.exposant != -1); //condition de sortie exposant==-1
}

monome saisieMonome(void)
{
    monome out;

    printf("Saisir un Monome: entrez -1 pour quitter");

    do
    {
        printf("\nDegres : ");
        scanf("%d", &out.exposant);
        printf("\nCoefficient : ");
        scanf("%f", &out.coeff);
    }
    while(out.exposant < -1); //une erreur si l'exposant est négatif

    return out;
}

//renvoie un monome* de taille taille polynome
void suppressionDoublons(monome* polynome, int* taillePolynome)
{
    int i, j = 0, estPresent = 0;

    monome * polynomeBuffer = malloc(0*sizeof(monome));

    for(i = 0; i < *taillePolynome; i++)//Suppressions des doublons
    {
        //verifie que polynome de i est présent dans polBuffer, et renvoie sa position,
        // -1 le cas échéant
        estPresent = estPresentDans(polynome[i], polynomeBuffer, j);

        if(estPresent != -1)//si présent
        {
            polynomeBuffer[estPresent].coeff += polynome[i].coeff;//on additionne les coeff
        }
        else if(polynome[i].coeff)//si le coeff n'est pas nul
        {
            j++;
            polynomeBuffer = (monome *) realloc(polynomeBuffer, j*sizeof(monome));//cré un nouvelle case dans buffer
            polynomeBuffer[j-1] = polynome[i];//la remplit avec le monome
        }
    }

    polynome = (monome *) realloc(polynome, 0*sizeof(monome));

    int k = 0;

    for(i = 0; i < j; i++)//Suppression des zéros
    {
        if(polynomeBuffer[i].coeff != 0)//si le coeff est non nul
        {
            k++;
            polynome = (monome *) realloc(polynome, k*sizeof(monome));//cré un nouvelle case dans buffer
            polynome[k-1] = polynomeBuffer[i];//la remplit avec le monome
        }
    }

    *taillePolynome = k;//la taille du poly de sortie est de k

    free(polynomeBuffer);//libère le buffer
}

int estPresentDans(monome toTest, monome* polynome, int taillePolynome)
{
    int i;
    if(polynome != NULL)//si le pointeur est non NULL
    {
        for(i = 0; i < taillePolynome; i++)
        {
            if (toTest.exposant == polynome[i].exposant)//si on déjà le degres correspondant
                return i;//renvoyer sa pos dans le tableau
        }
    }
    return -1;
}

//affichage d'un monome
void displayMonome(monome m)
{
    if(m.exposant == 0)
    {
        if(m.coeff!=0)
            printf("%+.2f ", m.coeff);
    }
    else
    {
        if (m.exposant == 1)
        {
            if(m.coeff == 1)
                printf(" + X ");
            else
            {
                if(m.coeff == -1)
                    printf(" - X ");
                else
                    printf("%+.2f * X ", m.coeff);
            }
        }
        else
        {
            if(m.coeff == 1)
                printf(" + X^%d ",m.exposant);
            else
            {
                if(m.coeff == -1)
                    printf(" - X^%d ",m.exposant);
                else
                    printf("%+.2f * X^%d ", m.coeff,m.exposant);
            }
        }
    }
}

void displayFirstMonome(monome m)
{
    if(m.exposant == 0)
    {
        if (m.coeff != 0)
            printf("%.2f ", m.coeff);
    }
    else
    {
        if (m.exposant == 1)
        {
            if(m.coeff == 1)
                printf(" X ");
            else
            {
                if(m.coeff == -1)
                    printf("- X ");
                else
                    printf("%.2f * X ", m.coeff);
            }
        }
        else
        {
            if(m.coeff == 1)
                printf("X^%d ",m.exposant);
            else
            {
                if(m.coeff == -1)
                    printf("- X^%d ",m.exposant);
                else
                    printf("%.2f * X^%d ", m.coeff,m.exposant);
            }
        }
    }
}

//affichage d'un polynome
void displayPolynome(monome* P, int tailleP)
{
    int i;
    if(!tailleP)
        printf("\nPolynome vide");
    else
    {
        printf("\nP = ");
        displayFirstMonome(P[0]);
    }

    for(i = 1; i < tailleP; i++)
    {
        displayMonome(P[i]);
    }
}

//tri par dichotomie recursive
void triPolynome(monome* P, int start, int stop)
{

    if (!estTrie(P, start, stop))//si le tableau n'est pas déjà trié
    {
        int pivot = placerPivot(P, start, stop);//place la valeur pivot et renvoie sa position

        if(!estTrie(P, start, pivot))//si le sous tableau n'est pas trié
            triPolynome(P, start, pivot);//on appelle la fonction entre start et pivot

        if(!estTrie(P, pivot+1, stop))//idem
            triPolynome(P, pivot+1, stop);//mais entre pivot+1 et stop
    }
}

//verifie qu'un polynome soit trié
int estTrie(monome* P, int start, int stop)
{
    int i;

    for(i = start; i < stop-1; i++)
    {
        if (P[i].exposant > P[i+1].exposant)
            return 0;
    }
    return 1;
}

//place le pivot et échange les valeurs gauche et droite
int placerPivot(monome* P, int start, int stop)
{
    int i,j, out=start;//on commence le compteur a start

    for(i = start+1; i < stop; i++)
    {
        if(P[start].exposant > P[i].exposant)
            out++;
    }

    monome buffer = P[start];//on échange les valeur de la première case
    P[start] = P[out];//avec sa bonne position
    P[out] = buffer;

    for(i = start; i < out; i++)
    {
        if(P[i].exposant > P[out].exposant)
        {
            j = out + 1;
            while((P[j].exposant > P[out].exposant) && (j < stop))
                j++;

            buffer = P[i];
            P[i] = P[j];
            P[j] = buffer;
        }
    }

    return out;
}

void ajouterTaillePolynome(monome* P, int i)
{
    P = (monome *) realloc(P, (i+1)*sizeof(monome));
    P[i].exposant = -1;
    P[i].coeff = i;
    printf("\ni=%d\n",i);
}

double eval(monome* Polynome, double x)
{
    double xPuissance = 1, out = 0;
    int puissance = 0, i, cptTaille = 0;

    while(Polynome[cptTaille].exposant != -1)
    {
        cptTaille++;
    }

    for(i = 0; i < cptTaille; i++)
    {
        if(Polynome[i].exposant)
        {
            while(puissance < Polynome[i].coeff)
            {
                puissance++;
                xPuissance *= x;
            }
        }
        out += (xPuissance * Polynome[i].coeff);
    }

    return out;
}

//saisie manuelle d'une phrase de type polynome
//monome * entrezPolynome()
void entrezPolynome(void)
{
    monome* polynome = NULL;
    polynome = malloc(0*sizeof(monome));

    int taille = 0;
    char buffer[TAILLE_POLYNOME]= {0};

    printf("\nEntrez un polynome :\n");
    fflush(stdin);
    gets(buffer);
    fflush(stdin);

    char* saisie = malloc(0*sizeof(char));

    concatenerPolynome(buffer, saisie);

    printf("\nsaisie: %s\n",saisie);

    taille++;
    polynome = (monome*) realloc(polynome, taille*sizeof(monome));
    polynome[taille-1] = premierMonome(saisie);

    printf("\npolynome :\n");
    displayMonome(polynome[0]);

    free(saisie);
    free(polynome);
    //return polynome;
}

void concatenerPolynome(char chaine[TAILLE_POLYNOME], char* sortie)
{
    int i=0, j=0;
    char* sortieBuffer = malloc(0*sizeof(char));
    //sortieBuffer = (char* ) realloc(sortieBuffer, 0*sizeof(char));

    do
    {
        if(chaine[i] != ' ')
        {
            j++;
            sortieBuffer = (char *) realloc(sortieBuffer, j*sizeof(char));
            sortieBuffer[j-1] = chaine[i];
            printf("%c", sortieBuffer[j-1]);
        }
        i++;
    }
    while (chaine[i-1] != '\0');
    sortie = (char *) realloc(sortie, (j+1)*sizeof(char));
    sortie[j] = '\0';
    strcpy(sortie, sortieBuffer);

    free(sortieBuffer);
}

/*En première position uniquement :
{signe -} {nombre entier ou décimal}
{signe -} {X}fait
{signe -} {X^} {nombre entier}fait
{nombre entier ou décimal}
{nombre entier ou décimal} {*X^} {nombre entier}
*/

/*#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="- This, a sample string.";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str," ,.-");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }
  return 0;
}*/

monome premierMonome(char* chaine)
{
    char* extrait;
    monome out;

    char separateurs[] = {'+','-','\0'};

    out.coeff = 1;
    if (*chaine == '-')
    {
        out.coeff = -1;
        extrait = strtok(chaine + 1, separateurs);
    }
    else
        extrait = strtok(chaine, separateurs);

    if(estUnMonomeValide(extrait))
    {
        if(*extrait == 'X')
            out.coeff *= 1;
        else
            out.coeff *= atof(extrait);

        printf("\ncoeff = %f", out.coeff);

        if(nbrOccChar(extrait, 'X'))
        {
            if(nbrOccChar(extrait, '^'))
            {

                out.exposant = atoi(strchr(extrait, '^') + 1);
                printf("\nexp = %d",out.exposant);
            }
            else
            {
                out.exposant = 1;
                printf("\nexp = %d",out.exposant);
            }
        }
        else out.exposant  = 0;
    }
    else
    {
        out.coeff = 0;
        out.exposant = 0;
    }

    return out;
}

int estUnMonomeValide(char* chaine)
{
    int i = 0, out = 1;

    if (chaine == NULL)
        return 0;

    char signeApparaissantUneFois[] = "+-X*^.";

    while(signeApparaissantUneFois[i-1] != '.')
    {
        out &= (nbrOccChar(chaine, signeApparaissantUneFois[i]) <= 1);
        i++;
    }

    //Combinaisons incompatible:
    out &= !(!(nbrOccChar(chaine, 'X')) && nbrOccChar(chaine, '*'));
    out &= !(!(nbrOccChar(chaine, 'X')) && nbrOccChar(chaine, '^'));
    out &= !(!(nbrOccChar(chaine, '*')) && nbrOccChar(chaine, '.'));

    return (out);
}

int nbrOccChar(char* chaine, char c)
{
    int i = 0, out = 0;

    if (chaine == NULL)
        return out;

    while(chaine[i] != '\0')
    {
        if(chaine[i] == c)
        {
            out++;
        }
        i++;
    }

    return out;
}

/*
monome extrairePremierMonome(char* chaine)
{
    int deg = 0;
    float exposant;

    char seps[3] = {'+', '-', '\0'};

    monome out;
    out.coeff = 0;
    out.exposant = 0;

    char* buffer;
    char* copieChaine = chaine;

    if (chaine[0] == '+')
    {
        printf("Erreur, signe + en première position\n");
        //question6();
    }//+
    else if (chaine[0] == '-')
    {
        if (chaine[1] == 'X')
        {
            if(estUnSep(chaine[2]))
            {
                out.coeff = -1;
                out.exposant = 1;
                return out;
            }//estunseparateur
            else if(chaine[2] == '^')
            {
                buffer = strtok(copieChaine+3, seps);
                estUnExposant(buffer, &deg);
                if (deg != -1)
                {
                    out.coeff = -1;
                    out.exposant = deg;
                    return out;
                }//deg valide
            }//signe puissance
        }//X
        else
        {
            buffer = strtok(copieChaine+1, seps);
            printf("\nbuffer=%s", buffer);
            estUnExposant(buffer, &deg);
            printf("\ndegres=%d\n",deg);
            if (deg != -1)
            {
                out.coeff = -1;
                out.exposant = deg;
                return out;
            }
        }
    }//-
    return out;
}
*/
void estUnExposant(char* string, int* degres)
{
    int i = 0, cptPuissance = 1, buffer;
    //char* deg = malloc(0*sizeof(char));
    *degres = -1;

    i = strlen(string);

    if (i)
        *degres = 0;

    while(i)
    {
        buffer = estUnNombre(string[i-1]);
        if(buffer != -1)
        {
            *degres += (buffer * cptPuissance);
            printf("\ndeg=%d", *degres);
            cptPuissance *= 10;
            i--;
        }
        else
        {
            printf("Erreur, pas un nombre entier");
            menu();
        }
    }
}

int estUnNombre(char c)
{
    if((c >= '0') && (c <= '9'))
        return (c-'0');
    return (-1);
}

int estUnSep(char c)
{
    return(((c == '+') || (c == '-')) || (c == '\0'));
}

/*
Pour toutes les autres positions :
{signe + ou -} {nombre entier ou décimal}
{signe + ou -} {nombre entier ou décimal} {*X^} {nombre entier}
{signe + ou -} {X^} {nombre entier}
{signe + ou -} {X}
*/
