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

void 
insertWord(List *list, int paragraph_number, char* wordBuffer)
{
    Node *new;
    int i;

    if(list->head==NULL)
    {    
        Node *new;
        if((new = (Node*) malloc(sizeof(Node)))==NULL)
            return -1;
        for(i=0; i<30;i++)
        {
            new->word[i] = '\0';
        }
                    
        //zera os paragrafos do novo Node
        for(i=0; i<25;i++)
        {
            new->paragraph[i] = 0;
        }
        i=0;
        int j = 0;
        while(wordBuffer[j] != '\0'){
            new->word[j] = wordBuffer[j];
            j++;
        }
        j = 0;

        while (new->paragraph[j] != 0)
        {
            j++;
        }
        new->paragraph[j]=paragraph_number;

        new -> next = NULL;
        list -> head = new;
        list -> tail = new;

        list->listSize++;
        printf("INSERIDO COM SUCESSO\n");
    }
    else
    if(isEqual(list,wordBuffer)==0){

        int i;
        Node *new;
        if((new = (Node*) malloc(sizeof(Node)))==NULL)
            return -1;  

        //insere \0 nas palavras do novo Node
        for(i=0; i<30;i++)
        {
            new->word[i] = '\0';
        }
                    
        //zera os paragrafos do novo Node
        for(i=0; i<25;i++)
        {
        new->paragraph[i] = 0;
        }
        i=0;

        int j = 0;
        while(wordBuffer[j] != '\0'){
            new->word[j] = wordBuffer[j];
            j++;
        }
        j = 0;

        while (new->paragraph[j] != 0)
        {
        j++;
        }
        new->paragraph[j]=paragraph_number;

        new->next=list->head;
        list->head=new;
        
        list->listSize++;
        printf("INSERIDO COM SUCESSO\n");
    }else{
        Node *aux = list->head;
    
        while(aux != NULL){

            int retorno = stricmp(wordBuffer, aux->word);
            //se 0 entao sao iguais
            if(retorno == 0)
            {                   
                for(int i=0;i<25;i++)
                {
                    if(aux->paragraph[i]==0)
                    {
                        aux->paragraph[i]=paragraph_number;
                        break;
                    }
                }
            }
            aux = aux->next; 
        }
    }
}

void sort(List *list){
    if(list->listSize>1)
    {
        Node *node = list->head;
       
       while(node!=NULL)
       {
            Node *nodeNext = node->next;
            while (nodeNext!=NULL)
            {
                int retorno = stricmp(node->word,nodeNext->word);
                if(retorno>0)
                {
                    swap(node,nodeNext);
                    node = nodeNext;
                    nodeNext = nodeNext->next;                                        
                }
                else
                if(retorno<0||retorno==0)
                {
                    node = nodeNext;
                    nodeNext = nodeNext->next;
                }
                else{
                    break;
                }
            }
       }
    }  
}

void swap(Node *node, Node* nodeNext)
{
    //aux <- node
    char auxWord[30];
    int i = 0;
    int auxParagraph[25];

    while(i<30)
    {
        auxWord[i]= node->word[i];
        i++;
    }
    i=0;
    while(i<25)
    {
        auxParagraph[i]= node->paragraph[i];
        i++;
    }
    i=0;
    //node <- nodeNext
    while(i<30)
    {
        node->word[i] = nodeNext->word[i];
         i++;
    }
    i=0;
    while(i<25)
    {
        node->paragraph[i]=nodeNext->paragraph[i];
        i++;
    }
    i=0;
    //nodeNext <- aux
    while(i<30)
    {
        nodeNext->word[i]= auxWord[i];
        i++;
    }
        i=0;
    while(i<25)
    {
        nodeNext->paragraph[i]=auxParagraph[i];
         i++;
    }
}

int isEqual(List *list, char *word){

    Node *aux = list->head;
    
    while(aux != NULL){

        int retorno = stricmp(word, aux->word);
        //se 0 entao sao iguais
        if(retorno == 0){
            return 1;
        }
        aux = aux->next; 
    }
    return 0;//se forem iguais
}

void readInput(List *list)
{
    Node *new;
    FILE *input = fopen("input.txt","r");

    char test;
    int n = 0;
    int paragraph_number = 1;
    char word[30];
    int i;

    for(i=0; i<30;i++){
        word[i] = '\0';
    }
    i=0;

    while(fgets(line_buffer, BUFFERSIZE, input))
    {   
        while(test = line_buffer[n]){

            if (test =='\n'){
                //PRECISA DE MAIS UM IF PARA CASO O ARQUIVO TENHA ACABADO
                if(line_buffer[n+1]=='\0'){
                    insertWord(list,paragraph_number,&word);
                    for(i=0; i<30;i++){
                        word[i] = '\0';
                    }
                    paragraph_number++;
                    n=0;
                    i=0;
                    break;
                }
                else{
                   insertWord(list,paragraph_number,&word);
                    paragraph_number++;
                    n=0;
                    for(i=0; i<30;i++){
                    word[i] = '\0';
                    }
                    i=0;
                    break;
                } 
            
            }
            else                
            if((test == 39)
                || (test >= 65 && test <= 90)
                || (test >= 97 && test <= 122))
            {
                word[i] = test;
                i++;
                n++;
            }
            else
            if(test == ' '){
                   
                insertWord(list,paragraph_number,&word);

                n++;
                
                for(i=0; i<30;i++){
                    word[i] = '\0';
                }
                i=0;
            }
            else{
                if(line_buffer[n+1]=='\n'){

                    //if(line_buffer[n+2]=='\0') break;
                
                    insertWord(list,paragraph_number,&word);

                    paragraph_number++;
                    n=0;
                    for(i=0; i<30;i++){
                    word[i] = '\0';                    
                    }

                    i=0;
                    break;
                }else{
                    n++;
                }
            }
        }
    }
}

void printList(List *list)
{   
    int x=0;
    Node *aux = list->head;
    printf("Tamanho da lista = %d\n",list->listSize);
    while(aux != NULL){
        printf("%s -> ",aux->word);
        printf("Paragrafo: ");
                
        while (aux->paragraph[x]> 0)
        {
            printf("%d, ", aux->paragraph[x]);
            x++;
        }
        printf("\n");
        x=0;
        aux = aux->next; 
    }
}

int main (int argc, char **argv)
{
    List *list;

    if(((list = (List*)malloc(sizeof(List))) == NULL))
        return -1;
    
    newList(list);
    readInput(list);
    sort(list);
    printList(list);

    int i;
    for (i = 0; i < argc; i ++)
    {
        printf("%d- Parametro = \"%s\"\n", i + 1, argv[i]);
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
                readInput(list);

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