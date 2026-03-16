/*Implemente um programa que realize a seguinte tarefa:

    Leia, de uma única vez, cinco números inteiro.
    Insira esses números, na ordem digitada, em uma árvore AVL inicialmente vazia.
    A cada inserção, verifique se houve necessidade de balanceamento da árvore.
    Exiba, na ordem em que ocorrerem, as rotações realizadas para manter a árvore balanceada.

Tipos de rotações a considerar:

    LL – rotação simples à direita
    RR – rotação simples à esquerda
    LR – rotação dupla (esquerda-direita)
    RL – rotação dupla (direita-esquerda)
    Nenhuma – caso a árvore já esteja balanceada

Exemplo de saída esperada:

      RL, LL, RL, LR.*/

#include <iostream>
using namespace std;

/* -----------------------------
   ESTRUTURAS E VARIÁVEIS GLOBAIS
   -----------------------------
   - fb (fator de balanço) usa a convenção:
     fb = altura(subárvore esquerda) - altura(subárvore direita)
     Logo:
       fb =  1 -> levemente "pesada" à esquerda
       fb = -1 -> levemente "pesada" à direita
       fb =  0 -> perfeitamente balanceada
   - Em inserções, quando fb "estoura" para +2 ou -2, precisamos rotacionar.
*/

struct NoAVL
{
    int chave;   // chave armazenada no nó
    int fb;      // fator de balanço conforme convenção acima
    NoAVL* dir;  // ponteiro para filho à direita
    NoAVL* esq;  // ponteiro para filho à esquerda
};

// Guarda as rotações realizadas, na ordem em que acontecem.
// Como são 5 inserções, o número de rotações será pequeno (no máx. algumas).
string rotacoes[5];
int contador; // inicializa em 0 (por ser global, zera automaticamente)

/* -----------------------------
   FUNÇÕES AUXILIARES DE NÓ / ROTAÇÕES
   ----------------------------- */

// Cria e retorna um novo nó AVL com fb=0 e sem filhos.
NoAVL* CriarNo(int chave){
    NoAVL* novoNo = new NoAVL;
    novoNo->chave = chave;
    novoNo->dir = nullptr;
    novoNo->esq = nullptr;
    novoNo->fb = 0;
    return novoNo;
}

/* RotacaoL
   ----------
   Aplica correções quando a árvore ficou "pesada à esquerda" (fb do p chegou a +2)
   Existem 2 subcasos:
     - LL: filho esquerdo (u) também está pesado à esquerda (u->fb == +1 ou 0 após inserções)
            -> rotação simples à direita (sobre p), registrando "LL"
     - LR: filho esquerdo (u) está pesado à direita (u->fb == -1)
            -> rotação dupla esquerda-direita: rotaciona u à esquerda e depois p à direita
               Registrando "LR"
   Retorna a nova raiz da subárvore.
*/
NoAVL* RotacaoL(NoAVL* p){
    NoAVL* u = p->esq; // filho esquerdo de p

    // Caso LR: o "joelho" está à direita de u
    if (u->fb == -1)
    {
        /* Rotação LR (esquerda-direita)
           Passos (em ponteiros):
             p
            /        u                v
           u   ->   / \    =>        / \
            \      v  ?             u   p
        (rearranjos de ponteiros abaixo) */

        NoAVL* v = u->dir;

        // Primeiro, "descer" as subárvores corretamente
        u->dir = v->esq; // subárvore esquerda de v vira filho direito de u
        v->esq = u;      // u passa a ser filho esquerdo de v

        p->esq = v->dir; // subárvore direita de v vira filho esquerdo de p
        v->dir = p;      // p passa a ser filho direito de v

        /* Ajuste dos fatores de balanço após LR:
           - Depende do fb de v no momento da rotação.
           - Tabelas padrão de AVL:
             se v->fb == -1: p->fb = 0; u->fb = +1
             se v->fb == +1: p->fb = -1; u->fb = 0
             se v->fb ==  0: p->fb = 0; u->fb = 0
        */
        if (v->fb == -1) {
            p->fb = 0;
            u->fb = 1;
        } else if (v->fb == 1) {
            p->fb = -1;
            u->fb = 0;
        } else {
            // v->fb == 0
            p->fb = 0;
            u->fb = 0;
        }

        v->fb = 0; // v torna-se a nova raiz dessa subárvore e fica balanceado

        // Registra rotação realizada
        rotacoes[contador] = "LR";
        contador++;

        return v; // nova raiz da subárvore
    }

    /* Caso LL: rotação simples à direita
       Estrutura:
           p                 u
          /        =>       / \
         u                 ?   p
    */
    p->esq = u->dir; // o antigo filho direito de u vira filho esquerdo de p
    u->dir = p;      // p desce para a direita de u

    // Após uma rotação simples por inserção, ambos tendem a ficar balanceados
    p->fb = 0;
    u->fb = 0;

    rotacoes[contador] = "LL";
    contador++;

    return u; // nova raiz da subárvore
}

/* RotacaoR
   ----------
   Simétrica da RotacaoL, para quando a árvore ficou "pesada à direita" (fb do p chegou a -2)
   Subcasos:
     - RR: filho direito (u) também pesado à direita -> rotação simples à esquerda
     - RL: filho direito (u) pesado à esquerda -> rotação dupla direita-esquerda
   Retorna a nova raiz da subárvore.
*/
NoAVL* RotacaoR(NoAVL* p){
    NoAVL* u = p->dir; // filho direito de p

    // Caso RL: o "joelho" está à esquerda de u
    if (u->fb == 1)
    {
        /* Rotação RL (direita-esquerda)
           Espelho da LR:
             p
              \           u                 v
               u   ->    / \     =>        / \
              /         v  ?              p   u
        */

        NoAVL* v = u->esq;

        u->esq = v->dir; // subárvore direita de v vira filho esquerdo de u
        v->dir = u;      // u passa a ser filho direito de v

        p->dir = v->esq; // subárvore esquerda de v vira filho direito de p
        v->esq = p;      // p passa a ser filho esquerdo de v

        /* Ajuste dos fb após RL:
           Tabelas padrão (espelho das da LR):
             se v->fb == -1: p->fb = +1; u->fb = 0
             se v->fb == +1: p->fb = 0;  u->fb = -1
             se v->fb ==  0: p->fb = 0;  u->fb = 0
        */
        if (v->fb == -1) {
            p->fb = 1;
            u->fb = 0;
        } else if (v->fb == 1) {
            p->fb = 0;
            u->fb = -1;
        } else {
            // v->fb == 0
            p->fb = 0;
            u->fb = 0;
        }

        v->fb = 0; // v vira a nova raiz local

        rotacoes[contador] = "RL";
        contador++;
        return v;
    }

    /* Caso RR: rotação simples à esquerda
         p                    u
          \         =>       / \
           u                p   ?
    */
    p->dir = u->esq; // antigo filho esquerdo de u vira filho direito de p
    u->esq = p;      // p desce para a esquerda de u

    p->fb = 0;
    u->fb = 0;

    rotacoes[contador] = "RR";
    contador++;
    return u;
}

/* Inserir
   ----------
   Insere uma chave na AVL (referência da raiz é passada por referência)
   - Parâmetro 'cresceu' indica ao ancestral se a altura da subárvore aumentou após a inserção.
   - Atualiza fator de balanço ao voltar da recursão.
   - Quando o fb "passa do limite" (de 1 para 2 ou de -1 para -2), chama rotação adequada.
   Retorna a (possivelmente nova) raiz da subárvore.
*/
NoAVL* Inserir (NoAVL*& raiz, int chave, bool& cresceu){

    // Caso base: posição de inserção
    if(raiz == nullptr){
        cresceu = true;          // altura dessa subárvore aumentou (era 0, virou 1)
        raiz = CriarNo(chave);
    }
    // Inserir à esquerda
    else if(chave < raiz->chave){
        Inserir (raiz->esq, chave, cresceu);

        if (cresceu){ // só atualiza fb se a subárvore esquerda cresceu
            if (raiz->fb == 0)
                raiz->fb = 1;      // ficou levemente mais alta à esquerda
            else if (raiz->fb == -1)
                raiz->fb = 0;      // alturas se equilibraram
            else if (raiz->fb == 1) // estava +1 e cresceu de novo -> estourou para +2 -> precisa rotacionar
            {
                raiz = RotacaoL (raiz); // resolve com LL ou LR internamente
                cresceu = false;        // após rotação, a altura global dessa subárvore não aumenta
            }
        }
    }
    // Inserir à direita (nota: chaves iguais vão para a direita; pode ser política de duplicatas)
    else {
        Inserir (raiz->dir, chave, cresceu);

        if (cresceu){ // só atualiza fb se a subárvore direita cresceu
            if (raiz->fb == 0)
                raiz->fb = -1;     // ficou levemente mais alta à direita
            else if (raiz->fb == 1)
                raiz->fb = 0;      // alturas se equilibraram
            else if (raiz->fb == -1) // estava -1 e cresceu de novo -> estourou para -2 -> precisa rotacionar
            {
                raiz = RotacaoR (raiz); // resolve com RR ou RL internamente
                cresceu = false;        // após rotação, altura dessa subárvore não aumenta
            }
        }
    }

    return raiz; // devolve (possível) nova raiz local, usada para reencadear o pai
}

int main()
{
    NoAVL* raiz = nullptr; // árvore inicialmente vazia
    int N;                 // valor lido em cada inserção
    bool cresceu = false;  // indica se a subárvore (a partir de uma chamada) aumentou de altura

    // Lê exatamente 5 inteiros e insere na ordem digitada
    for(int i = 0; i < 5; i++)
    {
        cin >> N;
        Inserir (raiz, N, cresceu);
    }

    // Exibe as rotações na ordem em que ocorreram.
    // (Saída simples: "LL - RR - ..." conforme seu código original)
    for(int i = 0; i < contador; i++)
    {
        cout << rotacoes[i] << " - ";
    }

    return 0;
}
