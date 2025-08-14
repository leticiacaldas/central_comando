## Agatha Scarton e Letícia Caldas

## Para Compilar:

1.  Navegar até o diretório raiz do projeto no seu terminal.
2.  Execute o comando `make`:

    ```bash
    make
    ```

    Isso criará o diretório `bin` e o executável `central_comando` dentro dele. Ele também criará um diretório `data` para armazenar os arquivos de persistência.

## Como Executar

Após a compilação, execute o programa a partir do diretório raiz:

```bash
make run
```

## Estruturas de Dados Utilizadas
Lista Encadeada: Usada para gerenciar a lista de equipamentos.

Fila de Prioridade (Heap): Usada para o Painel de Alertas de Missões, garantindo que as missões de maior ameaça sejam sempre as primeiras.

Pilha: Implementada para o Diário de Bordo, exibindo as missões concluídas em ordem LIFO.

Árvore Binária de Busca : Utilizada para armazenar e buscar vilões de forma eficiente.

## Exemplos de Uso
1. Adicionar um Vilão:

No menu principal, selecione "Arquivos de Vilões".

Escolha a opção para adicionar um novo vilão ou escolha entre os vilões pre definidos.

Insira os dados do vilão (nome, nível de habilidade, ponto fraco).

2. Adicionar uma Missão:

No menu principal, selecione "Painel de Alertas de Missões".

Escolha a opção para adicionar uma nova missão ou escolha entre as missões pre definidas.

Insira a descrição, local e nível de ameaça. 

Realizar uma Batalha:

No menu principal, selecione "Arsenal e Plano de Ação".

Selecione a missão pendente.

Selecione as tartarugas disponíveis e até 2 equipamentos.

A simulação será executada e o resultado exibido.

Verifique o "Diário de Bordo" e o "Gerenciar Tartarugas" para ver as consequências.
