# DM1
DM1 C SE3

Sujet:

Devoir Maison SE3 – Janvier 2015




EXERCICE 1

On veut coder un algorithme de cryptage très simple : on choisit un décalage (par exemple 5), et un a sera remplacé par un f, un b par un g, un c par un h, …, un x par un c, un y par un d, un z par un e. On ne cryptera que les lettres majuscules et minuscules sans toucher ni à la ponctuation ni à la mise en page. On procède comme suit :
1.	Ecrire une procédure void crypt( char *p ) de cryptage d'un caractère.
2.	Ecrire le main qui appellera la fonction crypt sur l'ensemble du message et imprimera le résultat.

PROBLEME

L’objectif de ce problème est la réalisation d’un programme pour la manipulation des polynômes d’une variable, munis de leurs principales opérations. Un certain nombre de fonctionnalités sont ajoutées au fil des questions. C’est à vous de les intégrer dans l’interface utilisateur (par le biais d’un menu) au fur et à mesure du développement de votre programme.
En mathématiques, un polynôme est la combinaison linéaire des puissances d'une variable, X par exemple. En algèbre générale, un polynôme P d'indéterminée X est une expression de la forme :
P = a0 + a1 X1 + a2 X2 + … + an Xn   avec ai  

1 SAISIE DU POLYNÔME 

Un polynôme sera représenté en mémoire comme un tableau dont chaque indice représente un monôme, c’est-à-dire un couple (coefficient, exposant).

Définissez la structure de donnée requise. Faire un programme permettant de saisir et de stocker le polynôme en mémoire. 

Pour ranger le tableau de structure résultant, vous fixerez la taille du tableau à une taille suffisante.

2  REDUCTION DES POLYNOMES

L’utilisateur a pu rentrer des monômes de même degré. Recherchez les monômes de même degré et ajoutez la valeur de leurs coefficients pour qu’ils ne fassent plus qu’un seul monôme. Réduisez la taille du tableau en conséquence en mémoire dynamique.

3 TRI PAR DEGRE CROISSANT

Triez le tableau de monômes, par la méthode de votre choix,  afin qu’ils soient classés par ordre de degré croissant.

4 AFFICHAGE

Une fois les monômes triés, affichez le polynôme sous la forme :

P = 123.0 - X + X^3 + 2 * X^4 – 4.5 * X^5 

5 EVALUATION

Ecrivez une fonction 

double eval(POINTEUR p, double x);

qui calcule et renvoie la valeur du polynôme représenté par p pour une valeur x de la variable.


6 ANALYSEUR SYNTAXIQUE. 

Réaliser un analyseur syntaxique qui permet à partir du polynôme saisi au clavier de vérifier que celui-ci est écrit correctement. 

Compresser cette chaîne en supprimant tous les espaces puis vérifier que le polynôme est une succession de monômes qui respectent l’une des écritures suivantes :

En première position uniquement :
{signe -} {nombre entier ou décimal}
{signe -} {X}
{signe -} {X^} {nombre entier}
{nombre entier ou décimal}
{nombre entier ou décimal} {*X^} {nombre entier}

Pour toutes les autres positions :
{signe + ou -} {nombre entier ou décimal}
{signe + ou -} {nombre entier ou décimal} {*X^} {nombre entier}
{signe + ou -} {X^} {nombre entier}
{signe + ou -} {X}

Exemple :
Saisir un Polynôme :
– 4.5 * X^5 + 2 * X^4 + X^3 - X + 123.0
Saisie correcte ! 

Saisir un Polynôme :
- 4.5 * X^5 / 2 * X^2 
Erreur : Symbole ‘/’ en 13eme position

Recommencez :
- 4.5 * X^5 * 2 * X^2 
Erreur : Symbole ‘*’ en 13eme position

Recommencez :
- 4.5 * X^5 ++ 2 * X^2 
Erreur : Symbole ‘+’ en 14eme position




