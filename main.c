#include <stdio.h>
#include <stdlib.h>
#include "expression.h"


void vider()
{
    char c;
    while(c=getchar()!='\n');
}

int main()
{

   do{
       traitement();
       vider();
   }while(1);

    return 0;
}
