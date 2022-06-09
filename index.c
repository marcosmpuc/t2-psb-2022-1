#include <stdio.h>
#include <stdlib.h>

#define INPUT fopen("input.txt", "rb")
#define OUTPUT fopen("output.txt", "wb")

#define BUFFERSIZE 512
static char line_buffer[BUFFERSIZE];
//static char *paragraph_number_last_digit = line_buffer[BUFFERSIZE - 1];

void help ()
{
    printf("HEEEEELP!!!!");
}

void usage ()
{
    printf("USAGE FUNCIONA?");
}

void addParagraphInfo (int position_to_write_at, FILE *output)
{
    char sentence[12] = {':', ' ', 'p', 'a', 'r', 'a', 'g', 'r', 'a', 'f', 'o', ' '};
    for (int i = 0; i < 12; i++)
        fputc(sentence[i], output);
    
    fputc('1', output);
    fputc('\n', output);

}

/*char* paragraphIncrement (char digits[])
{
    while (1) {
        
        if (*lastDigit < '9')
        {
            *lastDigit++;
            return lastDigit;
        } 
        else
        {
            *lastDigit = '0';
            if (*(--lastDigit) < '1' )
            {
                *lastDigit = '1';
                return lastDigit;
            }
        }

    }
}*/

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
    
    //char buffer[BUFFERSIZE]; printf("DECLARAÇÃO: POINTER DE CARACTERE buffer\n");

    fgets(line_buffer, BUFFERSIZE, input);
    char test;
    int n = 0;
    //char paragraphCount[4] = { NULL, NULL, NULL, '0'};
    int has_to_add = 0;

    while(test = line_buffer[n])
    {
        printf("TENTOU LER BYTES\n");
        if(test == EOF)
            break;
        if ((test == 39)
            || (test >= 65 && test <= 90)
            || (test >= 97 && test <= 122))
        {
            has_to_add = 1; printf("ACHOU CARACTERES ÚTEIS\n");
            fputc(test, output); printf("ESCREVEU BYTES\n");
            n++;
        }
        else
        {
            printf("NÃO ACHOU CARACTERE ÚTIL\n");
            if (has_to_add)
            {
                addParagraphInfo(++n, output);
                has_to_add = 0;
            }
            else
                n++;
            /*char sentence[12] = {',', ' ', 'p', 'a', 'r', 'a', 'g', 'r', 'a', 'f', 'o', ' '};
            for (int i = 0; i < 12; i++)
                fputc(sentence[i], output);
            paragraphIncrement(paragraphCount);
            /*char *check = paragraphCount;
            for (int i = 0; check == NULL; check--)
                fputc(*check, output);*/
            //fputc(line_buffer, output);
        }
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