#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerar_manual(const char *nome) {
    FILE *fp = fopen(nome, "wb");
    if(!fp) {
        printf("Erro ao criar arquivo %s\n", nome);
        return;
    }

    int n, x;
    printf("Quantos números deseja inserir em %s? ", nome);
    scanf("%d", &n);

    printf("Digite os %d números:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        fwrite(&x, sizeof(int), 1, fp);
    }

    fclose(fp);
    printf("Arquivo %s gerado com sucesso!\n\n", nome);
}

void gerar_automatico(const char *nome) {
    FILE *fp = fopen(nome, "wb");
    if(!fp) {
        printf("Erro ao criar arquivo %s\n", nome);
        return;
    }

    int n;
    printf("Quantos números aleatórios deseja gerar em %s? ", nome);
    scanf("%d", &n);

    printf("Gerando %d números aleatórios em %s...\n", n, nome);

    for(int i = 0; i < n; i++) {
        int x = rand() % 1000;  // números entre 0 e 999
        fwrite(&x, sizeof(int), 1, fp);
    }

    fclose(fp);
    printf("Arquivo %s gerado com sucesso!\n\n", nome);
}

int main() {
    srand(time(NULL));

    int modo;

    printf("GERADOR DE ARQUIVOS BINÁRIOS A.bin E B.bin\n");
    printf("-------------------------------------------\n\n");

    printf("Escolha o modo:\n");
    printf("1 - Digitar números manualmente\n");
    printf("2 - Gerar números aleatórios\n");
    printf("\nSua escolha: ");
    scanf("%d", &modo);

    if(modo == 1) {
        gerar_manual("A.bin");
        gerar_manual("B.bin");
    }
    else if(modo == 2) {
        gerar_automatico("A.bin");
        gerar_automatico("B.bin");
    }
    else {
        printf("Opção inválida.\n");
    }

    printf("Pronto! Agora você já pode usar A.bin e B.bin no seu programa.\n");

    return 0;
}
