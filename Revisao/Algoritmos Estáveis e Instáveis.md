## Algoritmos de Ordenação Estáveis e Instáveis

A estabilidade de um algoritmo de ordenação está relacionada à forma como ele trata elementos que possuem a mesma chave de ordenação.

### Ordenação Estável

Um algoritmo de ordenação é considerado **estável** quando mantém a ordem relativa original entre elementos que possuem a mesma chave de ordenação.

**Exemplos de algoritmos estáveis:**

- Bubble Sort
- Insertion Sort
- Merge Sort
- Counting Sort *(quando implementado de forma estável)*
- Radix Sort *(quando utiliza uma ordenação estável internamente)*

### Ordenação Instável

Um algoritmo de ordenação é considerado **instável** quando pode alterar a ordem relativa entre elementos que possuem a mesma chave de ordenação.

**Exemplos de algoritmos instáveis:**

- Selection Sort
- Quick Sort *(na implementação tradicional)*
- Heap Sort

### Resumo

| Algoritmo | Estável? |
|---|---|
| Bubble Sort | Sim |
| Insertion Sort | Sim |
| Merge Sort | Sim |
| Selection Sort | Não |
| Quick Sort | Geralmente não |
| Heap Sort | Não |
| Counting Sort | Pode ser estável |
| Radix Sort | Pode ser estável |

> A estabilidade não está diretamente relacionada à velocidade do algoritmo. Ela indica apenas se a ordem original dos elementos com chaves iguais é preservada durante a ordenação.

## Exemplo de Estabilidade

Considere uma lista de alunos que será ordenada pela nota:

| Ordem original | Aluno | Nota |
|---|---|---:|
| 1 | João | 8 |
| 2 | Maria | 7 |
| 3 | Pedro | 8 |
| 4 | Ana | 9 |

### Ordenação estável

Após a ordenação pela nota:

| Ordem | Aluno | Nota |
|---|---|---:|
| 1 | Maria | 7 |
| 2 | João | 8 |
| 3 | Pedro | 8 |
| 4 | Ana | 9 |

João continua antes de Pedro, pois ambos possuem nota `8` e João estava originalmente antes de Pedro.

### Ordenação instável

Em uma ordenação instável, a ordem relativa dos elementos com a mesma chave pode ser alterada:

| Ordem | Aluno | Nota |
|---|---|---:|
| 1 | Maria | 7 |
| 2 | Pedro | 8 |
| 3 | João | 8 |
| 4 | Ana | 9 |

A lista continua corretamente ordenada pelas notas, porém Pedro passou a aparecer antes de João.