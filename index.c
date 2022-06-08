#include <stdio.h>
#include <stdlib.h>

#define INPUT fopen("input.txt", "rb")
#define OUTPUT fopen("output.txt", "wb")

#define BUFFERSIZE 512

void help ()
{
    printf("HEEEEELP!!!!");
}

void usage ()
{
    printf("USAGE FUNCIONA?");
}

void processing (void)
{
    int *input;
    *input = fopen("input.txt", "r");
    int *output;
    *output = fopen("output.txt", "w");

    if(!input) printf("Não abriu entrada\n");
    if(!output) printf("Não abriu saída\n");
    
    char *buffer;

    /*int buffer = 1; printf("DECLARAÇÃO: POINTER DE CARACTERE buffer\n");

    *while (buffer > -1)
    {
        buffer = fgetc(INPUT); printf("TENTOU LER BYTES\n");
        if ((buffer == 39)
            || (buffer >= 65 && buffer <= 90)
            || (buffer >= 97 && buffer <= 122))
        {
            printf("ACHOU CARACTERES ÚTEIS\n");
            fputc(buffer, OUTPUT); printf("ESCREVEU BYTES\n");
        }
        else
        {
            printf("NÃO ACHOU CARACTERE ÚTIL\n");
            fputc(buffer, OUTPUT);
        }
        fputc(buffer, OUTPUT);
    }*/

    int n = 0;

    while ((n = read(INPUT, buffer, BUFFERSIZE)) > 0)
        write(OUTPUT, buffer, n);

    fclose(INPUT);
    fclose(OUTPUT);


    return;
}

int main (int argc, char **argv)
{

    processing();

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
            default:
                exit(0);
                break;
        }
    }

    return 0;
}