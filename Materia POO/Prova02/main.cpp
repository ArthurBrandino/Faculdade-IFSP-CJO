#include <iostream>
using namespace std;

class candidatos{

    string nome[5];
    string partido[5];
    int codigo[5];
    int votos[5];

    public:
        void cadastro(){
            candidatos dados[5];

            nome[0] = "Pokelino";
            partido[0] = "Gordinho Feliz";
            codigo[0] = 171;
            votos[0] = 0;

            nome[1] = "Fernando Buda";
            partido[1] = "Budista Flutuante";
            codigo[1] = 100;
            votos[1] = 0;

            nome[2] = "Alisson Mineiro";
            partido[2] = "Comedor de Queijo";
            codigo[2] = 201;
            votos[2] = 0;

            nome[3] = "Guto Manzano";
            partido[3] = "1% Programadores";
            codigo[3] = 101;
            votos[3] = 0;

            nome[4] = "Helton Peruca";
            partido[4] = "Peruqueiros $$$";
            codigo[4] = 666;
            votos[4] = 0;
        }

        void adicionarvoto(int codigo)
        {
            switch (codigo){
                case 171 : votos[0] += 1; cout << "* Seu voto foi computado, obrigado!"; break;
                case 100 : votos[1] += 1; cout << "* Seu voto foi computado, obrigado!"; break;
                case 201 : votos[2] += 1; cout << "* Seu voto foi computado, obrigado!"; break;
                case 101 : votos[3] += 1; cout << "* Seu voto foi computado, obrigado!"; break;
                case 666 : votos[4] += 1; cout << "* Seu voto foi computado, obrigado!"; break;
                default: cout << "Codigo Invalido!" << endl << endl;
            }
        }

        string getnome(int i){
            return nome[i];
        }

        string getpartido(int i){
            return partido[i];
        }
        
        int getvotos(int i){
            return votos[i];
        }

        int getcodigo(int i){
            return codigo[i];
        }
};

void exibirtexto()
{
    cout << ">> Cabine de Votacao - IFSP" << endl << endl;
    cout << "[171]              Pokelino (Gordinho Feliz)" << endl;
    cout << "[100]      Fernando Buda (Budista Flutuante)" << endl;
    cout << "[201]    Alisson Mineiro (Comedor de Queijo)" << endl;
    cout << "[101]        Guto Manzano (1% Programadores)" << endl;
    cout << "[666]        Helton Peruca (Peruqueiros $$$)" << endl << endl;
    cout << "[ -1]    Encerrar Votação" << endl << endl;
}

int main(){
    int codigo;
    candidatos dados;
    dados.cadastro();

    do{
        exibirtexto();

        cout << "Informe o número do seu Candidato: ";
        cin >> codigo;
        cout << endl;
        if(codigo == -1) break;
    
        dados.adicionarvoto(codigo); 

        cout << " Pressione <ENTER> para continuar... ";
        cin.ignore();
        cin.get();

    }while(true);


    cout << "* Votação Encerrada!" << endl << endl;

    cout << "Resultado Final - Eleições IFSP" << endl << endl;

    for (int i = 0; i < 5; i++)
        cout << "- " << dados.getnome(i) << ", do Partido " << dados.getpartido(i) << ": " << dados.getvotos(i) << " votos" << endl;

}