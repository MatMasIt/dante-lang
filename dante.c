#include "lexer.c"
int main()
{
    FILE *f = fopen("esempi/pvnrt.dante", "r");
    lex(f);
}