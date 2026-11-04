# Tabelas Hash

## Definição

Uma **tabela hash** é uma estrutura de dados que armazena pares de **chave e valor**. Ela usa uma **função hash** para transformar cada chave em um índice de um vetor, determinando onde o valor será armazenado.

Por exemplo, uma tabela pode associar o código de um produto à sua descrição:

```text
chave: 42  → valor: "Teclado"
```

A função hash calcula a posição da chave na tabela. Como chaves diferentes podem resultar no mesmo índice, podem ocorrer **colisões**.

## Como funciona

1. A chave é enviada para uma função hash.
2. A função calcula um índice válido na tabela.
3. O par chave-valor é armazenado nessa posição.
4. Para buscar ou remover um elemento, a mesma função calcula onde procurar.

Uma função hash simples para números inteiros é:

```text
índice = chave % tamanho_da_tabela
```

O resultado precisa ser ajustado para ficar entre `0` e `tamanho_da_tabela - 1`.

### Colisões

Uma colisão acontece quando duas chaves diferentes são direcionadas ao mesmo índice. Algumas formas de lidar com isso são:

- **Encadeamento:** cada posição da tabela guarda uma lista de elementos.
- **Endereçamento aberto:** se a posição estiver ocupada, procura-se outra posição livre na própria tabela.

O exemplo sem STL a seguir usa **encadeamento**.

## Usos

Tabelas hash são úteis quando é necessário localizar rapidamente um elemento pela sua chave, por exemplo:

- Consultar produtos por código.
- Armazenar e localizar usuários por identificador.
- Implementar conjuntos e dicionários.
- Contar ocorrências de palavras ou elementos.
- Criar caches e tabelas de símbolos em compiladores.

São menos adequadas quando é necessário manter os elementos ordenados ou fazer consultas por intervalo, como “encontrar todas as chaves entre 10 e 20”.

## Complexidade

O fator de carga, representado por **α**, indica a proporção entre a quantidade de elementos e o tamanho da tabela:

```text
α = quantidade_de_elementos / tamanho_da_tabela
```

| Operação | Caso médio | Pior caso |
|---|---:|---:|
| Busca | O(1) | O(n) |
| Inserção | O(1) | O(n) |
| Remoção | O(1) | O(n) |

O caso médio é rápido quando a função hash distribui bem as chaves e o fator de carga é controlado. No pior caso, muitas chaves caem na mesma posição e a operação pode precisar percorrer até `n` elementos.

O espaço ocupado é **O(n)**, além do espaço reservado para a tabela.

## Implementação em C++ sem contêineres da STL

Esta versão usa um vetor fixo de ponteiros e listas ligadas criadas manualmente. Não utiliza contêineres como `std::vector`, `std::list` ou `std::unordered_map`.

Ela armazena pares de inteiros. Se uma chave já existir, a inserção atualiza seu valor.

```cpp
#include <iostream>

class HashTable {
private:
    static const int TABLE_SIZE = 101;

    struct Node {
        int key;
        int value;
        Node* next;

        Node(int k, int v, Node* n)
            : key(k), value(v), next(n) {}
    };

    Node* buckets[TABLE_SIZE];

    int hashFunction(int key) const {
        int index = key % TABLE_SIZE;

        if (index < 0) {
            index += TABLE_SIZE;
        }

        return index;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            buckets[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* current = buckets[i];

            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    }

    void insert(int key, int value) {
        int index = hashFunction(key);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }

            current = current->next;
        }

        buckets[index] = new Node(key, value, buckets[index]);
    }

    bool search(int key, int& value) const {
        int index = hashFunction(key);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->key == key) {
                value = current->value;
                return true;
            }

            current = current->next;
        }

        return false;
    }

    bool remove(int key) {
        int index = hashFunction(key);
        Node* current = buckets[index];
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (previous == nullptr) {
                    buckets[index] = current->next;
                } else {
                    previous->next = current->next;
                }

                delete current;
                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }
};

int main() {
    HashTable table;

    table.insert(42, 100);
    table.insert(15, 200);
    table.insert(42, 300); // Atualiza o valor da chave 42.

    int value;

    if (table.search(42, value)) {
        std::cout << "Valor associado a 42: " << value << '\n';
    } else {
        std::cout << "Chave nao encontrada\n";
    }

    if (table.remove(15)) {
        std::cout << "Chave 15 removida\n";
    }

    return 0;
}
```

## Implementação com STL

A biblioteca padrão do C++ oferece `std::unordered_map`, um contêiner associativo baseado em tabela hash. Ele gerencia as colisões e a memória automaticamente.

```cpp
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<int, std::string> produtos;

    produtos[42] = "Teclado";
    produtos[15] = "Mouse";

    auto resultado = produtos.find(42);

    if (resultado != produtos.end()) {
        std::cout << "Produto: " << resultado->second << '\n';
    } else {
        std::cout << "Produto nao encontrado\n";
    }

    produtos.erase(15);

    return 0;
}
```

Em `std::unordered_map`, `find` procura uma chave e `erase` a remove. O uso de `operator[]` para inserir ou atualizar é prático, mas também cria uma entrada com valor padrão caso a chave ainda não exista.

## Resumo

A tabela hash transforma chaves em índices para permitir acesso rápido aos dados. Suas operações têm custo médio **O(1)**, mas podem chegar a **O(n)** no pior caso, especialmente quando há muitas colisões. Em C++, é possível implementá-la manualmente ou usar `std::unordered_map` quando não houver necessidade de controlar os detalhes internos.