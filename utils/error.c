#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
};