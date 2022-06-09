#include <stdio.h>
#include "endhtml.h"

void end_html (FILE *output)
{
    char end[] = {
        '\n',
        '\t', '<', '/', 'b', 'o', 'd', 'y', '>', '\n',
        '<', '/', 'h', 't', 'm', 'l', '>', '\n'
    };
    char *pointer = end;
    while(fputc(*pointer, output))
    {
        if (!*(++pointer)) break;
    }
}