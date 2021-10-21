#define stampa printf
#include <stdio.h>
#include <stdlib.h>
   int
 somma(int a,int b)
{   return a+b
;
}



int main()

{   int a = 0
;
   while( a < 10 )

{      stampa("%d\n",somma(a,1))
;
      a++;
}
}
