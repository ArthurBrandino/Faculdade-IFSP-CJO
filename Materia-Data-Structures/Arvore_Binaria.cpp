#include <iostream>
using namespace std;

// ============================================
//      Estrutura do Nó da Árvore Binária
// ============================================
struct No
{
    int chave;   // valor armazenado no nó
    No* dir;     // ponteiro para filho à direita
    No* esq;     // ponteiro para filho à esquerda
};

// ============================================
//      Implementação de Fila Manual
// ============================================
const int MAX = 100;             // tamanho máximo da fila
No* fila[MAX];                   // vetor que representa a fila
int ini = 0, fim = 0;            // índices de controle da fila

// Verifica se a fila está vazia
bool FilaVazia()
{
    return ini == fim;
}

// Verifica se a fila está cheia
bool FilaCheia()
{
    return (fim + 1) % MAX == ini;
}

// Insere um nó no final da fila
void Enfileirar(No* n)
{
    if (!FilaCheia())
    {
        fila[fim] = n;
        fim = (fim + 1) % MAX;
    }
}

// Remove um nó do início da fila
No* Desenfileirar()
{
    if (!FilaVazia())
    {
        No* n = fila[ini];
        ini = (ini + 1) % MAX;
        return n;
    }
    return nullptr;
}

// ============================================
//      Funções da Árvore Binária
// ============================================

// Insere um novo nó na árvore
void Inserir(int chave, No*& raiz)
{
    if (raiz == nullptr)                 // insere novo nó
    {
        raiz = new No;
        raiz->chave = chave;
        raiz->dir = nullptr;
        raiz->esq = nullptr;
    }
    else if (chave < raiz->chave)        // vai para a esquerda
        Inserir(chave, raiz->esq);
    else                                 // vai para a direita
        Inserir(chave, raiz->dir);
}

// Busca um valor na árvore
bool Busca(int pesq, No* raiz)
{
    if (raiz == nullptr)
        return false;
    else if (pesq == raiz->chave)           // achou
        return true;
    else if (pesq < raiz->chave)            // procura na esquerda
        return Busca(pesq, raiz->esq);
    else                                    // procura na direita
        return Busca(pesq, raiz->dir);
}

// Conta a quantidade de nós
int Contagem(No* raiz)
{
    if (raiz == nullptr)
        return 0;
    else
        return Contagem(raiz->esq) + 1 + Contagem(raiz->dir);
}

// Percorre a árvore em ordem (Esquerda, Raiz, Direita)
void EmOrdem(No* raiz)
{
    if (raiz != nullptr)
    {
        EmOrdem(raiz->esq);
        cout << raiz->chave << " - ";
        EmOrdem(raiz->dir);
    }
}

// Percorre a árvore em pré-ordem (Raiz, Esquerda, Direita)
void PreOrdem(No* raiz)
{
    if (raiz != nullptr)
    {
        cout << raiz->chave << " - ";
        PreOrdem(raiz->esq);
        PreOrdem(raiz->dir);
    }
}

// Percorre a árvore em pós-ordem (Esquerda, Direita, Raiz)
void PosOrdem(No* raiz)
{
    if (raiz != nullptr)
    {
        PosOrdem(raiz->esq);
        PosOrdem(raiz->dir);
        cout << raiz->chave << " - ";
    }
}

// Percorre a árvore em largura (nível por nível)
void Largura(No* raiz)
{
    if (raiz == nullptr) return;

    // reinicia fila
    ini = fim = 0;
    Enfileirar(raiz);

    while (!FilaVazia())
    {
        No* atual = Desenfileirar();
        cout << atual->chave << " - ";

        if (atual->esq != nullptr)
            Enfileirar(atual->esq);
        if (atual->dir != nullptr)
            Enfileirar(atual->dir);
    }
}

// Remove um nó da árvore (recursivo)
void Remover(No*& raiz, int chave)
{
    if(raiz == nullptr)
    {
        cout << "Valor nao encontrado!" << endl;
        return;
    }
    if (chave < raiz->chave)
        Remover(raiz->esq, chave);
    else if (chave > raiz->chave)
        Remover(raiz->dir, chave);
    else
        if(raiz->dir == nullptr && raiz->esq == nullptr)     // caso 1: nó folha
        {
            delete raiz;
        }
    else if (raiz->esq == nullptr)                           // caso 2: só tem filho direito
        {
            raiz = raiz->dir;
        }
    else if (raiz->dir == nullptr)                           // caso 2: só tem filho esquerdo
        {
            raiz = raiz->esq;
        }
    else                                                     // caso 3: dois filhos → substitui pelo sucessor
    {
        No* sucessor = raiz->dir;
        while(sucessor->esq != nullptr)
        {
            sucessor = sucessor->esq;
        }
        raiz->chave = sucessor->chave;
        Remover(raiz->dir, sucessor->chave);
    }
}

// Remove um nó da árvore (iterativo)
void RemoverIterativo(No*& raiz, int chave)
{
    No* atual = raiz;
    No* pai = nullptr;

    while(atual != nullptr && atual->chave != chave)         // procura o nó
    {
        pai = atual;
        if(chave < atual->chave)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    if(atual == nullptr)
    {
        cout << "Valor nao encontrado!" << endl;
        return;
    }

    if(atual->esq == nullptr && atual->dir == nullptr)        // caso 1: nó folha
    {
        if(pai == nullptr)
            raiz = nullptr;
        else if(pai->esq == atual)
            pai->esq = nullptr;
        else
            pai->dir = nullptr;

        delete atual;
    }

    else if(atual->esq == nullptr || atual->dir == nullptr)    // caso 2: nó com um filho
    {
        No* filho = (atual->esq != nullptr) ? atual->esq : atual->dir;

        if (pai == nullptr) 
            raiz = filho;
        else if (pai->esq == atual)
            pai->esq = filho;
        else
            pai->dir = filho;

        delete atual;
    }
    else {                                                    // caso 3: nó com dois filhos
        No* sucessorPai = atual;
        No* sucessor = atual->dir;

        while (sucessor->esq != nullptr) {
            sucessorPai = sucessor;
            sucessor = sucessor->esq;
        }

        atual->chave = sucessor->chave;

        if (sucessorPai->esq == sucessor)
            sucessorPai->esq = sucessor->dir;
        else
            sucessorPai->dir = sucessor->dir;

        delete sucessor;
    }
}

// ============================================
//             Programa principal
// ============================================
int main()
{
    No* raiz = nullptr;
    int pesq;

    // inserção de valores
    Inserir(4, raiz);
    Inserir(3, raiz);
    Inserir(5, raiz);
    Inserir(2, raiz);
    Inserir(7, raiz);

    // busca interativa
    cout << "Digite um numero para buscar: ";
    cin >> pesq;

    if (Busca(pesq, raiz))
        cout << "Encontrou" << endl;
    else
        cout << "Nao Encontrou" << endl;

    // estatísticas
    cout << "Total de nos: " << Contagem(raiz) << endl;

    // percursos
    cout << "Em Ordem: ";
    EmOrdem(raiz);
    cout << endl;

    cout << "Pre Ordem: ";
    PreOrdem(raiz);
    cout << endl;

    cout << "Pos Ordem: ";
    PosOrdem(raiz);
    cout << endl;

    cout << "Largura: ";
    Largura(raiz);
    cout << endl;

    return 0;
}
