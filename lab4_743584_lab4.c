#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> //caso use tolower ou toupper
/*
Nicolas Marcondes Molina
RA:743584
*/

int Fibonacci(int n)
{
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    if(n > 1)//passo
        return Fibonacci(n - 1) + Fibonacci(n - 2);//"divisao em 2"
}

int main()
{
    int a, i;
    scanf("%d", &a);
    i = Fibonacci(a);
    printf("%d\n", i);

    return 0;
}
