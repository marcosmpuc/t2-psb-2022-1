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

void addParagraphInfo (int position_to_write_at, FILE *outputTXT, FILE *outputHTML)
{
    char sentence[12] = {':', ' ', 'p', 'a', 'r', 'a', 'g', 'r', 'a', 'f', 'o', ' '};
    for (int i = 0; i < 12; i++)
    {
        fputc(sentence[i], outputTXT);
        if (i > 1) 
            fputc(sentence[i], outputHTML);
    }
    
    fputc('1', outputTXT);
    fputc('1', outputHTML);
    fputc('\n', outputTXT);
    fputc('\n', outputHTML);

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
    FILE *outputTXT  = fopen("output.txt", "w+");
    FILE *outputHTML = fopen("output.html", "w+");

    while (fgets(line_buffer, BUFFERSIZE, input))
    {
        char test;
        int n = 0;
        //char paragraphCount[4] = { NULL, NULL, NULL, '0'};
        int has_to_add = 0;
        int paragraph_number = 1;

        while(test = line_buffer[n])
        {
            if (test == EOF)
                return;
            if (test == '\n')
                break;
            if ((test == 39)
                || (test >= 65 && test <= 90)
                || (test >= 97 && test <= 122))
            {
                if(has_to_add == 0)
                {
                    fputc('<', outputHTML);
                    fputc('h', outputHTML);
                    fputc('1', outputHTML);
                    fputc('>', outputHTML);
                    has_to_add = 1;
                }
                
                printf("%c", test);
                fputc(test, outputTXT);
                fputc(test, outputHTML);
                n++;
            }
            else
            {
                if (has_to_add)
                {
                    n++;
                    fputc('<', outputHTML);
                    fputc('/', outputHTML);
                    fputc('h', outputHTML);
                    fputc('1', outputHTML);
                    fputc('>', outputHTML);
                    fputc('<', outputHTML);
                    fputc('p', outputHTML);
                    fputc('>', outputHTML);
                    printf(": parágrafo %d\n", paragraph_number);
                    addParagraphInfo(n, outputTXT, outputHTML);
                    fputc('<', outputHTML);
                    fputc('/', outputHTML);
                    fputc('p', outputHTML);
                    fputc('>', outputHTML);
                    
                    has_to_add = 0;
                }
                else
                    n++;
            }
        }
    }

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