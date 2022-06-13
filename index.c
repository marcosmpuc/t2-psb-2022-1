#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define BUFFERSIZE 512
#define WORDSIZE 30
#define PARAGRAPHCOUNT 25
static char line_buffer[BUFFERSIZE];

typedef struct Node
{
    char word[WORDSIZE];
    int paragraph[PARAGRAPHCOUNT];     
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
    int listSize;
} List;

void
version (void)
{
    printf ("\
    EN-US: Index generator - Versão 0.3.17\n\
    PT-BR: Gerador de índice remissivo - Versão 0.3.17\n\
    \n\
    -u to view usage options\n\
    -u para visualizar opções de visualização");
}

void
usage (void)
{
    printf ("\
    EN-US: Index generator command options - Versão 0.3.12\n\
    PT-BR: Opções de comando do gerador de índice remissivo - Versão 0.3.12\n\
    \n\
    -u (\"usage\") to view usage options\n\
    -u (\"usage\") para visualizar opções de visualização\n\
    \n\
    -s (\"shell\") to view index entries in terminal (shell)\n\
    -s (\"shell\") para visualizar registros do índice no terminal (shell)\n\
    \n\
    -w (\"web\") to generate HTML file\n\
    -w (\"web\") para gerar arquivo HTML\n\
    \n\
    -t (\"txt\") to generate .txt file\n\
    -t (\"txt\") para gerar arquivo .txt\n\
    \n\
    -c (\"csv\") to generate .csv file (order of columns: word; paragraph. separator: comma)\n\
    -c (\"csv\") para gerar arquivo .csv (ordem das colunas: palavra; parágrafo. separador: vírgula");
}

void
newList (List* list)
{
    list -> head = NULL;
    list -> tail = NULL;
    list -> listSize = 0;
}

void 
insertWord (List* list, int paragraph_number, char* wordBuffer)
{
    Node *new;
    int i;

    if (list -> head == NULL)
    {    
        Node *new;
        if ((new = (Node*) malloc (sizeof (Node))) == NULL)
            return -1;

        for (i = 0; i < WORDSIZE; i++)
            new -> word[i] = '\0';
                    
        //zera os paragrafos do novo Node
        for (i = 0; i < PARAGRAPHCOUNT; i++)
            new -> paragraph[i] = 0;

        i = 0;
        int j = 0;

        while (wordBuffer[j] != '\0')
        {
            new -> word[j] = wordBuffer[j];
            j++;
        }

        j = 0;

        while (new -> paragraph[j] != 0)
            j++;
        
        new -> paragraph[j] = paragraph_number;

        new -> next = NULL;
        list -> head = new;
        list -> tail = new;

        list -> listSize++;
        printf ("INSERIDO COM SUCESSO\n");
    }
    else if (isEqual (list, wordBuffer) == 0)
    {
        int i;
        Node *new;
        if ((new = (Node*) malloc (sizeof (Node))) == NULL)
            return -1;  

        //insere \0 nas palavras do novo Node
        for (i = 0; i < WORDSIZE; i++)
            new -> word[i] = '\0';
                    
        //zera os paragrafos do novo Node
        for (i = 0; i < PARAGRAPHCOUNT; i++)
            new -> paragraph[i] = 0;

        i = 0;

        int j = 0;
        while (wordBuffer[j] != '\0')
        {
            new -> word[j] = wordBuffer[j];
            j++;
        }
        j = 0;

        while (new -> paragraph[j] != 0)
            j++;

        new -> paragraph[j] = paragraph_number;

        new -> next = list -> head;
        list -> head = new;
        
        list -> listSize++;
        printf ("INSERIDO COM SUCESSO\n");
    }
    else
    {
        Node *aux = list -> head;
    
        while (aux != NULL)
        {
            int retorno = stricmp(wordBuffer, aux -> word);
            //se 0 entao sao iguais
            if (retorno == 0)
                for (int i = 0; i < PARAGRAPHCOUNT; i++)
                    if (aux -> paragraph[i] == 0)
                    {
                        aux -> paragraph[i] = paragraph_number;
                        break;
                    }
            aux = aux -> next; 
        }
    }
}

void
bubbleSort (List *list)
{
    if (list -> listSize>1)
    {
        Node *node = list -> head;
       
        while (node != NULL)
        {
            Node *nodeNext = node -> next;
            while (nodeNext != NULL)
            {
                int retorno = stricmp (node->word,nodeNext->word);
                if (retorno > 0)
                {
                    swap (node, nodeNext);                                      
                }
                nodeNext = nodeNext -> next;
            }
            node = node -> next;
       }
    }  
}

void
swap (Node *node, Node* nodeNext)
{
    char auxWord[WORDSIZE];
    int auxParagraph[PARAGRAPHCOUNT];

    int i = 0;
    while(i < WORDSIZE)
    {
        auxWord[i] = node -> word[i];
        i++;
    }
    
    i = 0;
    while (i < PARAGRAPHCOUNT)
    {
        auxParagraph[i] = node -> paragraph[i];
        i++;
    }

    i = 0;
    while (i < WORDSIZE)
    {
        node -> word[i] = nodeNext -> word[i];
         i++;
    }

    i = 0;
    while (i < PARAGRAPHCOUNT)
    {
        node -> paragraph[i] = nodeNext -> paragraph[i];
        i++;
    }

    i = 0;
    while (i < WORDSIZE)
    {
        nodeNext -> word[i] = auxWord[i];
        i++;
    }

    i=0;
    while(i < PARAGRAPHCOUNT)
    {
        nodeNext -> paragraph[i] = auxParagraph[i];
         i++;
    }
}

int
isEqual (List *list, char *word)
{
    Node *aux = list -> head;
    
    while (aux != NULL)
    {
        int retorno = stricmp (word, aux -> word);
        //se 0 entao sao iguais
        if (retorno == 0)
            return 1;
        
        aux = aux -> next; 
    }

    return 0; //se forem iguais
}


Node*
getWord (List *list, char *word)
{
    Node *aux = list -> head;
    char wordIn[WORDSIZE];
    int i = 0;
    while(i < WORDSIZE)
    {   
        wordIn[i] = word[i];
        i++;
    }
    while (aux != NULL)
    {
        int retorno = stricmp (wordIn, aux -> word);
        //se 0 entao sao iguais
        if (retorno == 0)
            return aux;
        aux = aux -> next; 
    }
    
}

void
readInput (List* list)
{
    Node *new;
    FILE *input = fopen ("input.txt","r");

    char test;
    int n = 0;
    int paragraph_number = 1;
    char word[WORDSIZE];
    int i;

    for (i = 0; i < WORDSIZE; i++)
        word[i] = '\0';
    i = 0;

    while (fgets (line_buffer, BUFFERSIZE, input))
    {   
        while (test = line_buffer[n])
        {

            if (test == '\n')
            {
                if (line_buffer[n+1] == '\0')
                {
                    insertWord (list, paragraph_number, &word);
                    for (i = 0; i < WORDSIZE; i++)
                        word[i] = '\0';
                    paragraph_number++;
                    n = 0;
                    i = 0;
                    break;
                }
                else
                {
                    insertWord (list, paragraph_number, &word);
                    paragraph_number++;
                    n = 0;
                    for (i = 0; i < WORDSIZE; i++)
                        word[i] = '\0';
                    
                    i = 0;
                    break;
                } 
            }
            else if ((test == 39)
                || (test >= 65 && test <= 90)
                || (test >= 97 && test <= 122))
            {
                word[i] = test;
                i++;
                n++;
            }
            else if (test == ' ')
            {  
                insertWord (list, paragraph_number, &word);
                n++;
                for (i = 0; i < WORDSIZE; i++)
                    word[i] = '\0';
                
                i = 0;
            }
            else
            {
                if (line_buffer[n+1] == '\n')
                {
                    insertWord (list, paragraph_number, &word);
                    paragraph_number++;
                    n = 0;
                    for (i =0 ; i < WORDSIZE; i++)
                        word[i] = '\0';
                    i = 0;
                    break;
                }
                else
                    n++;
            }
        }
    }
}

void
write_char_to_output (char word[], FILE *output_file, int max_quantity)
{
    for (int i = 0; i < max_quantity; i++)
    {
        if (word[i] != '\0')
            fputc(word[i], output_file);
        else return;
    }
}
void
write_int_to_output (int array[], FILE *output_file, int max_quantity)
{
    for (int i = 0; i < max_quantity; i++)
    {
        if (array[i] != '\0')
        {
            char number[4];
            int num = sprintf (number, "%d", array[i]);
            write_char_to_output (number, output_file, 5);
            if (array[i+1] != '\0')
                fputc(',', output_file);
        }
        else return;
    }
}

void printList (List* list, bool print_on_terminal, bool print_in_html,
                bool print_in_txt, bool print_in_csv)
{   
    FILE *html_output = fopen ("output.html", "w");
    FILE *txt_output = fopen ("output.txt", "w");
    FILE *csv_output = fopen ("output.csv", "w");
    
    int x = 0;
    Node *aux = list -> head;
    if(print_in_html)
        printf("Tamanho da lista = %d\n", list -> listSize);

    if(print_in_html)
    {
        fwrite ("<!DOCTYPE html>\n\
    <html lang=\"en\">\n\
    <head>\n\
        <meta charset=\"UTF-8\">\n\
        <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n\
        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\
        <title>Document</title>\n\
        <link rel=\"stylesheet\" href=\"output.css\">\n\
    </head>\n\
    <body>\n", 317, 1, html_output);
    }

    while (aux != NULL)
    {
        if (print_on_terminal)
        {
            printf ("%s -> ", aux -> word);
            printf ("Paragrafo: ");
        }
        if (print_in_html)
        {  
            fwrite ("<h1>", 4, 1, html_output);
            write_char_to_output (aux -> word, html_output, WORDSIZE);
            fwrite ("</h1>\n<p>Parágrafos: ", 22, 1, html_output);
            write_int_to_output (aux -> paragraph, html_output, PARAGRAPHCOUNT);
            fwrite ("</p>\n", 5, 1, html_output);
        }
        if (print_in_txt)
        {
            write_char_to_output (aux -> word, txt_output, WORDSIZE);
            fwrite (": ", 2, 1, txt_output);
            write_int_to_output (aux -> paragraph, txt_output, PARAGRAPHCOUNT);
            fwrite ("\n", 1, 1, txt_output);
        }
        if (print_in_csv)
        {
            write_char_to_output (aux -> word, csv_output, WORDSIZE);
            fwrite (",", 1, 1, csv_output);
            write_int_to_output (aux -> paragraph, csv_output, PARAGRAPHCOUNT);
            fwrite ("\n", 1, 1, csv_output);
        }
                
        while (aux -> paragraph[x] > 0)
        {
            if (print_on_terminal)
                printf ("%d, ", aux->paragraph[x]);
            x++;
        }
        if (print_on_terminal)
            printf ("\n");
        x = 0;
        aux = aux -> next; 
    }
    
    if (print_in_html)
    {
        fwrite ("    </body>\n\
</html>", 19, 1, html_output);
    }

    fclose (html_output);
    fclose (txt_output);
    fclose (csv_output);
}

void
printNode (Node* node)
{
    Node *aux = node;
    int i = 0;
    if (node != NULL)
    {
        while (node -> word[i] != 0)
        {   
            printf ("%c", node -> word[i]);
            i++;
        }
        printf (" -> Paragrafo:");

        i = 0;
        while (node -> paragraph[i] != 0)
        {   
            printf("%d, ", node -> paragraph[i]);
            i++;
        }
    }
    else printf ("Esse node não existe");
}

int
main (int argc, char** argv)
{
    List *list;

    if (((list = (List*)malloc(sizeof(List))) == NULL))
        return -1;
    
    newList (list);
    readInput (list);
    bubbleSort (list);

    //TESTE FUNÇÃO PESQUISA PALAVRA
    printf ("PESQUISA PALAVRA:\n");
    char word[WORDSIZE] = {'f','u','n','c','i','o','n','a'};
    printNode (getWord (list, &word));
    printf ("\n");

    int i;
    for (i = 0; i < argc; i ++)
        printf("%d- Parametro = \"%s\"\n", i + 1, argv[i]);

    int op;
    bool print_on_terminal = false; 
    bool print_in_html = false;
    bool print_in_txt = false;
    bool print_in_csv = false;

    Node *aux;

    while ((op = getopt (argc, argv, "vuswtcl:e")) != EOF)
    {
        switch (op)
        {
            case 'v'://version
                version ();
                break;
            case 'u'://usage
                usage ();
                break;
            case 's'://shell
                print_on_terminal = true;
                break;
            case 'w'://web
                print_in_html = true;
                break;
            case 't'://txt
                print_in_txt = true;
                break;
            case 'c'://csv
                print_in_csv = true;
                break;
            case 'l'://lookup
                //char optarg[WORDSIZE] = 
                aux = getWord (list, optarg);
                printf ("\"%s\" se encontra nos parágrafos\n", aux -> word);
                for (int i = 0; aux -> paragraph[i] != '\0'; i++)
                    printf ("%d\n", aux -> paragraph[i]);
                return 0;
            case ':':
                getWord(list, optarg);
                break;
            case 'e'://exit
                return 0;
            default:
                readInput (list);
        }
    }

    if (print_on_terminal || print_in_html || print_in_txt || print_in_csv)
        printList (list, print_on_terminal, print_in_html, print_in_txt, print_in_csv);
    else
        usage ();

}