#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void Ex1(){
    cout << "Programa de Apresentacao" << endl << endl;
    cout << "Alo Mundo!" << endl;
}

void Ex2(){
    cout << "Programa de Apresentacao de Valor" << endl << endl;
    int N;
    cout << "Informe um numero: "; cin >> N;
    cout << "O numero informado foi: " << N << endl;
}

void Ex3(){
    cout << "Programa de Calculo de Media Escolar" << endl << endl;
    double N1, N2, N3, N4, M;
    cout << "Entre com N1: "; cin >> N1; 
    cout << "Entre com N2: "; cin >> N2; 
    cout << "Entre com N3: "; cin >> N3; 
    cout << "Entre com N4: "; cin >> N4; 

    M = (N1 + N2 + N3 + N4)/4;

    cout << "Media: " << fixed << setprecision(2) << M << endl;
}

void Ex4(){
    cout << " Programa Calculo Salarial Simples" << endl << endl;
    double valor, salario;
    string mes;
    int horas;

    cout << "Informe qual mes: "; cin >> mes;
    cout << "Informe o valor recebido por hora: "; cin >> valor;
    cout << "Informe o nero de horas trabalhadas: "; cin >> horas;

    salario = valor * horas;

    cout << "No mes de " << mes << "o salario recebido foi R$" << fixed << setprecision(2) << salario << endl;
}

void Ex5(){
    cout << "Programa Conversao de Temperatura" << endl << endl;
    double C, F, K;
    cout << "Informe a temperatura em graus Celsius para conversao: "; cin >> C;
    F = (9 * C + 160)/5;
    K = C + 273.15;

    cout << fixed << setprecision(2) << C << " graus  Celsius = " << K << " Kelvin = " << F << " graus Fahrenheit" << endl;
}

void Ex6(){
    double tempo, velocidade, combustivel, distancia, gasto;
    cout << "Programa de Calculo de Gasto de Combustivel" << endl << endl;

    cout << "Informe o Tempo gasto na viagem:"; cin >> tempo;
    cout << "Informe a Velocidade Media: "; cin >> velocidade;
    cout << "Informe a Quantidade de Quilometros que o Automovel faz com 1 litro de Combustivel: "; cin >> combustivel;

    distancia = tempo * velocidade;
    gasto = distancia/combustivel;

    cout << "Velocidade Media: " << fixed << setprecision(2) << velocidade << endl;
    cout << "Tempo Gasto: "  << tempo << endl;
    cout << "Distancia Total: "  << distancia << endl;
    cout << "Total de Combustivel Gasto: "  << gasto << " Litros" << endl;

}

void Ex7(){
    cout << "Programa de Conversao de Temperaturas" << endl << endl;
    double F, K;
    cout << "Informe a temperatura em graus Fahrenheit para conversao: "; cin >> F;
    K = (F - 31) * (5/9) + 273.15;

    cout << fixed << setprecision(2) << K << " Kelvin " << endl;
}

void Ex8(){
    cout << "Programa de Calculo de Volume de Lata" << endl << endl;
    double V, A, R;
    const double pi = 3.141516;

    cout << "Entre com a Altura da Lata: "; cin >> A;
    cout << "Entre com o Raio da Lata: "; cin >> R;

    V = pi * R * R * A;

    cout << "O Volume da Lata e " << fixed << setprecision(2) << V << endl;
}

void Ex9(){
    cout << "Programa de Calculo de Peso de uma Esfera" << endl << endl;
    double P, D, R;
    const double pi = 3.141516;

    cout << "Forneca o valor da Densidade da Esfera: "; cin >> D;
    cout << "Forneca o valor do Raio da Esfera: "; cin >> R;

    P = D * 4 * pi * R * R *(R/3);

    cout << "O Peso da Esfera e: " << fixed << setprecision(2) << P << endl;
}

void Ex10(){
    cout << "Programa de Troca de Valores de Variaveis" << endl << endl;
    int A, B, T;

    cout << "Entre com o Valor da Variavel <A>: "; cin >> A;
    cout << "Entre com o Valor da Variavel <B>: "; cin >> B;

    T = A;
    A = B;
    B = T;

    cout << "Apos a troca o Valor da Variavel <A> e: " << A << " e o da Variavel <B> e: " << B << endl;
}

void Ex11(){
    cout << "Programa de Calculos" << endl << endl;
    int A, B;
    float C;

    cout << "Entre com um Numero Inteiro <A>: "; cin >> A;
    cout << "Entre com um Numero Inteiro <B>: "; cin >> B;
    cout << "Entre com um Numero Real <C>: "; cin >> C;

    cout << "O produto do dobro do <A> com metade do <B>: " << (A*2)*(B/2) << endl;
    cout << "A soma do triplo do <A> o com o <C>: " << A * 3 + C << endl;
    cout << "O <C> elevado ao cubo: " << pow(C, 3) << endl;
}

void Ex12(){
    cout << "Programa de Calculo de IMC" << endl << endl;
    char Sexo;
    float Altura, Peso, PesoIdeal, IMC;
    do{
        cout << "Entre com o seu Sexo <M> para Masculino e <F> para Feminino: ";    cin >> Sexo;
        Sexo = toupper(Sexo);
    }while(Sexo != 'M' && Sexo != 'F');

    cout << "Entre com a sua Altura: "; cin >> Altura;
    cout << "Entre com seu Peso: "; cin >> Peso;
    cout << endl << fixed << setprecision(2);
    cout << "Sexo: " << Sexo << " Altura: " << Altura << " Peso: " << Peso << endl;

    if(Sexo == 'M') 
        PesoIdeal = (72.7 * Altura) - 58;
    else 
        PesoIdeal = (62.1 * Altura) - 44.7;

    cout << "Seu peso ideal e: " << fixed << setprecision(2) << PesoIdeal << endl;

    IMC = Peso / (Altura * Altura);
    if(IMC > 18.5)
        cout << "Voce esta acima do Peso!";
    else if(IMC >= 18.5 && IMC <= 24.9)
        cout << "Voce esta dentro do Peso!";
    else
        cout << "Voce esta abaixo do Peso! ";
    cout << endl;
    
}

void Ex13(){
    cout << "Programa de Calculo de Quantidade de Latas de Tintas" << endl << endl;
    struct tinta{
        int Preco = 80;
        int Qtd = 18;
    };

    tinta lata;
    double Area, N, Total;

    cout << "Qual o Tamanho da Area a Ser Pintada? "; cin >> Area;
    cout << endl;
  
    N = ceil((Area / 3)/ lata.Qtd); // Calcula 1 litro por 3 metros e Qts latas de tintas serao necessarias
    Total = lata.Preco * N;    // Calcula o Tota em R$

    cout << "Deve ser compradas " << N << fixed << setprecision(2) << " Latas de Tinta. O Valor Total da compra e RS " << Total << endl;
}

void Ex14(){
    cout << "Programa Calculo de Multa de Peso Limite" << endl << endl;
    double Peso, Valor, Excedente;
    const int PesoLimite = 50, Multa = 4;

    cout << "Entre com o Peso: "; cin >> Peso;
    if(Peso > PesoLimite)
    {
        Excedente = Peso - PesoLimite;
        cout << "Houve um excedente de " << Excedente << "Kg" << endl;
        Valor = ceil(Excedente) * Multa;
        cout << "O valor a ser Pago e: RS " << fixed << setprecision(2) << Valor;
    }
    else
        cout << "O Peso esta Dentro do Limite!";
    cout << endl;

}

void Ex15(){
    double ValorHora, Horas, SalarioBruto, SalarioLiquido, ValorImpostoRenda, ValorINSS, ValorSindicato;

    cout << "Programa Calculo Salarial" << endl << endl;

    cout << "Entre com o Valor que Voce Ganha por Hora: "; cin >> ValorHora;
    cout << "Entre como Total de Horas Trabalhadas essse Mes: "; cin>> Horas;
    cout << endl;

    SalarioBruto = ValorHora * Horas;
    ValorImpostoRenda = SalarioBruto * 11/100;
    ValorINSS = SalarioBruto * 8/100;
    ValorSindicato = SalarioBruto * 5/100;
    SalarioLiquido = SalarioBruto - ValorImpostoRenda - ValorINSS - ValorSindicato;

    cout << "=> Calculo Salarial" << fixed << setprecision(2) << endl;
    cout << "+ Salario Bruto..: R$ " << SalarioBruto << endl;
    cout << "- IR (11%).......: R$ " << ValorImpostoRenda << endl;
    cout << "- INSS (8%)......: R$ " << ValorINSS << endl;
    cout << "- Sindicato (5%).: R$ " << ValorSindicato << endl;
    cout << "= Salario Liquido: R$ " << SalarioLiquido << endl;
}

void Ex16(){
    double MB, Mb, velocidade, tempo;

    cout << "Programa Calculo de Tempo de Download" << endl << endl;

    cout << "Entre com o Tamanho do Arquivo em <MB>: "; cin >> MB;
    cout << "Entre com a Velocidade da Internet em <Mbps>: "; cin >> velocidade;

    Mb = MB * 8;
    tempo = (Mb / velocidade)/60;

    cout << "O tempo de Download do Arquivo e " << fixed << setprecision(2) << tempo << " Minutos" << endl;
}

void Ex17(){
    cout << "Programa Qual Valor e Maior" << endl << endl;
    int A, B;
    cout << "Entre com o Valor de <A>: "; cin >> A;
    cout << "Entre com o Valor de <B>: "; cin >> B;

    (A>B)? cout << "<A> e maior: " << A : cout << "<B> e maior: " << B;
    cout << endl;

}

void Ex18(){
    cout << "Programa: Valor e Positivo ou Negativo?" << endl << endl;
    int N;
    cout << "Entre com o Valor de <N>: "; cin >> N;
    (N>0)? cout << "Valor Positivo!" : cout << "Valor Negativo!";
    cout << endl;
}

void Ex19(){
    cout << "Programa: Letra e Vogal ou Consoante? " << endl << endl;
    char N;
    cout << "Entre com uma Letra: "; cin >> N;
    N = toupper(N); 
    if (N == 'A' || N == 'E' || N == 'I' || N == 'O' || N == 'U')
        cout << N << " eh uma Vogal";
    else if (N >= 'A' && N <= 'Z')
        cout << N << " eh uma Consoante";
    else 
        cout << "Caractere nao eh uma letra!";
    
        cout << endl;
}

int Trocador (int &A, int &B)
{
    int trocador;
    trocador = A;
    A = B;
    B = trocador;
    return A, B;
}

void Ex20(){
    cout << "Programa: Ordem Decrescente" << endl << endl;
    int A, B, C;
    cout << "Entre com o Valor de <A>: "; cin >> A;
    cout << "Entre com o Valor de <B>: "; cin >> B;
    cout << "Entre com o Valor de <C>: "; cin >> C;
    
    if(A < B)   Trocador(A, B);
    if(A < C)   Trocador(A, C);
    if(B < C)   Trocador(B, C);

    cout << A << " >> " << B << " >> " << C << endl;
}

void Ex21(){
    cout << "Programa Saudacao por Turno" << endl << endl;
    char N;
    cout << "Entre com o Turno em que voce Estuda. <M> Matutino - <V> Vespertino - <N> Noturno: "; cin >> N;
    N = toupper(N);

    switch (N){
        case 'M' : cout << "Bom dia!" << endl; break;
        case 'V' : cout << "Boa Tarde!" << endl; break;
        case 'N' : cout << "Boa Noite!" << endl; break;
        default : cout << "Valor Invalido!" << endl;
    };
}

void Ex22(){
    cout << "Programa Sistema de Notas Escolares" << endl << endl;
    double N1, N2, M;
    char Conceito;
    string Situacao;

    do{
        cout << "Entre com o Valor da <Nota 1>: "; cin >> N1;
    }while(N1 < 0 || N1>10);
    do{
        cout << "Entre com o Valor da <Nota 2>: "; cin >> N2;
    }while(N2 < 0 && N2 > 10);

    M = (N1 + N2)/2;

    if(M >= 9 && M <= 10) Conceito = 'A';
    else if (M >= 7.5 && M < 9) Conceito = 'B';
    else if (M >= 6 && M < 7.5) Conceito = 'C';
    else if (M >= 4 && M < 6) Conceito = 'D';
    else  Conceito = 'E';

    (Conceito == 'A' || Conceito == 'B' || Conceito == 'C') ?  Situacao = "Aprovado!" : Situacao = "Repovado!";


    cout << left << setw(6) << "N1" << setw(6) << "N2" << setw(25) << "Media de Aproveitamento" << setw(11) << "Conceito" << setw(14) << "Situacao" << endl;
    cout << left << setw(6) << fixed << setprecision(1) << N1 << setw(6) << N2;
    cout << right << setw(15) << M;
    cout << left << setw(10) << "";
    cout << right << setw(4) << Conceito; 
    cout << left << setw(7) << "" << setw(14) << Situacao << endl;

}

int main(){

    Ex22();
    
    cout << "Tecle <Enter> para Encerrar...";
    cin.ignore();
    cin.get();

    return 0;
}