#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"Graph.h"

int main(void)
{
    int lenStream = 0;
    char* stream = readinput(&lenStream);

    OptionManager(stream[0], stream, lenStream);

    free(stream);

    return 0;
}