#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/tartarugas.h"


void inicializarTartarugas(Tartaruga **tartarugas, int *numTartarugas)
{
    *numTartarugas = 4;
    *tartarugas = (Tartaruga *)malloc(*numTartarugas * sizeof(Tartaruga));
    if (*tartarugas == NULL)
    {
        perror("Erro ao alocar memória para tartarugas");
        exit(EXIT_FAILURE);
    }

    strcpy((*tartarugas)[0].nome, "Leonardo");
    (*tartarugas)[0].status = DISPONIVEL;
    (*tartarugas)[0].nivel = 5.0;
    (*tartarugas)[0].missoesFerido = 0;

    strcpy((*tartarugas)[1].nome, "Donatello");
    (*tartarugas)[1].status = DISPONIVEL;
    (*tartarugas)[1].nivel = 5.0;
    (*tartarugas)[1].missoesFerido = 0;

    strcpy((*tartarugas)[2].nome, "Raphael");
    (*tartarugas)[2].status = DISPONIVEL;
    (*tartarugas)[2].nivel = 5.0;
    (*tartarugas)[2].missoesFerido = 0;

    strcpy((*tartarugas)[3].nome, "Michelangelo");
    (*tartarugas)[3].status = DISPONIVEL;
    (*tartarugas)[3].nivel = 5.0;
    (*tartarugas)[3].missoesFerido = 0;
}


void listarStatusTartarugas(const Tartaruga *tartarugas, int numTartarugas)
{
    printf("\n--- STATUS DAS TARTARUGAS NINJA ---\n");
    for (int i = 0; i < numTartarugas; i++)
    {
        printf("Nome: %s\n", tartarugas[i].nome);
        printf("  Status: ");
        switch (tartarugas[i].status)
        {
        case DISPONIVEL:
            printf("Disponível\n");
            break;
        case EM_MISSAO:
            printf("Em Missão\n");
            break;
        case FERIDO:
            printf("Ferido (Indisponível por %d missões)\n", tartarugas[i].missoesFerido);
            break;
        }
        printf("  Nível: %.1f\n", tartarugas[i].nivel);
        printf("----------------------------------\n");
    }
}

void resetarTartarugas(Tartaruga *tartarugas, int numTartarugas)
{
    if (tartarugas == NULL)
    {
        printf("Erro: Ponteiro de tartarugas é nulo!\n");
        return;
    }

    printf("Resetando todas as tartarugas para os valores padrão...\n");

    for (int i = 0; i < numTartarugas; i++)
    {
        tartarugas[i].status = DISPONIVEL;
        tartarugas[i].nivel = 5.0;
        tartarugas[i].missoesFerido = 0;
    }

    printf("Tartarugas resetadas com sucesso!\n");
    printf("Todas estão com nível 5.0 e disponíveis para missões!\n");
}