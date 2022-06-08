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
void file()
{
}

int main (int argc, char **argv)
{
    int i;
    for (i = 0; i < argc; i ++)
    {
        printf("%d- Parametro = \"%s\"\n", i + 1, argv[i]);
    }

    
    int op;

    while ((op = getopt(argc, argv, "uhf")) != EOF)
    {
        switch (op)
        {
            case 'u':
                usage();
                break; 
            case 'h':
                help();
                break;
            case 'f':
                FILE *file;
                file = fopen("%s",argv[2]);

                    if(file == NULL) 
                {
                    printf("Nao foi possivel abrir o arquivo.\n");
                    getchar();  
                    exit(0);
                }

                char frase[8];
                
                while(fgets(frase, 8, file) != NULL)
                {
                    printf("%s", frase);
                }
                break;
            default:
                exit(0);
        }
    }

    return 0;
}