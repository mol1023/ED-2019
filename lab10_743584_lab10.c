/*
NICOLAS MARCONDES MOLINA
RA:743584
*/
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100000


int t;
char pilha[N];
void criapilha (void) {
   t = 0;
}

void empilha (char y) {
   pilha[t++] = y;
}

char desempilha (void) {
   return pilha[--t];
}

int pilhavazia (void) {
   return t <= 0;
}

int balanceada (char s[])
{
   criapilha ();
   for (int i = 0; s[i] != '\0'; ++i) {
      char c;
      switch (s[i]) {
         case ')': if (pilhavazia ()) return 0;
                   c = desempilha ();
                   if (c != '(') return 0;
                   break;
         case ']': if (pilhavazia ()) return 0;
                   c = desempilha ();
                   if (c != '[') return 0;
                   break;
         case '}': if (pilhavazia ()) return 0;
                   c = desempilha ();
                   if (c != '{') return 0;
                   break;
         default:  empilha (s[i]);
      }
   }
   return pilhavazia ();
}

int main(){
    int i, T, j = 0, x;
    char exp[100000];
    scanf ("%d", &T);

    loop:
    j++;
    scanf ("%s", exp);
    x = balanceada(exp);
    if(x==0)
        printf("N\n");
    else
        printf("S\n");

    if(j < T){
       goto loop;
    }else
       exit(1);

}
