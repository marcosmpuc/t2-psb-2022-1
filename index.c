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
    FILE *input = fopen("input.txt", "r+");
    FILE *output  = fopen("output.txt", "w+");

    /*if(!input) printf("Não abriu entrada\n");
    if(!output) printf("Não abriu saída\n");
    
    char buffer[BUFFERSIZE];
    int n = 0;
    while((n = read(input, buffer, BUFFERSIZE)) > 0)
    {
        write(output, buffer, n);
    }
    */
    
    char buffer[BUFFERSIZE]; printf("DECLARAÇÃO: POINTER DE CARACTERE buffer\n");

    fgets(buffer, BUFFERSIZE, input);
    char test;
    int n = 0;
    int paragraphCount = 0;

    while(test = buffer[n])
    {
        printf("TENTOU LER BYTES\n");
        if(test == '\0')
            break;
        if ((test == 39)
            || (test >= 65 && test <= 90)
            || (test >= 97 && test <= 122))
        {
            printf("ACHOU CARACTERES ÚTEIS\n");
            fputc(test, output); printf("ESCREVEU BYTES\n");
        }
        else
        {
            printf("NÃO ACHOU CARACTERE ÚTIL\n");
            char sentence[12] = {',', ' ', 'p', 'a', 'r', 'a', 'g', 'r', 'a', 'f', 'o', ' '};
            for (int i = 0; i < 12; i++)
                fputc(sentence[i], output);
            // escreve número do parágrafo
            fputc('\n', output);
        }
        n++;
    }

    /*while (fgets(buffer, 106, INPUT))
    {
        printf("TENTOU LER BYTES\n");
        if(*buffer == '\0')
            break;
        if ((*buffer == 39)
            || (*buffer >= 65 && *buffer <= 90)
            || (*buffer >= 97 && *buffer <= 122))
        {
            printf("ACHOU CARACTERES ÚTEIS\n");
            fputc(buffer, OUTPUT); printf("ESCREVEU BYTES\n");
        }
        else
        {
            printf("NÃO ACHOU CARACTERE ÚTIL\n");
            fputc(buffer, OUTPUT);
        }
    }*/
    /*
    int n = 0;

    while ((n = read(INPUT, buffer, BUFFERSIZE)) > 0)
        write(OUTPUT, buffer, n);

    fclose(input);
    fclose(output);
    */

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
                break;
            default:
                exit(0);
                break;
        }
    }
    return 0;
}