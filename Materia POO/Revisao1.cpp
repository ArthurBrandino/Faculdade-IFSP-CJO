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

void Trocador (int &A, int &B)
{
    int trocador;
    trocador = A;
    A = B;
    B = trocador;
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
    }
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

void Ex23(){
    cout << "Programa: Decompositor de Numeros" << endl << endl;
   
    int N, C, D, U, X;
    do{
        cout << "Entre com um numero de 0 a 999: "; cin >> N;
        if (N >= 1000 || N  < 0) cout << "Numero Invalido! " << endl;
    }while(N >= 1000 || N  < 0);

    C = N / 100;
    X = N % 100;
    D = X / 10;
    X = X % 10;
    U = X;

    cout << "O Numero " << N << " Decomposto e: ";
    if(C != 0)  (C == 1) ? cout << C << " centena" : cout << C << " centenas";
    if(D != 0 && U != 0 && C != 0) cout << ", ";
    else if((D != 0 && C != 0)) cout << " e ";

    if(D != 0)  (D == 1) ? cout << D << " dezena" : cout << D << " dezenas";
    if(U != 0 && D != 0) cout << " e ";

    if(U != 0)  (U == 1) ? cout << U << " unidade" : cout << U << " unidades";

    cout << '.' << endl;
    
}

void Ex24(){
    cout << "Programa: Verificacao de Paridade" << endl << endl;
    int N;
    cout << "Entre com um Numero: "; cin >> N;

    (0 == N % 2)? cout << "O Numero " << N << " e Par!" : cout << "O Numero " << N << " e Impar!";
    cout << endl;
}
void pedirRespostaEx25(string pergunta, int &contador)
{
    char resposta;
    while(true){
        cout << pergunta; cin >> resposta;
        resposta = toupper(resposta);
        if(resposta != 'S' && resposta != 'N') cout << "Resposta Invalida!" << endl;
        else break;
    }
    if(resposta == 'S') contador++;
}

void Ex25(){
    cout << "Programa: Investigador de Crime" << endl << endl;
    char resposta;
    int contador = 0;

    string pergunta1 = "1. Telefonou para a vitima?   (S/N): "; 
    string pergunta2 = "2. Esteve no local do crime?  (S/N): "; 
    string pergunta3 = "3. Mora perto da vitima?      (S/N): "; 
    string pergunta4 = "4. Devia para a vitima?       (S/N): "; 
    string pergunta5 = "5. Já trabalhou com a vitima? (S/N): "; 

    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Por favor, colha o depoimento do suspeito e responda as perguntas a seguir." << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    pedirRespostaEx25(pergunta1, contador);
    pedirRespostaEx25(pergunta2, contador);
    pedirRespostaEx25(pergunta3, contador);
    pedirRespostaEx25(pergunta4, contador);
    pedirRespostaEx25(pergunta5, contador);

    switch(contador){
        case 2 : cout << "O individuo e considerado Suspeito"; break;
        case 3 : 
        case 4 : cout << "O individuo e considerado Cumplice"; break;
        case 5 : cout << "O individuo e considerado Assasino"; break;
        default : cout << "O individuo e considerado Inocente"; break;
    }
    cout << endl;
}

void Ex26(){
    cout << "Programa: Localizador de Menor Preço" << endl << endl;
    struct Produto{
        string nome;
        float valor;
    };
    Produto Produtos[3];
    int menor = 0;
    
   for (int i = 0; i < 3; i++)
   {
        cout << "Entre com o Nome do Produto <" << i+1 << ">: "; cin >> Produtos[i].nome;
        while(true){
            cout << "Entre com o Valor do Produto <" << i+1 << ">: ";
            if(cin >> Produtos[i].valor && Produtos[i].valor > 0) break;
            else {
                cout <<"Valor Invalido!" << endl;
                cin.clear(); 
                cin.ignore(1000, '\n');
            }
        }
   }

    for (int i = 1; i < 3; i++)
    {
        if (Produtos[i].valor < Produtos[menor].valor) menor = i ;
    }

    cout << "O Produto mais barato e: "  << Produtos[menor].nome << " R$ " << fixed << setprecision(2) << Produtos[menor].valor << endl; 
}

void Ex27(){
    cout << "Programa: Reajuste Salarial" << endl << endl;
    double salarioAntes, salarioReajuste, reajuste, percentual;

    cout << "Entre com o seu Salario para o calculo de Reajuste: "; cin >> salarioAntes;

    if(salarioAntes <= 2000) percentual = 20;
    else if (salarioAntes > 2000 && salarioAntes <= 4000) percentual = 15;
    else if (salarioAntes > 4000 && salarioAntes <= 8000) percentual = 10;
    else percentual = 5;

    reajuste = salarioAntes * (percentual/100);
    salarioReajuste = salarioAntes + reajuste;

    cout << "Salario Antes do Reajuste: R$" << fixed << setprecision(2) << salarioAntes << endl;
    cout << "Percentual de Aumento Aplicado: " << setprecision(0) << percentual << "%" << endl;
    cout << "Valor do Aumento: R$ " <<  setprecision(2) << reajuste << endl;
    cout << "Salario com Reajuste: R$ " << salarioReajuste << endl;
}

void Ex28(){
    cout << "Programa: Seletor de Dia da Semana" << endl << endl;
    int opcao;
    
    cout << "***************************************************************************************************************" << endl;
    cout << "1- Domingo | 2- Segunda-feira | 3- Terca-feira | 4- Quarta-feira | 5- Quinta-feira | 6- Sexta-feira | 7- Sabado" << endl;
    cout << "***************************************************************************************************************" << endl;
    while (true) {
        cout << "Entre com o numero correspondente ao dia da semana (1-7): ";
        if (cin >> opcao) {
            if (opcao >= 1 && opcao <= 7) {
                switch (opcao) {
                    case 1: cout << "Voce Selecionou: Domingo" << endl; break;
                    case 2: cout << "Voce Selecionou: Segunda-feira" << endl; break;
                    case 3: cout << "Voce Selecionou: Terca-feira" << endl; break;
                    case 4: cout << "Voce Selecionou: Quarta-feira" << endl; break;
                    case 5: cout << "Voce Selecionou: Quinta-feira" << endl; break;
                    case 6: cout << "Voce Selecionou: Sexta-feira" << endl; break;
                    case 7: cout << "Voce Selecionou: Sabado" << endl; break;
                }
                break; 
            } else {
                cout << "Erro: Digite um valor entre 1 e 7!" << endl;
            }
        } else {
            cout << "Erro: Entrada invalida! Digite apenas numeros." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void Ex29(){
    cout << "Programa: Classificador de Triangulo" << endl << endl;
    int A, B, C;

    while(true)
    {
        cout << "Entre com o Valor do Lado <A> do Triangulo: "; cin >> A;
        cout << "Entre com o Valor do Lado <B> do Triangulo: "; cin >> B;
        cout << "Entre com o Valor do Lado <C> do Triangulo: "; cin >> C;
        
        if(A + B > C && A + C > B && B + C > A) break;

        cout << "Os Valores Nao Formam um Triangulo!" << endl;
    }
  
    if(A == B && B == C) 
        cout << "O Triangulo eh Equilatero!";
    else if(A != B && A != C && B != C)
        cout << "O Triangulo eh Escaleno!";
    else
        cout << "O Triangulo eh Isosceles!";

    cout << endl;
}

void Ex30(){
    cout << "Programa: Calculo de Bhaskara" << endl << endl;
    double A, B, C, delta, result;

    cout << "*  Ax^2 + Bx + C  *" << endl ;
    cout << "Entre com o Valor de <A>: "; cin >> A;
    if(A == 0)
    {
        cout << "A Equacao nao e do Segundo Grau! \nFinalizando o programa..." << endl;
        return;
    }

    cout << "Entre com o Valor de <B>: "; cin >> B;
    cout << "Entre com o Valor de <C>: "; cin >> C;

    delta = pow(B,2) - 4*A*C;
    
    if(delta < 0) cout << "A Equacao Nao Possui Raizes Reais! \nFinalizando o Programa..." << endl;
    else{
        if(delta > 0)
        {
            result = (-B + pow(delta, 0.5))/( 2* A);
            double result2 = (-B - pow(delta, 0.5))/( 2* A);
            cout << "A Equacao Possui 2 Raizes Reais!" << endl;
            cout << "x1 = " << result << " x2 = " << result2 << endl;
            cout << "Finalizando o Programa..." << endl;
        }
        else{
            result = -B /(2 * A);
            cout << "A Equacao Possui 1 Raiz Real!" << endl;
            cout << "x = " << result << endl;
            cout << "Finalizando o Programa..." << endl;
        }
    }
}

void Ex31(){
    cout << "Programa: Verificador de Ano Bissexto" << endl << endl;
    int ano;
    cout << "Entre com o Ano Desejado: "; cin >> ano;

    (!(ano % 4) && (ano % 100)) || !(ano % 400 )? cout << "O Ano eh Bissesxto" : cout << "O Ano Nao eh Bissesxto";
    cout << endl;
}

void Ex32(){
    cout << "Programa: Validador de Data Completa" << endl << endl;
    char barra;
    int dia, mes, ano;

    cout << "Entre com uma data <dd/mm/aaaa>: "; cin >> dia >> barra >> mes >> barra >> ano;
   
    bool dataValida = ((dia > 0 && dia <= 31) &&
                        (mes > 0 && mes <= 12) &&
                        ( ano >= 1900 && ano <= 2100));

    dataValida  ?   cout << "A data informada eh Valida!" : 
                    cout << "A data informada nao eh Valida!";

    cout << endl;
}

void Ex33(){
    cout << "Programa: Simulador de Saque de Caixa Eletronico" << endl << endl;
    int notas[] = {1, 5, 10, 50, 100};
    int valor, minimo = 10, maximo = 1000;

    cout << "Valor Minimo de Saque R$ " << fixed << setprecision(2) << minimo << endl;
    cout << "Valor Maximo de Saque R$ " << maximo << endl << endl;

    while(true){
        cout << "Entre com o Valor a ser Sacado: "; cin >> valor;
        if(!(valor < minimo || valor > maximo)) break;
        cout << "Valor Fora do Limite!" << endl;
    }

    cout << "Valor do Saque: " << valor << endl;
    cout << "Notas Oferecidas: ";

    for(int i = 4; i >= 0; i--)
    {
        int quantidade = valor / notas[i];
        valor %= notas[i];
        if(quantidade > 0) cout << quantidade << " nota(s) de R$ " << notas[i] << " - ";
    }
    cout << endl;
}

void Ex34(){
    cout << "Programa: Identificador de Tipo Numerico" << endl << endl;
    double n;
    cout << "Entre com um Numero: "; cin >> n;

    (ceil(n) == n)? cout << "O Numero eh Inteiro" : cout << "O Numero eh Decimal";
    cout << endl;
}

void Ex35(){
    cout << "Programa: Calculadora com Diagnostico de Numero" << endl << endl;
    double A, B, result;
    int opcao;
    bool sair = false;
    cout << "Entre com o Valor de <A>: "; cin >> A;
    cout << "Entre com o Valor de <B>: "; cin >> B;

    do{
        cout << "Escolha Qual Operacao Sera Realizada:" << endl;
        cout << "(1) Adicao +" << endl;
        cout << "(2) Subtracao -" << endl;
        cout << "(3) Mutiplicacao X" << endl;
        cout << "(4) Divisao /" << endl;
        cout << "Opcao: "; cin >> opcao;

        switch(opcao){
            case 1 : result = A + B; sair = true; break;
            case 2 : result = A - B; sair = true; break;
            case 3 : result = A * B; sair = true; break;
            case 4 : if(B != 0){
                            result = A / B; sair = true; 
                    } 
                    else 
                        cout << "Erro: Divisao por zero nao permitida!" << endl;
                    break;
            default : cout << "Opcao Invalida!" << endl;
        };
    }while(!sair);

    cout << "O resultado da Opercao eh: " << result << endl;
    !((int)result % 2)? cout << "a. O numero eh Par!" << endl : cout << "a. O numero eh Impar!" << endl;
    (result >= 0)? cout << "b. O numero eh Positivo!" << endl : cout << "b. O numero eh Negativo!" << endl;
    (result == ceil(result))? cout << "c. O numero eh Inteiro!" << endl : cout << "c. O numero eh Decimal!" << endl;

}

int main(){

    Ex34();
    
    cout << "Tecle <Enter> para Encerrar...";
    cin.ignore();
    cin.get();

    return 0;
}