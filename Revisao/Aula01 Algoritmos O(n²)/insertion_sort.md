O Insertion Sort (ou "Ordenação por Inserção") é um algoritmo de ordenação bem intuitivo.  
Ele funciona da mesma forma que a maioria das pessoas usa para ordenar cartas em um jogo de baralho: você pega uma carta por vez e a insere na posição correta dentro do grupo de cartas que já estão ordenadas na sua mão.  
Como o Insertion Sort funciona?O vetor é dividido mentalmente em duas partes: uma sublista ordenada (à esquerda) e uma sublista não ordenada (à direita).  
Começamos considerando o primeiro elemento (índice 0) como uma lista já ordenada de tamanho.  
1.Pegamos o próximo elemento não ordenado (chamado de chave ou key);  
2.Comparamos a chave com os elementos da esquerda (a parte ordenada), movendo para a direita todos os elementos que forem maiores que ela;  
3.Inserimos a chave no espaço vago.  
Repetimos até o final do vetor.

```cpp
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = arr[i]; // Elemento que vamos inserir na parte ordenada
        int j = i - 1;

        // Move os elementos de arr[0..i-1] que são maiores que a chave
        // para uma posição à frente de sua posição atual
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        // Insere a chave na sua posição correta
        arr[j + 1] = chave;
    }
}
```
