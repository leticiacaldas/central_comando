#ifndef VILOES_H
#define VILOES_H

#include <stdlib.h> 


typedef struct Vilao {
    char nome[50];
    int nivelHabilidade;
    char pontoFraco[100];
    struct Vilao *esquerda;
    struct Vilao *direita;
} Vilao;


Vilao* criarVilao(const char *nome, int nivelHabilidade, const char *pontoFraco);
Vilao* inserirVilao(Vilao *raiz, Vilao *novoVilao);
Vilao* buscarVilao(Vilao *raiz, const char *nome);
void adicionarVilaoPadrao(Vilao **raizViloes, int escolha);
Vilao* encontrarMinimo(Vilao *no);
Vilao* removerVilao(Vilao *raiz, const char *nome);
void exibirViloesEmOrdem(Vilao *raiz);
void liberarArvoreViloes(Vilao *raiz);
void exibirMenuViloesPadrao(void);

#endif