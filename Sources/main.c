#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

int main()
{
    char menuChoix;

    do
    {
        menuChoix = menu();

    }while(menuChoix != '0');

    return 0;
}
