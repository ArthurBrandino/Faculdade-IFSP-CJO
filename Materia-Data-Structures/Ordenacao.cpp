#include <iostream>

using namespace std;

void mostrarVetor(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++)
    { 
        cout << vetor[i];
        if(i + 1 != tamanho)
            cout << " - "; 
    }
    cout << endl;
}


//Compara elementos adjacentes, Troca se estiverem na ordem errada, Repete até que não haja mais trocas
void bubbleSort(int vetor[], int tamanho)
{
    bool trocou;
    for(int j = 0; j < tamanho - 1; j++)
    {
        trocou = false;
        for(int i = 0; i < tamanho -1 - j; i++)
        {
            if(vetor[i] > vetor[i+1])
            {
                int auxiliar = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = auxiliar;
                trocou =
                 true;
            }
        }
        if(trocou)
            break;
    }
}

/*
    1. Divide o array em duas partes: ordenada (inicialmente vazia) e
    não ordenada.
    
    2. Encontra o menor elemento na parte não ordenada.
    
    3. Troca esse elemento com o primeiro elemento da parte não
    ordenada.
    
    4. Expande a parte ordenada para incluir esse elemento.
    
    5. Repete até que toda a lista esteja ordenada.
*/
void selectionSort(int vetor[], int tamanho)
{
    for(int i = 0; i < tamanho - 1; i++)
    {
        int menor = i;
        for (int j = i + 1; j < tamanho; j++)
        {
            if(vetor[j] < vetor[menor])
                menor = j;
        }

        if(menor != i)
        {
            int aux = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = aux; 
        }
    }
}


/*
    1. Divide o array em duas partes: ordenada (inicialmente apenas o
    primeiro elemento) e não ordenada.
    
    2. PeĀa o primeiro elemento da parte não ordenada.
    
    3. Insere este elemento na posição correta dentro da parte
    ordenada.
    
    4. Expande a parte ordenada para incluir esse elemento.
    
    5. Repete até que toda a lista esteja ordenada.
*/
void insertionSort(int vetor[], int tamanho)
{
    int cont, atual;
    for(int i = 1; i < tamanho; i++)
    {
        atual = vetor[i];
        cont = i - 1;
        while (cont >= 0 && vetor[cont] > atual)
        {
            vetor[cont + 1] = vetor[cont];
            cont--;
        }
        vetor[cont + 1] = atual;
    }
}

void countingSort(int vetor[], int tamanho)
{
    int maior = vetor[0];

    for (int i = 1; i < tamanho; i++)
        if(vetor[i] >= maior) maior = vetor[i];
    
    int contagem[maior + 1];

    for (int i = 0; i <= maior; i++)
        contagem[i] = 0;
    
    for (int i = 0; i < tamanho; i++)
        contagem[vetor[i]]++;
    
    for(int i = 1; i  <= maior; i++)
        contagem[i] = contagem[i] + contagem[i-1];

    int vetorSaida[tamanho];

    for (int i = tamanho -1; i >= 0; i--)
    {
        vetorSaida[contagem[vetor[i]]-1] = vetor[i];
        contagem[vetor[i]]--;
    }
    
    for (int i = 0; i < tamanho; i++)
        vetor[i] = vetorSaida[i];
    
}

int main()
{
    int vetor[] = {5,2,8,1,9,7};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    mostrarVetor(vetor, tamanho);
    selectionSort(vetor, tamanho);
    mostrarVetor(vetor, tamanho);

    return 0;
}
