# Buscas Sequenciais e Sequenciais Indexadas

## 1. Busca Sequencial (Linear Search)

### O que é?

A **busca sequencial** (ou linear) é o método mais simples e elementar de recuperação de dados. Consiste em percorrer uma estrutura de dados (como vetores, listas encadeadas ou arquivos) elemento por elemento, do início até o fim ou até que o valor desejado seja encontrado.

Não exige que os dados estejam previamente ordenados, o que a torna aplicável a praticamente qualquer conjunto de informações.

---

### Como funciona?

Existem três variantes principais da busca sequencial:

#### 1. Busca Sequencial Simples (Vetor Não Ordenado)
- Inicia no primeiro elemento (índice `0`).
- Compara o elemento atual com a chave de busca.
- Se forem iguais, encerra a busca com sucesso retornando a posição.
- Caso contrário, avança para o próximo elemento.
- Se atingir o fim da estrutura sem encontrar o valor, conclui que o elemento não está presente.

#### 2. Busca Sequencial em Vetor Ordenado (com Parada Antecipada)
- Se os dados estiverem ordenados (por exemplo, em ordem crescente), não é necessário percorrer o vetor inteiro quando a chave procurada não existir.
- Assim que o algoritmo encontra um elemento **estritamente maior** que a chave procurada, a busca pode ser interrompida imediatamente, pois nenhum elemento posterior poderá ser igual à chave.

#### 3. Busca Sequencial com Sentinela
- Em uma busca sequencial tradicional, a cada iteração são realizados dois testes:
  1. Verificar se o índice atingiu o fim do vetor (`i < n`);
  2. Verificar se o elemento atual é a chave procurada (`v[i] == chave`).
- A técnica da **sentinela** consiste em reservar uma posição extra no final do vetor e inserir ali a chave procurada antes de iniciar o laço.
- Isso elimina o primeiro teste (`i < n`), pois a chave com certeza será encontrada (no pior caso, na posição da sentinela). Após o laço, verifica-se se a posição encontrada foi a da sentinela ou uma posição válida do vetor original.

---

### Complexidade da Busca Sequencial

Seja $n$ a quantidade de elementos no vetor:

| Caso | Vetor Não Ordenado | Vetor Ordenado | Observações |
|---|:---:|:---:|---|
| **Melhor Caso** | $O(1)$ | $O(1)$ | O elemento é o primeiro do vetor. |
| **Caso Médio** | $O(n)$ | $O(n)$ | No vetor desordenado examina $\approx n/2$ elementos. No ordenado, mesmo em caso de falha, examina em média metade dos elementos. |
| **Pior Caso** | $O(n)$ | $O(n)$ | O elemento é o último ou não existe no vetor ($n$ comparações). |
| **Espaço Auxiliar** | $O(1)$ | $O(1)$ | Não requer memória adicional além de variáveis simples. |

---

## 2. Busca Sequencial Indexada (Indexed Sequential Search)

### O que é?

A **busca sequencial indexada** é uma técnica projetada para acelerar a busca sequencial em conjuntos de dados **ordenados**, reduzindo significativamente a quantidade de elementos examinados.

Ela combina o conceito de **tabela auxiliar de índices** com a busca sequencial. Essa técnica serviu de base para métodos clássicos de acesso a arquivos e registros em disco, como o **ISAM** (*Indexed Sequential Access Method*), sendo fundamental para entender como bancos de dados organizam índices primários e secundários para evitar a leitura completa de arquivos volumosos.

---

### Como funciona?

O conjunto de dados principal (ordenado) é dividido em **blocos** (ou páginas). Em paralelo, mantém-se uma **tabela de índices** auxiliar, muito menor que a coleção original.

Cada entrada na tabela de índices armazena:
1. Uma **chave representativa do bloco** (geralmente a maior chave contida naquele bloco, ou a primeira);
2. Um **ponteiro ou índice** que indica a posição inicial desse bloco no vetor/arquivo principal.

```text
Tabela de Índices:
+--------------+----+----+----+
| Chave Máxima | 18 | 45 | 89 |
+--------------+----+----+----+
| Posição      | 0  | 4  | 8  |
+--------------+----+----+----+
                 |    |    |
                 v    v    v
Vetor de Dados Principal (ordenado):
Bloco 0: [ 3,  7, 12, 18 ]   (posições 0 a 3)
Bloco 1: [ 22, 29, 35, 45 ]  (posições 4 a 7)
Bloco 2: [ 51, 63, 77, 89 ]  (posições 8 a 11)
```

O algoritmo de busca ocorre em **duas fases**:

1. **Fase 1 (Busca no Índice):**
   - Percorre-se a tabela de índices (que é pequena) até encontrar a primeira entrada cuja chave máxima seja **maior ou igual** à chave procurada.
   - Isso determina com precisão em qual bloco o elemento pode estar.
   - Se a chave procurada for maior do que a chave do último índice, ela certamente não existe no vetor.

2. **Fase 2 (Busca no Bloco de Dados):**
   - Acessa-se diretamente o bloco correspondente no vetor principal, a partir do índice registrado na tabela auxiliar.
   - Realiza-se uma busca sequencial **apenas dentro desse bloco**.
   - Como os elementos dentro do bloco também estão ordenados, a busca pode usar parada antecipada se encontrar um elemento maior.

---

### Complexidade e Dimensionamento Ótimo

Seja:
- $n$: número total de elementos no vetor principal;
- $k$: tamanho de cada bloco (quantidade de elementos por bloco);
- $b$: número de blocos na tabela de índices, onde $b = \lceil n / k \rceil$.

No pior caso, o número total de comparações é a soma do pior caso da Fase 1 com o pior caso da Fase 2:

$$\text{Comparações no Pior Caso} = b + k = \frac{n}{k} + k$$

#### Qual é o tamanho de bloco ideal ($k$)?
Para minimizar a função $f(k) = \frac{n}{k} + k$, calcula-se a primeira derivada em relação a $k$ e iguala-se a zero:

$$f'(k) = -\frac{n}{k^2} + 1 = 0 \implies k^2 = n \implies k = \sqrt{n}$$

Portanto, o tamanho ideal para cada bloco é **$\sqrt{n}$**, o que resulta em aproximadamente **$\sqrt{n}$** blocos na tabela de índice.

Substituindo $k = \sqrt{n}$:

$$\text{Pior Caso} = \frac{n}{\sqrt{n}} + \sqrt{n} = \sqrt{n} + \sqrt{n} = 2\sqrt{n}$$

| Caso | Complexidade de Tempo | Explicação |
|---|:---:|---|
| **Melhor Caso** | $O(1)$ | Chave encontrada na primeira posição do primeiro bloco. |
| **Caso Médio** | $O(\sqrt{n})$ | Busca percorre em média metade dos blocos e metade dos elementos do bloco. |
| **Pior Caso** | $O(\sqrt{n})$ | Máximo de $2\sqrt{n}$ comparações quando $k = \sqrt{n}$. |
| **Espaço Auxiliar** | $O(\sqrt{n})$ | Memória necessária para armazenar a tabela de índices ($n/k$ entradas). |

> [!NOTE]
> Se a busca na tabela de índices for binária em vez de sequencial, o custo da primeira fase cai de $O(b)$ para $O(\log b)$, resultando em um tempo total de $O(\log(n/k) + k)$.

---

## 3. Comparativo entre os Métodos

| Critério | Busca Sequencial Simples | Busca Sequencial Ordenada | Busca Sequencial Indexada | Busca Binária |
|---|:---:|:---:|:---:|:---:|
| **Requer Ordenação?** | Não | Sim | Sim | Sim |
| **Complexidade (Melhor)** | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| **Complexidade (Médio)** | $O(n)$ | $O(n)$ | $O(\sqrt{n})$ | $O(\log n)$ |
| **Complexidade (Pior)** | $O(n)$ | $O(n)$ | $O(\sqrt{n})$ | $O(\log n)$ |
| **Espaço Auxiliar** | $O(1)$ | $O(1)$ | $O(\sqrt{n})$ | $O(1)$ |
| **Acesso Aleatório ($O(1)$)** | Não obrigatório (funciona em listas) | Não obrigatório | Exigido para pular blocos | Obrigatório |
| **Custo de Inserção/Remoção** | $O(1)$ (no final) | $O(n)$ | $O(n)$ ou reorganização de blocos | $O(n)$ |

---

## 4. Implementação em C++ (com STL)

O código a seguir apresenta:
1. `buscaSequencial`: busca linear padrão em vetor arbitrário;
2. `buscaSequencialOrdenada`: com critério de parada antecipada;
3. `BuscaSequencialIndexada`: classe completa que constrói a tabela de índices com tamanho ótimo $k = \sqrt{n}$ e executa a busca em duas fases;
4. Demonstração prática na função `main()`.

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// ============================================================================
// 1. Busca Sequencial Simples
// ============================================================================
int buscaSequencial(const std::vector<int>& vetor, int chave) {
    for (size_t i = 0; i < vetor.size(); ++i) {
        if (vetor[i] == chave) {
            return static_cast<int>(i); // Retorna o indice encontrado
        }
    }
    return -1; // Elemento nao encontrado
}

// ============================================================================
// 2. Busca Sequencial em Vetor Ordenado (Parada Antecipada)
// ============================================================================
int buscaSequencialOrdenada(const std::vector<int>& vetor, int chave) {
    for (size_t i = 0; i < vetor.size(); ++i) {
        if (vetor[i] == chave) {
            return static_cast<int>(i);
        }
        // Se encontramos um valor maior que a chave em um vetor ordenado,
        // a chave com certeza nao esta presente no restante do vetor.
        if (vetor[i] > chave) {
            break;
        }
    }
    return -1;
}

// ============================================================================
// 3. Busca Sequencial Indexada
// ============================================================================

// Entrada na tabela de indices
struct Indice {
    int chaveMaxima;    // Maior chave contida no bloco correspondente
    size_t posicaoInicio; // Indice onde o bloco se inicia no vetor de dados
};

class BuscaSequencialIndexada {
private:
    std::vector<int> dados;
    std::vector<Indice> tabelaIndices;
    size_t tamanhoBloco;

public:
    // Construtor: recebe o vetor ja ordenado e monta o indice
    BuscaSequencialIndexada(const std::vector<int>& vetorOrdenado) {
        dados = vetorOrdenado;
        if (dados.empty()) {
            tamanhoBloco = 0;
            return;
        }

        // Tamanho otimo do bloco: floor(sqrt(n))
        tamanhoBloco = static_cast<size_t>(std::sqrt(dados.size()));
        if (tamanhoBloco == 0) {
            tamanhoBloco = 1;
        }

        // Criacao da tabela de indices
        for (size_t i = 0; i < dados.size(); i += tamanhoBloco) {
            size_t fimBloco = std::min(i + tamanhoBloco - 1, dados.size() - 1);
            tabelaIndices.push_back({dados[fimBloco], i});
        }
    }

    // Metodo de busca em duas fases
    int buscar(int chave) const {
        if (dados.empty()) {
            return -1;
        }

        // FASE 1: Busca sequencial na tabela de indices para encontrar o bloco
        int blocoAlvo = -1;
        for (size_t i = 0; i < tabelaIndices.size(); ++i) {
            if (chave <= tabelaIndices[i].chaveMaxima) {
                blocoAlvo = static_cast<int>(i);
                break;
            }
        }

        // Se a chave for maior que a chave maxima do ultimo bloco, nao existe
        if (blocoAlvo == -1) {
            return -1;
        }

        // FASE 2: Busca sequencial apenas dentro do bloco selecionado
        size_t inicio = tabelaIndices[blocoAlvo].posicaoInicio;
        size_t fim = std::min(inicio + tamanhoBloco, dados.size());

        for (size_t i = inicio; i < fim; ++i) {
            if (dados[i] == chave) {
                return static_cast<int>(i);
            }
            // Parada antecipada dentro do bloco ordenado
            if (dados[i] > chave) {
                break;
            }
        }

        return -1;
    }

    void imprimirEstrutura() const {
        std::cout << "\n=== Estrutura da Busca Sequencial Indexada ===" << '\n';
        std::cout << "Total de elementos: " << dados.size() << '\n';
        std::cout << "Tamanho de cada bloco (k = sqrt(n)): " << tamanhoBloco << '\n';
        std::cout << "Quantidade de blocos no indice: " << tabelaIndices.size() << "\n\n";

        for (size_t i = 0; i < tabelaIndices.size(); ++i) {
            size_t inicio = tabelaIndices[i].posicaoInicio;
            size_t fim = std::min(inicio + tamanhoBloco, dados.size());

            std::cout << "Bloco " << i 
                      << " [Inicio: idx " << inicio 
                      << ", Chave Maxima: " << tabelaIndices[i].chaveMaxima << "] -> Conteudo: [ ";
            for (size_t j = inicio; j < fim; ++j) {
                std::cout << dados[j] << " ";
            }
            std::cout << "]\n";
        }
        std::cout << "=============================================\n\n";
    }
};

// ============================================================================
// Funcao Principal de Teste
// ============================================================================
int main() {
    // Vetor ordenado de exemplo (16 elementos -> k = sqrt(16) = 4 blocos de 4)
    std::vector<int> dados = {4, 7, 10, 15, 18, 22, 25, 29, 33, 40, 42, 50, 55, 60, 64, 70};

    std::cout << "Dados ordenados:\n[ ";
    for (int v : dados) {
        std::cout << v << " ";
    }
    std::cout << "]\n";

    // 1. Teste da Busca Sequencial Padrao
    int chave1 = 25;
    int idxSeq = buscaSequencial(dados, chave1);
    std::cout << "\n[Busca Sequencial] Chave " << chave1 
              << (idxSeq != -1 ? " encontrada no indice: " + std::to_string(idxSeq) : " nao encontrada") 
              << '\n';

    // 2. Teste da Busca Sequencial Ordenada (chave inexistente)
    int chave2 = 30;
    int idxOrd = buscaSequencialOrdenada(dados, chave2);
    std::cout << "[Busca Sequencial Ordenada] Chave " << chave2 
              << (idxOrd != -1 ? " encontrada no indice: " + std::to_string(idxOrd) : " nao encontrada (parada antecipada)") 
              << '\n';

    // 3. Teste da Busca Sequencial Indexada
    BuscaSequencialIndexada bsi(dados);
    bsi.imprimirEstrutura();

    std::vector<int> consultas = {4, 29, 50, 70, 1, 30, 99};

    for (int chave : consultas) {
        int pos = bsi.buscar(chave);
        if (pos != -1) {
            std::cout << "Consulta " << chave << ": ENCONTRADO na posicao " << pos 
                      << " (dados[" << pos << "] = " << dados[pos] << ")\n";
        } else {
            std::cout << "Consulta " << chave << ": NAO ENCONTRADO\n";
        }
    }

    return 0;
}
```

---

### Equivalentes na STL do C++

A Standard Template Library (STL) disponibiliza algoritmos prontos que representam esses padrões:

- **`std::find` (`<algorithm>`)**: implementa a busca sequencial padrão ($O(n)$) iterando sobre qualquer contêiner ou intervalo de iteradores (como `std::vector`, `std::list`).
  ```cpp
  auto it = std::find(vetor.begin(), vetor.end(), chave);
  if (it != vetor.end()) {
      int indice = std::distance(vetor.begin(), it);
  }
  ```

- **`std::lower_bound` / `std::binary_search` (`<algorithm>`)**: para coleções ordenadas com acesso aleatório, a STL implementa busca binária ($O(\log n)$), superando o desempenho da busca sequencial indexada em memória primária:
  ```cpp
  bool existe = std::binary_search(vetor.begin(), vetor.end(), chave);
  ```

---

## 5. Aplicações e Contexto Prático

### Quando utilizar a Busca Sequencial?
- Conjuntos de dados pequenos ($n$ reduzido), onde o custo de ordenar ou criar índices não compensa.
- Dados não ordenados e que sofrem frequentes inserções/remoções ($O(1)$ na inserção).
- Estruturas de acesso puramente sequencial, como listas encadeadas simples ou leitura de arquivos *stream* (fitas magnéticas, logs contínuos).

### Quando utilizar a Busca Sequencial Indexada?
- **Sistemas de Arquivos e Bancos de Dados (ISAM):** quando a base de dados é muito grande para caber na memória principal (RAM), ela é armazenada em disco em blocos (páginas). A **tabela de índices**, por ser muito menor ($O(\sqrt{n})$), pode ser mantida inteiramente na RAM. O sistema busca no índice em memória e realiza apenas **uma leitura de bloco em disco**, minimizando gargalos de entrada/saída (I/O).
- **Transição para Árvores B e B+:** a indexação sequencial multinível é o princípio predecessor direto das Árvores B e B+, amplamente utilizadas em bancos de dados relacionais modernos (como PostgreSQL e MySQL/InnoDB).

---

## 6. Resumo

- **Busca Sequencial:** examina elemento a elemento. Simples, funciona em dados desordenados, mas tem custo linear $O(n)$. Em coleções ordenadas, permite parada antecipada.
- **Técnica da Sentinela:** otimiza a busca sequencial removendo o teste de limite de vetor no laço principal.
- **Busca Sequencial Indexada:** divide uma coleção ordenada em blocos e usa uma tabela de índices auxiliar. Funciona em duas fases: busca no índice para identificar o bloco e busca sequencial dentro do bloco.
- **Dimensionamento Ótimo:** escolhendo blocos de tamanho $k = \sqrt{n}$, a complexidade no pior caso atinge $O(\sqrt{n})$, com overhead de espaço de $O(\sqrt{n})$.
- **Importância em ED III:** fundamental para o acesso eficiente a arquivos e introdução a técnicas de indexação em armazenamento secundário.
