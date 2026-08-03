O Selection Sort (Ordenação por Seleção) é um algoritmo simples que funciona encontrando o menor elemento da parte ainda não ordenada do vetor e colocando-o na posição correta.


A ideia é:  
Procure o menor elemento do vetor.  
Troque esse elemento com a primeira posição.  
Agora considere que a primeira posição já está ordenada.  
Procure o menor elemento do restante do vetor.  
Repita até o final.


O algoritmo possui complexidade:  
Melhor caso: O(n²)  
Caso médio: O(n²)  
Pior caso: O(n²)  
Memória: O(1), pois ordena no próprio vetor.

```cpp

void selectionSort(int v[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int menor = i;

        // Procura o menor elemento
        for (int j = i + 1; j < n; j++)
        {
            if (v[j] < v[menor])
                menor = j;
        }

        // Troca os elementos
        int aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
    }
}
```
