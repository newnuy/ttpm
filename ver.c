#include <stdio.h>

#include "ver.h"

#define VERSION_FILE_PATH "./version"



void printVersion(void)
{
    FILE *fp;
    int c;

    fp = fopen(VERSION_FILE_PATH, "r");
    if (fp != NULL) {
        while ((c = fgetc(fp)) != EOF)
            putchar(c);
        fclose(fp);
    }
}
