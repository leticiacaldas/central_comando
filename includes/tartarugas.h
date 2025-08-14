#ifndef TARTARUGAS_H
#define TARTARUGAS_H

typedef enum
{
    DISPONIVEL,
    EM_MISSAO,
    FERIDO
} StatusTartaruga;

typedef struct
{
    char nome[50];
    StatusTartaruga status;
    float nivel;
    int missoesFerido;
} Tartaruga;


void inicializarTartarugas(Tartaruga **tartarugas, int *numTartarugas);
void listarStatusTartarugas(const Tartaruga *tartarugas, int numTartarugas);
void resetarTartarugas(Tartaruga *tartarugas, int numTartarugas);

#endif