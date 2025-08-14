#ifndef MISSOES_H
#define MISSOES_H

#include "tartarugas.h"
#include "equipamentos.h"


typedef struct {
    int id;
    char descricao[200];
    char local[100];
    int nivelAmeaca;
    long long timestamp; 
} MissaoPendente;


typedef struct {
    MissaoPendente *missoes;
    int capacidade;
    int tamanho;
} FilaMissoes;


typedef struct MissaoConcluida {
    int idMissao;
    char descricao[200];
    char resultado[50]; 
    
    struct MissaoConcluida *proximo;
} MissaoConcluida;


typedef struct {
    MissaoConcluida *topo;
} DiarioBordo;


FilaMissoes* criarFilaMissoes(int capacidade);
void inserirMissaoFila(FilaMissoes *fila, MissaoPendente novaMissao);
MissaoPendente extrairMissaoPrioritaria(FilaMissoes *fila);
void adicionarMissaoPadrao(FilaMissoes *filaMissoes, int escolha);
void exibirMissaoPrioritaria(const FilaMissoes *fila);
void exibirMenuMissoesPadrao(void);
void liberarFilaMissoes(FilaMissoes *fila);


DiarioBordo* criarDiarioBordo();
void adicionarMissaoConcluida(DiarioBordo *diario, MissaoConcluida novaMissao);
void exibirDiarioBordo(const DiarioBordo *diario);
void liberarDiarioBordo(DiarioBordo *diario);


void simularBatalha(MissaoPendente *missao, Tartaruga *equipeTartarugas[], int numMembrosEquipe, Equipamento *equipamentosSelecionados[], int numEquipamentos, DiarioBordo *diario, Tartaruga *todasTartarugas, int numTodasTartarugas);


#endif 
