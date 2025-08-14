#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/equipamentos.h"


Equipamento *criarEquipamento(const char *nome, const char *favoritoDe)
{
    Equipamento *novoEquipamento = (Equipamento *)malloc(sizeof(Equipamento));
    if (novoEquipamento == NULL)
    {
        perror("Erro ao alocar memória para equipamento");
        exit(EXIT_FAILURE);
    }
    strcpy(novoEquipamento->nome, nome);
    strcpy(novoEquipamento->favoritoDe, favoritoDe);
    novoEquipamento->proximo = NULL;
    return novoEquipamento;
}


Equipamento *adicionarEquipamento(Equipamento *lista, Equipamento *novoEquipamento)
{
    if (lista == NULL)
    {
        return novoEquipamento;
    }
    Equipamento *atual = lista;
    while (atual->proximo != NULL)
    {
        atual = atual->proximo;
    }
    atual->proximo = novoEquipamento;
    return lista;
}


void listarEquipamentos(Equipamento *lista)
{
    if (lista == NULL)
    {
        printf("O Arsenal está vazio, precisamos de mais equipamentos!\n");
        return;
    }
    printf("\n--- ARSENAL DA CENTRAL DE COMANDO ---\n");
    Equipamento *atual = lista;
    int i = 1;
    while (atual != NULL)
    {
        printf("%d. Nome: %s\n", i++, atual->nome);
        if (strlen(atual->favoritoDe) > 0)
        {
            printf("   Favorito de: %s\n", atual->favoritoDe);
        }
        printf("----------------------------------\n");
        atual = atual->proximo;
    }
}


void liberarListaEquipamentos(Equipamento *lista)
{
    Equipamento *atual = lista;
    while (atual != NULL)
    {
        Equipamento *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}


Equipamento *carregarEquipamentos(void)
{
    Equipamento *lista = NULL;
    lista = adicionarEquipamento(lista, criarEquipamento("Katanas", "Leonardo"));
    lista = adicionarEquipamento(lista, criarEquipamento("Bo", "Donatello"));
    lista = adicionarEquipamento(lista, criarEquipamento("Nunchakus", "Michelangelo"));
    lista = adicionarEquipamento(lista, criarEquipamento("Sai", "Raphael"));
    lista = adicionarEquipamento(lista, criarEquipamento("Bumerangue-Pizza", ""));
    lista = adicionarEquipamento(lista, criarEquipamento("Comunicador-Casco", ""));
    return lista;
}


Equipamento *buscarEquipamentoPorNome(Equipamento *lista, const char *nome)
{
    Equipamento *atual = lista;
    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL; 
}