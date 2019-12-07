#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> //caso use tolower ou toupper
/*
Nicolas Marcondes Molina
RA:743584
*/

int binarizacao(int n)
{
    if(n == 0)
        return 0;
    else
    {
        return (n % 2 + 10 * binarizacao(n/2));
    }
}

int main()
{
    int numero, a;
    scanf("%d", &numero);
    a = binarizacao(numero);
    printf("%d\n", a);

    return 0;
}
