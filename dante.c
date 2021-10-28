#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
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
char **str_split(char *a_str, const char a_delim)
{
    char **result = 0;
    size_t count = 0;
    char *tmp = a_str;
    char *last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char *) * count);

    if (result)
    {
        size_t idx = 0;
        char *token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
int prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}
int countats(char *line)
{
    int tot = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == '@')
        {
            tot++;
            continue;
        }

        if (line[i] == ' ' || line[i] == '\t')
            continue;

        return tot;
    }

    return tot;
}
char *strstrip(char *s)
{
    size_t size;
    char *end;

    size = strlen(s);

    if (!size)
        return s;

    end = s + size - 1;
    while (end >= s && isspace(*end))
        end--;
    *(end + 1) = '\0';

    while (*s && isspace(*s))
        s++;

    return s;
}
int main(int argc, char * argv[])
{
    FILE *fp = NULL;
    FILE *fo = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **tokens;
    char * inputfn;
    int lastInput = 0, lastOutput = 0;
    for(int i = 0; i < argc; i++){
       if(lastInput){
           inputfn = argv[i];
           fp = fopen(argv[i],"r");
           lastInput = 0;
	}
        if(lastOutput){
            if (strcmp(argv[i],"stdout")==0) fo = stdout;
            else fo = fopen(argv[i], "w+");
            lastOutput = 0;
        }
       if(argv[i][0]=='-'){
           if(argv[i][1]=='i') lastInput = 1;
           else if(argv[i][1]=='o') lastOutput = 1;
        }
    }

    //fp = fopen("pvnrt.dante", "r");

    if (fp == NULL){
        printf("No input file");
        exit(1);
    }
    if (fo == NULL){
        fo = fopen(strcat(inputfn,".out.c"),"w");
    }


    int prevAts = 0;
    FILE *head = fopen("dantehead.c","r");
    char t;
    while((t = fgetc(head))!=EOF){
       fprintf(fo,"%c", t);
    }
    fclose(head);
    while ((read = getline(&line, &len, fp)) != -1)
    {

        int addSemicolon = 1;
        char *copy = strdup(line);
        int ats = countats(copy);
        if (ats < prevAts)
        {
            fprintf(fo,"}");
        }
        else if (ats > prevAts)
        {
            fprintf(fo,"{");
        }
        prevAts = ats;
        if (strlen(strstrip(copy)) == 0)
            addSemicolon = 0;
        tokens = str_split(line, '"');
        for (int i = 0; *(tokens + i); i++)
        {
            if (!i % 2 || *(tokens + i + 1) == NULL)
            {
                char *newstr = replace(*(tokens + i), "restituisci", "return");
                if (strstr(newstr, "principale") != NULL)
                {
                    addSemicolon = 0;
                    newstr = replace(newstr, "principale", "int main()");
                }
                if (strstr(newstr, "finchè ") != NULL)
                {
                    addSemicolon = 0;
                    newstr = replace(newstr, "finchè", "while(");
                    strcat(strstrip(newstr), " )\n");
                }
                if (strstr(newstr, "se ") != NULL)
                {
                    addSemicolon = 0;
                    newstr = replace(newstr, "se ", "if(");
                    strcat(strstrip(newstr), " )\n");
                }
                if (strstr(newstr, "caso") != NULL)
                {
                    addSemicolon = 0;
                    newstr = replace(newstr, "caso", "case ");
                    strcat(strstrip(newstr), " :");
                }

                if (strstr(newstr, "altrimenti ") != NULL)
                {
                    addSemicolon = 0;
                    newstr = replace(newstr, "altrimenti ", "else if(");
                    strcat(strstrip(newstr), " )\n");
                }
                if (strstr(newstr, "infine ") != NULL)
                {
                    addSemicolon = 0;
                    newstr = replace(newstr, "infine", "else(");
                    strcat(strstrip(newstr), " )\n");
                }
                if (strstr(newstr, "valuta ") != NULL)
                {
                    addSemicolon = 0;
                    newstr = replace(newstr, "valuta", "switch(");
                    strcat(strstrip(newstr), " )\n");
                }

                if (strstr(newstr, "funzione") != NULL)
                {
                    addSemicolon = 0;
                    char **partsAB = str_split(line, ')');
                    *(partsAB + 1) = replace(*(partsAB + 1), "restituisce", "");
                    *(partsAB + 1) = replace(*(partsAB + 1), "intero", "int");
                    *(partsAB + 1) = replace(*(partsAB + 1), "decimale", "double");
                    *(partsAB + 1) = replace(*(partsAB + 1), "testo", "char * ");
                    *(partsAB + 1) = replace(*(partsAB + 1), "carattere", "char");
                    *(partsAB + 1) = replace(*(partsAB + 1), "vuoto", "void");
                    *(partsAB + 1) = replace(*(partsAB + 1), "NULLA", "NULL");
                    fprintf(fo,"%s", *(partsAB + 1));
                    newstr = strcat(*(partsAB + 0), ")");
                    newstr = replace(newstr, "funzione", "");
                }
                if (strstr(newstr, "struttura") != NULL)
                {
                    addSemicolon = 0;
                }
                newstr = replace(newstr, "intero", "int");
                newstr = replace(newstr, "decimale", "double");
                newstr = replace(newstr, "testo", "char * ");
                newstr = replace(newstr, "carattere", "char");
                newstr = replace(newstr, "struttura", "typedef struct");
                newstr = replace(newstr, "vuoto", "void");
                newstr = replace(newstr, "NULLA", "NULL");
                if (strstr(newstr, "importa") != NULL)
                {
                    addSemicolon = 0;
                }
                newstr = replace(newstr, "importa", "#include");
                newstr = replace(newstr, "definisci", "#define");
                newstr = replace(newstr, "funzione", "");
                newstr = replace(newstr, " o ", " || ");
                newstr = replace(newstr, " e ", " && ");
                newstr = replace(newstr, "non ", "!");
                for (int i = 0; i < strlen(newstr); i++)
                {
                    if (newstr[i] != '@')
                        fprintf(fo,"%c", newstr[i]);
                }
            }
            else
            {
                fprintf(fo,"\"%s\"", *(tokens + i));
            }
            free(*(tokens + i));
        }
        if (addSemicolon)
            fprintf(fo,";");
        fprintf(fo,"\n");

//        fprintf(fo, "%s", line);
    }
    for (int i = 0; i < prevAts; i++)
    {
        fprintf(fo,"}\n");
    }
    fclose(fp);
    fclose(fo);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
