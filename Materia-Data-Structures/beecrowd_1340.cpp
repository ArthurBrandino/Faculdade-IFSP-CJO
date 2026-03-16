#include <iostream>

using namespace std;

int fila[4];
int inicio = 0, fim = 0;

//Inserir
void Inserir(int valor){
    fila[fim] = valor;
    fim++;
}

//Fila
void Desenfileirar(){
    inicio++;
}

//Fila de Prioridade
void removerPrioridade(){
    int maior = inicio;
    for (int i = inicio; i < fim; i++)
    {
        if(fila[i] > fila[maior])
            maior = i;
    }
    fila[maior] = -1;

}
//Pilha
void Desempilhar(int valor){
    fim--;
}

int main()
{
    
    return 0;
}
