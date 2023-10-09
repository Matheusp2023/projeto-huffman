#include <stdio.h>
#include <list.h>
#include <tree.h>
#include <encode.h>

unsigned long long int sizeArchive(FILE *arquivo) {
    // Salva a posição atual do cursor no arquivo
    unsigned long long int posicao_atual = ftell(arquivo);

    // Vá até o final do arquivo
    if (fseek(arquivo, 0, SEEK_END) != 0) {
        perror("Erro ao buscar o final do arquivo");
        return -1; // Retorno de erro
    }
    // Obtenha a posição atual, que é o tamanho do arquivo
    unsigned long long int tamanho = ftell(arquivo);

    if (tamanho == -1) {
        perror("Erro ao obter o tamanho do arquivo");
        return -1; // Retorno de erro
    }

    // Volta para a posição original do cursor no arquivo
    if (fseek(arquivo, posicao_atual, SEEK_SET) != 0) {
        perror("Erro ao retornar para a posição original do arquivo");
        return -1; // Retorno de erro
    }
    return tamanho;
}

void buildTable(Node* tree_node,BitHuff table[],BitHuff code){         
    if(isLeaf(tree_node))
    {
        table[getByteFromVoidPointer(tree_node->byte)] = code;
        return;
    }
    else
    {
        code.size++;
        code.bitH <<= 1;
        if(tree_node->left != NULL)
        buildTable(tree_node->left, table, code);
        code.bitH++;
        if(tree_node->right != NULL)
        buildTable(tree_node->right, table, code);
    }        
}

int trashsize(int frequency[],BitHuff table[]){
    unsigned long long int totalBits = 0;
    for(int i = 0;i < 256;i++){
        if(frequency[i] == 0) continue;
        totalBits += frequency[i] * table[i].size;
    }
    int trash = (8 - (totalBits % 8));
    return trash;
}
/*
    setando o primeiro byte do arquivo
*/
void setFirstByte(FILE *file,int trashSize,int treeSize){
    unsigned char byte_completo = 0x00;
    // setando tamanho do lixo nos tres primeiros bits
    byte_completo = byte_completo | (trashSize << 5);// operação ou bit a bit com o tamanho do lixo 
    // setando os 5 bits mais significativos da árvore
    byte_completo = byte_completo | (treeSize >> 8);// operação ou bit a bit pra setar os 5 primeiro bits do tamanho da árvore
    //escrevendo 
    fwrite(&byte_completo,sizeof(unsigned char),1,file);
}
/*
    setando o segundo byte
*/
void setSecondByte(FILE *file,int treesize){
    unsigned char byte_completo = 0x00; 
    // setando os 8 bits menos significativos da árvore 
    byte_completo = byte_completo | treesize;// operação ou bit a bit com o restante do tamanho da árvore
    fwrite(&byte_completo,sizeof(unsigned char),1,file);
}
/*
    setar a árvore no arquivo compactado
*/
void setTree(FILE *file,struct Node *bt)
{
    if (bt != NULL) {
    unsigned char x = getByteFromVoidPointer(bt->byte);
    if(((x == '*') || (x == '\\')) && isLeaf(bt)){
        unsigned char y = '\\';
        fwrite(&y,sizeof(unsigned char),1,file);
    }
    // seta em pré ordem pois está antes das chamadas recursivas
    fwrite(&x,sizeof(unsigned char),1,file);
    setTree(file,bt->left);
    setTree(file,bt->right);
    }
}
void setBytes(FILE *fileIn,FILE *fileOut,BitHuff table[],int trashSize){
    // buffer size é o tamanho do que já foi setado
    // caractere é o que vai receber os bytes do arquivo
    short buffer_size = 0, caractere;
    // buffer é o que vai ser setado no arquivo
    unsigned char buffer = 0; 
    // aux é o tamanho do que a gente não conseguiu setar e o code_temp vai guardar primeiramente 
    // o que a gente consegue setar depois o que não conseguimos setar como short int(2 bytes)
    unsigned short int aux, code_tmp = 0;
    while((caractere = getc(fileIn)) != EOF)
    {        
        // checa se conseguimos setar todos os bits no buffer
        if((table[caractere].size + buffer_size) <= 8)
        {
            buffer <<= table[caractere].size; // abre espaço para setar a nova codificação
            buffer = buffer | table[caractere].bitH;// seta a nova codificação no buffer
            buffer_size += table[caractere].size;// aumenta o tamanho pra dizer quanto já foi setado
        }    
        // caso não consiga setar todos    
        else 
        {
            aux = table[caractere].size;                         
            buffer <<= (8 - buffer_size);// abre espaço para o quanto a gente CONSEGUE setar
            code_tmp = table[caractere].bitH >> (table[caractere].size - (8 - buffer_size));// code_tmp o quanto a gente consegue setar
            aux -= (8 - buffer_size);// tamanho do que a gente não conseguiu setar(o resto)            
            buffer = buffer | code_tmp;            
            fprintf(fileOut, "%c", buffer);
            buffer = 0;
            buffer_size = aux;// buffer size vai receber o tamanho do resto                
            code_tmp = table[caractere].bitH << (16 - buffer_size);
            code_tmp >>= (16 - buffer_size); // vai guardar o que não conseguimos setar
            buffer = code_tmp;                       
        }
        // se o buffer está cheio
        if(buffer_size == 8)
        {            
            fprintf(fileOut, "%c", buffer);
            buffer = 0;
            buffer_size = 0;
        }
    }    
    // para caso tenha lixo 
    if(buffer_size > 0 && buffer_size < 8)
    {         
        buffer <<= trashSize;//joga os bits setados pro começo do byte     
        fprintf(fileOut, "%c", buffer);
        buffer = 0;
        buffer_size = 0; 
    }
}