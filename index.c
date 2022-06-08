#include <stdio.h>
#include <stdlib.h>

void help ()
{
    printf("HEEEEELP!!!!");
}

void usage ()
{
    printf("USAGE FUNCIONA?");
}

int main (int argc, char **argv)
{

    int i;
    for (i = 0; i < argc; i ++)
    {
        printf("%d- Parâmetro = \"%s\"\n", i + 1, argv[i]);
    }

    int op;

    while ((op = getopt(argc, argv, "uhe")) != EOF)
    {
        switch (op)
        {
            case 'u':
                usage();
                break; 
            case 'h':
                help();
                break;
            default:
                exit(0);
        }
    }

    return 0;
}