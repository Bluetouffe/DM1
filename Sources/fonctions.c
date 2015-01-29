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

    monome * p1 = malloc(0*sizeof(monome));
    int taille = 0;
    saisie(p1, &taille);

    displayPolynome(p1, taille);//affichage du polynome saisie

    free(p1);
}

void saisie(monome* polynome, int* taille)
{
    saisiePolynome(polynome, taille);
}

void question2(void)
{
    monome * p2 = malloc(0*sizeof(monome));
    int taille = 0;
    saisie(p2, &taille);

    suppressionDoublons(p2, &taille);//suppression des doublons et des zéros

    printf("\nPolynome reduit:\n");

    displayPolynome(p2, taille);//affichage du polynome réduit

    free(p2);
}

void question3(void)
{
    monome * p3 = malloc(0*sizeof(monome));
    int taille = 0;
    saisie(p3, &taille);

    suppressionDoublons(p3, &taille);

    triPolynome(p3, 0, taille);
    printf("\ntableau trié:\n");
    displayPolynome(p3, taille);

    free(p3);
}

void question4(void)
{
    question3();
}

void question5(void)
{
    monome * p5 = malloc(0*sizeof(monome));
    int taille = 0;
    double x = 0;
    saisie(p5, &taille);

    suppressionDoublons(p5, &taille);

    triPolynome(p5, 0, taille);
    printf("\n");
    displayPolynome(p5, taille);

    ajouterTaillePolynome(p5, taille);

    printf("Entrez le nombre a évaluer :");
    scanf("%lf", &x);

    printf("\nP(x)= %.2f\n", eval(p5, x));

    free(p5);
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
                printf(" + X^%d ", m.exposant);
            else
            {
                if(m.coeff == -1)
                    printf(" - X^%d ", m.exposant);
                else
                    printf("%+.2f * X^%d ", m.coeff, m.exposant);
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
    int taille = 0, tailleMonome = 0, taillePolynome = 0, start = 0;

    char buffer[TAILLE_POLYNOME]= {0};

    printf("\nEntrez un polynome :\n");
    fflush(stdin);
    gets(buffer);
    fflush(stdin);

    //pour debug
    printf("\nSaisie buffer: %s\n",buffer);

    char* saisie = calloc(strlen(buffer) - nbrOccChar(buffer, ' ') + 1,sizeof(char));
    concatenerPolynome(buffer, saisie);

    //pour debug
    printf("\nSaisie: %s\n",saisie);

    taillePolynome = nbrOccChar(saisie, '-') + nbrOccChar(saisie, '+') + 1;

    //pour debug
    printf("\ntaille polynome: %d", taillePolynome);

    monome* polynome = (monome*) calloc(taillePolynome, sizeof(monome));

    while(strlen(saisie) - start != 0)
    {
        taille++;

        if(taille == 1)
            polynome[taille-1] = premierMonome(saisie, &tailleMonome);
        else
            polynome[taille-1] = extraitMonome(saisie, &tailleMonome, start);

        start += tailleMonome;
    }

    printf("\nPolynome non trie, non reduit:");
    displayPolynome(polynome, taille);

    suppressionDoublons(polynome, &taille);
    printf("\nPolynome non trie, reduit:");
    displayPolynome(polynome, taille);

    triPolynome(polynome, 0, taille);
    printf("\nPolynome trie, reduit:");
    displayPolynome(polynome, taille);

    free(saisie);
    free(polynome);
}

void concatenerPolynome(char chaine[TAILLE_POLYNOME], char* sortie)
{
    int i, j, tailleChaine;
    i = j = 0;
    tailleChaine = strlen(chaine)-nbrOccChar(chaine, ' ');
    char* sortieBuffer = NULL;
    sortieBuffer = (char*) calloc(tailleChaine+1, sizeof(char));

    do
    {
        if(chaine[i] != 32)
        {
            sortieBuffer[j] = chaine[i];
            j++;
        }
        i++;
    }
    while(j<tailleChaine && i<strlen(chaine));

    sortieBuffer[j] = '\0';

    sortie = (char*) realloc(sortie, (j+1) * sizeof(char));
    for (i = 0; i <= j; i++)
    {
        sortie[i] = sortieBuffer[i];
    }

    free(sortieBuffer);
}

/*
{signe -} {nombre entier ou décimal}
{signe -} {X}fait
{signe -} {X^} {nombre entier}fait
{nombre entier ou décimal}
{nombre entier ou décimal} {*X^} {nombre entier}
*/
monome premierMonome(char* chaine, int* length)
{
    char* extrait;
    char* buffer = (char*) calloc(strlen(chaine)+1, sizeof(char));
    strcpy(buffer, chaine);

    monome out;

    char separateurs[] = {'+','-','\0'};

    out.coeff = 1;
    if (*buffer == '-')
    {
        out.coeff = -1;
        extrait = strtok(buffer + 1, separateurs);
        *length = strlen(extrait) + 1;
    }
    else
    {
        extrait = strtok(buffer, separateurs);
        *length = strlen(extrait);
    }
    //pour debug
    //printf("\ntaille = %d", *length);

    if(estUnMonomeValide(extrait))
    {
        if(*extrait == 'X')
            out.coeff *= 1;
        else
            out.coeff *= atof(extrait);

        if(nbrOccChar(extrait, 'X'))
        {
            if(nbrOccChar(extrait, '^'))
            {

                out.exposant = atoi(strchr(extrait, '^') + 1);
            }
            else
            {
                out.exposant = 1;
            }
        }
        else out.exposant  = 0;
    }
    else
    {
        out.coeff = 0;
        out.exposant = 0;
    }

    free(buffer);
    return out;
}

/*
Pour toutes les autres positions :
{signe + ou -} {nombre entier ou décimal}
{signe + ou -} {nombre entier ou décimal} {*X^} {nombre entier}
{signe + ou -} {X^} {nombre entier}
{signe + ou -} {X}
*/
monome extraitMonome(char* chaine, int* length, int start)
{
    char* extrait;
    char* buffer = (char*) calloc(strlen(chaine) + 1 - start, sizeof(char));
    strcpy(buffer, &chaine[start]);
    /*for (i=0; i <= (strlen(chaine) - start); i++)
    {
        buffer[i] = chaine[i+start-1];
    }*/
    printf("\nBuffer= %s", buffer);
    monome out;

    char separateurs[] = {'+','-','\0'};

    out.coeff = 1;
    if (*buffer == '-')
    {
        out.coeff = -1;
        extrait = strtok(buffer + 1, separateurs);
        *length = strlen(extrait) + 1;
    }
    else
    {
        extrait = strtok(buffer+1, separateurs);
        *length = strlen(extrait) + 1;
    }
    //pour debug
    //printf("\ntaille = %d", *length);

    if(estUnMonomeValide(extrait))
    {
        if(*extrait == 'X')
            out.coeff *= 1;
        else
            out.coeff *= atof(extrait);

        if(nbrOccChar(extrait, 'X'))
        {
            if(nbrOccChar(extrait, '^'))
            {

                out.exposant = atoi(strchr(extrait, '^') + 1);
            }
            else
            {
                out.exposant = 1;
            }
        }
        else out.exposant  = 0;
    }
    else
    {
        out.coeff = 0;
        out.exposant = 0;
    }

    free(buffer);
    return out;
}

int estUnMonomeValide(char* chaine)
{
    int i = 0, out = 1;

    if (chaine == NULL)
        return 0;

    char signeUneFois[] = "+-X*^.";

    do
    {
        out &= (nbrOccChar(chaine, signeUneFois[i]) <= 1);
        i++;
    }
    while(signeUneFois[i-1] != '.');

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
