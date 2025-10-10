/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("..\\clientes.bin", "rb");
    char cpf_procurado[] = "12345678901\0";

    while(1) {
        char nome[40];
        char cpf[11];
        int conta;
        int agencia;
        float saldo;
        if (fscanf(fp, "%s%s%i%i%f", nome, cpf, &conta, &agencia, &saldo) != 5) break;

        if(strcmp(cpf_procurado, cpf) == 0) {
            printf("%s", nome);
            printf("%s", cpf);
            printf("%i", conta);
            printf("%f", saldo);
        }
    }

    return 0;
} 
*/       


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura do registro (63 bytes no total)
typedef struct {
    char nome[40];          // 40 bytes
    char cpf[11];           // 11 bytes
    int conta_corrente;     // 4 bytes
    int agencia;           // 4 bytes
    float saldo;           // 4 bytes
} Cliente;                 // Total: 63 bytes

int main() {
    FILE *fp = fopen("..\\clientes.bin", "rb");
    
    if (fp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    char cpf_procurado[12] = "12345678901"; // Inclui espaço para o null terminator
    
    Cliente cliente;
    
    // Lê registro por registro até o final do arquivo
    while(fread(&cliente, sizeof(Cliente), 1, fp) == 1) {
        printf("Lendo cliente %s ; cpf: %s\n", cliente.nome, cliente.cpf);
        
        if(strcmp(cpf_procurado, cliente.cpf) == 0) {
            printf("Cliente encontrado:\n");
            printf("Nome: %s\n", cliente.nome);
            printf("CPF: %s\n", cliente.cpf);
            printf("Conta: %d\n", cliente.conta_corrente);
            printf("Agência: %d\n", cliente.agencia);
            printf("Saldo: %.2f\n", cliente.saldo);
            break;
        }
    }
    
    fclose(fp);
    return 0;
}