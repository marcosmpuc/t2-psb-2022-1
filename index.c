#include <stdio.h>

#define BUFFERSIZE 1

int exportTXT

int exportHTML ()
{
  
}

int main (void)
{
  FILE *input;
  input = fopen("text.txt", "r");

  FILE *output;
  output = fopen("output.txt", "w");

  if(input == NULL) 
  {
    printf("Não foi possível abrir o arquivo.\n");
    getchar();  
    exit(0);
  }

  char *buffer;             // Aponta para o buffer de leitura e escrita.
  char *word;               // Aponta para um buffer de tamanho dinâmico, que reconstruirá palavras individuais.
  //int inputFileDescriptor;  // Define qual arquivo será o arquivo de entrada.
  //int outputFileDescriptor; // Define qual arquivo será o arquivo de saída.
  int progress = 0;         // Conta quantos caracteres foram adicionados ao buffer iniciado pelo pointer "palavra".
  int paragraphCount = 0;   // Conta quantos parágrafos já foram lidos de todo o arquivo de entrada.

  while (*buffer) // Teste implícito: um char "falso" é apenas aquele é que termina uma string.
  {
    read(input, buffer, BUFFERSIZE);  // Lê o arquivo de entrada, caractere por caractere.
    if ((*buffer == 39)                             // Se o último caractere lido é um apóstrofo, ou ...
        || (*buffer >= 65 && *buffer <= 90)         // uma letra maiúscula, ou ...
        || (*buffer >= 97 && *buffer <= 122))       // uma letra minúscula, ...
    {                                               // executa o seguinte:
      char *nextLetter = word + progress++;         // cria um pointer temporário que aponta ao primeiro byte que pode receber o último caractere lido;
      *nextLetter = *buffer;                        // e torna o caractere lido o último caractere conhecido da palavra reconstruída.
    }
    else                                             // Se o if falhou, ...
    {                                                // executa o seguinte:
      progress = 0;                                  // reinicia o contador de caracteres úteis encontrados; 
      write(output, word, BUFFERSIZE);               // escreve a palavra reconstruída no arquivo de saída.
      if (*buffer == '\n')
        paragraphCount++;
    }
  }
}