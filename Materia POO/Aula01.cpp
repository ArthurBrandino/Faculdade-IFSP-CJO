int main(int argc, char* argv[]){
    cout << "Exemplo de Argumentos da Função Principal \n\n";
    cout << "Numero de argumentos: " << argv << "\n\n";

    for (int i = 0; i < argc; i++)
    {
        cout << "Argumento " << i << ": " << argv[i] << "\n";
    }
    
    return 0;
}