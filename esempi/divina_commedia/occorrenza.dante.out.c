#include <string.h>
#include <stdarg.h>
#define apriFile fopen
#define file FILE*
#define leggiRigaFile fscanf
#define scriviRigaFile fprintf
#include <stdio.h>
#include <stdlib.h>
#define Matematica <math.h>
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define rad2 sqrt
#define eleva pow
#define costante const
#define caso case
#define predefinito default:
#define VERO 1
#define FALSO 0
#define booleano int
#define fine break
#define restituisci return
#define replace rimpiazzaTesto
#define leggiIntero _IleggiIntero
#define leggiDecimale _IleggiDecimale
#define leggiRiga _IleggiRiga
#define leggiCarattere _IleggiCarattere
#define leggiParola _IleggiParola
#define testoContiene strstr
#define chiudiFile fclose
char *replace(
    char const *const original,
    char const *const pattern,
    char const *const replacement)
{
    size_t const replen = strlen(replacement);
    size_t const patlen = strlen(pattern);
    size_t const orilen = strlen(original);

    size_t patcnt = 0;
    const char *oriptr;
    const char *patloc;

    // find how many times the pattern occurs in the original string
    for (oriptr = original; patloc = strstr(oriptr, pattern); oriptr = patloc + patlen)
    {
        patcnt++;
    }

    {
        // allocate memory for the new string
        size_t const retlen = orilen + patcnt * (replen - patlen);
        char *const returned = (char *)malloc(sizeof(char) * (retlen + 1));

        if (returned != NULL)
        {
            // copy the original string,
            // replacing all the instances of the pattern
            char *retptr = returned;
            for (oriptr = original; patloc = strstr(oriptr, pattern); oriptr = patloc + patlen)
            {
                size_t const skplen = patloc - oriptr;
                // copy the section until the occurence of the pattern
                strncpy(retptr, oriptr, skplen);
                retptr += skplen;
                // copy the replacement
                strncpy(retptr, replacement, replen);
                retptr += replen;
            }
            // copy the rest of the string.
            strcpy(retptr, oriptr);
        }
        return returned;
    }
}
void stampa(char *fmt, ...) {
    va_list args;
    fmt = replace(fmt,"%intero", "%d");
    fmt = replace(fmt, "%decimale", "%lf");
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

int leggi(char *fmt, ...)
{
    int rc;

    va_list args;
    fmt = replace(fmt,"%intero", "%d");
    fmt = replace(fmt, "%decimale", "%lf");
    va_start(args, fmt);
    rc = vscanf(fmt, args);
    va_end(args);

    return rc;
}

int _IleggiIntero(){
    int temp;
    scanf("%d", &temp);
    return temp;
}
double _IleggiDecimale(){
    double temp;
    scanf("%lf",&temp);
    return temp;
}
char * _IleggiRiga(){
    char * t = NULL;
    scanf("%[^\n]s",t);
    return t;
}

char * _IleggiParola(){
    char * t = NULL;
    scanf("%s",t);
    return t;
}
char _IleggiCarattere(){
    char c;
    scanf("%c", &c);
    return c;
}
int main()

{	file dc = apriFile("DC.txt","r")
;
	char *  a
;
	leggiRigaFile(dc,"%[^\n]s",a)
;
	stampa("%s",a)
;
	chiudiFile(dc)
;
}
