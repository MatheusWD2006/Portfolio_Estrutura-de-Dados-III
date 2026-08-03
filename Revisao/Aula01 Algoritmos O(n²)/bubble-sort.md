O Bubble Sort (ou "Ordenação por Bolha") é um dos algoritmos de ordenação mais simples de entender.
Ele recebe esse nome porque os maiores elementos "flutuam" gradualmente para o final do vetor a cada passagem, exatamente como bolhas de ar subindo na água.
Como o Bubble Sort funciona? O algoritmo compara pares de elementos vizinhos do início ao fim da lista: se o elemento da esquerda for maior que o da direita, eles trocam de lugar. Ele avança um passo e repete a comparação para o próximo par.Ao final da primeira passagem completa, o maior elemento da lista com certeza estará travado na última posição. O processo se repete para o restante da lista até que nenhuma troca seja necessária. 

Bubble Sort Implementações:

// Função que ordena um vetor de inteiros usando variáveis temporárias

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false; // Flag para otimizar caso o vetor já esteja ordenado
        // A cada passo 'i', os últimos 'i' elementos já estão no lugar certo
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Troca manual sem usar std::swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                
                trocou = true; // Marca que houve alteração
            }
        }
        // Se nenhuma troca aconteceu nesta passagem, o vetor já está ordenado
        if (!trocou) {
            break;
        }
    }
}
// Com swap ao invés de variáveis temporárias

#include <utility> // Para swap

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Substitui as 3 linhas da variável 'temp' por uma única chamada
                swap(arr[j], arr[j + 1]);
                
                trocou = true;
            }
        }
        if (!trocou) {
            break; // Otimização: para se o vetor já estiver ordenado
        }
    }
}


Exemplos de Uso: