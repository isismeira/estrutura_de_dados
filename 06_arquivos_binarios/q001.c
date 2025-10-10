#include <stdio.h>
#include <stdlib.h>

#define WORD_SIZE 10

int main() {
    FILE *fa, *fb, *fc;
    char palavraA[WORD_SIZE], palavraB[WORD_SIZE];

    fa = fopen("..\\a.bin", "rb");
    fb = fopen("..\\b.bin", "rb");
    fc = fopen("..\\c.bin", "wb");

    if (fa == NULL || fb == NULL || fc == NULL) {
        perror("Erro ao abrir arquivos");
        return 1;
    }


    while (fread(palavraA, sizeof(char), WORD_SIZE, fa) == WORD_SIZE) {
        // Volta ao início de b.bin para cada nova palavra de a.bin
        fseek(fb, 0, SEEK_SET);

        while (fread(palavraB, sizeof(char), WORD_SIZE, fb) == WORD_SIZE) {
            fwrite(palavraA, sizeof(char), WORD_SIZE, fc);
            fwrite(palavraB, sizeof(char), WORD_SIZE, fc);
        }
    }

    fclose(fa);
    fclose(fb);
    fclose(fc);

    printf("Arquivo c.bin gerado com sucesso!\n");
    return 0;
}
