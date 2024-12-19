#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char* ftostr(char *path){
    //try to open file
    FILE* fptr;
    if ((fptr = fopen(path, "r")) == NULL){
        perror("Error: ");
        return NULL;
    }
    
    //allocate space, write contents to space.
    char c;
    size_t max = LEN_STD;
    size_t count = 0;
    char* final = malloc(sizeof(char) * max);
    if (final == NULL){
        fclose(fptr);
        free(final);
        return NULL;
    }
    while ((c=fgetc(fptr)) != EOF) {
        if (count >= max){
            max *= 2;
            final = realloc(final, max);
            if (final == NULL){
                fclose(fptr);
                free(final);
                return NULL;
            }
        }
        final[count] = (char) c;
        count++;
    }
    
    //final realloc.
    final = realloc(final, count + 1);
    if (final == NULL){
        fclose(fptr);
        free(final);
        return NULL;
    }
    
    if (count > 0)
        final[count] = '\0';

    fclose(fptr);
    return final;
}
