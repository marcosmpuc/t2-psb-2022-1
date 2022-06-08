#include <stdio.h>

#define BUFFERSIZE 1
#define LONGEST_ACCEPTED_WORD 1024

int main(void) {
  char *buffer;             // Aponta para o buffer de leitura e escrita.
  char *palavra;            // Aponta para um buffer de tamanho dinâmico, que reconstruirá palavras individuais.
  int inputFileDescriptor;  // Define qual arquivo será o arquivo de entrada.
  int outputFileDescriptor; // Define qual arquivo será o arquivo de saída.
  int progresso = 0;        // Conta quantos caracteres foram adicionados ao buffer iniciado pelo pointer "palavra".

  while (*buffer) // Teste implícito: um char "falso" é apenas aquele é que
                  // termina uma string
  {
    read(inputFileDescriptor, buffer,
         BUFFERSIZE);                         // Lê o arquivo de entrada, caractere por caractere.
    if ((*buffer == 39)                       // Se o último caractere lido é um apóstrofo, ou ...
        || (*buffer >= 65 && *buffer <= 90)   // uma letra maiúscula, ou ...
        || (*buffer >= 97 && *buffer <= 122)) // uma letra minúscula, ...
    {                                         // executa o seguinte:
      char *endereco = palavra + progresso++; //   cria um pointer temporário que aponta ao primeiro byte que pode receber o último caractere lido;
      endereco = buffer;                      //   e torna o caractere lido o último caractere conhecido da palavra reconstruída.
    }
    else                                                // Se o if da linha 18 falhou, ...
    {                                                   // executa o seguinte:
      progresso = 0;                                    // reinicia o contador de caracteres úteis encontrados, 
      write(outputFileDescriptor, palavra, BUFFERSIZE); // escreve a palavra reconstruída no arquivo de saída.
    }
  }
}