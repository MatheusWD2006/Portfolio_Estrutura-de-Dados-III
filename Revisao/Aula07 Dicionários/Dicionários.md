# Dicionários (mapas)

## O que é um dicionário?

Um **dicionário** é uma estrutura de dados que armazena pares **chave–valor**. A chave identifica cada elemento e é usada para localizar o valor associado.

Exemplos:

- matrícula → dados do estudante;
- palavra → definição;
- nome de usuário → perfil.

Em geral, cada chave é única. Se uma chave já cadastrada for inserida novamente, a operação pode atualizar o valor correspondente. As operações fundamentais são:

| Operação | Descrição |
|---|---|
| `inserir(chave, valor)` | Adiciona o par ou atualiza o valor da chave existente. |
| `buscar(chave)` | Localiza a chave e retorna seu valor, se existir. |
| `remover(chave)` | Remove o par identificado pela chave. |

O dicionário é um **tipo abstrato de dados**: sua definição descreve o que as operações fazem, não como os dados precisam ser organizados. Tabelas hash e árvores de busca são implementações possíveis, com diferentes garantias de desempenho e ordenação.

## Tabela hash

Uma forma comum de implementar um dicionário é usar uma **tabela hash**. Uma função hash transforma a chave em um índice de um vetor:

```text
índice = hash(chave)
```

Assim, a busca pode acessar diretamente a posição provável da chave, sem percorrer todos os elementos. Como chaves diferentes podem produzir o mesmo índice, podem ocorrer **colisões**.

Há diferentes estratégias para tratar colisões. No exemplo abaixo é usada a **sondagem linear** (*linear probing*): se a posição estiver ocupada por outra chave, examinam-se as posições seguintes até encontrar a chave, uma posição vazia ou o fim da tabela.

Na remoção, uma posição não pode simplesmente voltar a ser considerada vazia: isso poderia interromper uma busca por uma chave que foi deslocada durante a sondagem. Por isso, a implementação marca a posição como **removida** (*tombstone*). A busca passa por posições removidas, enquanto a inserção pode reutilizá-las.

## Complexidade

Seja `n` o número de pares armazenados e `m` a capacidade da tabela. O **fator de carga** é `α = n / m`.

| Operação em tabela hash | Caso médio | Pior caso |
|---|---:|---:|
| Inserção | `O(1)` | `O(n)` |
| Busca | `O(1)` | `O(n)` |
| Remoção | `O(1)` | `O(n)` |

O caso médio depende de uma boa distribuição das chaves e de manter o fator de carga controlado. Se muitas chaves colidirem, uma operação poderá examinar quase toda a tabela. Em implementações de produção, a tabela costuma aumentar de tamanho e redistribuir os elementos (*rehashing*) quando o fator de carga ultrapassa um limite.

As operações no código a seguir têm custo `O(m)` no pior caso, que equivale a `O(n)` quando a tabela está cheia ou próxima disso. Como a capacidade é fixa, não há redimensionamento automático.

## Implementação didática em C++ sem contêineres da STL

Este exemplo implementa um dicionário de `int` para `int` usando um vetor de capacidade fixa e sondagem linear. Não utiliza `std::map`, `std::unordered_map` nem outros contêineres da STL.

```cpp
class Dicionario {
private:
    static const int CAPACIDADE = 101;

    enum Estado {
        VAZIO,
        OCUPADO,
        REMOVIDO
    };

    struct Entrada {
        int chave;
        int valor;
        Estado estado;
    };

    Entrada tabela[CAPACIDADE];

    int hash(int chave) const {
        int indice = chave % CAPACIDADE;
        return indice < 0 ? indice + CAPACIDADE : indice;
    }

public:
    Dicionario() {
        for (int i = 0; i < CAPACIDADE; ++i) {
            tabela[i].estado = VAZIO;
        }
    }

    // Insere uma chave ou atualiza seu valor.
    // Retorna false se não houver posição disponível.
    bool inserir(int chave, int valor) {
        int inicio = hash(chave);
        int primeiraRemovida = -1;

        for (int passo = 0; passo < CAPACIDADE; ++passo) {
            int indice = (inicio + passo) % CAPACIDADE;
            Entrada& entrada = tabela[indice];

            if (entrada.estado == OCUPADO) {
                if (entrada.chave == chave) {
                    entrada.valor = valor;
                    return true;
                }
            } else if (entrada.estado == REMOVIDO) {
                if (primeiraRemovida == -1) {
                    primeiraRemovida = indice;
                }
            } else {
                int destino = primeiraRemovida == -1
                    ? indice
                    : primeiraRemovida;
                tabela[destino].chave = chave;
                tabela[destino].valor = valor;
                tabela[destino].estado = OCUPADO;
                return true;
            }
        }

        // A tabela pode não ter posições vazias, mas ainda ter tombstones.
        if (primeiraRemovida != -1) {
            tabela[primeiraRemovida].chave = chave;
            tabela[primeiraRemovida].valor = valor;
            tabela[primeiraRemovida].estado = OCUPADO;
            return true;
        }

        return false;
    }

    // Retorna true se encontrou a chave e grava o valor em "valor".
    bool buscar(int chave, int& valor) const {
        int inicio = hash(chave);

        for (int passo = 0; passo < CAPACIDADE; ++passo) {
            int indice = (inicio + passo) % CAPACIDADE;
            const Entrada& entrada = tabela[indice];

            if (entrada.estado == VAZIO) {
                return false;
            }
            if (entrada.estado == OCUPADO && entrada.chave == chave) {
                valor = entrada.valor;
                return true;
            }
        }

        return false;
    }

    // Retorna true se removeu a chave.
    bool remover(int chave) {
        int inicio = hash(chave);

        for (int passo = 0; passo < CAPACIDADE; ++passo) {
            int indice = (inicio + passo) % CAPACIDADE;
            Entrada& entrada = tabela[indice];

            if (entrada.estado == VAZIO) {
                return false;
            }
            if (entrada.estado == OCUPADO && entrada.chave == chave) {
                entrada.estado = REMOVIDO;
                return true;
            }
        }

        return false;
    }
};
```

O uso de `bool` permite distinguir sucesso de falha: `buscar` retorna `false` quando a chave não existe; `inserir` retorna `false` quando a tabela está cheia e não há sequer uma posição removida para reutilizar; e `remover` retorna `false` quando não encontra a chave.

## Dicionários na STL do C++

A biblioteca padrão do C++ oferece contêineres associativos prontos. Eles não mudam a ideia do dicionário (chave–valor), mas usam implementações diferentes:

| Contêiner | Implementação típica | Busca, inserção e remoção | Ordenação das chaves |
|---|---|---|---|
| `std::map` | Árvore de busca balanceada | `O(log n)` | Sim; percorre em ordem crescente pelo comparador. |
| `std::unordered_map` | Tabela hash | `O(1)` em média; `O(n)` no pior caso | Não. |

Exemplo de uso:

```cpp
#include <map>
#include <unordered_map>

std::map<int, int> ordenado;
std::unordered_map<int, int> porHash;

ordenado[10] = 42;   // associa a chave 10 ao valor 42
porHash[10] = 42;
```

`std::map` é adequado quando a ordenação ou consultas por intervalo são importantes. `std::unordered_map` costuma ser conveniente quando se deseja acesso rápido por chave e a ordem não importa. Ambos gerenciam detalhes como armazenamento e colisões; em `std::unordered_map`, também podem redimensionar a tabela. Para aprender como o dicionário funciona internamente, uma implementação própria como a deste resumo ajuda a visualizar essas responsabilidades; em aplicações reais, os contêineres da STL geralmente são a escolha mais segura e prática.