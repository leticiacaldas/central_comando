#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../includes/tartarugas.h"
#include "../includes/viloes.h"
#include "../includes/missoes.h"
#include "../includes/equipamentos.h"

#define MAX_MISSOES_PENDENTES 10

void limparBufferEntrada();
int lerInteiro();
float lerFloat();
void lerString(char *buffer, int tamanho);
void exibirMenuPrincipal();
void menuGerenciarTartarugas(Tartaruga *tartarugas, int numTartarugas);
void menuPainelAlertasMissoes(FilaMissoes *filaMissoes);
void menuArquivosViloes(Vilao **raizViloes);
void menuArsenalPlanoAcao(Tartaruga *todasTartarugas, int numTartarugas, FilaMissoes *filaMissoes, Equipamento *listaEquipamentos, DiarioBordo *diario);
void menuDiarioBordo(DiarioBordo *diario);
void adicionarMissaoPadrao(FilaMissoes *filaMissoes, int escolha);
void adicionarVilaoPadrao(Vilao **raizViloes, int escolha);

int main()
{
    // Inicialização
    Tartaruga *todasTartarugas = NULL;
    int numTartarugas = 0;
    inicializarTartarugas(&todasTartarugas, &numTartarugas);

    Vilao *raizViloes = NULL; 

    FilaMissoes *filaMissoes = criarFilaMissoes(MAX_MISSOES_PENDENTES); 

    Equipamento *listaEquipamentos = carregarEquipamentos(); 

    DiarioBordo *diario = criarDiarioBordo(); 

    int escolha;
    do
    {
        exibirMenuPrincipal();
        printf("Sua escolha : ");
        escolha = lerInteiro();

        switch (escolha)
        {
        case 1:
            menuGerenciarTartarugas(todasTartarugas, numTartarugas);
            break;
        case 2:
            menuPainelAlertasMissoes(filaMissoes);
            break;
        case 3:
            menuArquivosViloes(&raizViloes);
            break;
        case 4:
            menuArsenalPlanoAcao(todasTartarugas, numTartarugas, filaMissoes, listaEquipamentos, diario);
            break;
        case 5:
            menuDiarioBordo(diario);
            break;
        case 0:
            printf("\nEncerrando sistema... Não deixem o Destruidor invadir o sistema!\n");
            break;
        default:
            printf("Opção inválida, tente novamente !\n");
            break;
        }
        printf("\nPressione Enter para continuar...");
        limparBufferEntrada();
        getchar();
    } while (escolha != 0);

    free(todasTartarugas);
    liberarArvoreViloes(raizViloes);
    liberarFilaMissoes(filaMissoes);
    liberarListaEquipamentos(listaEquipamentos);
    liberarDiarioBordo(diario);

    return 0;
}

// --- Funções Auxiliares de I/O ---

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int lerInteiro()
{
    int num;
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        if (sscanf(buffer, "%d", &num) == 1)
        {
            return num;
        }
    }
    printf("Entrada inválida. Por favor, digite um número inteiro.\n");
    return -1;
}

float lerFloat()
{
    float num;
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        if (sscanf(buffer, "%f", &num) == 1)
        {
            return num;
        }
    }
    printf("Entrada inválida. Por favor, digite um número decimal.\n");
    return -1.0; // erro
}

void lerString(char *buffer, int tamanho)
{
    if (fgets(buffer, tamanho, stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = 0;
    }
    else
    {
        buffer[0] = '\0';
    }
}

// --- Menus ---

void exibirMenuPrincipal()
{
    printf("\n--- CENTRAL DE COMANDO DAS TARTARUGAS NINJA ---\n");
    printf("1. Gerenciar Tartarugas\n");
    printf("2. Painel de Alertas de Missões\n");
    printf("3. Arquivos de Vilões\n");
    printf("4. Arsenal e Plano de Ação (Iniciar Missão)\n");
    printf("5. Diário de Bordo do Mestre Splinter\n");
    printf("0. Sair\n");
    printf("------------------------------------------------\n");
}

void menuGerenciarTartarugas(Tartaruga *tartarugas, int numTartarugas)
{
    system("clear || cls");
    int escolha;
    do
    {
        printf("\n--- GERENCIAR TARTARUGAS NINJA ---\n");
        printf("1. Ver Status das Tartarugas\n");
        printf("2. Resetar Todas as Tartarugas\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("---------------------------------\n");
        printf("Sua escolha: ");
        escolha = lerInteiro();

        switch (escolha)
        {
        case 1:
            listarStatusTartarugas(tartarugas, numTartarugas);
            break;
        case 2:
        {
            printf("\n  ATENÇÃO: Isso irá resetar todas as tartarugas para nível 5.0 e status disponível!\n");
            printf("Deseja continuar? (s/n): ");
            char resposta[10];
            lerString(resposta, sizeof(resposta));
            if (tolower(resposta[0]) == 's')
            {
                resetarTartarugas(tartarugas, numTartarugas);
            }
            else
            {
                printf("Reset cancelado. As tartarugas permanecem como estavam.\n");
            }
            break;
        }
        case 0:
            printf("Voltando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida, tente novamente.\n");
            break;
        }
        if (escolha != 0)
        {
            printf("\nPressione Enter para continuar...");
            limparBufferEntrada();
            getchar();
        }
        system("clear || cls");
    } while (escolha != 0);
}

void menuPainelAlertasMissoes(FilaMissoes *filaMissoes)
{
    system("clear || cls");
    int escolha;
    do
    {
        printf("\n--- PAINEL DE ALERTAS DE MISSÕES ---\n");
        printf("1. Exibir Missão de Maior Prioridade\n");
        printf("2. Adicionar Nova Missão Personalizada\n");
        printf("3. Adicionar Missão Pré-definida\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("-----------------------------------\n");
        printf("Sua escolha: ");
        escolha = lerInteiro();

        switch (escolha)
        {
        case 1:
            exibirMissaoPrioritaria(filaMissoes);
            break;
        case 2:
        {
            MissaoPendente novaMissao;
            printf("Descrição da Missão: ");
            lerString(novaMissao.descricao, sizeof(novaMissao.descricao));
            printf("Local da Missão: ");
            lerString(novaMissao.local, sizeof(novaMissao.local));
            printf("Nível de Ameaça (1-10): ");
            novaMissao.nivelAmeaca = lerInteiro();
            if (novaMissao.nivelAmeaca < 1 || novaMissao.nivelAmeaca > 10)
            {
                printf("Nível de ameaça inválido. Deve ser entre 1 e 10.\n");
                break;
            }
            inserirMissaoFila(filaMissoes, novaMissao);
            printf("Alerta de missão recebido! A cidade conta com vocês!\n");
            break;
        }
        case 3:
        {
            exibirMenuMissoesPadrao();
            printf("Escolha uma missão (1-5): ");
            int escolhaMissao = lerInteiro();
            if (escolhaMissao >= 1 && escolhaMissao <= 5)
            {
                adicionarMissaoPadrao(filaMissoes, escolhaMissao);
                printf("Missão adicionada à fila de alertas!\n");
            }
            else
            {
                printf("Opção inválida. Escolha entre 1 e 5.\n");
            }
            break;
        }
        case 0:
            printf("Voltando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida, tente novamente.\n");
            break;
        }
        if (escolha != 0)
        {
            printf("\nPressione Enter para continuar...");
            limparBufferEntrada();
            getchar();
        }
        system("clear || cls");
    } while (escolha != 0);
}

void menuArquivosViloes(Vilao **raizViloes)
{
    system("clear || cls");
    int escolha;
    do
    {
        printf("\n--- ARQUIVOS DE VILÕES ---\n");
        printf("1. Listar Todos os Vilões\n");
        printf("2. Adicionar Novo Vilão (Personalizado)\n");
        printf("3. Adicionar Vilão Pré-definido\n");
        printf("4. Buscar Vilão por Nome\n");
        printf("5. Remover Vilão por Nome\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("--------------------------\n");
        printf("Sua escolha: ");
        escolha = lerInteiro();

        switch (escolha)
        {
        case 1:
            if (*raizViloes == NULL)
            {
                printf("Nenhum vilão registrado. O submundo está calmo por agora.\n");
            }
            else
            {
                printf("\n--- VILÕES REGISTRADOS ---\n");
                exibirViloesEmOrdem(*raizViloes);
            }
            break;
        case 2:
        {
            char nome[50], pontoFraco[100];
            int nivel;
            printf("Nome do Vilão: ");
            lerString(nome, sizeof(nome));
            printf("Nível de Habilidade (1-10): ");
            nivel = lerInteiro();
            if (nivel < 1 || nivel > 10)
            {
                printf("Nível de habilidade inválido. Deve ser entre 1 e 10.\n");
                break;
            }
            printf("Ponto Fraco: ");
            lerString(pontoFraco, sizeof(pontoFraco));
            Vilao *novo = criarVilao(nome, nivel, pontoFraco);
            *raizViloes = inserirVilao(*raizViloes, novo);
            printf("Vilão %s adicionado aos arquivos!\n", nome);
            break;
        }
        case 3:
        {
            exibirMenuViloesPadrao();
            printf("Escolha um vilão (1-5): ");
            int escolhaVilao = lerInteiro();
            if (escolhaVilao >= 1 && escolhaVilao <= 5)
            {
                adicionarVilaoPadrao(raizViloes, escolhaVilao);
                printf("Vilão adicionado aos arquivos! Cuidado, ele está por aí!\n");
            }
            else
            {
                printf("Opção inválida. Escolha entre 1 e 5.\n");
            }
            break;
        }
        case 4:
        {
            char nomeBusca[50];
            printf("Nome do Vilão a buscar: ");
            lerString(nomeBusca, sizeof(nomeBusca));
            Vilao *encontrado = buscarVilao(*raizViloes, nomeBusca);
            if (encontrado != NULL)
            {
                printf("\n--- VILÃO ENCONTRADO ---\n");
                printf("Nome: %s\n", encontrado->nome);
                printf("  Nível de Habilidade: %d\n", encontrado->nivelHabilidade);
                printf("  Ponto Fraco: %s\n", encontrado->pontoFraco);
                printf("--------------------------\n");
            }
            else
            {
                printf("Vilão '%s' não encontrado. Ufa, menos um problema!\n", nomeBusca);
            }
            break;
        }
        case 5:
        {
            char nomeRemover[50];
            printf("Nome do Vilão a remover: ");
            lerString(nomeRemover, sizeof(nomeRemover));
            Vilao *vilaoEncontrado = buscarVilao(*raizViloes, nomeRemover);
            if (vilaoEncontrado != NULL)
            {
                *raizViloes = removerVilao(*raizViloes, nomeRemover);
                printf("Vilão %s removido dos arquivos. Missão cumprida!\n", nomeRemover);
            }
            else
            {
                printf("Vilão '%s' não encontrado para remoção.\n", nomeRemover);
            }
            break;
        }
        case 0:
            printf("Voltando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida, tente novamente.\n");
            break;
        }
        if (escolha != 0)
        {
            printf("\nPressione Enter para continuar...");
            limparBufferEntrada();
            getchar();
        }
        system("clear || cls");
    } while (escolha != 0);
}

void menuArsenalPlanoAcao(Tartaruga *todasTartarugas, int numTartarugas, FilaMissoes *filaMissoes, Equipamento *listaEquipamentos, DiarioBordo *diario)
{
    system("clear || cls");
    printf("\n--- ARSENAL E PLANO DE AÇÃO ---\n");

    if (filaMissoes->tamanho == 0)
    {
        printf("Não há missões pendentes.\n");
        return;
    }

    
    exibirMissaoPrioritaria(filaMissoes);
    printf("\nDeseja iniciar esta missão? (s/n): ");
    char resposta[10];
    lerString(resposta, sizeof(resposta));
    if (tolower(resposta[0]) != 's')
    {
        printf("Missão não iniciada. Voltando ao menu.\n");
        return;
    }

    MissaoPendente missaoSelecionada = filaMissoes->missoes[0];

    // Seleção de Tartarugas
    Tartaruga *equipeTartarugas[4];
    int numMembrosEquipe = 0;

    printf("\n--- SELEÇÃO DE EQUIPE ---\n");
    for (int i = 0; i < numTartarugas; i++)
    {
        if (todasTartarugas[i].status == DISPONIVEL)
        {
            printf("%s (Nível: %.1f) está disponível. Deseja incluí-lo(a) na equipe? (s/n): ", todasTartarugas[i].nome, todasTartarugas[i].nivel);
            lerString(resposta, sizeof(resposta));
            if (tolower(resposta[0]) == 's')
            {
                if (numMembrosEquipe < 4)
                {
                    equipeTartarugas[numMembrosEquipe++] = &todasTartarugas[i];
                    todasTartarugas[i].status = EM_MISSAO;
                }
                else
                {
                    printf("Equipe cheia! Apenas 4 tartarugas podem ir.\n");
                    break;
                }
            }
        }
        else
        {
            printf("%s está %s e não pode participar da missão.\n", todasTartarugas[i].nome,
                   (todasTartarugas[i].status == FERIDO ? "FERIDO" : "EM MISSÃO (erro no status, será resetado)"));

            if (todasTartarugas[i].status == EM_MISSAO)
            {
                todasTartarugas[i].status = DISPONIVEL;
            }
        }
    }

    if (numMembrosEquipe == 0)
    {
        printf("Nenhuma tartaruga selecionada. Missão cancelada. Precisamos de heróis!\n");

        for (int i = 0; i < numMembrosEquipe; i++)
        {
            equipeTartarugas[i]->status = DISPONIVEL;
        }
        return;
    }

    printf("\n--- SELEÇÃO DE EQUIPAMENTOS ---\n");
    listarEquipamentos(listaEquipamentos);
    printf("Escolha até 2 equipamentos (digite o nome, um por vez, ou 'fim' para terminar):\n");

    Equipamento *equipamentosSelecionados[2] = {NULL, NULL};
    int numEquipamentosSelecionados = 0;
    char nomeEquipamento[50];

    while (numEquipamentosSelecionados < 2)
    {
        printf("Equipamento %d: ", numEquipamentosSelecionados + 1);
        lerString(nomeEquipamento, sizeof(nomeEquipamento));
        if (strcmp(nomeEquipamento, "fim") == 0 || strcmp(nomeEquipamento, "FIM") == 0)
        {
            break;
        }
        Equipamento *eq = buscarEquipamentoPorNome(listaEquipamentos, nomeEquipamento);
        if (eq != NULL)
        {
            equipamentosSelecionados[numEquipamentosSelecionados++] = eq;
            printf("Equipamento '%s' adicionado!\n", eq->nome);
        }
        else
        {
            printf("Equipamento '%s' não encontrado no arsenal.\n", nomeEquipamento);
        }
    }

    // Sempre remove a missão de maior prioridade (topo do heap)
    extrairMissaoPrioritaria(filaMissoes);

    simularBatalha(&missaoSelecionada, equipeTartarugas, numMembrosEquipe, equipamentosSelecionados, numEquipamentosSelecionados, diario, todasTartarugas, numTartarugas);

    printf("\nPressione Enter para continuar...");
    limparBufferEntrada();
    getchar();
    system("clear || cls");
}

void menuDiarioBordo(DiarioBordo *diario)
{
    system("clear || cls"); 
    exibirDiarioBordo(diario);
}

void exibirMenuMissoesPadrao()
{
    printf("\n--- MISSÕES PRÉ-DEFINIDAS ---\n");
    printf("1. Destruidor chegou! (Ameaça: 8)\n");
    printf("2. Bebop e Thanos roubando banco (Ameaça: 7)\n");
    printf("3. Clan do Pé atacando o porto (Ameaça: 4)\n");
    printf("4. Krang invadindo a cidade (Ameaça: 5)\n");
    printf("5. Tatsu sequestrou o Lula (Ameaça: 3)\n");
    printf("------------------------------\n");
}


void exibirMenuViloesPadrao()
{
    printf("\n--- VILÕES PRÉ-DEFINIDOS ---\n");
    printf("1. Destruidor (Nível: 10) - Ponto Fraco: Orgulho e arrogância\n");
    printf("2. Krang (Nível: 9) - Ponto Fraco: Alergia a polen\n");
    printf("3. Bebop (Nível: 6) - Ponto Fraco: Burrice e impulsividade\n");
    printf("4. Thanos (Nível: 6) - Ponto Fraco: Lentidão mental\n");
    printf("5. Tatsu (Nível: 8) - Ponto Fraco: Código de honra ninja\n");
    printf("----------------------------\n");
}

