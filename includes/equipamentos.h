#ifndef EQUIPAMENTOS_H
#define EQUIPAMENTOS_H


typedef struct Equipamento {
    char nome[50];
    char favoritoDe[50]; 
    struct Equipamento *proximo;
} Equipamento;


Equipamento* criarEquipamento(const char *nome, const char *favoritoDe);
Equipamento* adicionarEquipamento(Equipamento *lista, Equipamento *novoEquipamento);
void listarEquipamentos(Equipamento *lista);
void liberarListaEquipamentos(Equipamento *lista);
Equipamento* buscarEquipamentoPorNome(Equipamento *lista, const char *nome);
Equipamento* carregarEquipamentos(void);

#endif 