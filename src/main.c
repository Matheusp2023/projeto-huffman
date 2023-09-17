#include <stdio.h>

#define MAX 100

int main()
{
    FILE *archive;
    char file_path[MAX]; // Arrey que armazena o nome do arquivo
    printf("Digite o caminho da pasta do arquivo: ");
    scanf("%s", file_path);

    // Abre o arquivo para leitura
    archive = fopen(file_path, "rb");

    // Caso de erro na leitura do arquivo
    if (archive == NULL)
    {
        perror("Erro ao abrir o arquivo");
    }
    
    unsigned char byte; // Variavel que armazenara cada bit temporariamente

    // Le cada byte do arquivo
    while (fread(&byte, sizeof(unsigned char), 1, archive) == 1)
    {
        // Processa cada bit do byte
        for (int i = 7; i >= 0; i--)
        {
            // Extrair o valor do bit
            int bit = (byte >> i) & 1;

            printf("%d", bit);
        }
        printf("\n");
    }

    // Fecha o arquivo
    fclose(archive);
    
    return 0;
}