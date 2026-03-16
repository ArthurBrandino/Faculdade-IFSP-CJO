#include <iostream>
#include <iomanip>
using namespace std;

const int INF = 99999999;

struct No {
    int vertice;
    int peso;
    No* proximo;
};

// retorna o índice do vértice com a menor distância ainda não processado
int encontrarMinimaDistancia(int* distancias, bool* processados, int numV) {
    int idx = -1;
    for (int i = 0; i < numV; i++) {
        if (!processados[i] && distancias[i] < INF) {
            if (idx == -1 || distancias[i] < distancias[idx]) {
                idx = i;
            }
        }
    }
    return idx; // pode ser -1 se todos processados ou inalcançáveis
}

void dijkstra(No** grafo, int raiz, int numV, int* distancias, int* predecessores) {
    bool* processados = new bool[numV];

    // inicializa vetores
    for (int i = 0; i < numV; i++) {
        distancias[i] = INF;
        predecessores[i] = -1;
        processados[i] = false;
    }
    distancias[raiz] = 0;
    predecessores[raiz] = raiz;

    // relaxa numV-1 vezes
    for (int k = 0; k < numV - 1; k++) {
        int u = encontrarMinimaDistancia(distancias, processados, numV);
        if (u == -1) break;                 // não há mais vértices alcançáveis
        if (distancias[u] == INF) break;    // segurança

        // percorre vizinhos de u na lista de adjacência
        for (No* p = grafo[u]; p != nullptr; p = p->proximo) {
            int v = p->vertice;
            int w = p->peso;
            if (!processados[v] && distancias[u] + w < distancias[v]) {
                distancias[v] = distancias[u] + w;
                predecessores[v] = u;
            }
        }
        processados[u] = true;
    }

    delete[] processados;
}

// imprime caminho recursivamente da raiz até destino
void imprimirCaminhoRec(int* predecessores, int raiz, int destino) {
    if (destino == raiz) {
        cout << raiz;
        return;
    }
    if (predecessores[destino] == -1) {
        cout << "(sem caminho)";
        return;
    }
    imprimirCaminhoRec(predecessores, raiz, predecessores[destino]);
    cout << " -> " << destino;
}

int main() {
    int V, A;

    // leitura de V
    while (true) {
        cout << "Entre o numero de vertices: ";
        if (cin >> V && V > 0) break;
        cout << "Valor invalido. Tente novamente.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // leitura de A
    while (true) {
        cout << "Entre o numero de arestas: ";
        if (cin >> A && A >= 0) break;
        cout << "Valor invalido. Tente novamente.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // aloca lista de adjacência
    No** grafo = new No*[V];
    for (int i = 0; i < V; i++) grafo[i] = nullptr;

    // leitura das arestas
    for (int i = 0; i < A; i++) {
        int origem, destino, peso;
        cout << "Entre a aresta (origem destino peso) 0-index: ";
        cin >> origem >> destino >> peso;

        if (origem < 0 || origem >= V || destino < 0 || destino >= V) {
            cout << "Aresta ignorada: vertice fora do intervalo [0," << V-1 << "]\n";
            i--;
            continue;
        }

        // insere destino na lista de origem (GRAFO DIRECIONADO)
        No* novoDestino = new No{destino, peso, grafo[origem]};
        grafo[origem] = novoDestino;

        // Se quiser NÃO DIRECIONADO, descomente:
        // No* novoOrigem = new No{origem, peso, grafo[destino]};
        // grafo[destino] = novoOrigem;
    }

    int raiz;
    while (true) {
        cout << "Entre o vertice raiz (origem do Dijkstra): ";
        if (cin >> raiz && raiz >= 0 && raiz < V) break;
        cout << "Origem invalida. Tente novamente.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // executa dijkstra
    int* distancias = new int[V];
    int* predecessores = new int[V];
    dijkstra(grafo, raiz, V, distancias, predecessores);

    // imprime resultados
    cout << "\nDistancias minimas a partir de " << raiz << ":\n";
    for (int v = 0; v < V; v++) {
        cout << "Vertice " << setw(2) << v << " | Dist = ";
        if (distancias[v] >= INF) cout << "INF";
        else                      cout << distancias[v];

        cout << " | Caminho: ";
        if (distancias[v] >= INF) cout << "(sem caminho)";
        else                      imprimirCaminhoRec(predecessores, raiz, v);
        cout << '\n';
    }

    // libera memória da lista
    for (int i = 0; i < V; i++) {
        No* p = grafo[i];
        while (p) {
            No* tmp = p->proximo;
            delete p;
            p = tmp;
        }
    }
    delete[] grafo;
    delete[] distancias;
    delete[] predecessores;

    return 0;
}
