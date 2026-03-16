#include <iostream>
using namespace std;

struct No
{
    string chave;   
    No* dir;     
    No* esq;     
};

void Inserir(int chave, No*& raiz)
{
    for(char c : chave)                        //Laço para inserir cada letra da string CHAVE
    {
        if (raiz == nullptr)                 
        {
            raiz = new No;
            raiz->c = c;
            raiz->dir = nullptr;
            raiz->esq = nullptr;
        }
        else if (!=(Busca(c, raiz)))        
            if (c < raiz->chave)                // vai para a direita( Reverso )
                Inserir(c, raiz->dir)
            else                                 // vai para a esquerda( Reverso )
                Inserir(c, raiz->esq);
    }
}

bool Busca(int pesq, No* raiz)
{
    if (raiz == nullptr)
        return false;
    else if (pesq == raiz->chave)           // achou
        return true;
    else if (pesq > raiz->chave)            // procura na direita (reverso)
        return Busca(pesq, raiz->esq);
    else                                    // procura na esquerda (reverso)
        return Busca(pesq, raiz->dir);
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

// ============================================
//             Programa principal
// ============================================
int main()
{
    No* raiz = nullptr;
    char palavra;

    cout << "Entre com um nome: " << endl;
    cin >> palavra;
    Inserir(palavra, raiz);

    // percursos
    cout << "Em Ordem: ";
    EmOrdem(raiz);
    cout << endl;

    cout << "Largura: ";
    Largura(raiz);
    cout << endl;

    return 0;
}
