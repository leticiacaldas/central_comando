#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/viloes.h"


Vilao* criarVilao(const char *nome, int nivelHabilidade, const char *pontoFraco) {
    Vilao *novoVilao = (Vilao *) malloc(sizeof(Vilao));
    if (novoVilao == NULL) {
        perror("Erro ao alocar memória para vilão");
        exit(EXIT_FAILURE);
    }
    strcpy(novoVilao->nome, nome);
    novoVilao->nivelHabilidade = nivelHabilidade;
    strcpy(novoVilao->pontoFraco, pontoFraco);
    novoVilao->esquerda = NULL;
    novoVilao->direita = NULL;
    return novoVilao;
}

void adicionarVilaoPadrao(Vilao **raizViloes, int escolha)
{
    char nome[50], pontoFraco[100];
    int nivel;

    switch (escolha)
    {
    case 1:
        strcpy(nome, "Destruidor");
        nivel = 10;
        strcpy(pontoFraco, "Orgulho e arrogância");
        break;
    case 2:
        strcpy(nome, "Krang");
        nivel = 9;
        strcpy(pontoFraco, "Alergia a polen");
        break;
    case 3:
        strcpy(nome, "Bebop");
        nivel = 6;
        strcpy(pontoFraco, "Burrice e impulsividade");
        break;
    case 4:
        strcpy(nome, "Thanos");
        nivel = 6;
        strcpy(pontoFraco, "Lentidão mental");
        break;
    case 5:
        strcpy(nome, "Tatsu");
        nivel = 8;
        strcpy(pontoFraco, "Código de honra ninja");
        break;
    default:
        printf("Opção inválida de vilão!\n");
        return;
    }

    Vilao *novo = criarVilao(nome, nivel, pontoFraco);
    *raizViloes = inserirVilao(*raizViloes, novo);
}


Vilao* inserirVilao(Vilao *raiz, Vilao *novoVilao) {
    if (raiz == NULL) {
        return novoVilao;
    }
    int comparacao = strcmp(novoVilao->nome, raiz->nome);
    if (comparacao < 0) {
        raiz->esquerda = inserirVilao(raiz->esquerda, novoVilao);
    } else if (comparacao > 0) {
        raiz->direita = inserirVilao(raiz->direita, novoVilao);
    } else {
        printf("Vilão com o nome '%s' já existe.\n", novoVilao->nome);
        free(novoVilao); // vilão duplicado
    }
    return raiz;
}


Vilao* buscarVilao(Vilao *raiz, const char *nome) {
    if (raiz == NULL || strcmp(raiz->nome, nome) == 0) {
        return raiz;
    }
    if (strcmp(nome, raiz->nome) < 0) {
        return buscarVilao(raiz->esquerda, nome);
    } else {
        return buscarVilao(raiz->direita, nome);
    }
}


Vilao* encontrarMinimo(Vilao *no) {
    Vilao *atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}


Vilao* removerVilao(Vilao *raiz, const char *nome) {
    if (raiz == NULL) {
        return raiz;
    }

    int comparacao = strcmp(nome, raiz->nome);
    if (comparacao < 0) {
        raiz->esquerda = removerVilao(raiz->esquerda, nome);
    } else if (comparacao > 0) {
        raiz->direita = removerVilao(raiz->direita, nome);
    } else {
        
        if (raiz->esquerda == NULL) {
            Vilao *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Vilao *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        Vilao *temp = encontrarMinimo(raiz->direita);

        
        strcpy(raiz->nome, temp->nome);
        raiz->nivelHabilidade = temp->nivelHabilidade;
        strcpy(raiz->pontoFraco, temp->pontoFraco);

        
        raiz->direita = removerVilao(raiz->direita, temp->nome);
    }
    return raiz;
}


void exibirViloesEmOrdem(Vilao *raiz) {
    if (raiz != NULL) {
        exibirViloesEmOrdem(raiz->esquerda);
        printf("Nome: %s\n", raiz->nome);
        printf("  Nível de Habilidade: %d\n", raiz->nivelHabilidade);
        printf("  Ponto Fraco: %s\n", raiz->pontoFraco);
        printf("----------------------------------\n");
        exibirViloesEmOrdem(raiz->direita);
    }
}

void liberarArvoreViloes(Vilao *raiz) {
    if (raiz != NULL) {
        liberarArvoreViloes(raiz->esquerda);
        liberarArvoreViloes(raiz->direita);
        free(raiz);
    }
}