<div align="center">
    <h1>Central de Comando - Tartarugas Ninja 🐢</h1>
    <img src="https://user-images.githubusercontent.com/placeholder/demo.gif" alt="Demonstração" width="500"/>
</div>

Projeto acadêmico para gerenciamento de missões, vilões, tartarugas e equipamentos, inspirado no universo das Tartarugas Ninja. Desenvolvido em C por Agatha Scarton e Letícia Caldas.

---

## 🚀 Funcionalidades

| Função                | Descrição                                                                 |
|-----------------------|---------------------------------------------------------------------------|
| Gerenciar Vilões      | Adicione, busque e liste vilões usando árvore binária de busca            |
| Missões               | Painel de alertas com fila de prioridade (heap)                           |
| Diário de Bordo       | Missões concluídas em ordem LIFO (pilha)                                  |
| Equipamentos          | Lista encadeada para gerenciar arsenal                                    |
| Simulação de Batalha  | Escolha tartarugas, equipamentos e execute batalhas                      |
| Persistência          | Dados salvos em arquivos no diretório `data/`                             |

---

## 🛠️ Como Compilar

1. Navegue até o diretório raiz do projeto:
     ```bash
     cd central_comando
     make
     ```
     O executável será gerado em `bin/central_comando`.

## ▶️ Como Executar

```bash
make run
```

---

## 📚 Estruturas de Dados
- **Lista Encadeada:** Equipamentos
- **Fila de Prioridade (Heap):** Missões
- **Pilha:** Diário de Bordo
- **Árvore Binária de Busca:** Vilões

---

## 💡 Exemplos de Uso

### 1. Adicionar um Vilão
No menu principal, selecione "Arquivos de Vilões". Escolha adicionar novo vilão ou um pré-definido. Insira nome, nível de habilidade e ponto fraco.

### 2. Adicionar uma Missão

No menu principal, selecione "Painel de Alertas de Missões". Adicione nova missão ou escolha uma pré-definida. Insira descrição, local e nível de ameaça.

### 3. Realizar uma Batalha
Selecione "Arsenal e Plano de Ação". Escolha missão pendente, tartarugas e até 2 equipamentos. Acompanhe o resultado e verifique o "Diário de Bordo".

---

## 👩‍💻 Contribuição
Pull requests são bem-vindos! Para contribuir, faça um fork, crie uma branch e envie seu PR.

## 📄 Licença
Este projeto é apenas para fins acadêmicos.

## 🙋‍♀️ Autores
- Agatha Scarton
- Letícia Caldas ([lbcaldas@inf.ufpel.edu.br](mailto:lbcaldas@inf.ufpel.edu.br))
