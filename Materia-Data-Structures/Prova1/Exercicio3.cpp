
#include <iostream>
using namespace std;

struct NoAVL
{
    int chave;   
    int fb;      
    NoAVL* dir;  
    NoAVL* esq;  
};


NoAVL* CriarNo(int chave){
    NoAVL* novoNo = new NoAVL;
    novoNo->chave = chave;
    novoNo->dir = nullptr;
    novoNo->esq = nullptr;
    novoNo->fb = 0;
    return novoNo;
}

NoAVL* RotacaoL(NoAVL* p){
    NoAVL* u = p->esq; 

    if (u->fb == -1)
    {
        NoAVL* v = u->dir;

        u->dir = v->esq;
        v->esq = u;     

        p->esq = v->dir; 
        v->dir = p;      

        if (v->fb == -1) {
            p->fb = 0;
            u->fb = 1;
        } else if (v->fb == 1) {
            p->fb = -1;
            u->fb = 0;
        } else {
            p->fb = 0;
            u->fb = 0;
        }

        v->fb = 0; 
        cout <<  "Rotacao realizada: LR" << endl;
        return v; 
    }
    p->esq = u->dir; 
    u->dir = p;      

    p->fb = 0;
    u->fb = 0;

    cout <<  "Rotacao realizada: LL" << endl;
    return u; 
}

NoAVL* RotacaoR(NoAVL* p){
    NoAVL* u = p->dir; 
    if (u->fb == 1)
    {

        NoAVL* v = u->esq;

        u->esq = v->dir; 
        v->dir = u;     

        p->dir = v->esq; 
        v->esq = p;      

        if (v->fb == -1) {
            p->fb = 1;
            u->fb = 0;
        } else if (v->fb == 1) {
            p->fb = 0;
            u->fb = -1;
        } else {
            p->fb = 0;
            u->fb = 0;
        }

        v->fb = 0;

        cout <<  "Rotacao realizada: RL" << endl;
        return v;
    }  
    p->dir = u->esq; 
    u->esq = p;     

    p->fb = 0;
    u->fb = 0;

    cout <<  "Rotacao realizada: RR" << endl;
    return u;
}

NoAVL* Inserir (NoAVL*& raiz, int chave, bool& cresceu){

    if(!(Busca(chave)))
    {
        
        if(raiz == nullptr){
            cresceu = true;          
        }
        else if(chave < raiz->chave){
            Inserir (raiz->esq, chave, cresceu);

            if (cresceu){ 
                if (raiz->fb == 0)
                    raiz->fb = 1;      
                else if (raiz->fb == -1)
                    raiz->fb = 0;      
                else if (raiz->fb == 1) 
                {
                    raiz = RotacaoL (raiz); 
                    cresceu = false;        
                }
            }
        }
        
        else {
            Inserir (raiz->dir, chave, cresceu);

            if (cresceu){ 
                if (raiz->fb == 0)
                    raiz->fb = -1;     
                else if (raiz->fb == 1)
                    raiz->fb = 0;      
                else if (raiz->fb == -1) 
                {
                    raiz = RotacaoR (raiz); 
                    cresceu = false;        
                }
            }
        }

        return raiz;
    }
}

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


// Percorre a árvore em largura (nível por nível)
void Largura(No* raiz)
{
    cout << "Arvore em Largura: " << endl;
    if (raiz == nullptr) return;

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

int main()
{
    NoAVL* raiz = nullptr; // árvore inicialmente vazia
    bool cresceu = false;  // indica se a subárvore (a partir de uma chamada) aumentou de altura
    int N;
    char sair = 'S', inserir;

   
    Inserir (raiz, 30, cresceu);
    Inserir (raiz, 29, cresceu);
    Inserir (raiz, 00, cresceu);
    Inserir (raiz, 07, cresceu);
    Inserir (raiz, 04, cresceu);
    Inserir (raiz, 20, cresceu);
    Inserir (raiz, 06, cresceu);

    cout << "Deseja inserir mais valores?(S/N) ";
    cin >> inserir;
    inserir = toupper(inserir);

    if(inserir == 'S')
        do 
        {
            cout << "Inserindo: "
            cin >> N;
            Inserir (raiz, N, cresceu);
            Largura();

            cout << "\n Deseja continuar inserindo?(S/N) ";
            cin >> sair 
            sair = toupper(sair);
        }while(sair == N)

    return 0;
}
