# Merge Sort

### Disciplina: Estrutura de Dados III

### Trabalho de Revisão

### Alunos:
- Matheus Witte Ditz
- Gabriel Rizzatto
- Andrey Dalla Costa

---

## Origem e história

O Merge Sort foi criado por John von Neumann em 1945. A ideia de dividir um problema em subproblemas menores, resolvê-los recursivamente e depois combinar (fazer o *merge*) se tornou um dos exemplos mais clássicos do paradigma de divisão e conquista (*divide and conquer*), influenciando algoritmos posteriores.

## Abordagem

O Merge Sort é um algoritmo de divisão e conquista. Isso significa que ele resolve o problema seguindo três etapas:

- **Dividir:** o vetor é dividido ao meio, gerando duas metades.
- **Conquistar:** cada metade é ordenada recursivamente, aplicando o mesmo processo até restar apenas um elemento, que já está "ordenado" por definição.
- **Combinar (*merge*):** as duas metades já ordenadas são intercaladas em um único vetor ordenado.

## Como funciona

Dado um vetor de `n` elementos:

1. Se o vetor tem 0 ou 1 elemento, já está ordenado. Esse é o caso base da recursão.

2. Caso contrário, divide-se o vetor em duas metades: esquerda e direita.

3. Aplica-se o Merge Sort recursivamente em cada metade.

4. As duas metades ordenadas são mescladas: compara-se o primeiro elemento de cada metade, coloca-se o menor no vetor de saída e repete-se o processo até que todos os elementos estejam em ordem.


## Explicação simples: a analogia das cartas

Imagine que você tem um monte de cartas de baralho bagunçadas na mão e quer organizá-las.

A sequência funciona assim:

1. Você divide o monte ao meio, entrega metade para um amigo e fica com a outra metade.

2. Cada pessoa divide sua parte ao meio novamente. Isso se repete até cada pessoa ficar com apenas uma carta.

3. Uma carta sozinha já está "organizada", pois não há outra carta para comparar.

4. Começa o caminho de volta: cada dupla compara suas cartas e forma um pequeno monte de duas cartas em ordem.

5. Os montes de duas cartas são juntados, comparando carta por carta, para formar montes maiores e ordenados.

6. O processo se repete até sobrar um único monte, totalmente ordenado.

A parte de dividir o monte corresponde à divisão. Nessa etapa, ninguém organiza nada: apenas reparte as cartas. A parte de juntar comparando as cartas corresponde ao *merge*, que é quando a ordenação realmente acontece.

## Complexidade

| Cenário | Complexidade |
| --- | --- |
| Melhor caso | `O(n log n)` |
| Caso médio | `O(n log n)` |
| Pior caso | `O(n log n)` |

### O que essa complexidade significa

A notação `O(n log n)` descreve como o tempo de execução do algoritmo cresce em relação ao tamanho da entrada (`n`), no pior caso.

- O fator `log n` vem da etapa de divisão: como o vetor é sempre dividido ao meio, são necessárias `log₂(n)` divisões até chegar aos casos base, que são vetores de tamanho 1. Isso forma uma árvore de recursão com `log n` níveis.
- O fator `n` vem da etapa de *merge*: em cada nível da recursão, o trabalho total de mesclar as sublistas é proporcional a `n`, pois cada elemento é percorrido uma vez.
- Multiplicando os dois fatores, ou seja, `n` elementos processados em cada um dos `log n` níveis, obtém-se o total de `n log n` operações.

O espaço `O(n)` refere-se à memória auxiliar usada para armazenar os vetores temporários usados durante o *merge*.

## Estabilidade

O Merge Sort é um algoritmo estável. Isso significa que, se dois elementos possuem o mesmo valor de comparação, a ordem inicial entre eles é preservada no resultado final.

Essa característica é garantida porque, durante o *merge*, quando os elementos de ambos os lados são iguais, a implementação padrão prioriza o elemento que veio da metade esquerda. Por consequência da divisão, esse elemento aparecia antes no vetor original.

## In-place ou não?

O Merge Sort, em sua implementação clássica, não é *in-place*. Ele requer memória auxiliar proporcional ao tamanho do vetor (`O(n)`) para armazenar os elementos durante a etapa de *merge*, pois não é possível mesclar duas sublistas ordenadas diretamente no mesmo espaço de memória sem sobrescrever dados que ainda serão lidos.


```cpp
// Função auxiliar para intercalar (merge) duas metades ordenadas
void merge(int arr[], int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Cria vetores temporários para as duas metades
    int* esquerda = new int[n1];
    int* direita = new int[n2];

    // Copia os dados para os vetores temporários
    for (int i = 0; i < n1; i++) {
        esquerda[i] = arr[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        direita[j] = arr[meio + 1 + j];
    }

    // Intercala os vetores temporários de volta em arr[inicio..fim]
    int i = 0;      // Índice inicial da primeira metade
    int j = 0;      // Índice inicial da segunda metade
    int k = inicio; // Índice inicial do vetor combinado

    while (i < n1 && j < n2) {
        if (esquerda[i] <= direita[j]) {
            arr[k] = esquerda[i];
            i++;
        } else {
            arr[k] = direita[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de esquerda[], se houver
    while (i < n1) {
        arr[k] = esquerda[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de direita[], se houver
    while (j < n2) {
        arr[k] = direita[j];
        j++;
        k++;
    }

    // Libera a memória alocada dinamicamente
    delete[] esquerda;
    delete[] direita;
}

// Função principal do Merge Sort
void mergeSort(int arr[], int inicio, int fim) {
    // Caso base: sub-arranjo de tamanho 0 ou 1 já está ordenado
    if (inicio >= fim) {
        return;
    }

    // Evita overflow de (inicio + fim) / 2
    int meio = inicio + (fim - inicio) / 2;

    // Divide e conquista: ordena as duas metades
    mergeSort(arr, inicio, meio);
    mergeSort(arr, meio + 1, fim);

    // Combina as duas metades ordenadas
    merge(arr, inicio, meio, fim);
}
```

### Exemplo: `[6, 3, 8, 2]`

1. Divide `[6, 3, 8, 2]` em `[6, 3]` e `[8, 2]`.

2. Divide `[6, 3]` em `6` e `3`, e `[8, 2]` em `8` e `2`.

3. Cada parte tem apenas um elemento.

4. Compara `6` e `3`, formando `[3, 6]`.

5. Compara `8` e `2`, formando `[2, 8]`.

6. Por fim, compara `[3, 6]` e `[2, 8]`, formando `[2, 3, 6, 8]`.

> Cada "encontro de dois montes" é um *merge* separado. No exemplo, o *merge* acontece três vezes no vetor final, juntando os elementos soltos duas vezes e os pares uma.

### Exemplo com chamadas recursivas

Considere o vetor `[8, 3, 5]`. O elemento `5`, sozinho, representa um caso base e não precisa ser alterado. Quem decide juntar o `5` com o par `[3, 8]` é a chamada `mergeSort(arr, 0, 2)`, ou seja, a chamada que recebe o array inteiro, onde o início é 0 e o fim é 2.

Essa chamada espera o retorno de `mergeSort(arr, 0, 1)` e de `mergeSort(arr, 2, 2)`. Primeiro, `mergeSort(arr, 0, 1)` chama `mergeSort(arr, 0, 0)`, que retorna `[3]`, e `mergeSort(arr, 1, 1)`, que retorna `[8]`. Depois, `mergeSort(arr, 0, 1)` executa `merge(arr, 0, 0, 1)`, juntando `[3]` e `[8]` para formar `[3, 8]`. Já `mergeSort(arr, 2, 2)` representa o caso base do elemento `5`. Só depois que essas duas chamadas retornam é que `mergeSort(arr, 0, 2)` executa `merge(arr, 0, 1, 2)` formando `[3, 5, 8]`.

O erro mais comum ao analisar esse processo é observar apenas as chamadas "filhas" e esquecer que cada uma delas também é "pai" de outras duas. Não existe uma categoria fixa de "chamada pai" e "chamada filha": isso depende do ponto de vista.

Como nesse exemplo `[8, 3, 5]`, `mergeSort(arr, 0, 2)` é pai de `mergeSort(arr, 0, 1)` e `mergeSort(arr, 2, 2)`. Porém, quando o foco muda para `mergeSort(arr, 0, 1)`, essa chamada passa a ser pai de suas próprias subchamadas. Isso se repete em cada nível até chegar ao caso base, que é a única chamada que não é pai de nenhuma outra. Lembrando que pai não é exatamente o termo correto, é apenas uma forma de explicar.

Esse ponto de vista explica por que `merge` é chamado várias vezes ao longo da execução, e não apenas uma vez no final.

### A ordem das chamadas

O Merge Sort resolve um lado por vez, nunca os dois ao mesmo tempo.

Usando a analogia das cartas, imagine que o baralho foi dividido em duas pilhas: uma à esquerda e outra à direita. O algoritmo resolve toda a pilha da esquerda antes de começar na pilha da direita. Só quando as duas pilhas maiores estão ordenadas é que elas são juntadas em um último *merge*.

Isso é exatamente o que o código faz, e por isso a ordem das linhas importa:

```cpp

mergeSort(arr, inicio, meio);      // Resolve o lado esquerdo por completo primeiro

mergeSort(arr, meio + 1, fim);     // Começa depois que o lado esquerdo termina

merge(arr, inicio, meio, fim);     // Junta as duas metades por último

```

# Questões sobre Merge Sort

---

## 1. ENADE 2019

O Merge Sort é um método de ordenação baseado na divisão do vetor em partes menores. Essas partes são ordenadas recursivamente e, posteriormente, combinadas por meio da operação de **merge (intercalação)**.

O algoritmo apresentado combina os vetores `a[lo..mid]` e `a[mid+1..hi]` no vetor `a[lo..hi]`.

A implementação do método `sort` deve completar a divisão recursiva do vetor.

### Alternativas

**a)**

```java
if (hi == lo)
    return;

int mid = lo + (hi - lo)/2;

sort(a, lo, mid);
sort(a, mid, hi);

merge(a, lo, mid, hi);
```

**b)**

```java
if (hi > lo)
    return;

int mid = lo + (hi - lo)/2;

sort(a, lo, mid);
sort(a, mid, hi);

merge(a, lo, mid, hi);
```

**c)**

```java
if (hi <= lo)
    return;

int mid = lo + (hi - lo)/2;

sort(a, lo, mid);
sort(a, mid, hi);

merge(a, lo, mid, hi);
```

**d)**

```java
if (hi > lo)
    return;

int mid = lo + (hi - lo)/2;

sort(a, lo, mid);
sort(a, mid+1, hi);

merge(a, lo, mid, hi);
```

**e)**

```java
if (hi <= lo)
    return;

int mid = lo + (hi - lo)/2;

sort(a, lo, mid);
sort(a, mid+1, hi);

merge(a, lo, mid, hi);
```

### Resposta: **E**

### Explicação

O Merge Sort utiliza o paradigma de **Divisão e Conquista**. Para implementar sua versão recursiva, é necessário realizar três etapas:

1. Definir o **caso base**;
2. Dividir o vetor em duas partes;
3. Ordenar recursivamente as duas partes e realizar o `merge`.

### 1. Caso base

Um vetor ou subvetor que possui apenas um elemento já está ordenado.

Isso ocorre quando:

```text
hi <= lo
```

Nesse caso, não há mais nada para dividir e a função deve simplesmente retornar:

```java
if (hi <= lo)
    return;
```

### 2. Divisão do vetor

O ponto central do intervalo é calculado por:

```java
int mid = lo + (hi - lo)/2;
```

Essa forma é equivalente a:

```text
(lo + hi) / 2
```

mas evita possíveis problemas de **overflow de inteiros** quando `lo` e `hi` possuem valores muito grandes.

### 3. Chamadas recursivas

O vetor é dividido em duas partes:

```text
[lo ........ mid] [mid + 1 ........ hi]
```

Por isso, as chamadas devem ser:

```java
sort(a, lo, mid);
sort(a, mid+1, hi);
```

O segundo intervalo começa em `mid + 1`, pois o próprio método `merge` considera as duas partes como:

```text
a[lo..mid]
a[mid+1..hi]
```

### 4. Intercalação

Depois que as duas metades estiverem ordenadas, elas são combinadas:

```java
merge(a, lo, mid, hi);
```

Portanto, a implementação correta é:

```java
if (hi <= lo)
    return;

int mid = lo + (hi - lo)/2;

sort(a, lo, mid);
sort(a, mid+1, hi);

merge(a, lo, mid, hi);
```

### Conclusão

A alternativa correta é a **(E)**.

---

# 2. Questão 33 — POSCOMP 2013

Considere o algoritmo:

```text
MERGESORT(V, i, j)

(1) Se (i < j) então
(2)     m = (i+j)/2;
(3)     MERGESORT(v, i, m);
(4)     MERGESORT(v, m+1, j);
(5)     MESCLAR(v, i, m, j);
(6) Fim;
```

Sobre o comportamento assintótico do algoritmo de ordenação Merge Sort, assinale a alternativa que apresenta corretamente sua complexidade.

### Alternativas

* **(A)** O(log n)
* **(B)** O(n log n)
* **(C)** O(n²)
* **(D)** O(n³)
* **(E)** O(2ⁿ)

### Resposta: **B — O(n log n)**

### Explicação

O Merge Sort divide o vetor em duas partes aproximadamente iguais até que os subvetores possuam apenas um elemento.

Podemos analisar sua complexidade observando dois fatores:

### 1. Número de níveis da divisão

A cada etapa, o tamanho do problema é aproximadamente dividido por 2:

```text
n
↓
n/2
↓
n/4
↓
n/8
↓
...
↓
1
```

Para reduzir `n` até `1`, são necessários aproximadamente:

```text
log₂ n
```

níveis de divisão.

Portanto, a árvore de recursão possui **O(log n)** níveis.

### 2. Custo da intercalação

Em cada nível, os elementos precisam ser percorridos para realizar a operação de intercalação.

O trabalho total de um nível é:

```text
O(n)
```

Assim, temos:

```text
O(n) × O(log n)
```

resultando em:

```text
O(n log n)
```

### Conclusão

A complexidade assintótica do Merge Sort é:

**O(n log n)**

Portanto, a alternativa correta é a **(B)**.

---

# 3. Questão 15 — POSCOMP 2015

Considere o algoritmo que implementa o seguinte processo:

> Uma coleção desordenada de elementos é dividida em duas metades e cada metade é utilizada como argumento para a reaplicação recursiva do procedimento. Os resultados das duas reaplicações são então combinados pela intercalação dos elementos de ambas, resultando em uma coleção ordenada.

Qual é a complexidade desse algoritmo?

### Alternativas

* **(A)** O(n²)
* **(B)** O(n^(2n))
* **(C)** O(2ⁿ)
* **(D)** O(log n × log n)
* **(E)** O(n × log n)

### Resposta: **E — O(n × log n)**

### Explicação

O enunciado descreve diretamente o funcionamento do **Merge Sort**.

As principais características citadas são:

* A coleção é dividida em duas metades;
* Cada metade é processada recursivamente;
* Os resultados são combinados por **intercalação**.

O processo de divisão gera aproximadamente:

```text
O(log n)
```

níveis de recursão.

Em cada nível, os elementos precisam ser percorridos durante a intercalação, resultando em:

```text
O(n)
```

de trabalho.

Portanto:

```text
O(n) × O(log n)
```

ou:

```text
O(n log n)
```

### Conclusão

A alternativa correta é a **(E)**.

---

# 4. Complexidade de tempo do Merge Sort

### Pergunta

Qual é a complexidade de tempo do Merge Sort nos casos melhor, médio e pior? Explique por que ela não muda entre os casos.

### Resposta

O Merge Sort possui a seguinte complexidade nos três casos:

| Caso        |   Complexidade |
| ----------- | -------------: |
| Melhor caso | **O(n log n)** |
| Caso médio  | **O(n log n)** |
| Pior caso   | **O(n log n)** |

### Por que a complexidade não muda?

O funcionamento do Merge Sort é determinado principalmente pela estrutura do algoritmo, e não pela disposição inicial dos elementos.

Independentemente de o vetor estar:

* completamente desordenado;
* parcialmente ordenado;
* completamente ordenado;

o algoritmo continua dividindo o vetor recursivamente até chegar a subvetores de tamanho 1.

Depois disso, os subvetores são novamente combinados por meio da operação de `merge`.

Podemos visualizar o processo da seguinte maneira:

```text
Vetor original
      ↓
    Divide
      ↓
 ┌────┴────┐
 ↓         ↓
Metade   Metade
 ↓         ↓
Divide   Divide
 ↓         ↓
...       ...
 ↓         ↓
Subvetores de tamanho 1
      ↓
   Intercala
      ↓
   Intercala
      ↓
Vetor ordenado
```

### Comparação com outros algoritmos

Em alguns algoritmos, a disposição inicial dos elementos pode alterar significativamente o tempo de execução.

Por exemplo, o **Insertion Sort** pode apresentar comportamento O(n) no melhor caso quando o vetor já está ordenado.

No Merge Sort tradicional, isso não acontece porque o algoritmo não deixa de realizar suas divisões e intercalações apenas porque os elementos já estão ordenados.

Assim, temos:

```text
Quantidade de níveis → O(log n)
Trabalho por nível   → O(n)

O(log n) × O(n) = O(n log n)
```

### Conclusão

A complexidade permanece **O(n log n) nos três casos** porque o Merge Sort mantém sua estrutura de divisão e intercalação independentemente da ordem inicial dos elementos.

---

# 5. Propriedades do Merge Sort aplicado a vetores

Sobre o Merge Sort aplicado a vetores, é correto afirmar que:

* **(A)** É in-place e instável.
* **(B)** É in-place e estável.
* **(C)** Usa O(n) de memória auxiliar e pode ser implementado de forma estável.
* **(D)** Usa O(log n) de memória auxiliar e é sempre instável.
* **(E)** Não usa memória auxiliar, pois ordena por trocas.

### Resposta: **C**

> **Usa O(n) de memória auxiliar e pode ser implementado de forma estável.**

### Memória auxiliar

O Merge Sort tradicional aplicado a vetores utiliza um vetor auxiliar durante a operação de `merge`.

Por exemplo:

```java
private static Comparable[] aux;
```

Esse vetor auxiliar possui tamanho proporcional ao vetor original.

Portanto:

```text
Memória auxiliar = O(n)
```

Por utilizar essa memória adicional, a implementação tradicional do Merge Sort **não é in-place**.

### Estabilidade

Um algoritmo de ordenação é considerado **estável** quando elementos que possuem a mesma chave mantêm entre si a ordem relativa que tinham antes da ordenação.

O Merge Sort pode ser implementado de forma estável.

Durante a intercalação, quando dois elementos possuem a mesma chave, deve-se escolher primeiro o elemento que pertence à metade esquerda.

Por exemplo:

```text
Antes:

[A₁, A₂]

A₁ e A₂ possuem a mesma chave.
```

Uma intercalação estável mantém:

```text
[A₁, A₂]
```

em vez de inverter os elementos.

### Conclusão

O Merge Sort tradicional com vetor auxiliar:

* utiliza **O(n)** de memória auxiliar;
* pode ser **estável**;
* não é *in-place*.

Portanto, a alternativa correta é a **(C)**.

---

# 6. POSCOMP 2015 — Complexidade no pior caso

Quais destes algoritmos de ordenação têm a classe de complexidade assintótica, no pior caso, em **O(n log n)**?

### Alternativas

* **(A)** QuickSort, MergeSort e HeapSort
* **(B)** QuickSort e SelectionSort
* **(C)** MergeSort e HeapSort
* **(D)** QuickSort e BubbleSort
* **(E)** QuickSort, MergeSort e SelectionSort

### Resposta: **C — MergeSort e HeapSort**

Para resolver a questão, é necessário analisar a complexidade de cada algoritmo no **pior caso**.

| Algoritmo      |      Pior caso |
| -------------- | -------------: |
| Merge Sort     | **O(n log n)** |
| Heap Sort      | **O(n log n)** |
| Quick Sort     |      **O(n²)** |
| Selection Sort |      **O(n²)** |
| Bubble Sort    |      **O(n²)** |

### Merge Sort

O Merge Sort divide o vetor aproximadamente pela metade em cada etapa e realiza a intercalação dos elementos.

Sua complexidade no pior caso é:

```text
O(n log n)
```

### Heap Sort

O Heap Sort utiliza uma estrutura de **Heap Binário**.

As operações de ajuste e remoção no heap possuem custo logarítmico, e essas operações são realizadas para os elementos do vetor.

Sua complexidade no pior caso é:

```text
O(n log n)
```

### Quick Sort

O Quick Sort normalmente apresenta:

```text
Melhor caso:  O(n log n)
Caso médio:   O(n log n)
Pior caso:    O(n²)
```

O pior caso ocorre quando as divisões ficam muito desbalanceadas. Um exemplo clássico é quando o pivô escolhido produz uma partição com quase todos os elementos de um lado.

Portanto, ele **não pode ser incluído** entre os algoritmos que possuem pior caso O(n log n).

### Selection Sort

O Selection Sort procura repetidamente o menor elemento para colocá-lo na posição correta.

No pior caso, continua realizando aproximadamente o mesmo número de comparações:

```text
O(n²)
```

### Bubble Sort

O Bubble Sort realiza comparações entre elementos adjacentes em várias passagens pelo vetor.

No pior caso:

```text
O(n²)
```

### Conclusão

Os dois algoritmos apresentados que possuem complexidade **O(n log n) no pior caso** são:

```text
Merge Sort → O(n log n)
Heap Sort  → O(n log n)
```

Portanto, a alternativa correta é:

**(C) MergeSort e HeapSort.**

---

# Resumo — Merge Sort

| Característica   | Merge Sort                                               |
| ---------------- | -------------------------------------------------------- |
| Paradigma        | Divisão e Conquista                                      |
| Melhor caso      | **O(n log n)**                                           |
| Caso médio       | **O(n log n)**                                           |
| Pior caso        | **O(n log n)**                                           |
| Memória auxiliar | **O(n)**                                                 |
| Estável          | **Sim, na implementação adequada**                       |
| In-place         | **Não, na implementação tradicional com vetor auxiliar** |

## Funcionamento básico

```text
              Vetor
                ↓
             Dividir
            ↙       ↘
         Metade    Metade
           ↓          ↓
        Dividir    Dividir
           ↓          ↓
          ...        ...
           ↓          ↓
       Subvetores de tamanho 1
           ↓          ↓
        Intercalar / Merge
              ↓
        Vetor ordenado
```

### Ideia principal

O Merge Sort pode ser resumido em três etapas:

```text
1. DIVIDIR
   ↓
2. ORDENAR RECURSIVAMENTE
   ↓
3. INTERCALAR (MERGE)
```

A divisão gera **O(log n)** níveis e cada nível realiza **O(n)** trabalho na intercalação.

Por isso:

```text
O(n) × O(log n) = O(n log n)
```


## Materiais Adicionais:

- CPP Better Explained: Merge sort in C++
  <https://www.cppbetterexplained.com/posts/merge-sort-algorithm-cpp/>

- GeeksforGeeks: C++ Program for Merge Sort
  <https://www.geeksforgeeks.org/cpp/cpp-program-for-merge-sort/>

- Github: celzin/ Merge-Sort
  <https://github.com/celzin/Merge-Sort>

- Coddy Tech: Merge Sort Visualise
  <https://coddy.tech/visualize/sorting/merge-sort?lang=pt&view=bars&speed=1&size=14>

- Algoritmos — Merge Sort, com links para vídeo, link para Visual Go e implementação em Java
  <https://guilherme-rmendes95.medium.com/algoritmos-merge-sort-ef12dadeba2a>
