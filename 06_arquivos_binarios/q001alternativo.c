#include <stdio.h>
#include <stdlib.h>

#define WORD_SIZE 10

int main() {
    FILE *fa, *fb, *fc;
    char palavraA[WORD_SIZE], palavraB[WORD_SIZE];

    fa = fopen("..\\a.bin", "rb");
    fb = fopen("..\\b.bin", "rb");
    fc = fopen("..\\c_2.bin", "wb+");

    if (fa == NULL || fb == NULL || fc == NULL) {
        perror("Erro ao abrir arquivos");
        return 1;
    }

    // Lê uma palavra de cada arquivo por vez até que um dos arquivos termine
    while(1) {
        if (fread(palavraA, sizeof(char), WORD_SIZE, fa) != WORD_SIZE){
            break;
        } 

        if (fread(palavraB, sizeof(char), WORD_SIZE, fb) != WORD_SIZE) {
            break;
        }
        
        fwrite(palavraA, sizeof(char), WORD_SIZE, fc);
        fwrite(palavraB, sizeof(char), WORD_SIZE, fc);
    }

    fclose(fa);
    fclose(fb);
    fclose(fc);

    printf("Arquivo c.bin gerado com sucesso!\n");
    return 0;
}