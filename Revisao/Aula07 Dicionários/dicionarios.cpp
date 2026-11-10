#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

// ============================================================================
// Estrutura de Dados III - Aula 07: Dicionários
// Exemplo de uso de dicionários utilizando a STL do C++:
// - map: árvore balanceada (chaves ordenadas, busca/inserção O(log n))
// - unordered_map: tabela hash (sem ordenação, busca/inserção O(1) média)
// - vector: contêiner sequencial auxiliar para entrada e processamento de dados
// ============================================================================

int main() {
    cout << "=============================================\n";
    cout << "      EXEMPLO DE DICIONARIOS (STL C++)       \n";
    cout << "=============================================\n\n";

    // 1. Dados de entrada usando um vector de pares (chave: matricula, valor: nome)
    // Os dados chegam desordenados no vetor:
    vector<pair<int, string>> listaAlunos = {
        {103, "Carlos"},
        {101, "Ana"},
        {105, "Mariana"},
        {102, "Bruno"},
        {104, "Beatriz"}
    };

    // =========================================================================
    // PARTE 1: map (Baseado em Arvore Rubro-Negra - Ordenado)
    // =========================================================================
    cout << "--- 1. map (Chaves sempre ORDENADAS) ---\n";
    map<int, string> mapaOrdenado;

    // Inserindo os dados do vetor no mapa
    for (const auto& aluno : listaAlunos) {
        // O operador [] insere uma nova chave ou atualiza o valor se ja existir
        mapaOrdenado[aluno.first] = aluno.second;
    }

    // Iteracao: note que os elementos sao percorridos em ordem crescente da chave
    cout << "Elementos no map:\n";
    for (const auto& par : mapaOrdenado) {
        cout << "  Matricula: " << par.first << " -> Aluno: " << par.second << "\n";
    }

    // Operacao de busca: find() retorna um iterador
    int buscaId = 102;
    auto itBusca = mapaOrdenado.find(buscaId);
    if (itBusca != mapaOrdenado.end()) {
        cout << "\nBusca: Matricula " << buscaId << " encontrada! Aluno: " << itBusca->second << "\n";
    } else {
        cout << "\nBusca: Matricula " << buscaId << " nao encontrada.\n";
    }

    // Operacao de remocao: erase() remove pela chave
    mapaOrdenado.erase(102);
    cout << "Matricula 102 removida do map.\n";
    cout << "Matricula 102 ainda existe? " 
              << (mapaOrdenado.find(102) != mapaOrdenado.end() ? "Sim" : "Nao") << "\n\n";

    // =========================================================================
    // PARTE 2: unordered_map (Baseado em Tabela Hash - Nao Ordenado)
    // =========================================================================
    cout << "--- 2. unordered_map (TABELA HASH - Acesso O(1) medio) ---\n";
    unordered_map<int, string> mapaHash;

    // Inserindo os mesmos dados do vetor
    for (const auto& aluno : listaAlunos) {
        mapaHash[aluno.first] = aluno.second;
    }

    // Iteracao: a ordem dos elementos depende da funcao hash interna (nao eh ordenada)
    cout << "Elementos no unordered_map:\n";
    for (const auto& par : mapaHash) {
        cout << "  Matricula: " << par.first << " -> Aluno: " << par.second << "\n";
    }

    // Busca no unordered_map (tempo constante medio O(1))
    buscaId = 105;
    if (mapaHash.find(buscaId) != mapaHash.end()) {
        cout << "\nBusca: Matricula " << buscaId << " encontrada! Aluno: " << mapaHash[buscaId] << "\n";
    }

    // Remocao no unordered_map
    mapaHash.erase(105);
    cout << "Matricula 105 removida do unordered_map.\n\n";

    // =========================================================================
    // PARTE 3: Aplicacao classica com vector (Contagem de frequencia)
    // =========================================================================
    cout << "--- 3. Exemplo Pratico: Contar frequencia de um vector ---\n";
    vector<int> numeros = {4, 2, 4, 5, 2, 3, 4, 1, 5, 4, 2};

    cout << "Vetor de numeros: ";
    for (int num : numeros) {
        cout << num << " ";
    }
    cout << "\n";

    // Contagem rapida usando unordered_map (chave: numero, valor: contagem)
    unordered_map<int, int> frequencia;
    for (int num : numeros) {
        // Se a chave ainda nao existir, o C++ inicializa com 0 e depois incrementa
        frequencia[num]++;
    }

    cout << "\nFrequencia de cada numero:\n";
    for (const auto& par : frequencia) {
        cout << "  Numero " << par.first << " apareceu " << par.second << " vez(es)\n";
    }

    return 0;
}
