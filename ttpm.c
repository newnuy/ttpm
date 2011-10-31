#include <stdio.h>
#include <string.h>

#include "points.h"
#include "ver.h"


int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(*++argv, "--version") == 0) {
        printVersion();
        return 0;
    }

    startMenu();

    return 0;
}
