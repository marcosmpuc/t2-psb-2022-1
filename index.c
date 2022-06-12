#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFERSIZE 512
static char line_buffer[BUFFERSIZE];

typedef struct Node
{
    char word[30];
    int paragraph[25];     
    struct Node *next;
}Node;

typedef struct
{
    Node *head;
    Node *tail;
    int listSize;
}List;

void version (void)
{
    printf("\
    EN-US: Index generator - Versão 0.3.17\n\
    PT-BR: Gerador de índice remissivo - Versão 0.3.17\n\
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

void newList(List *list)
{
    list -> head = NULL;
    list -> tail = NULL;
    list -> listSize = 0;
}

void readInput(List *list)
{
    Node *new;
    FILE *input = fopen("input.txt","r");

    char test;
    int n = 0;
    int paragraph_number = 1;
    char word[30];
    int i = 0;

    while(fgets(line_buffer, BUFFERSIZE, input))
    {
        while(test = line_buffer[n]){

            if (test =='\n'){
                break;
            }
                
            if((test == 39)
                || (test >= 65 && test <= 90)
                || (test >= 97 && test <= 122))
            {
                word[i] = test;
                i++;
                n++;
            }
        }
        if(list->head==NULL)
        {
            new -> next = NULL;
            list -> head = new;
            list -> tail = new;
        }
    }
}

int main (int argc, char **argv)
{
    List *list;

    if(((list = (List*)malloc(sizeof(List))) == NULL))
        return -1;
    
    newList(list);
    readInput(list);

    int i;
    for (i = 0; i < argc; i ++)
    {
        printf("%d- Parâmetro = \"%s\"\n", i + 1, argv[i]);
    }

    int op;
    int print_on_terminal = 0; 
    int print_in_html = 0;
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
                readInput(list);
        }
    }
}