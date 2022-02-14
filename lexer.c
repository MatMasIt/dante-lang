#include <stdio.h>
#include <string.h>
#include "utils/arraylist.h"
#include "utils/arraylist.c"
#include "common.h"
#include "tokens.h"
#include "stree.c"
int lex(FILE *file)
{
    flag inComment = false;
    size_t maxl = 256;

    char *line = malloc(maxl * sizeof(char));
    char *parsingUnit = malloc(maxl * sizeof(char));
    if (!line)
    {
        printf("Memory not allocated!!\n");
        return -2;
    }

    while (fgets(line, maxl, file))
    {
        while (line[strlen(line) - 1] != '\n' && line[strlen(line) - 1] != '\r')
        {
            char *tmp = realloc(line, 2 * maxl * sizeof(char));
            fseek(file, 0, SEEK_SET); // or wherever you want to seek to
            if (tmp)
            {
                line = tmp;
                maxl *= 2;
                fgets(line, maxl, file);
            }
            else
            {
                printf("Not enough memory for this line!!\n");
                return -3;
            }
        }

        char *temp = realloc(parsingUnit, maxl * sizeof(char));
        parsingUnit = temp;
        printf("%s\n", line); // just to check
        if (strlen(line) > 0 && line[0] == '#')
        {
            // ignore pure comment lines
            continue;
        }
        if (strlen(line) > 1 && line[0] == '#' && line[1] == '#')
        {
            inComment = !inComment;
        }
        if (inComment)
        {
            continue;
        }
        // now let's tokenize
        int j = 0;
        flag foundToken = false;
        for (int i = 0; i < strlen(line); i++)
        {
            foundToken = false;
            parsingUnit[i - j] = line[i];
            if (strncmp(parsingUnit, MAIN_T, strlen(MAIN_T)) == 0)
            {
                printf("MAIN");
                foundToken = true;
            }
            if (foundToken)
            {
                j = i;
                parsingUnit[0] = '\0';
            }
        }
    }
    free(line);
    free(parsingUnit);
}