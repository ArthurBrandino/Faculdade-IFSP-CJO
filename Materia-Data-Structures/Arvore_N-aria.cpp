// ============================================
//          Programa de Árvore N-ária
// ============================================

#include <iostream>
#include <string>
using namespace std;

// Estrutura de nó da árvore
struct No
{
    string chave;
    No* filho;
    No* irmao;
};

/* ========================================
            Cria um novo nó da árvore
    ========================================*/ 
No* CriarNo(string valor)
{
    No* novoNo = new No();
    novoNo->chave = valor;
    novoNo->filho = nullptr;
    novoNo->irmao = nullptr;
    return novoNo; 
}

/* ===================================
            Exibe os nós da árvore
    ====================================*/  
void Exibir(No* raiz)
{
    if(raiz == nullptr) 
        return;

    cout << raiz->chave;   // imprime o nome do nó

    if(raiz->filho != nullptr)
    {
        cout << "(";
        Exibir(raiz->filho);  // percorre os filhos
        cout << ")";
    }

    if(raiz->irmao != nullptr)   
    {
        cout << ", ";
        Exibir(raiz->irmao);     // percorre os irmãos
    }
}

/* =========================================
             Busca um nó pelo valor
    ========================================== */
No* Buscar(No* raiz, string valor)
{
    if(raiz == nullptr) return nullptr;

    if(raiz->chave == valor) 
        return raiz;

    No* encontrado = Buscar(raiz->filho, valor);
    if(encontrado != nullptr) return encontrado;

    return Buscar(raiz->irmao, valor);
}

/* =====================================
            Insere um novo nó 
    =====================================*/
void Inserir(No* raiz, string pai, string valor)
{
    No* noPai = Buscar(raiz, pai);
    if(noPai == nullptr) 
    {
        cout << "Pai Inexistente: " << pai << endl;
        return;
    }

    No* novoNo = CriarNo(valor);

    if(noPai->filho == nullptr) 
        noPai->filho = novoNo;
    else
    {
        No* irmaofinal = noPai->filho;
        while (irmaofinal->irmao != nullptr)
        {
            irmaofinal = irmaofinal->irmao;
        }
        irmaofinal->irmao = novoNo;
    }
}

int main()
{
    // Cria a raiz da árvore
    No* raiz = CriarNo("Igor");

    Inserir(raiz, "Igor", "Joaozinho");
    Inserir(raiz, "Igor", "Mariazinha");
    Inserir(raiz, "Mariazinha", "Aninha");

    Exibir(raiz);

    return 0;
}
