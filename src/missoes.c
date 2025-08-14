#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../includes/missoes.h"
#include <math.h>

static int proximoIdMissao = 1;


void trocarMissoes(MissaoPendente *a, MissaoPendente *b)
{
    MissaoPendente temp = *a;
    *a = *b;
    *b = temp;
}


void heapify(FilaMissoes *fila, int i)
{
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < fila->tamanho && fila->missoes[esquerda].nivelAmeaca > fila->missoes[maior].nivelAmeaca)
    {
        maior = esquerda;
    }
    if (direita < fila->tamanho && fila->missoes[direita].nivelAmeaca > fila->missoes[maior].nivelAmeaca)
    {
        maior = direita;
    }

    if (esquerda < fila->tamanho && fila->missoes[esquerda].nivelAmeaca == fila->missoes[maior].nivelAmeaca &&
        fila->missoes[esquerda].timestamp < fila->missoes[maior].timestamp)
    {
        maior = esquerda;
    }
    if (direita < fila->tamanho && fila->missoes[direita].nivelAmeaca == fila->missoes[maior].nivelAmeaca &&
        fila->missoes[direita].timestamp < fila->missoes[maior].timestamp)
    {
        maior = direita;
    }

    if (maior != i)
    {
        trocarMissoes(&fila->missoes[i], &fila->missoes[maior]);
        heapify(fila, maior);
    }
}


FilaMissoes *criarFilaMissoes(int capacidade)
{
    FilaMissoes *fila = (FilaMissoes *)malloc(sizeof(FilaMissoes));
    if (fila == NULL)
    {
        perror("Erro ao alocar memória para fila de missões");
        exit(EXIT_FAILURE);
    }
    fila->missoes = (MissaoPendente *)malloc(capacidade * sizeof(MissaoPendente));
    if (fila->missoes == NULL)
    {
        perror("Erro ao alocar memória para missões na fila");
        exit(EXIT_FAILURE);
    }
    fila->capacidade = capacidade;
    fila->tamanho = 0;
    return fila;
}


void inserirMissaoFila(FilaMissoes *fila, MissaoPendente novaMissao)
{
    if (fila->tamanho == fila->capacidade)
    {
        printf("A fila de missões está cheia!\n");
        return;
    }

    novaMissao.id = proximoIdMissao++;
    novaMissao.timestamp = time(NULL);

    fila->tamanho++;
    int i = fila->tamanho - 1;
    fila->missoes[i] = novaMissao;

    
    while (i != 0 &&
           (fila->missoes[(i - 1) / 2].nivelAmeaca < fila->missoes[i].nivelAmeaca ||
            (fila->missoes[(i - 1) / 2].nivelAmeaca == fila->missoes[i].nivelAmeaca &&
             fila->missoes[(i - 1) / 2].timestamp > fila->missoes[i].timestamp)))
    {
        trocarMissoes(&fila->missoes[i], &fila->missoes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void adicionarMissaoPadrao(FilaMissoes *filaMissoes, int escolha)
{
    MissaoPendente novaMissao;

    switch (escolha)
    {
    case 1:
        strcpy(novaMissao.descricao, "Destruidor Chegou!");
        strcpy(novaMissao.local, "Technodrome - Dimensão X");
        novaMissao.nivelAmeaca = 8;
        break;
    case 2:
        strcpy(novaMissao.descricao, "Bebop e Thanos estão roubando o Banco!");
        strcpy(novaMissao.local, "Downtown Manhattan");
        novaMissao.nivelAmeaca = 7;
        break;
    case 3:
        strcpy(novaMissao.descricao, "Clan do Pé atacando o porto");
        strcpy(novaMissao.local, "Porto de Nova York");
        novaMissao.nivelAmeaca = 4;
        break;
    case 4:
        strcpy(novaMissao.descricao, "Krang e suas tropas estão invadindo a cidade");
        strcpy(novaMissao.local, "Centro de Nova York");
        novaMissao.nivelAmeaca = 5;
        break;
    case 5:
        strcpy(novaMissao.descricao, "Tatsu sequestrou o Lula!");
        strcpy(novaMissao.local, "Edifício abandonado - Brasilia");
        novaMissao.nivelAmeaca = 3;
        break;
    default:
        printf("Opção inválida de missão!\n");
        return;
    }

    inserirMissaoFila(filaMissoes, novaMissao);
}

MissaoPendente extrairMissaoPrioritaria(FilaMissoes *fila) {
    if (fila->tamanho <= 0) {
        MissaoPendente missaoVazia = {0};
        printf("Nenhuma missão pendente na fila! A cidade está calma... por enquanto.\n");
        return missaoVazia;
    }
    
    MissaoPendente raiz = fila->missoes[0];
    fila->missoes[0] = fila->missoes[--fila->tamanho];
    if (fila->tamanho > 0) heapify(fila, 0);
    
    return raiz;
}

void exibirMissaoPrioritaria(const FilaMissoes *fila)
{
    if (fila->tamanho == 0)
    {
        printf("Nenhuma missão pendente. Tudo tranquilo no esgoto!\n");
        return;
    }

    MissaoPendente *missao = &fila->missoes[0];
    printf("\n--- MISSÃO DE MAIOR PRIORIDADE ---\n");
    printf("ID: %d\n", missao->id);
    printf("Descrição: %s\n", missao->descricao);
    printf("Local: %s\n", missao->local);
    printf("Nível de Ameaça: %d\n", missao->nivelAmeaca);
    printf("----------------------------------\n");
}

void liberarFilaMissoes(FilaMissoes *fila)
{
    if (fila != NULL)
    {
        free(fila->missoes);
        free(fila);
    }
}



DiarioBordo *criarDiarioBordo()
{
    DiarioBordo *diario = (DiarioBordo *)malloc(sizeof(DiarioBordo));
    if (diario == NULL)
    {
        perror("Erro ao alocar memória para diário de bordo");
        exit(EXIT_FAILURE);
    }
    diario->topo = NULL;
    return diario;
}

void adicionarMissaoConcluida(DiarioBordo *diario, MissaoConcluida novaMissao)
{
    MissaoConcluida *novoNo = (MissaoConcluida *)malloc(sizeof(MissaoConcluida));
    if (novoNo == NULL)
    {
        perror("Erro ao alocar memória para missão concluída");
        exit(EXIT_FAILURE);
    }
    *novoNo = novaMissao;
    novoNo->proximo = diario->topo;
    diario->topo = novoNo;
}

void exibirDiarioBordo(const DiarioBordo *diario)
{
    if (diario->topo == NULL)
    {
        printf("\n--- DIÁRIO DE BORDO DO MESTRE SPLINTER ---\n");
        printf("O diário está vazio. Nenhuma missão concluída ainda... Treinem mais!\n");
        printf("-----------------------------------------\n");
        return;
    }

    printf("\n--- DIÁRIO DE BORDO DO MESTRE SPLINTER ---\n");
    MissaoConcluida *atual = diario->topo;
    while (atual != NULL)
    {
        printf("ID Missão: %d\n", atual->idMissao);
        printf("  Descrição: %s\n", atual->descricao);
        printf("  Resultado: %s\n", atual->resultado);
        printf("-----------------------------------------\n");
        atual = atual->proximo;
    }
}

void liberarDiarioBordo(DiarioBordo *diario)
{
    if (diario != NULL)
    {
        MissaoConcluida *atual = diario->topo;
        while (atual != NULL)
        {
            MissaoConcluida *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        free(diario);
    }
}



void simularBatalha(MissaoPendente *missao, Tartaruga *equipeTartarugas[], int numMembrosEquipe,
                    Equipamento *equipamentosSelecionados[], int numEquipamentos,
                    DiarioBordo *diario, Tartaruga *todasTartarugas, int numTodasTartarugas)
{
    float forcaEquipe = 0.0;
    int bonusFavorito = 0;

   
    for (int i = 0; i < numMembrosEquipe; i++)
    {
        forcaEquipe += equipeTartarugas[i]->nivel;
    }

    
    for (int i = 0; i < numEquipamentos; i++)
    {
        for (int j = 0; j < numMembrosEquipe; j++)
        {
            if (strcmp(equipamentosSelecionados[i]->favoritoDe, equipeTartarugas[j]->nome) == 0)
            {
                forcaEquipe += 0.5;
                bonusFavorito++;
                printf("  (Bônus de +0.5 para %s por usar seu equipamento favorito!)\n",
                       equipeTartarugas[j]->nome);
                break;
            }
        }
    }

    
    forcaEquipe /= numMembrosEquipe;

    printf("\nForça Base da Equipe: %.1f\n", forcaEquipe);
    printf("Bônus de Equipamento Favorito: %.1f\n", bonusFavorito * 0.5);

    
    srand(time(NULL));
    float sorte = (float)(rand() % 5) - 2.0;
    printf("Sorte: %.1f\n", sorte);

    
    float caosMutante = (float)rand() / (float)RAND_MAX;
    printf("Caos Mutante: %.1f\n", caosMutante);

    float resultado = forcaEquipe - missao->nivelAmeaca + sorte - caosMutante;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Cálculo: Força Equipe (%.1f) - Nível Ameaça (%d) + Sorte (%.1f) - Caos Mutante (%.1f) = Resultado Final: %.1f\n",
           forcaEquipe, missao->nivelAmeaca, sorte, caosMutante, resultado);

    MissaoConcluida mc;
    mc.idMissao = missao->id;
    strcpy(mc.descricao, missao->descricao);

    if (resultado > 3.0)
    {
        strcpy(mc.resultado, "Vitória Perfeita!");
        printf("PIZZA PARA TODOS! Vitória Perfeita!\n");
        for (int i = 0; i < numMembrosEquipe; i++)
        {
            equipeTartarugas[i]->status = DISPONIVEL;
            equipeTartarugas[i]->nivel += 0.3;
            printf("%s ganhou +0.3 de nível! (Nível atual: %.1f)\n",
                   equipeTartarugas[i]->nome, equipeTartarugas[i]->nivel);
        }
    }
    else if (resultado >= 0.0 && resultado <= 3.0)
    {
        strcpy(mc.resultado, "Vitória com Custo!");
        printf("Vitória com custo. Precisamos de um tempo para se recuperar.\n");
        
        
        int tartarugaFeridaIdx = rand() % numMembrosEquipe;
        equipeTartarugas[tartarugaFeridaIdx]->status = FERIDO;
        equipeTartarugas[tartarugaFeridaIdx]->missoesFerido = 2; 
        printf("%s está FERIDO! Indisponível por 2 missões. Cuidem-se, amigos!\n",
               equipeTartarugas[tartarugaFeridaIdx]->nome);

        for (int i = 0; i < numMembrosEquipe; i++)
        {
            if (i != tartarugaFeridaIdx)
            {
                equipeTartarugas[i]->status = DISPONIVEL;
                equipeTartarugas[i]->nivel += 0.2;
                printf("%s ganhou +0.2 de nível! (Nível atual: %.1f)\n",
                       equipeTartarugas[i]->nome, equipeTartarugas[i]->nivel);
            }
        }
    }
    else
    { 
        
        strcpy(mc.resultado, "Derrota!");
        printf(" Derrota. O Destruidor vai rir dessa...\n");
        for (int i = 0; i < numMembrosEquipe; i++)
        {
            equipeTartarugas[i]->status = FERIDO;
            equipeTartarugas[i]->missoesFerido = 3;
            printf("%s está FERIDO! Indisponível por 3 missões.\n",
                   equipeTartarugas[i]->nome);
        }
        printf("Sem aumento de nível para ninguém. Precisamos treinar mais!\n");
        printf("A missão falhou e não será registrada no Diário de Bordo. Tentaremos novamente!\n");
        return;
    }

    adicionarMissaoConcluida(diario, mc);

    
    for (int i = 0; i < numTodasTartarugas; i++)
    {
        int participou = 0;
        for (int j = 0; j < numMembrosEquipe; j++)
        {
            if (&todasTartarugas[i] == equipeTartarugas[j])
            {
                participou = 1;
                break;
            }
        }
        if (!participou && todasTartarugas[i].status == FERIDO && todasTartarugas[i].missoesFerido > 0)
        {
            todasTartarugas[i].missoesFerido--;
            if (todasTartarugas[i].missoesFerido == 0)
            {
                todasTartarugas[i].status = DISPONIVEL;
                printf("%s se recuperou dos ferimentos e está DISPONÍVEL novamente!\n",
                       todasTartarugas[i].nome);
            }
        }
    }
}

