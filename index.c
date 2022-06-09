#include <stdio.h>
#include <stdlib.h>
//#include "startHTML.h"
//#include "endHTML.h"

#define INPUT fopen("input.txt", "rb")
#define OUTPUT fopen("output.txt", "wb")

#define BUFFERSIZE 512
static char line_buffer[BUFFERSIZE];
static char HTML_start[] = {
        '<', '!', 'D', 'O', 'C', 'T', 'Y', 'P', 'E', ' ', 'h', 't', 'm', 'l', '>', '\n',
        '<', 'h', 't', 'm', 'l', ' ', 'l', 'a', 'n', 'g', '=', '"', 'p', 't', '"', '>', '\n',
        '\t', '<', 'h', 'e', 'a', 'd', '>', '\n',
        '\t', '\t', '<', 'm', 'e', 't', 'a', ' ', 'c', 'h', 'a', 'r', 's', 'e', 't', '=', '"', 'U', 'T', 'F', '-', '8', '"', ' ', '/', '>', '\n',
        '\t', '\t', '<', 'l', 'i', 'n', 'k', ' ', 'r', 'e', 'l', ' ', '=', '"', 's', 't', 'y', 'l', 'e', 's', 'h', 'e', 'e', 't', '"', ' ', 'h', 'r', 'e', 'f', '=', '"', 'o', 'u', 't', 'p', 'u', 't', '.', 'c', 's', 's', '"', '>', '\n',
        '\t', '\t', '<', 't', 'i', 't', 'l', 'e', '>', 'O', 'u', 't', 'p', 'u', 't', '<', '/', 't', 'i', 't', 'l', 'e', '>', '\n',
        '\t', '<', '/', 'h', 'e', 'a', 'd', '>', '\n',
        '\t', '<', 'b', 'o', 'd', 'y', '>', '\n'
    };
static char HTML_end[] = {
        '\n',
        '\t', '<', '/', 'b', 'o', 'd', 'y', '>', '\n',
        '<', '/', 'h', 't', 'm', 'l', '>', '\n'
    };
//static char *paragraph_number_last_digit = line_buffer[BUFFERSIZE - 1];

void version (void)
{
    printf("\
    EN-US: Index generator - Versão 0.3.12\n\
    PT-BR: Gerador de índice remissivo - Versão 0.3.12\n\
    \n\
    -u to view usage options\n\
    -u para visualizar opções de visualização");
}

void usage (void)
{
    printf("\
    EN-US: Index generator command options - Versão 0.3.12\n\
    PT-BR: Opções de comando do gerador de índice remissivo - Versão 0.3.12\n\
    \n\
    -u to view usage options\n\
    -u para visualizar opções de visualização\n\
    \n\
    -s to view index entries in terminal (shell)\n\
    -s para visualizar registros do índice no terminal (shell)\n\
    \n\
    -h to generate HTML file\n\
    -h para gerar arquivo HTML\n\
    \n\
    -t to generate .txt file\n\
    -t para gerar arquivo .txt\n\
    \n\
    -c to generate .csv file (order of columns: word; paragraph. separator: comma)\n\
    -c para gerar arquivo .csv (ordem das colunas: palavra; parágrafo. separador: vírgula");
}

void addParagraphInfo (int position_to_write_at, FILE *output)
{
    char sentence[10] = {'p', 'a', 'r', 'a', 'g', 'r', 'a', 'f', 'o', ' '};
    for (int i = 0; i < 10; i++)
    {
        fputc(sentence[i], output);
    }
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

void processing (int print_on_terminal, int print_in_html, int print_in_txt, int print_in_csv)
{
    FILE *input = fopen("input.txt", "r+");
    FILE *outputTXT  = fopen("output.txt", "w+");
    FILE *outputHTML = fopen("output.html", "w+");
    FILE *outputCSV = fopen("output.CSV", "w+");
    
    if (print_in_html)
    {
        char *pointer = HTML_start;
        while(fputc(*pointer, outputHTML))
        {
            if (!*(++pointer)) break;
        }
        //start_html(outputHTML);
    }

    while (fgets(line_buffer, BUFFERSIZE, input))
    {
        char test;
        int n = 0;
        //char paragraphCount[4] = { NULL, NULL, NULL, '0'};
        int has_to_add = 0;
        char paragraph_number = '1';


        while(test = line_buffer[n])
        {
            if (test == '\n')
                break;
            if ((test == 39)
                || (test >= 65 && test <= 90)
                || (test >= 97 && test <= 122))
            {
                if(has_to_add == 0)
                {
                    if (print_in_html)
                    {
                        fputc('<', outputHTML);
                        fputc('h', outputHTML);
                        fputc('1', outputHTML);
                        fputc('>', outputHTML);
                    }
                    has_to_add = 1;
                }
                
                if (print_on_terminal)
                    printf("%c", test);
                if (print_in_txt)
                    fputc(test, outputTXT);
                if (print_in_html)
                    fputc(test, outputHTML);
                if (print_in_csv)
                    fputc(test, outputCSV);
                
                n++;
            }
            else
            {
                if (has_to_add)
                {
                    n++;
                    if (print_on_terminal)
                        printf(": parágrafo %d\n", paragraph_number);
                    if(print_in_html)
                    {
                        fputc('<', outputHTML);
                        fputc('/', outputHTML);
                        fputc('h', outputHTML);
                        fputc('1', outputHTML);
                        fputc('>', outputHTML);
                        fputc('<', outputHTML);
                        fputc('p', outputHTML);
                        fputc('>', outputHTML);
                        addParagraphInfo(n, outputHTML);
                        fputc(paragraph_number, outputHTML);
                        fputc('<', outputHTML);
                        fputc('/', outputHTML);
                        fputc('p', outputHTML);
                        fputc('>', outputHTML);
                        fputc('\n', outputHTML);
                    }
                    if (print_in_txt)
                    {
                        fputc(':', outputTXT);
                        fputc(' ', outputTXT);
                        addParagraphInfo(n, outputTXT);
                        fputc(paragraph_number, outputTXT);
                        fputc('\n', outputTXT);
                    }
                    if (print_in_csv)
                    {
                        fputc(',', outputCSV);
                        fputc(paragraph_number, outputCSV);
                        fputc('\n', outputCSV);
                    }
                    
                    has_to_add = 0;
                }
                else
                    n++;
            }
        }
    }

    if (print_in_html)
    {
        char *pointer = HTML_end;
        while(fputc(*pointer, outputHTML))
        {
            if (!*(++pointer)) break;
        }
        //end_html(outputHTML);
    }

    return;
}

int main (int argc, char **argv)
{
    int i;
    for (i = 0; i < argc; i ++)
    {
        printf("%d- Parâmetro = \"%s\"\n", i + 1, argv[i]);
    }

    int op;
    int print_on_terminal = 0; 
    int print_in_html = 1;
    int print_in_txt = 0;
    int print_in_csv = 0;

    while ((op = getopt(argc, argv, "vushtce")) != EOF)
    {
        switch (op)
        {
            case 'v':
                version();
            case 'u':
                usage();
                break;
            case 's':
                print_on_terminal = 1;
                break;
            case 'h':
                print_in_html = 1;
                break;
            case 't':
                print_in_txt = 1;
                break;
            case 'c':
                print_in_csv = 1;
                break;
            case 'e':
                return 0;
            default:
                usage();
        }
    }
    
    if (!print_on_terminal && !print_in_html && !print_in_txt && !print_in_csv)
        usage();
    else
        processing(print_on_terminal, print_in_html, print_in_txt, print_in_csv);

    return 0;
}