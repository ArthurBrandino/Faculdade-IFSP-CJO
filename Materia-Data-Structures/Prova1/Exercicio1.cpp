#include <iostream>
#include <iomanip>

using namespace std;

struct SNode {
    int val;
    SNode* prox;
    SNode* anter;
};
    // Insere no fim: O(n) (caminha até o último)
    void push_back(int x) {
        SNode* n = new SNode(x);
        if (!head) { head = n; return; }
        SNode* p = head;
        while (p->prox) p = p->prox;
        p->prox = n;
    }

    // Busca: O(n) — retorna ponteiro (ou nullptr)
    SNode* find(int x) {
        for (SNode* p = head; p; p = p->next) if (p->val == x) return p;
        return nullptr;
    }

    // Exibe a lista
    void print() const {
        for (SNode* p = head; p; p = p->next) {
            cout << p->val << (p->next ? ' ' : '\n');
        }
    }



int main()
{
    string palavra;
    int i;
    
   do
   {
        cout << "Insira uma palavra com numero impar de letras" << endl;
        cin >> palavra 
        for(char c : palavra)
            i++;
   }While(i%2 == 0);

   for(char c : palavra)
        push_back(c);

    

}
