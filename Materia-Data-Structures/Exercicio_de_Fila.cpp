#include <iostream>
using namespace std;

/*
    Fila circular estática de inteiros

    Por que fila circular?
      - No seu código original, quando 'fim' chegava ao tamanho do vetor, a fila
        era considerada "cheia" para sempre, mesmo após removermos elementos.
      - A fila circular resolve isso fazendo 'inicio' e 'fim' "darem a volta"
        (módulo CAP), permitindo reutilizar as posições liberadas.

    Convenções:
      - CAP = capacidade máxima de elementos na fila.
      - 'inicio' aponta para o índice do primeiro elemento (frente).
      - 'fim' aponta para a posição onde o próximo elemento será inserido.
      - 'qtde' armazena quantos elementos existem na fila (facilita checar cheia/vazia).
*/

const int CAP = 4;     // capacidade da fila (pode ajustar se quiser)
int fila[CAP];         // armazenamento da fila
int inicio = 0;        // índice da frente
int fim = 0;           // próximo índice de inserção
int qtde = 0;          // quantidade de elementos na fila

// Retorna true se a fila está vazia
bool Vazia() {
    return qtde == 0;
}

// Retorna true se a fila está cheia
bool Cheia() {
    return qtde == CAP;
}

// Enfileira (insere) um valor no final da fila
void Enfileirar(int valor) {
    if (Cheia()) {
        cout << "Fila cheia! Nao foi possivel enfileirar " << valor << ".\n";
        return;
    }
    fila[fim] = valor;           // guarda no próximo slot
    fim = (fim + 1) % CAP;       // avança circularmente
    qtde++;                      // aumenta a contagem
}

// Remove o elemento da frente da fila
void Desenfileirar() {
    if (Vazia()) {
        cout << "Fila vazia! Nao ha o que desenfileirar.\n";
        return;
    }
    // (Opcional) limpar posição para facilitar visualização ao exibir
    fila[inicio] = 0;
    inicio = (inicio + 1) % CAP; // avança a frente circularmente
    qtde--;                      // diminui a contagem
}

// Retorna (sem remover) o elemento da frente
int Frente() {
    if (Vazia()) {
        cout << "Fila vazia! Nao ha frente.\n";
        return -1; // valor sentinela
    }
    return fila[inicio];
}

// Retorna a quantidade de elementos atualmente na fila
int Tamanho() {
    return qtde;
}

// Exibe a fila na ordem lógica (da frente ao fim)
void Exibir() {
    if (Vazia()) {
        cout << "[fila] (vazia)\n";
        return;
    }

    cout << "[fila] ";
    // percorre 'qtde' elementos começando de 'inicio'
    for (int i = 0; i < qtde; i++) {
        int idx = (inicio + i) % CAP;
        cout << fila[idx] << (i + 1 < qtde ? ' ' : '\n');
    }
}

// (Opcional) Exibe o buffer físico (índices reais do array) para depuração
void ExibirBufferBruto() {
    cout << "[buffer] ";
    for (int i = 0; i < CAP; i++) {
        cout << fila[i] << (i + 1 < CAP ? ' ' : '\n');
    }
    cout << "inicio=" << inicio << " fim=" << fim << " qtde=" << qtde << "\n";
}

int main() {
    // Inicialmente, o array pode conter lixo. Vamos zerar (opcional, só p/ visual)
    for (int i = 0; i < CAP; i++) fila[i] = 0;

    // ---- Mesmo fluxo que você usou, para comparar comportamento ----
    Enfileirar(3);
    Enfileirar(5);
    Enfileirar(4);
    Enfileirar(9);
    Exibir();                // esperado: 3 5 4 9
    Enfileirar(9);           // não deve entrar (cheia)
    Desenfileirar();         // remove 3
    Desenfileirar();         // remove 5
    Exibir();                // esperado: 4 9

    // ---- Demonstração do reaproveitamento (circularidade) ----
    Enfileirar(8);           // entra no lugar "circular"
    Enfileirar(7);           // entra também
    Exibir();                // esperado: 4 9 8 7
    cout << "Frente: " << Frente() << "\n"; // esperado: 4
    cout << "Tamanho: " << Tamanho() << "\n"; // esperado: 4 (cheia)

    // Depuração opcional do buffer físico:
    // ExibirBufferBruto();

    return 0;
}
