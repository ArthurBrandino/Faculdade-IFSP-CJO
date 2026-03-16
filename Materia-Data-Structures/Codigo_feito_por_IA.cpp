#include <bits/stdc++.h>
using namespace std;

struct Node {
    char key;
    int h;
    Node *l, *r;
    Node(char k) : key(k), h(1), l(nullptr), r(nullptr) {}
};

int height(Node* n){ return n ? n->h : 0; }

int balance(Node* n){ return n ? height(n->l) - height(n->r) : 0; }

void update(Node* n){ n->h = 1 + max(height(n->l), height(n->r)); }

Node* rotRight(Node* y){
    Node* x = y->l;
    Node* T2 = x->r;
    x->r = y; y->l = T2;
    update(y); update(x);
    return x;
}

Node* rotLeft(Node* x){
    Node* y = x->r;
    Node* T2 = y->l;
    y->l = x; x->r = T2;
    update(x); update(y);
    return y;
}

// Insere ignorando duplicatas
Node* insertAVL(Node* root, char key){
    if(!root) return new Node(key);
    if(key < root->key) root->l = insertAVL(root->l, key);
    else if(key > root->key) root->r = insertAVL(root->r, key);
    else return root; // duplicata: não insere

    update(root);
    int bf = balance(root);

    // 4 casos
    if(bf > 1 && key < root->l->key)       return rotRight(root);            // LL
    if(bf < -1 && key > root->r->key)      return rotLeft(root);             // RR
    if(bf > 1 && key > root->l->key){      // LR
        root->l = rotLeft(root->l);
        return rotRight(root);
    }
    if(bf < -1 && key < root->r->key){     // RL
        root->r = rotRight(root->r);
        return rotLeft(root);
    }
    return root;
}

void bfsPrint(Node* root){
    if(!root){ cout << "(vazia)\n"; return; }
    queue<Node*> q; q.push(root);
    bool first = true;
    while(!q.empty()){
        Node* n = q.front(); q.pop();
        cout << (first ? "" : " ") << n->key;
        first = false;
        if(n->l) q.push(n->l);
        if(n->r) q.push(n->r);
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1) Inicialize com seu primeiro nome
    string primeiroNome = "Arthur"; // <- troque aqui se quiser
    Node* root = nullptr;

    // normaliza para minúsculas e insere
    vector<bool> visto(256,false);
    for(char c : primeiroNome){
        if(!isalpha((unsigned char)c)) continue;
        c = (char)tolower((unsigned char)c);
        if(!visto[(unsigned char)c]){
            root = insertAVL(root, c);
            visto[(unsigned char)c] = true;
        }
    }

    // 2) Lê a palavra do usuário
    string palavra;
    if(!(cin >> palavra)) return 0;

    // 3) Insere apenas letras não repetidas (da palavra)
    vector<bool> vistoPal(256,false);
    for(char c : palavra){
        if(!isalpha((unsigned char)c)) continue;
        c = (char)tolower((unsigned char)c);
        if(!vistoPal[(unsigned char)c]){
            root = insertAVL(root, c);
            vistoPal[(unsigned char)c] = true;
        }
    }

    // 4) Imprime percurso em largura
    bfsPrint(root);
    return 0;
}
